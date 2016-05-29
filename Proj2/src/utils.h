/*
 * utils.h
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#define NUM_ROUTES 5
#define MAX_CAPACITY 3

struct Coord{
	float longitude;
	float latitude;
};

bool sortPOI(Coord c1, Coord c2);
std::string intToString ( int Number);

#endif /* UTILS_H_ */
