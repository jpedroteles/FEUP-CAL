/*
 * street.h
 *
 *  Created on: 24 Apr 2016
 *      Author: Pedro
 */

#ifndef street_H_
#define street_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <unistd.h>
#include <cmath>

#include "utils.h"
#include "Graph.h"

using namespace std;

class ExceptionStreetNotFound{};

class Street{
	unsigned id;
	string name;
	int length;
	Coord coords;
public:
	vector<string> connections;

	Street(string name, int comp, Coord coords,vector<string> connections,unsigned id);
	Street(string name, int comp,float lat,float lon,vector<string> connections,unsigned id);

	string getName() const;
	void setName(string n);
	int getLength();
	void setLength(int comp);
	bool operator==(const Street& r1);
	Coord getCoords();
	void setCoords(Coord coords);
	unsigned getId() const;
	void setId(unsigned id);

};

void loadStreets(string filename,Graph<Street*> &graph, list<Street*> &streets);
void graphCreate(Graph<Street*> &graph, list<Street*> &streets);

#endif /* street_H_ */
