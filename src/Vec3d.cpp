/*
 * Vec3d.cpp
 *
 *  Created on: 26.12.2013
 *      Author: sebastian
 */

#include "Vec3d.h"
#include <cmath>
#include <iostream>
#include <sstream>

Vec3d::Vec3d() {
	// TODO Auto-generated constructor stub

	mCoords[0] = 0;
	mCoords[1] = 0;
	mCoords[2] = 0;

}

Vec3d::Vec3d(double x, double y, double z) {
	// TODO Auto-generated constructor stub

	mCoords[0] = x;
	mCoords[1] = y;
	mCoords[2] = z;
}


Vec3d::~Vec3d() {
	// TODO Auto-generated destructor stub
}

std::string Vec3d::toString() {

	std::ostringstream convert;


	convert << "( " << mCoords[0] << ", " << mCoords[1] << ", " << mCoords[2] << " )";

	return convert.str();
}


Vec3d Vec3d::operator+(const Vec3d& other){

	return Vec3d(mCoords[0] + other.mCoords[0],mCoords[1] + other.mCoords[1],mCoords[2] + other.mCoords[2]);

	//return Vec3d(this->x() + other.x(), this->y() + other.y(), this->z() + other.z());
}


Vec3d Vec3d::operator-(const Vec3d& other) {

	return Vec3d(this->x() - other.x(), this->y() - other.y(), this->z() - other.z());
}


void Vec3d::set(double x, double y, double z) {
	mCoords[0] = x;
	mCoords[1] = y;
	mCoords[2] = z;
}


Vec3d Vec3d::operator*(const double factor) {

	return Vec3d(mCoords[0] * factor, mCoords[1] * factor, mCoords[2] * factor);
}

double Vec3d::length() {
	return sqrt(this->x() * this->x() + this->y() * this->y() + this->z() * this->z());
}

Vec3d Vec3d::normalize() {
	double length = this->length();

	double x = this->x() / length;
	double y = this->y() / length;
	double z = this->z() / length;

	return Vec3d(x,y,z);
}
