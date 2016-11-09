/*
 * OctreeNode.h
 *
 *  Created on: 26.12.2013
 *      Author: sebastian
 */

#ifndef OCTREENODE_H_
#define OCTREENODE_H_

class OctreeNode {
public:
	OctreeNode();
	virtual ~OctreeNode();

	unsigned int mNumPoints;

	OctreeNode* mChildren[8];
};

#endif /* OCTREENODE_H_ */
