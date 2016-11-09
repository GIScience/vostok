/*
 * OctreeRaycaster.h
 *
 *  Created on: 15.05.2016
 *      Author: sebastian
 */

#ifndef SRC_OCTREERAYCASTER_H_
#define SRC_OCTREERAYCASTER_H_


#include "octree/Octree.h"
#include "Vec3d.h"

class OctreeRaycaster {
public:
	OctreeRaycaster(Octree* octree);
	virtual ~OctreeRaycaster();

	void raycast(Vec3d rayOrigin, Vec3d rayDir);
	void raycast_recursive(Vec3d center, int depth);

	Octree* mOctree;

	Vec3d mRayDir;
	Vec3d mRayOrigin;
};

#endif /* SRC_OCTREERAYCASTER_H_ */
