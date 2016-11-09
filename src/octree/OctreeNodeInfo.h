/*
 * OctreeNodeInfo.h
 *
 *  Created on: 26.12.2013
 *      Author: sebastian
 */

#ifndef OCTREENODEINFO_H_
#define OCTREENODEINFO_H_

#include "../Vec3d.h"
#include "OctreeNode.h"

class OctreeNodeInfo {
public:
	OctreeNodeInfo(Vec3d pos, double size, OctreeNode* ref);
	virtual ~OctreeNodeInfo();

	int getChildIndex(Vec3d& v);
	Vec3d getChildPosByIndex(unsigned int childIndex) const;

	Vec3d getFarIntersection(Vec3d& rayStart, Vec3d& rayDir);

	void insertPointRecursive(Vec3d& v, unsigned int depth, unsigned int maxDepth);

	Vec3d mPos;
	double mSize;
	OctreeNode* mRef;
};

#endif /* OCTREENODEINFO_H_ */
