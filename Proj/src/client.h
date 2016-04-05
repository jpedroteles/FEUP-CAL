/*
 * client.h
 *
 *  Created on: Apr 5, 2016
 *      Author: Pedro
 */
#ifndef CLIENTE_H_
#define CLIENTE_H_


#include <iostream>
#include <vector>
#include <string>

using namespace std;

class client{

private:
	string name;
	vector<string> pontosInteresse;
public:
	string getName();
	void setName(string newName);
};

#endif  /* CLIENTE_H_ */

