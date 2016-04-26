/*
 * main.cpp
 */

#include "graphviewer.h"
#include "Graph.h"
#include "street.h"
#include "POI.h"

using namespace std;


float convertCoordy(float coord){
    float y_limit = 41.140;
    return 600 - (coord - y_limit) * 100000;
}

float convertCoordx(float coord){
    float x_limit = -8.61124;
    return 600 - (x_limit - coord) * 100000;
}

void view_Graph(Graph<Street*> graph) {
	unsigned idE = 0;
	unsigned idV = 0;
	float window_size = 3000;
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	vector<Vertex<Street*> *> vertexes = graph.getVertexSet();
	for (unsigned int i = 0; i < vertexes.size(); i++){
		gv->addNode(i, convertCoordx(vertexes[i]->getInfo()->getCoords().longitude), convertCoordy(vertexes[i]->getInfo()->getCoords().latitude));
		gv->setVertexLabel(i,vertexes[i]->getInfo()->getName());
	}
	gv->rearrange();
	vector<Edge<Street*> > edges;
	for (unsigned int j = 0; j < vertexes.size(); j++) {
		edges = vertexes[j]->getAdj();
		for (unsigned int k = 0; k < edges.size(); k++) {
			gv->addEdge(idE++, vertexes[j]->getInfo()->getId(), edges[k].getDest()->getInfo()->getId(), EdgeType::DIRECTED);
		}
	}
	gv->rearrange();
}

int main(){
	Graph<Street*> graph;
	list<Street*> streets;

	loadStreets("ruas.txt", graph,streets);
	view_Graph(graph);
	getchar();
	return 0;
}

