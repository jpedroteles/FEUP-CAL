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

float convertCoordy(float coord){
	float y_limit = 41.140;
	return 1000 - (coord - y_limit) * 90000;
}

float convertCoordx(float coord){
	float x_limit = -8.61124;
	return 850 - (x_limit - coord) * 55000;
}

bool checkPOI(list<wayList> organised_POIs, Street* street){
	list<wayList>::iterator primit =organised_POIs.begin();
	list<Way>::iterator it;
	list<Street *>::iterator iterB;
	list<Street *>::iterator iterE;
	list<Street *>::iterator check;

	for(; primit != organised_POIs.end();primit++){
		it = primit->ways.begin();
		for(; it!= primit->ways.end(); it++){
			iterB = it->streets.begin();
			iterE = it->streets.end();
			for(;iterB!=iterE;iterB++)
				check = find(iterB,iterE, street);
			if(check!=iterE)
				return true;
		}
	}
	return false;
}

void displaySelectedway(Graph<Street*> graph, list<wayList> organizedPOIs){
	unsigned idE = 0;
	vector<string> POIs_name;
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->setBackground("background.jpg");
	gv->createWindow(1280, 830);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	vector<Vertex<Street*> *> vertexes = graph.getVertexSet();

	for (unsigned int i = 0; i < vertexes.size(); i++){
		gv->addNode(i, convertCoordx(vertexes[i]->getInfo()->getCoords().longitude), convertCoordy(vertexes[i]->getInfo()->getCoords().latitude));
		gv->setVertexLabel(i,vertexes[i]->getInfo()->getName());
	}

	for (unsigned int i = 0; i < vertexes.size(); i++){
		for(list<wayList>::iterator it = organizedPOIs.begin(); it!= organizedPOIs.end();it++){
			if(it->pois->getStreet()->getName() == vertexes[i]->getInfo()->getName()){
				gv->setVertexColor(vertexes[i]->getInfo()->getId(), "yellow");
			}
		}
	}
	gv->rearrange();
	vector<Edge<Street*> > edges;
	for (unsigned int j = 0; j < vertexes.size(); j++) {
		edges = vertexes[j]->getAdj();
		for (unsigned int k = 0; k < edges.size(); k++) {
			if(checkPOI(organizedPOIs, edges[k].getDest()->getInfo())){
				gv->addEdge(idE, vertexes[j]->getInfo()->getId(), edges[k].getDest()->getInfo()->getId(), EdgeType::DIRECTED);
				gv->setEdgeColor(idE++,"orange");
			}
			else
				gv->addEdge(idE++, vertexes[j]->getInfo()->getId(), edges[k].getDest()->getInfo()->getId(), EdgeType::DIRECTED);
		}
	}
	gv->rearrange();
}

int main(){
	Graph<Street*> graph;
	list<Street*> streets;
	list<POI*> POIs;

	loadStreets("ruas.txt", graph, streets);
	loadPOIs("pois.txt", POIs, streets);

	list<wayList> organizedPOIs = ordPOI(graph, POIs);
	Graph<POI*> poiGraph = convertToGraph(organizedPOIs);
	list<POI*> orderedPOIs = poiGraph.branchAndBoundSmallestCircuit();
	list<Street*> way = streetPath(organizedPOIs,orderedPOIs);

	displaySelectedway(graph, organizedPOIs);

	while(true){}
	return 0;
}
