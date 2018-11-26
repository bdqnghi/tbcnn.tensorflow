/*
 * MST_class.h
 *
 *  Created on: Nov 12, 2016
 *      Author: User
 */

#ifndef MST_CLASS_H_
#define MST_CLASS_H_

#include <vector>

using namespace std;

#include "Graph.h"


// Template class for the MST Node list
template <class T>
class MST {

private:

	int from;
	int to;
	T distance;

	// Minimum-spanning-tree distance
	T mst_distance;

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
	MST(int from, int to, T distance):from(from),
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

	T get_distance() {
		return distance;
	}

	// Calculate the minimum-spanning-tree distance
	// An implementation of the Jarnik-Prim algorithm
	void PrimMST(Graph<T>);

	// Calculate the minimum-spanning-tree distance
	// An implementation of the Kruskal algorithm
	void KruskalMST(Graph<T>);

	// Generate k clusters
	// Return maximum spacing
	T k_Cluster(Graph<T>, int);

	void create_set(vector<T>&, vector<T>&, int);
	void merge_set(vector<T>&, vector<T>&, int, int);
	T find_set(vector<T>&, int);


	// Print the Minimum-Spanning-Tree
	void print_MST(style_t, algorithm_t);

};	// end - MST Template class


#endif /* MST_CLASS_H_ */
