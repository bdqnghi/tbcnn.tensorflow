/*
 * DepthFirstSearch.cpp
 *
 *  Created on: 2017. 6. 4.
 *      Author: ghbae
 */

#include "../GraphADT/GraphADT.h"

void Graph::depthFirstSearch(int sourceID) {
	resetSPRMetrics();
	fprintf(fp,"DEPTH-FIRST SEARCH (SRC: %2d)\n\t",sourceID);
	depthFirstSearch(vertex[sourceID]);
	fprintf(fp,"\n");
}

void Graph::depthFirstSearch(Vertex* source) {
	source->setKnown(true); //source or root

	fprintf(fp,"%2d",source->getVertexID());

	Edge* e = source->getEdgeHead();

	//Need stack or recursion.
	while (e != NULL) { //Visit every edges in this vertex.
		if (!vertex[e->getVertexID()]->getKnown()) {
			fprintf(fp," -> ");
			depthFirstSearch(vertex[e->getVertexID()]);
		}
		e = e->getNext();
	} //printf("back <- ");
}
