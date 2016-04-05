/*
 * locals.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: Pedro
 */
#include "locals.h"

using namespace std;
	double locals::getLatitude(){
		return latitude;
	}

	void locals::setLatitude(double latitude) {
		this->latitude = latitude;
	}

	double locals::getLongitude(){
		return longitude;
	}

	void locals::setLongitude(double longitude) {
		this->longitude = longitude;
	}

	string locals::getName(){
		return name;
	}

	void locals::setName(string name) {
		this->name = name;
	}


