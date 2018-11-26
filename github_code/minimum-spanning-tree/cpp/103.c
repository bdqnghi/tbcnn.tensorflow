/*
 * MST.h
 *
 *  Created on: Oct 8, 2016
 *      Author: Shawn Flynn
 */

#ifndef MST_H_
#define MST_H_

#include "MST_class.h"


// Calculate the minimum-spanning-tree distance
// An implementation of the Jarnik-Prim algorithm
template <class T>
void MST<T>::PrimMST(Graph<T> graph) {

	// Initialize the number of vertices
	int vertices = graph.Vertices();

	// Initialize the node visited array
	vector<bool> visited(vertices, false);

	// Generate MST edge list if necessary
	if (pMSTEdge_list == nullptr)
		pMSTEdge_list = new list<MST>;
	// Else clear it
	else
		pMSTEdge_list->clear();

	// Number of edges in the MST
	int num_edges = 0;

	// Start at the first vertex
	visited[0] = true;

	// While were are not done
	while(num_edges < vertices - 1){

		// Initialize to large value
		int min_dist = 999999;

		// Indices of the minimum edge nodes
		int min_from , min_to;

		// Loop through the nodes
		for(int from = 0; from < vertices; ++from) {

			// If node has been visited
			if(visited[from]) {

				// Look for adjacent nodes
				for(int to = 0; to < vertices; ++to){

					// If this node has not been selected
					if(!visited[to]) {

						int edge_distance = graph.get_edge_value(from, to);

						// If this is a smaller (non-zero) distance
						if (edge_distance && (edge_distance <= min_dist)) {

							// Set as new minimum
							min_dist = edge_distance;

							// Save this node info
							min_from = from;
							min_to = to;
						}
					}
				}
			}
		}

		// Indicate this node has been visited
		visited[min_to] = true;

		// Put this node into the edge list
		pMSTEdge_list->push_back(MST(min_from, min_to, min_dist));

		// Increment the MST distance
		mst_distance += min_dist;

		// Increment the number of MST edges
		num_edges += 1;
	}

}	// end - PrimMST()


// Calculate the minimum-spanning-tree distance
// An implementation of the Kruskal algorithm
template <class T>
void MST<T>::create_set(vector<T>& pRank, vector<T>& pParent, int x) {
	pRank.at(x) = 0;
	pParent.at(x) = x;
}

template <class T>
T MST<T>::find_set(vector<T>& pParent, int x) {
	T at_x = pParent.at(x);
	if (x != at_x)
		pParent.at(x) = find_set(pParent, at_x);

	return pParent.at(x);
}

template <class T>
void MST<T>::merge_set(vector<T>& pRank, vector<T>& pParent, int x, int y) {
	T at_x = pRank.at(x);
	T at_y = pRank.at(y);
	if (at_x > at_y)
		pParent.at(y) = x;
	else
		pParent.at(x) = y;

	if (at_x == at_y)
		pRank.at(y) += 1;
}

template <class T>
void MST<T>::KruskalMST(Graph<T> graph) {

	const bool DEBUG = false;
//	const bool DEBUG = true;

	// The edge list
	list< pair<T, pair<T, T>> > edges;

	// Graph size
	int size = graph.Vertices();

	// Generate necessary structures
	vector<T> rank(size, 0);
	vector<T> parent(size);

	// Initialize the parent vector
	for (int i = 0; i < size; ++i)
		parent[i] = i;

	// Generate MST edge list if necessary
	if (pMSTEdge_list == nullptr)
		pMSTEdge_list = new list<MST>;
	else
		pMSTEdge_list->clear();

	// Initialize the total distance
	mst_distance = 0;

	// Initialize the remaining node count
	int remaining = size - 1;

	// Create the edge list
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			if (int cost = graph.get_edge_value(row, col))
				edges.push_back((make_pair(cost, make_pair(row, col))));
		}
	}

	// Create the parent set
	for(int i = 0; i < size; ++i)
		create_set(rank, parent, i);

	// Sort the edges
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

	// Iterate through the edges
	for (auto& edge : edges) {

		// Find the parent nodes
		T u = find_set(parent, edge.second.first);
		T v = find_set(parent, edge.second.second);

		// If they are in the same tree - skip
		if (u == v)
			continue;

		// Merge the trees
		merge_set(rank, parent, u, v);

		// Put this node into the edge list
		pMSTEdge_list->push_back(MST(edge.second.first,
									 edge.second.second,
									 edge.first));

		// Accumulate the total cost
		mst_distance += edge.first;

		// If nothing remaining - exit loop
		if (!--remaining)
			break;
	}

	// If anything remaining - no MST
	if (remaining)
		mst_distance = numeric_limits<int>::infinity();

}	// end - KruskalMST()

template <class T>
T MST<T>::k_Cluster(Graph<T> graph, int k) {

//	const bool DEBUG = false;
	const bool DEBUG = true;

	// The edge list
	list< pair<T, pair<T, T>> > edges;

	// Graph size
	int size = graph.Vertices();

	// Maximum spacing
	T maximum_spacing = 1000000;

	// Generate necessary structures
	vector<T> rank(size, 0);
	vector<T> parent(size);

	// Initialize the parent vector
	for (int i = 0; i < size; ++i)
		parent[i] = i;

	// Generate MST edge list if necessary
	if (pMSTEdge_list == nullptr)
		pMSTEdge_list = new list<MST>;
	else
		pMSTEdge_list->clear();

	// Initialize the total distance
	mst_distance = 0;

	// Initialize the remaining node count
	T remaining = size - 1;

	// Create the edge list
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			if (int cost = graph.get_edge_value(row, col))
				edges.push_back((make_pair(cost, make_pair(row, col))));
		}
	}

	// Create the parent set
	for(int i = 0; i < size; ++i)
		create_set(rank, parent, i);

	// Sort the edges
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

	// Iterate through the edges
	for (auto& edge : edges) {

		// Find the parent nodes
		T u = find_set(parent, edge.second.first);
		T v = find_set(parent, edge.second.second);

		// If they are in the same tree - skip
		if (u == v)
			continue;

		// Merge the trees
		merge_set(rank, parent, u, v);

		// Put this node into the edge list
		pMSTEdge_list->push_back(MST(edge.second.first,
									 edge.second.second,
									 edge.first));

		// Accumulate the total cost
		mst_distance += edge.first;

		// If k clusters remain - exit loop
		if (--remaining == k-1)
			break;
	}

	// Loop through the edges
	for (auto &edge : edges) {

		// Skip if they have the same parent
		if (find_set(parent, edge.second.first) == find_set(parent, edge.second.second))
			continue;

		// Check for smaller distance
		if (edge.first < maximum_spacing)
			maximum_spacing = edge.first;

	}

	// Return the maximum spacing
	return maximum_spacing;

}	// end - k_cluster()

// Print the Minimum-Spanning-Tree
template <class T>
void MST<T>::print_MST(style_t style, algorithm_t algorithm) {

	bool first = true;

	// Check for an edge list
	if (pMSTEdge_list == nullptr) {
		cout << "No MST edge list" << endl;
		return ;
	}

	// Output the title
	if (algorithm == PRIM)
		cout << "Prim ";
	else
		cout << "Kruskal ";

	cout << "MST Edges and distance:" << endl << endl;

	// Iterate through the MSTNodes list
	for (auto &i : *pMSTEdge_list) {

		// Get the values
		T from = i.get_from();
		T to   = i.get_to();

		// Output the node information
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

		// Clear the first flag
		first = false;
	}

	// Print the MST distance
	cout << " = " << mst_distance << endl << endl;

}	// end - print_MST()

#endif /* MST_H_ */
