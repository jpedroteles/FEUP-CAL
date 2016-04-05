/*
 * locals.h
 *
 *  Created on: Apr 5, 2016
 *      Author: Pedro
 */

#ifndef LOCALS_H_
#define LOCALS_H_


#include <iostream>
#include <vector>
#include <string>

using namespace std;

class locals{
private:
	string name;
	double latitude;
	double longitude;
public:

	//constructors
		locals();
		locals(string name,double latitude,double longitude);
		string getName();
		void setName(string name);
		double getLatitude();
		void setLatitude(double latitude);
		double getLongitude();
		void setLongitude(double longitude);
};



#endif /* LOCALS_H_ */
