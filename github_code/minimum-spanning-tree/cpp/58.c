/*
 * MST.h
 *
 *  Created on: Oct 8, 2016
 *      Author: Shawn Flynn
 */

#ifndef MST_H_
#define MST_H_

#include <vector>

using namespace std;

#include "Graph.h"


// Class for the MST Node list
class MST {

private:

	int from;
	int to;
	int distance;

	// Minimum-spanning-tree distance
	int mst_distance;

	// The MST node list
	list<MST>* pMSTEdge_list;

public:

	// MST Algorithm
	enum algorithm_t {PRIM, KRUSKAL};

	// Output style
	enum style_t {NUMERIC, LOWERCASE, UPPERCASE};

	// Default constructor
	MST():from(0),
		  to(0),
		  distance(0),
		  mst_distance(0),
		  pMSTEdge_list(nullptr) {
	}

	// Value constructor
	MST(int from, int to, int distance):from(from),
										to(to),
										distance(distance),
										mst_distance(0),
										pMSTEdge_list(nullptr) {
	}

	int get_from() {
		return from;
	}

	int get_to() {
		return to;
	}

	int get_distance() {
		return distance;
	}

	// Calculate the minimum-spanning-tree distance
	// An implementation of the Jarnik-Prim algorithm
	void PrimMST(Graph);

	// Calculate the minimum-spanning-tree distance
	// An implementation of the Kruskal algorithm
	void KruskalMST(Graph);

	// Generate k clusters
	// Return maximum spacing
	int k_Cluster(Graph, int);

	// Print the Minimum-Spanning-Tree
	void print_MST(style_t, algorithm_t);

};	// end - MSTNode class



#endif /* MST_H_ */
