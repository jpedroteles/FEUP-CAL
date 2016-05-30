/*
 * passengers.h
 */

#include <string>
#include <vector>
#include <list>
#include <unistd.h>
#include <cmath>

#ifndef PASSENGERS_H_
#define PASSENGERS_H_

using namespace std;

class Passengers{
private:
	string name;
	string itinerario;
	vector<string> passengersName;
public:
	Passengers(string name, string itinerario);
	string getName() const;
	void setName(string name);
	string getItinerario() const;
	void setItinerario(int itinerario);
	bool operator==(const Passengers &p);
};

void loadPassengers(string filename,list<Passengers> &passengers);

#endif /* PASSENGERS_H_ */
