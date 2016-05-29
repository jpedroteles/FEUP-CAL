/*
 * menu.h
 */

#ifndef MENU_H_
#define MENU_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iomanip>

#include "graphviewer.h"
#include "Graph.h"
#include "street.h"
#include "POI.h"
#include "utils.h"
#include "way.h"
#include "matcher.h"


using namespace std;

void welcome();
void Options();
void listItinerary();
void listPassengers();
void displaySelectedWay(Graph<Street*> graph, list<wayList> organizedPOIs,
		list<Street*> way);
string enterName();
string searchpassengers();




#endif /* MENU_H_ */
