/*
 * main.cpp
 */

#include "graphviewer.h"
#include "Graph.h"
#include "street.h"
#include "POI.h"

using namespace std;


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
		//gv->addNode(i, convert_coordinates_x(vertexes[i]->getInfo()->getCoords().longitude), convert_coordinates_y(vertexes[i]->getInfo()->getCoords().latitude));
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

