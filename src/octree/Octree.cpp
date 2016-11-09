/*
 * Octree.cpp
 *
 *  Created on: 26.12.2013
 *      Author: sebastian
 */
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <stack>
#include "Octree.h"

Octree::Octree(std::vector<double> min, std::vector<double> max, double voxelSize) {

	mMin = Vec3d(min[0], min[1], min[2]);
	m_voxelSize = voxelSize;

	//################## BEGIN Determine required minimum size ####################
	// First, find out the minimum required size of the octree volume to cover the entire point cloud:

	Vec3d diff = Vec3d(max[0], max[1], max[2]) - mMin;

	std::cout << "Point cloud size:            ";
	std::cout << diff.mCoords[0] << " x " << diff.mCoords[1] << " x " << diff.mCoords[2] << std::endl;

	double requiredMinSize = std::max(std::max(diff.mCoords[0], diff.mCoords[1]), diff.mCoords[2]);
	//################## END Determine required minimum size ####################

	//################## BEGIN Determine actual size ####################
	// Now, calculate the actual required size of the octree,
	// which must be a power-of-2 multiple of the user-defined voxel size:
	mSize = m_voxelSize;
	mDepth = 0;

	while (mSize < requiredMinSize) {
		mSize *= 2;
		++mDepth;
	}

	//################## END Determine actual size ####################

	std::cout << "Required octree volume size: " << mSize << std::endl;
	std::cout << "Required octree depth:       " << mDepth << std::endl << std::endl;
}

Octree::~Octree() {
	// TODO Auto-generated destructor stub
}
