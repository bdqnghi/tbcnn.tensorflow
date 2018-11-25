

#ifndef MST_CLASS_H_
#define MST_CLASS_H_

#include <vector>

using namespace std;

#include "Graph.h"



template <class T>
class MST {

private:

	int from;
	int to;
	T distance;

	
	T mst_distance;

	
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

	
	
	void PrimMST(Graph<T>);

	
	
	void KruskalMST(Graph<T>);

	
	
	T k_Cluster(Graph<T>, int);

	void create_set(vector<T>&, vector<T>&, int);
	void merge_set(vector<T>&, vector<T>&, int, int);
	T find_set(vector<T>&, int);


	
	void print_MST(style_t, algorithm_t);

};	


#endif 
