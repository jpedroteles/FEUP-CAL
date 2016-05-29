/*
 * menu.cpp
 */

#include "menu.h"

using namespace std;

#define NUM_ROUTES 5

pair<string, int> passengerInfo;

void welcome() {
	cout << endl << endl;
	cout << " __        __   _                          " << endl;
	cout << " \\ \\      / /__| | ___ ___  _ __ ___   ___ " << endl;
	cout << "  \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\" << endl;
	cout << "   \\ V  V /  __/ | (_| (_) | | | | | |  __/" << endl;
	cout << "    \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|" << endl << endl
			<< endl;

	cout << "LOGIN:" << endl;
	string name = enterName();
	int routeNumber = searchPassengerRoute(name);

	passengerInfo = make_pair(name, routeNumber);

	Options();
}

void Options() {
	cout << endl;
	bool valid = false;
	int yourChoice;

	cout << "1. Display passenger info" << endl;
	cout << "2. Select a route" << endl;
	cout << "3. List routes" << endl;
	cout << "4. List passengers" << endl;
	cout << "5. Search \"Point of Interest\"" << endl;
	cout << "6. Search passengers" << endl;
	cout << "7. Exit" << endl << endl;
	do {
		cout << "Choose one of these options: ";
		cin >> yourChoice;
		if (yourChoice >= 1 && yourChoice <= 7)
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
		displayPassengerInfo();
		break;
	case 2:
		break;
	case 3:
		listRoutes();
		break;
	case 4:
		listPassengers();
		break;
	case 5:
		break;
	case 6:
		searchPassengers();
		break;
	case 7:
		saveData();
		break;
	default:
		break;
	}
}

void displayPassengerInfo() {
	cout << "\nPassenger Info:\n" << endl;

	cout << "Name - " << passengerInfo.first << endl;
	if (passengerInfo.second == 0)
		cout << "You haven't selected a route yet." << endl;
	else
		cout << "Route - " << passengerInfo.second << endl;

	Options();
}

string enterName() {
	string name;
	fflush(stdin);
	do {
		cout << "Enter passenger name: ";
		getline(cin, name);
	} while (name.empty());

	return name;
}

void listRoutes() {
	cout << "\nNumber of routes = " << NUM_ROUTES << "\n" << endl;

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

	while (getline(file, name)) {
		getline(file, route);
		i++;

		cout << setw(20) << left << name << route << endl;
	}

	cout << "\nNumber of passengers = " << i << endl;

	Options();
}
void searchPassengers() {
	string toSearch = enterName();

	vector<pair<string, int> > matches = numStringMatchingPassengers(toSearch);
	if (matches.empty()) {
		matches = numApproximateStringMatchingPassengers(toSearch);
		if (matches.empty()) {
			cout << "\nNo exact or approximate matches found." << endl;
			return Options();
		} else
			cout << "\nNo exact matches found. Were you looking for these?"
					<< endl;
	}

	cout << "\nNumber of matches = " << matches.size() << endl;

	cout << setw(18) << left << "\nName" << "Route" << endl;
	for (size_t i = 0; i < matches.size(); i++) {
		cout << setw(20) << left << matches[i].first << matches[i].second
				<< endl;
	}

	Options();
}

void saveData() {

	vector<pair<string, int> > passengers;

	ifstream fileIn("passageiros.txt");
	if (!fileIn.is_open()) {
		cout << "ERROR: Can't open passengers file!" << endl;
		return;
	}

	string lineName;
	string lineRoute;
	bool foundName = false;

	while (getline(fileIn, lineName)) {
		getline(fileIn, lineRoute);
		if (lineName == passengerInfo.first) {
			foundName = true;
			passengers.push_back(
					make_pair(passengerInfo.first, passengerInfo.second));
		} else
			passengers.push_back(make_pair(lineName, atoi(lineRoute.c_str())));
	}

	if (!foundName && passengerInfo.second != 0)
		passengers.push_back(
				make_pair(passengerInfo.first, passengerInfo.second));

	sort(passengers.begin(), passengers.end());

	fileIn.close();
	ofstream fileOut("passageiros.txt", ios::trunc);
	if (!passengers.empty()) {
		fileOut << passengers[0].first << endl;
		fileOut << passengers[0].second;
	}
	for (size_t i = 1; i < passengers.size(); i++) {
		fileOut << "\n" << passengers[i].first << endl;
		fileOut << passengers[i].second;
	}

}
