


using namespace std;

#include "MST.h"

#include <limits>




void MST::PrimMST(Graph graph) {

	
	int vertices = graph.Vertices();

	
	vector<bool> visited(vertices, false);

	
	if (pMSTEdge_list == nullptr)
		pMSTEdge_list = new list<MST>;
	
	else
		pMSTEdge_list->clear();

	
	int num_edges = 0;

	
	visited[0] = true;

	
	while(num_edges < vertices - 1){

		
		int min_dist = 999999;

		
		int min_from , min_to;

		
		for(int from = 0; from < vertices; ++from) {

			
			if(visited[from]) {

				
				for(int to = 0; to < vertices; ++to){

					
					if(!visited[to]) {

						int edge_distance = graph.get_edge_value(from, to);

						
						if (edge_distance && (edge_distance <= min_dist)) {

							
							min_dist = edge_distance;

							
							min_from = from;
							min_to = to;
						}
					}
				}
			}
		}

		
		visited[min_to] = true;

		
		pMSTEdge_list->push_back(MST(min_from, min_to, min_dist));

		
		mst_distance += min_dist;

		
		num_edges += 1;
	}

}	





void create_set(vector<int>& pRank, vector<int>& pParent, int x) {
	pRank.at(x) = 0;
	pParent.at(x) = x;
}

int find_set(vector<int>& pParent, int x) {
	int at_x = pParent.at(x);
	if (x != at_x)
		pParent.at(x) = find_set(pParent, at_x);

	return pParent.at(x);
}

void merge_set(vector<int>& pRank, vector<int>& pParent, int x, int y) {
	int at_x = pRank.at(x);
	int at_y = pRank.at(y);
	if (at_x > at_y)
		pParent.at(y) = x;
	else
		pParent.at(x) = y;

	if (at_x == at_y)
		pRank.at(y) += 1;
}

void MST::KruskalMST(Graph graph) {

	const bool DEBUG = false;


	
	list< pair<int, pair<int, int>> > edges;

	
	int size = graph.Vertices();

	
	vector<int> rank(size, 0);
	vector<int> parent(size);

	
	for (int i = 0; i < size; ++i)
		parent[i] = i;

	
	if (pMSTEdge_list == nullptr)
		pMSTEdge_list = new list<MST>;
	else
		pMSTEdge_list->clear();

	
	mst_distance = 0;

	
	int remaining = size - 1;

	
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			if (int cost = graph.get_edge_value(row, col))
				edges.push_back((make_pair(cost, make_pair(row, col))));
		}
	}

	
	for(int i = 0; i < size; ++i)
		create_set(rank, parent, i);

	
	edges.sort();

	if (DEBUG) {
		for (auto &edge : edges) {
			cout << edge.second.first
				 << "->"
				 << edge.second.second
				 << ":"
				 << edge.first
				 << endl;
		}
	}

	
	for (auto& edge : edges) {

		
		int u = find_set(parent, edge.second.first);
		int v = find_set(parent, edge.second.second);

		
		if (u == v)
			continue;

		
		merge_set(rank, parent, u, v);

		
		pMSTEdge_list->push_back(MST(edge.second.first,
									 edge.second.second,
									 edge.first));

		
		mst_distance += edge.first;

		
		if (!--remaining)
			break;
	}

	
	if (remaining)
		mst_distance = numeric_limits<int>::infinity();

}	

int MST::k_Cluster(Graph graph, int k) {


	const bool DEBUG = true;

	
	list< pair<int, pair<int, int>> > edges;

	
	int size = graph.Vertices();

	
	int maximum_spacing = 1000000;

	
	vector<int> rank(size, 0);
	vector<int> parent(size);

	
	for (int i = 0; i < size; ++i)
		parent[i] = i;

	
	if (pMSTEdge_list == nullptr)
		pMSTEdge_list = new list<MST>;
	else
		pMSTEdge_list->clear();

	
	mst_distance = 0;

	
	int remaining = size - 1;

	
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			if (int cost = graph.get_edge_value(row, col))
				edges.push_back((make_pair(cost, make_pair(row, col))));
		}
	}

	
	for(int i = 0; i < size; ++i)
		create_set(rank, parent, i);

	
	edges.sort();

	if (DEBUG) {
		for (auto &edge : edges) {
			cout << edge.second.first
				 << "->"
				 << edge.second.second
				 << ":"
				 << edge.first
				 << endl;
		}
		cout << endl;
	}

	
	for (auto& edge : edges) {

		
		int u = find_set(parent, edge.second.first);
		int v = find_set(parent, edge.second.second);

		
		if (u == v)
			continue;

		
		merge_set(rank, parent, u, v);

		
		pMSTEdge_list->push_back(MST(edge.second.first,
									 edge.second.second,
									 edge.first));

		
		mst_distance += edge.first;

		
		if (--remaining == k-1)
			break;
	}

	
	for (auto &edge : edges) {

		
		if (find_set(parent, edge.second.first) == find_set(parent, edge.second.second))
			continue;

		
		if (edge.first < maximum_spacing)
			maximum_spacing = edge.first;

	}

	
	return maximum_spacing;

}	


void MST::print_MST(style_t style, algorithm_t algorithm) {

	bool first = true;

	
	if (pMSTEdge_list == nullptr) {
		cout << "No MST edge list" << endl;
		return ;
	}

	
	if (algorithm == PRIM)
		cout << "Prim ";
	else
		cout << "Kruskal ";

	cout << "MST Edges and distance:" << endl << endl;

	
	for (auto &i : *pMSTEdge_list) {

		
		int from = i.get_from();
		int to   = i.get_to();

		
		if (first) {
			if (style == NUMERIC)
				cout << from << ":" << to;
			if (style == LOWERCASE)
				cout << static_cast<char>(97 + from) << ":"
					 << static_cast<char>(97 + to);
			if (style == UPPERCASE)
				cout << static_cast<char>(65 + from) << ":"
					 << static_cast<char>(65 + to);
		} else {
			if (style == NUMERIC)
				cout << " - " << from << ":" << to;
			if (style == LOWERCASE)
				cout << " - "
					 << static_cast<char>(97 + from) << ":"
					 << static_cast<char>(97 + to);
			if (style == UPPERCASE)
				cout << " - "
					 << static_cast<char>(65 + from) << ":"
					 << static_cast<char>(65 + to);
		}

		
		first = false;
	}

	
	cout << " = " << mst_distance << endl << endl;

}	

