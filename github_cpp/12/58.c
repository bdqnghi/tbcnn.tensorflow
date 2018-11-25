

#ifndef MST_H_
#define MST_H_

#include <vector>

using namespace std;

#include "Graph.h"



class MST {

private:

	int from;
	int to;
	int distance;

	
	int mst_distance;

	
	list<MST>* pMSTEdge_list;

public:

	
	enum algorithm_t {PRIM, KRUSKAL};

	
	enum style_t {NUMERIC, LOWERCASE, UPPERCASE};

	
	MST():from(0),
		  to(0),
		  distance(0),
		  mst_distance(0),
		  pMSTEdge_list(nullptr) {
	}

	
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

	
	
	void PrimMST(Graph);

	
	
	void KruskalMST(Graph);

	
	
	int k_Cluster(Graph, int);

	
	void print_MST(style_t, algorithm_t);

};	



#endif 
