/*
 * street.cpp
 *
 *  Created on: 24 Apr 2016
 *      Author: Pedro
 */
#include "street.h";

using namespace std;

Street::Street(string name, int comp, Coord coords, vector<string> connections, unsigned id){
	this->name = name;
	this->length = comp;
	this->coords = coords;
	this->connections = connections;
	this->id = id;
}

Street::Street(string name, int comp, float lat, float lon, vector<string> connections, unsigned id){
	this->name = name;
	this->length = comp;
	Coord newCoords;
	newCoords.latitude = lat;
	newCoords.longitude = lon;
	this->coords = newCoords;
	this->connections = connections;
	this->id = id;
}

string Street::getname() const{
	return name;
}

int Street::getlength(){
	return length;
}

void Street::setname(string n){
	this->name = n;
}

void Street::setlength(int comp){
	this->length = comp;
}

bool Street::operator==(const Street& r1){
	if(r1.getname() == name)
		return true;
	else return false;
}

Coord Street::getCoords(){
	return coords;
}

void Street::setCoords(Coord coords){
	this->coords = coords;
}

unsigned Street::getId() const {
	return id;
}

void Street::setId(unsigned id) {
	this->id = id;
}

void loadStreets(string filename,Graph<Street*> &graph, list<Street*> &streets){
	ifstream file;
	file.open(filename.c_str());
	string name;
	Coord coords;
	int comp;
	unsigned id = 0;
	// Reading of street file
	while(!file.eof()){
		getline(file, name);
		file >> comp;
		file.ignore();
		file >> coords.latitude;
		file >> coords.longitude;
		file.ignore();
		vector<string> adjaStreet;
		while(!file.eof() && (char) file.peek() != '\n'){
			string adjacentStreet;
			getline(file,adjacentStreet);
			adjaStreet.push_back(adjacentStreet);
		}
		Street * street = new Street(name, comp, coords, adjaStreet, id++);
		streets.push_back(street);
		graph.addVertex(street);

		while(!file.eof() && file.peek() == '\n')
			file.ignore();

	}
	file.close();
	//Finished



}

