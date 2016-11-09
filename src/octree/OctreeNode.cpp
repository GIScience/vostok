/*
 * OctreeNode.cpp
 *
 *  Created on: 26.12.2013
 *      Author: sebastian
 */

#include <iostream>
#include "OctreeNode.h"

OctreeNode::OctreeNode() {
	// TODO Auto-generated constructor stub

	for (unsigned int i = 0; i < 8; ++i) {
		mChildren[i] = 0;
	}

	mNumPoints = 0;
}

OctreeNode::~OctreeNode() {
	// TODO Auto-generated destructor stub
}

