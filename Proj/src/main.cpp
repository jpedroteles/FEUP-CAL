/*
 * main.cpp
 */

#include "graphviewer.h"
#include "Graph.h"
#include "street.h"
#include "POI.h"
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

void viewGraph(GraphViewer* gv, Graph<Street*> graph) {
	unsigned idE = 0;
	unsigned idV = 0;
	float window_size = 3000;
	gv->setBackground("background.jpg");
	gv->createWindow(1280, 830);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("white");

	vector<Vertex<Street*> *> vertexes = graph.getVertexSet();
	for (unsigned int i = 0; i < vertexes.size(); i++) {
		gv->addNode(i,
				convertCoordx(vertexes[i]->getInfo()->getCoords().longitude),
				convertCoordy(vertexes[i]->getInfo()->getCoords().latitude));
		gv->setVertexLabel(i, vertexes[i]->getInfo()->getName());
	}
	gv->rearrange();
	vector<Edge<Street*> > edges;
	for (unsigned int j = 0; j < vertexes.size(); j++) {
		edges = vertexes[j]->getAdj();
		for (unsigned int k = 0; k < edges.size(); k++) {
			gv->addEdge(idE++, vertexes[j]->getInfo()->getId(),
					edges[k].getDest()->getInfo()->getId(), EdgeType::DIRECTED);
		}
	}
	gv->rearrange();
}

void displaySelectedPath(GraphViewer* gv) {
	//Recebe os POIs com os caminhos e compara com o grafo
	gv->setVertexColor(1, "yellow");

	gv->setEdgeThickness(10, 3);
	gv->setEdgeColor(10, "orange");
}

int main() {
	GraphViewer *gv = new GraphViewer(500, 500, false);

	Graph<Street*> graph;
	list<Street*> streets;
	list<POI*> poi;
	list<wayList> organizedPOIs;

	loadStreets("ruas.txt", graph, streets);

	loadPOIs("pois.txt", poi, streets);
	organizedPOIs = organizePOI(graph, poi);
	convertToGraph(organizedPOIs);

	viewGraph(gv, graph);
	displaySelectedPath(gv);

	getchar();
	return 0;
}

