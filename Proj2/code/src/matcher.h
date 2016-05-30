/*
 * matcher.h
 *
 *  Created on: 27/05/2016
 *      Author: josep
 */

#ifndef MATCHER_H_
#define MATCHER_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int kmp(string text, string pattern);
int numStringMatching(string filename, string toSearch);
int editDistance(string pattern, string text);
float numApproximateStringMatching(string filename, string toSearch);


vector<string> numStringMatchingPOI(string toSearch);
vector<string> numApproximateStringMatchingPOI(string toSearch);

vector<int> numStringMatchingRoutes(string toSearch);

int searchPassengerRoute(string name);
vector<pair<string, int> > numStringMatchingPassengers(string name);
vector<pair<string, int> > numApproximateStringMatchingPassengers(string name);

#endif /* MATCHER_H_ */
