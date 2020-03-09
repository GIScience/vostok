/*
 * ProjectConfig.h
 *
 *  Created on: 28.04.2014
 *      Author: sebastian
 */

#ifndef PROJECTCONFIG_H_
#define PROJECTCONFIG_H_

#include <string>

class ProjectConfig {
public:
	ProjectConfig();
	virtual ~ProjectConfig();

	std::string getSettingsString();
	bool loadFromFile(std::string filePath);

	double mVoxelSize;

	std::string mShadowPointsFilePath;
	std::string mOutputFilePath;
	std::string mQueryPointsFilePath;


	std::string mProj4string_input;
	std::string mShadowPointsInputFormat;
	std::string mQueryPointsInputFormat;

	// Day and minute step lengths:
	int m_dayStart;
	int m_dayEnd;
	int m_dayStep;
	int m_minuteStep;
	int m_year;
	int m_timezone;
	float m_lon;
	float m_lat;

	int m_openMp;

	// Different flags:
	int m_computeShadows;
    
    //min. solar elevation angle
    double m_minSunAngle;

};

#endif /* PROJECTCONFIG_H_ */
