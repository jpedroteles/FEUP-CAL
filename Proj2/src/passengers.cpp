/*
 * passengers.cpp
 */

#include "passengers.h"

Passengers::Passengers(string name, string itinerario){
	this->name=name;
	this->itinerario=itinerario;
}

string Passengers::getName() const{
	return this->name;

}
void Passengers:: setName(string name){
	this->name = name;
}
string Passengers:: getItinerario() const{
	return this->itinerario;
}
void Passengers::setItinerario(int itinerario){
	this->itinerario = itinerario;
}
bool Passengers::operator==(const Passengers &p){
	if(p.getName() == name)
			return true;
		return false;
}
