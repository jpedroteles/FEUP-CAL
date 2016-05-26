/*
 * menu.cpp
 */

#include "menu.h"

using namespace std;

void welcome()
{
	cout << endl <<  endl;
	cout <<  " __        __   _                          " << endl;
	cout <<  " \\ \\      / /__| | ___ ___  _ __ ___   ___ " << endl;
	cout <<  "  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\" << endl;
	cout <<  "   \\ V  V /  __/ | (_| (_) | | | | | |  __/" << endl;
	cout <<  "    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|" << endl << endl << endl;

	Options();
}

void Options()
{
	cout <<  endl;
	bool valid = false;
	int yourchoice;

	cout << "1. See itinerary" << endl;
	cout << "2. See passengers" << endl;
	cout << "3. Search itinerary" << endl;
	cout << "4. Search passengers" << endl;
	cout << "5. Return" << endl << endl;
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
			Options();
		}
	}
	while (!valid);

	if (yourchoice == 1)
		listPoi();
	if (yourchoice == 2)
		//cenas
		if (yourchoice == 3)
			//cenas
			if (yourchoice == 4)
				//cenas
				if (yourchoice == 5)
					welcome();
}

string enterName() {
	string name;

	do {
		cout << "Introduza o nome do passageiro:" << endl;
		getline(cin, name);
	} while (name.empty());

	return name;
}

void listPoi(){
	list<POI*> POIs;
	Graph<Street*> graph;
	list<POI*> route;
	list<Street*> streets;
	loadStreets("ruas.txt", graph, streets);
	loadPOIs("pois.txt", POIs, streets);
	loadRoute("itinerario1.txt", route, POIs);
	list<wayList> organizedPOIs = ordPOI(graph, route);
	Graph<POI*> poiGraph = convertToGraph(organizedPOIs);
	list<POI*> orderedPOIs = poiGraph.branchAndBoundSmallestCircuit();
	list<POI*>::iterator it = orderedPOIs.begin();

	for (it; it != orderedPOIs.end(); it++) {
		cout << (*it)->getName() << endl;
	}
	cout <<  endl;
	Options();
}
