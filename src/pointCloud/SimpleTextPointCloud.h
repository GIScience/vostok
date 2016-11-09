

#ifndef SRC_POINTCLOUD_SIMPLETEXTPOINTCLOUD_H_
#define SRC_POINTCLOUD_SIMPLETEXTPOINTCLOUD_H_

#include "AbstractPointCloud.h"
#include <iostream>
#include <fstream>


class SimpleTextPointCloud : public AbstractPointCloud {
protected:

	bool mSourceFileGood;

	std::string mFilePath;
	std::string mPattern;
	std::ifstream* mSourceFile;

	unsigned int mLineNumber;

	void updateMetaFile();

public:

	SimpleTextPointCloud(std::string filePath, std::string pattern);
	virtual ~SimpleTextPointCloud();
	virtual bool endOfCloud();
	virtual std::vector<double> getNextPoint();
	virtual void resetCursor();
	bool sourceFileGood();

};

#endif /* SRC_POINTCLOUD_SIMPLETEXTPOINTCLOUD_H_ */
