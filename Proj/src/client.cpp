/*
 * client.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: Pedro
 */
#include "client.h"

using namespace std;

string client::getName(){
	return name;
}

void client::setName(string newName){
	name = newName;
}
