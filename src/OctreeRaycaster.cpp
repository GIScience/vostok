/*
 * OctreeRaycaster.cpp
 *
 *  Created on: 15.05.2016
 *      Author: sebastian
 */

#include "OctreeRaycaster.h"

#include <iostream>

OctreeRaycaster::OctreeRaycaster(Octree* octree) {
	// TODO Auto-generated constructor stub

	mOctree = octree;
}

OctreeRaycaster::~OctreeRaycaster() {
	// TODO Auto-generated destructor stub
}

void OctreeRaycaster::raycast(Vec3d rayOrigin, Vec3d rayDir) {

	mRayDir = rayDir;
	mRayOrigin = rayOrigin;

	Vec3d center;

	raycast_recursive(center, 0);
}

void OctreeRaycaster::raycast_recursive(Vec3d center, int depth) {

	// Idee: Box intersection mit allen child nodes + nach entfernung von t0 sortieren
	/*
	//############ BEGIN Evaluate x direction ###############
	if (mRayDir.x() > 0) {
		// Positive direction -> ray enters left side first
	} else if (mRayDir.x() < 0) {
		// Negative direction -> ray enters right side first
	} else {
		// Direction normal to x axis -> ray stays on the side where it is
	}
	//############ END Evaluate x direction ###############


	//############ BEGIN Evaluate y direction ###############
	if (mRayDir.y() > 0) {
		// Positive direction -> ray enters forward side first
	} else if (mRayDir.y() < 0) {
		// Negative direction -> ray enters backward side first
	} else {
		// Direction normal to x axis -> ray stays on the side where it is
	}
	//############ END Evaluate y direction ###############


	//############ BEGIN Evaluate z direction ###############
	if (mRayDir.z() > 0) {
		// Positive direction -> ray enters bottom side first
	} else if (mRayDir.z() < 0) {
		// Negative direction -> ray enters top side first
	} else {
		// Direction normal to z axis -> ray stays on the side where it is
	}
	//############ END Evaluate z direction ###############
	*/
}
