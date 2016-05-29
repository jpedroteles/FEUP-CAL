/*
 * menu.cpp
 */

#include "menu.h"

using namespace std;

#define NUM_ROUTES 5

void welcome() {
	cout << endl << endl;
	cout << " __        __   _                          " << endl;
	cout << " \\ \\      / /__| | ___ ___  _ __ ___   ___ " << endl;
	cout << "  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\" << endl;
	cout << "   \\ V  V /  __/ | (_| (_) | | | | | |  __/" << endl;
	cout << "    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|" << endl << endl
			<< endl;

	Options();
}

void Options() {
	cout << endl;
	bool valid = false;
	int yourChoice;

	cout << "1. See itinerary" << endl;
	cout << "2. See passengers" << endl;
	cout << "3. Search itinerary" << endl;
	cout << "4. Search passengers" << endl;
	cout << "5. Exit" << endl << endl;
	do {
		cout << "Choose one of these options: ";
		cin >> yourChoice;
		if (yourChoice >= 1 && yourChoice <= 6)
			valid = true;
		else

		{
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');

			}
			cout << endl << "Invalid option" << endl << endl;
			Sleep(1000);
			Options();
		}
	} while (!valid);

	switch (yourChoice) {
	case 1:
		listItinerary();
		break;
	case 2:
		listPassengers();
		break;
	case 3:
		break;
	case 4:
		enterName();
		break;
	case 5:
		return;
		break;
	default:
		break;
	}
}

string enterName() {
	string name;
	do {
		cout << "Introduza o nome do passageiro:" << endl;
		getline(cin, name);
	} while (name.empty());

	return name;
}

void listItinerary() {
	cout << "Number of routes = " << NUM_ROUTES << endl;

	int choice = 0;
	do {
		cout << "Select a route number: ";
		cin >> choice;
	} while (choice <= 0 || choice > NUM_ROUTES);

	Graph<Street*> graph;
	list<Street*> streets;
	list<POI*> POIs;

	loadStreets("ruas.txt", graph, streets);
	loadPOIs("pois.txt", POIs, streets);

	list<POI*> route;

	string path = "itinerario";
	path += intToString(choice) + ".txt";
	loadRoute(path, route, POIs);

	list<wayList> organizedPOIs = ordPOI(graph, route);
	Graph<POI*> poiGraph = convertToGraph(organizedPOIs);
	list<POI*> orderedPOIs = poiGraph.branchAndBoundSmallestCircuit();
	list<Street*> way = streetPath(organizedPOIs, orderedPOIs);

	cout << "\nRoute " << choice << ":\n" << "Avenida dos Aliados";

	list<POI*>::iterator it = orderedPOIs.begin();
	for (it++; it != orderedPOIs.end(); it++) {
		cout << " - " << (*it)->getName();
	}
	cout << endl;

	displaySelectedWay(graph, organizedPOIs, way);

	Options();
}

void listPassengers() {
	cout << "List of passengers:\n" << endl;
	cout << setw(18) << left << "Name" << "Route" << endl;

	ifstream file;
	file.open("passageiros.txt");
	string name;
	string route;
	int i = 0;

	while (!file.eof()) {
		getline(file, name);
		getline(file, route);
		i++;

		cout << setw(20) << left << name << route << endl;
	}

	cout << "\nNumber of passengers = " << i << endl;

	Options();
}
string searchpassengers() {
	string toSearch = enterName();

	cout << endl << numStringMatching("passageiros.txt", toSearch) << endl;

	return NULL;
}
