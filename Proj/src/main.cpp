/*
 * main.cpp
 */

#include "graphviewer.h"
#include "Graph.h"
#include "street.h"
#include "POI.h"
#include "utils.h"
#include "way.h"

using namespace std;

float convertCoordy(float coord) {
	float y_limit = 41.140;
	return 1000 - (coord - y_limit) * 90000;
}

float convertCoordx(float coord) {
	float x_limit = -8.61124;
	return 850 - (x_limit - coord) * 55000;
}

bool checkPOI(list<wayList> organised_POIs, Street* street) {
	list<wayList>::iterator primit = organised_POIs.begin();
	list<Way>::iterator it;
	list<Street *>::iterator iterB;
	list<Street *>::iterator iterE;
	list<Street *>::iterator check;

	for (; primit != organised_POIs.end(); primit++) {
		it = primit->ways.begin();
		for (; it != primit->ways.end(); it++) {
			iterB = it->streets.begin();
			iterE = it->streets.end();
			for (; iterB != iterE; iterB++)
				check = find(iterB, iterE, street);
			if (check != iterE)
				return true;
		}
	}
	return false;
}

void displaySelectedWay(Graph<Street*> graph, list<wayList> organizedPOIs,
		list<Street*> way) {
	unsigned idE = 0;
	vector<string> POIs_name;
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->setBackground("background.jpg");
	gv->createWindow(1280, 830);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	vector<Vertex<Street*> *> vertexes = graph.getVertexSet();

	for (unsigned int i = 0; i < vertexes.size(); i++) {
		gv->addNode(i,
				convertCoordx(vertexes[i]->getInfo()->getCoords().longitude),
				convertCoordy(vertexes[i]->getInfo()->getCoords().latitude));
		gv->setVertexLabel(i, vertexes[i]->getInfo()->getName());
	}

	for (unsigned int i = 0; i < vertexes.size(); i++) {
		for (list<wayList>::iterator it = organizedPOIs.begin();
				it != organizedPOIs.end(); it++) {
			if (i == 0) {
				gv->setVertexColor(vertexes[i]->getInfo()->getId(), "green");
				continue;
			}
			if (it->pois->getStreet()->getName()
					== vertexes[i]->getInfo()->getName()) {
				gv->setVertexColor(vertexes[i]->getInfo()->getId(), "yellow");
			}
		}
	}
	gv->rearrange();

	int edgeNumber = 1;
	way.insert(way.begin(), vertexes[0]->getInfo());
	for (list<Street*>::iterator it = way.begin(); it != way.end(); it++) {
		list<Street*>::iterator it2 = it;
		it2++;


		Vertex<Street*>* vOrigem;
		Vertex<Street*>* vDestino;

		for (size_t i = 0; i < vertexes.size(); i++) {
			if (vertexes[i]->getInfo()->getName() == (*it)->getName())
				vOrigem = vertexes[i];

			if (it2 != way.end())
				if (vertexes[i]->getInfo()->getName() == (*it2)->getName())
					vDestino = vertexes[i];
		}
		if (it2 == way.end()) {
			gv->setVertexColor(vOrigem->getInfo()->getId(), "red");
		} else {
			cout << "vOrigem = " << vOrigem->getInfo()->getName() << endl;
			cout << "vDestino = " << vDestino->getInfo()->getName() << endl
					<< endl;

			for (size_t i = 0; i < vOrigem->getAdj().size(); i++) {
				if (vOrigem->getAdj()[i].getDest()->getInfo()->getName()
						== vDestino->getInfo()->getName()) {
					vOrigem->setDrawn(i);
					gv->addEdge(idE, vOrigem->getInfo()->getId(),
							vDestino->getInfo()->getId(), EdgeType::DIRECTED);
					gv->setEdgeColor(idE, "yellow");
					gv->setEdgeLabel(idE++, intToString(edgeNumber++));
				}
			}
		}
	}
	gv->rearrange();

	vector<Edge<Street*> > edges;
	for (unsigned int j = 0; j < vertexes.size(); j++) {
		edges = vertexes[j]->getAdj();
		for (unsigned int k = 0; k < edges.size(); k++) {
			if (!edges[k].isDrawn()) {
				gv->addEdge(idE++, vertexes[j]->getInfo()->getId(),
						edges[k].getDest()->getInfo()->getId(),
						EdgeType::DIRECTED);
			}
		}
	}
	gv->rearrange();
}

int main() {
	Graph<Street*> graph;
	list<Street*> streets;
	list<POI*> POIs;

	loadStreets("ruas.txt", graph, streets);
	loadPOIs("pois.txt", POIs, streets);

	list<wayList> organizedPOIs = ordPOI(graph, POIs);
	Graph<POI*> poiGraph = convertToGraph(organizedPOIs);
	list<POI*> orderedPOIs = poiGraph.branchAndBoundSmallestCircuit();
	list<Street*> way = streetPath(organizedPOIs, orderedPOIs);

	displaySelectedWay(graph, organizedPOIs, way);

	getchar();
	return 0;
}
