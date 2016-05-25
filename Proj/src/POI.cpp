/*
 * POI.cpp
 */

#include "POI.h"

POI::POI(string name, Street* street){
	this->name = name;
	this->street = street;
}


string POI::getName() const{
	return this->name;
}

void POI::setName(string name){
	this->name = name;
}

Street * POI::getStreet() const{
	return this->street;
}

void POI::setStreet(Street * rua){
	this->street = rua;
}

bool POI::operator==(const POI &p){
	if(p.getName() == name)
		return true;
	return false;
}

void loadPOIs(string filename, list<POI*> &vecPOI, list<Street*> &streets){
	ifstream file;
	file.open(filename.c_str());
	string name,streetName;
	while(!file.eof()){
		getline(file, name);
		getline(file, streetName);
		file.ignore();
		list<Street*>::iterator it = streets.begin();
		Street* street;
		for(;it != streets.end(); it++)
			if((*it)->getName() == streetName)
				street = *it;
		if(street == NULL)
			throw ExceptionStreetNotFound();
		POI * poi = new POI(name, street);
		vecPOI.push_back(poi);
	}

	file.close();
}

void loadRoute(string filename, list<POI*> &vecRoute, list<POI*> &vecPOI){
	ifstream file;
	file.open(filename.c_str());
	string name,streename;
	int i = 0;

	while(!file.eof()){
		getline(file, name);

		list<POI*>::iterator it = vecPOI.begin();
		POI* poi;
		for(;it != vecPOI.end();it++)
			if((*it)->getName() == name)
				poi = *it;
		if(poi == NULL)
			throw ExceptionPOINotFound();
		vecRoute.push_back(poi);
	}
}
