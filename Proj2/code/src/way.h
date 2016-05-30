/*
 * way.h
 */

#ifndef WAY_H_
#define WAY_H_

#include <list>
#include <string>

#include "utils.h"
#include "Graph.h"
#include "POI.h"
#include "street.h"

using namespace std;

struct Way{
	POI * orig;
	POI * dest;
	int dist;
	list<Street*> streets;
};

struct wayList{
	POI * pois;
	list<Way> ways;
};

list<wayList> ordPOI(Graph<Street*> graph, list<POI*> POIs);

Graph<POI*> convertToGraph(list<wayList> organizedPOIs);

list<Street*> streetPath(list<wayList> organizedPOIs, list<POI*> orderedPOIs);

Graph<Street*> graphical(list<Street*> streetPath);
#endif /* WAY_H_ */
