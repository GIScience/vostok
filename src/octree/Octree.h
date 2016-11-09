/*
 * Octree.h
 *
 *  Created on: 26.12.2013
 *      Author: sebastian
 */

#ifndef OCTREE_H_
#define OCTREE_H_

#include <vector>
#include "../Vec3d.h"
#include "OctreeNode.h"
#include "OctreeNodeInfo.h"

class Octree {
public:

	Octree(std::vector<double> min, std::vector<double> max, double voxelSize);

	virtual ~Octree();

	unsigned int mDepth;
	Vec3d mMin;
	double mSize;
	OctreeNode mRoot;

	double m_voxelSize;

protected:


};

#endif /* OCTREE_H_ */
