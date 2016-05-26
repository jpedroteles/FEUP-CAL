/*
 * menu.cpp
 */

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "graphviewer.h"
#include "Graph.h"
#include "street.h"
#include "POI.h"
#include "utils.h"
#include "way.h"

using namespace std;

void welcome()
{
	cout << endl <<  endl;
	cout <<  " __        __   _                          " << endl;
	cout <<  " \\ \\      / /__| | ___ ___  _ __ ___   ___ " << endl;
	cout <<  "  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\" << endl;
	cout <<  "   \\ V  V /  __/ | (_| (_) | | | | | |  __/" << endl;
	cout <<  "    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|" << endl << endl << endl;

	//load all "configs"
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


}

void Options()
{
	bool valid = false;
	int yourchoice;
	system("CLS");

	cout << "1. See itinerary" << endl;
	cout << "2. See passengers" << endl;
	cout << "3. Search itinerary" << endl;
	cout << "4. Search passengers" << endl;
	cout << "6. Return" << endl << endl;
	do
	{
		cout << "Choose one of those options: ";
		cin >> yourchoice;
		if (yourchoice >= 1 && yourchoice <= 6)
			valid = true;
		else

		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');

			}
			cout << endl << "Invalid option" << endl << endl;
			Sleep(1000);
			//Options()
		}
	}
	while (!valid);

	if (yourchoice == 1)
		//cenas
	if (yourchoice == 2)
		//cenas
	if (yourchoice == 3)
		//cenas
	if (yourchoice == 4)
		//cenas
	if (yourchoice == 5)
		//cenas
	if (yourchoice == 6)
		welcome();
}
