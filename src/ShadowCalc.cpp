// TODO 2: Fix problem with self-shadowing on sloped surfaces

// Required by MSVC to know math constants like "M_PI":
#define _USE_MATH_DEFINES

#include "ShadowCalc.h"

#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <omp.h>
#include <stack>
#include <vector>
#include "OctreeRaycaster.h"


ShadowCalc::ShadowCalc(AbstractPointCloud& shadowCloud, double voxelSize) : m_octree(shadowCloud.getMin(), shadowCloud.getMax(), voxelSize) {

	//########## BEGIN Read input file for second time to build octree #################
	std::cout << "Building octree... " << std::flush;

	shadowCloud.resetCursor();

	while (!shadowCloud.endOfCloud()) {

		std::vector<double> p = shadowCloud.getNextPoint();

		//############### BEGIN Insert point into octree ###############
		// TODO 4: Make this a method of something (new octree builder class?)?
		bool createColumn = true;

		OctreeNodeInfo rootInfo(m_octree.mMin, m_octree.mSize, &m_octree.mRoot);

		if (createColumn) {
			for (double z = p[2]; z > m_octree.mMin.mCoords[2]; z -= m_octree.m_voxelSize) {

				Vec3d v(p[0], p[1], z);

				rootInfo.insertPointRecursive(v, 0, m_octree.mDepth);
			}
		} else {
			Vec3d v(p[0], p[1], p[2]);
			rootInfo.insertPointRecursive(v, 0, m_octree.mDepth);
		}
		//############### END Insert point into octree ###############
	}

	std::cout << "finished." << std::endl << std::endl << std::flush;

}

ShadowCalc::~ShadowCalc() {
	// TODO Auto-generated destructor stub
}

bool ShadowCalc::computeShadow(const posdata& solposData, const std::vector<double>& point) {

	double azimuth_deg = solposData.azim;
	double elevation_deg = solposData.elevref;
    
	if (elevation_deg < 0 ) {
		return true;
	}


	//########## BEGIN Adapt SOLPOS elevation & azimuth to octree coordinate system & convert to radians ##########

	// Apply correction to make coordinate system work with SOLPOS:
	// N=0, E=90, S=180, W=270
	azimuth_deg = 90 - azimuth_deg;
	elevation_deg = 90 - elevation_deg;

	// Make sure that azimuth_deg value is in 0...360 range:
	while (azimuth_deg < 0) {
		azimuth_deg += 360;
	}

	azimuth_deg = azimuth_deg - 360 * ((int) azimuth_deg % 360);

	// Convert azimuth and elevation from degrees to radians:
	double azimuth_rad = azimuth_deg * (M_PI / 180.0);

	// Apply correction for UTM convergence:
	//azimuth_rad += utm_convergence_rad;

	double elevation_rad = elevation_deg * (M_PI / 180.0);

	//########## END Adapt elevation & azimuth to octree coordinate system & convert to radians ##########

	//################################ BEGIN Generate light direction vector ###############################

	// Compute x (ground plane) components of light direction vector:
	double rayDirX = cos(azimuth_rad);

	// Compute y (ground plane) components of light direction vector:
	double rayDirY = sin(azimuth_rad);

	// Compute z (elevation) component of light direction vector:
	double bla = tan(elevation_rad);

	double rayDirZ = 1;

	if (bla != 0) {
		rayDirZ = 1.0 / bla;
	} else {
		rayDirZ = 1;
		rayDirX = 0;
		rayDirY = 0;

		std::cout << "Parallele Strahlen!" << std::endl;
	}

	// Create light direction vector and make it short:
	Vec3d rayDir(rayDirX, rayDirY, rayDirZ);

	// TODO 3: Is this fixed length okay for all voxel sizes?
	rayDir = rayDir.normalize() * 0.001;

	// TODO 3: Das ist alles komisch hier. Kann mit neuem Raycasting wohl stark vereinfacht werden

	//############################### END Generate light direction vector #################################

	//########## BEGIN Define ray start offset depending on light direction ###########

	// ATTENTION:
	// In order to avoid self-shadowing artifacts,
	// we begin raycasting at some distance from the query point:

	// TODO 3: Make "shadow ignore distance" configurable?
	double halfSize = m_octree.m_voxelSize * 2;

	Vec3d rayStartOffset(halfSize, halfSize, halfSize);

	if (rayDir.x() > 0) {
		rayStartOffset.mCoords[0] += halfSize;
	} else {
		rayStartOffset.mCoords[0] -= halfSize;
	}

	if (rayDir.y() > 0) {
		rayStartOffset.mCoords[1] += halfSize;
	} else {
		rayStartOffset.mCoords[1] -= halfSize;
	}

	if (rayDir.z() > 0) {
		rayStartOffset.mCoords[2] += halfSize;
	} else {
		rayStartOffset.mCoords[2] -= halfSize;
	}

	rayStartOffset = rayStartOffset + rayDir;

	//########## END Define ray start offset depending on light direction ###########

	// Compute shadow:
	Vec3d v(point[0], point[1], point[2]);
	Vec3d origin = v + rayStartOffset;
	std::vector<OctreeNodeInfo> touchedVoxels = raycast(origin, rayDir);

	return (touchedVoxels.size() == 0);
}


std::vector<OctreeNodeInfo> ShadowCalc::raycast(Vec3d& rayStart, Vec3d& rayDir) {

	std::vector<OctreeNodeInfo> touchedVoxels;

	std::stack<OctreeNodeInfo> stack;

	OctreeNodeInfo info(m_octree.mMin, m_octree.mSize, &m_octree.mRoot);

	stack.push(info);

	while (stack.size() > 0) {

		OctreeNodeInfo node = stack.top();

		// If current node is a leaf/voxel...
		if (node.mRef->mNumPoints > 0) {

			// Add voxel to result vector:
			touchedVoxels.push_back(node);
			return touchedVoxels;
		}

		int childIndex = node.getChildIndex(rayStart);

		if (childIndex == -1) {
			/* "childIndex == -1" means that rayStart is now outside of the current node region
			 * (that means, in another branch of the octree). In order to find the node where rayStart
			 * now resides, we have to move up in the tree until we reach the (direct or indirect)
			 * parent/ancestor of the node where rayStart now resides.
			 * From there, we go down again towards the new rayStart node.
			 *
			 * Going up in the tree means pop()ing the current node from the stack:
			 */

			stack.pop();

		} else if (node.mRef->mChildren[childIndex] == 0) {
			/* "node.mRef->mChildren[childIndex] == 0" means that the node that contains rayStart has
			 * no child node at the rayStart position. This means that we cannot go deeper down the tree.
			 * So we skip the node's region and move forward to the next node. This involves:
			 *
			 * 1. Calculation of the point where the ray exits the current node (and enters the new one)
			 *
			 * 2. Setting rayStart to that new position (+ a very little distance further to make sure
			 *    that rayStart is really inside the new node)
			 *
			 * 3. Move up in the tree (i.e. pop the current node from the stack), since we need to find
			 *    the new node, which is in a parallel branch (read the comment for the case
			 *    "childIndex == -1" (above) for comparison)
			 */

			rayStart = node.getFarIntersection(rayStart, rayDir) + (rayDir * 0.001);

			stack.pop();

		} else {
			/* Finally, the last case: If the node has a child at the rayStart position,
			 * we have to go down the branch that is represented by that child. This means
			 * putting the child onto the stack:
			 */

			Vec3d childPos = node.getChildPosByIndex(childIndex);

			OctreeNodeInfo child(childPos, node.mSize / 2, node.mRef->mChildren[childIndex]);

			stack.push(child);
		}
	}

	return touchedVoxels;
}
