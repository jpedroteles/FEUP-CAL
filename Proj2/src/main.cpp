/*
 * main.cpp
 */

#include "graphviewer.h"
#include "Graph.h"
#include "street.h"
#include "POI.h"
#include "utils.h"
#include "way.h"
#include "menu.h"

using namespace std;

int main() {
	Graph<Street*> graph;
	list<Street*> streets;
	list<POI*> POIs;

	loadStreets("ruas.txt", graph, streets);
	loadPOIs("pois.txt", POIs, streets);

	list<POI*> route;
	loadRoute("itinerario1.txt", route, POIs);

	list<wayList> organizedPOIs = ordPOI(graph, route);
	Graph<POI*> poiGraph = convertToGraph(organizedPOIs);
	list<POI*> orderedPOIs = poiGraph.branchAndBoundSmallestCircuit();
	list<Street*> way = streetPath(organizedPOIs, orderedPOIs);

	welcome();

	//displaySelectedWay(graph, organizedPOIs, way);
	//getchar();
	return 0;
}
