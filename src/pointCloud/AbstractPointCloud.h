/*
 * AbstractPointCloud.h
 *
 *  Created on: 13.05.2016
 *      Author: geomer
 */

#ifndef SRC_POINTCLOUD_ABSTRACTPOINTCLOUD_H_
#define SRC_POINTCLOUD_ABSTRACTPOINTCLOUD_H_

#include <map>
#include <vector>
#include <string>

class AbstractPointCloud {
public:
	AbstractPointCloud();
	virtual ~AbstractPointCloud();

	virtual std::vector<double> getNextPoint() = 0;

	virtual void resetCursor() = 0;

	virtual bool endOfCloud() = 0;

	std::vector<std::string> getFieldNames() { return mFieldNames; }

	std::vector<double> getMin() { return mMin; };
	std::vector<double> getMax() { return mMax; };

	virtual unsigned int getNumPoints() = 0;

protected:

	std::vector<std::string> mFieldNames;
	unsigned int mCursorPos;

	unsigned int mNumPoints;

	std::vector<double> mMin;
	std::vector<double> mMax;
};

#endif /* SRC_POINTCLOUD_ABSTRACTPOINTCLOUD_H_ */
