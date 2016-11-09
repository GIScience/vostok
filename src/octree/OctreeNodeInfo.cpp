/*
 * OctreeNodeInfo.cpp
 *
 *  Created on: 26.12.2013
 *      Author: sebastian
 */

#include "OctreeNodeInfo.h"

#include <cfloat>


OctreeNodeInfo::OctreeNodeInfo(Vec3d pos, double size, OctreeNode* ref) {
	mPos = pos;
	mSize = size;
	mRef = ref;
}


OctreeNodeInfo::~OctreeNodeInfo() {
	// TODO Auto-generated destructor stub
}



int OctreeNodeInfo::getChildIndex(Vec3d& v) {


	//############ BEGIN Check if v is outside of nodeInfo extent #############
	Vec3d relPos = v - mPos;

	for (unsigned int ii = 0; ii < 3; ++ii) {
		if (relPos.mCoords[ii] < 0 || relPos.mCoords[ii] > mSize)
			return -1;
	}
	//############ END Check if v is outside of nodeInfo extent #############

	//################ BEGIN Figure out child index #################

	double halfSize = mSize / 2;

	// Assume front/left/bottom:
	unsigned int childIndex = 0;

	// Back half:
	if (relPos.z() >= halfSize) {
		childIndex += 1;
	}

	// Right half:
	if (relPos.x() >= halfSize) {
		childIndex += 2;
	}

	// Top half:
	if (relPos.y() >= halfSize) {
		childIndex += 4;
	}

	//################ END Figure out child index #################

	return childIndex;
}




Vec3d OctreeNodeInfo::getChildPosByIndex(unsigned int childIndex) const {

	double halfSize = mSize / 2;

	Vec3d result = mPos;

	if (childIndex == 2 || childIndex == 3 || childIndex == 6 || childIndex == 7) {
		result.mCoords[0] += halfSize;
	}

	if (childIndex > 3) {
		result.mCoords[1] += halfSize;
	}

	if ((childIndex + 1) % 2 == 0) {
		result.mCoords[2] += halfSize;
	}

	return result;
}



Vec3d OctreeNodeInfo::getFarIntersection(Vec3d& rayStart, Vec3d& rayDir) {

	Vec3d intersect;

	double min_dist = DBL_MAX;

	for (unsigned int dimPlane = 0; dimPlane < 3; ++dimPlane) {

		// We only need to check one of the parallel walls of each box, depending on the ray direction.
		// Offset defines which wall is checked:
		double offset = (rayDir.mCoords[dimPlane] > 0) ? mSize : 0;

		// TODO 3: What happens if rayDir.mCoords[dimPlane] == 0 (division by zero!) ?
		double t = (mPos.mCoords[dimPlane] + offset - rayStart.mCoords[dimPlane]) / rayDir.mCoords[dimPlane];

		if (t < min_dist) {
			min_dist = t;
		}
	}

	return rayStart + (rayDir * min_dist);
}



void OctreeNodeInfo::insertPointRecursive(Vec3d& v, unsigned int depth, unsigned int maxDepth) {

	if (depth == maxDepth) {

		mRef->mNumPoints++;
		return;
	}

	int childIndex = getChildIndex(v);

	if (childIndex == -1) {
		//	mNumPointsDiscarded++;
		return;
	}

	if (mRef->mChildren[childIndex] == 0) {
		mRef->mChildren[childIndex] = new OctreeNode();
	}

	OctreeNode* newNode = mRef->mChildren[childIndex];

	Vec3d newPos = getChildPosByIndex(childIndex);

	OctreeNodeInfo childInfo(newPos, mSize / 2, newNode);

	childInfo.insertPointRecursive(v, depth + 1, maxDepth);
}

