/*
 * way.cpp
 */
#include "way.h"

using namespace std;

list<wayList> ordPOI(Graph<Street*> graph, list<POI*> POIs){
	list<wayList> organizedPOIs;
	list<POI*>::iterator it = POIs.begin();
	for(; it != POIs.end(); it++){
		POI* p = *it;
		// Funcao das aulas praticas para escolher o caminho mais curto
		graph.dijkstraShortestPath(p->getStreet());

		wayList wlist;
		wlist.pois = p;
		list<POI*>::iterator it2 = POIs.begin();
		for(; it2 != POIs.end(); it2++){
			if(*it == *it2)
				continue;
			POI* dest = *it2;
			Way way;
			way.orig = p;
			way.dest = dest;
			Vertex<Street*> * v = graph.getVertex(dest->getStreet());
			way.dist = v->getDist();
			way.streets.push_front(v->getInfo());
			do{
				v = v->path;
				if(v == NULL)
					break;
				way.streets.push_front(v->getInfo());
			}while(v->getDist() != 0);
			wlist.ways.push_front(way);
		}
		organizedPOIs.push_back(wlist);
	}
	return organizedPOIs;
}

Graph<POI*> convertToGraph(list<wayList> organizedPOIs){
	Graph<POI*> graph;
	list<wayList>::iterator it = organizedPOIs.begin();
	POI* poi = it->pois;
	graph.addVertex(poi);
	list<Way>::iterator path = it->ways.begin();
	for(; path != it->ways.end(); path++){
		POI* dest = path->dest;
		if (dest == poi)
			continue;
		graph.addVertex(dest);
		graph.addEdge(poi, dest, path->dist);
	}
	it++;
	for(; it != organizedPOIs.end(); it++){
		POI* poi = it->pois;
		if(graph.getVertex(poi) == NULL)
			graph.addVertex(poi);
		list<Way>::iterator path = it->ways.begin();
		for(; path != it->ways.end(); path++){
			POI* dest = path->dest;
			if (dest == poi)
				continue;
			graph.addEdge(poi, dest, path->dist);
		}
	}
	return graph;
}

list<Street*> streetPath(list<wayList> organizedPOIs, list<POI*> orderedPOIs){
	list<Street*> streetPath;
	list<POI*>::iterator it = orderedPOIs.begin();
	POI* origin;
	POI* dest = *it;
	streetPath.push_back(dest->getStreet());
	it++;
	for(; it != orderedPOIs.end(); it++){
		origin = dest;
		dest = *it;
		list<wayList>::iterator orgListIt = organizedPOIs.begin();
		for(; orgListIt != organizedPOIs.end(); orgListIt++){
			if(orgListIt->pois == origin){
				list<Way>::iterator pathListIt = orgListIt->ways.begin();
				for(; pathListIt != orgListIt->ways.end(); pathListIt++){
					if(pathListIt->dest != dest)
						continue;
					list<Street*> path = pathListIt->streets;
					path.pop_front();
					streetPath.insert(streetPath.end(), path.begin(), path.end());
				}
				break;
			}
		}
	}
	return streetPath;
}

Graph<Street*> graphical(list<Street*> streetPath){
	Graph<Street*>retGraph;
	list<Street*>::iterator circuitIt = streetPath.begin();
	Street* previousStreet;
	Street* currentStreet = *circuitIt;
	retGraph.addVertex(currentStreet);
	circuitIt++;
	for(; circuitIt != streetPath.end(); circuitIt++){
		previousStreet = currentStreet;
		currentStreet = *circuitIt;
		retGraph.addVertex(currentStreet);
		retGraph.addEdge(previousStreet, currentStreet, ((double) previousStreet->getLength() + currentStreet->getLength())/2 );
	}
	return retGraph;
}
