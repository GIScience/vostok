/*
 * Vec3d.h
 *
 *  Created on: 26.12.2013
 *      Author: sebastian
 */

#ifndef VEC3D_H_
#define VEC3D_H_

#include <string>

class Vec3d {
public:
	Vec3d();
	Vec3d(double x, double y, double z);
	virtual ~Vec3d();

	std::string toString();

	Vec3d operator+(const Vec3d& other);
	Vec3d operator-(const Vec3d& other);
	Vec3d operator*(const double factor);

	Vec3d normalize();

	void set(double x, double y, double z);

	inline double x() const { return mCoords[0]; };
	inline double y() const { return mCoords[1]; };
	inline double z() const { return mCoords[2]; };

	double mCoords[3];

	double length();


};

#endif /* VEC3D_H_ */

