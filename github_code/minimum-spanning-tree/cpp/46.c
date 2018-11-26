
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string.h>
#include <list>
#include <vector>
#include <limits>
#include <utility>

using namespace std;

// Class for the MST Node list
class MSTNode {

private:

	int from;
	int to;
	int distance;

public:

	// Default constructor
	MSTNode():from(0),
			  to(0),
			  distance(0) {
	}

	// Value constructor
	MSTNode(int from, int to, int distance):from(from),
											to(to),
											distance(distance) {
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

};	// end - MSTNode class


// Class for the Adjacency Matrix graph representation
class Graph {

private:

	// Number of vertices
	int vertices;
	// Number of edges
	int edges;

	// Minimum-spanning-tree distance
	int mst_distance;

	// Shortest path distance
	int shortest_path_distance;

	// The Adjacency Matrix
	vector< vector<int> > graph;

	// The neighboring node list
	list<int>* pNeighbors_list;

	// The MST node list
	list<MSTNode>* pMSTEdge_list;

	// List of shortest path nodes
	list<int>* pPath_list;

public:

	// Output style
	enum style_t {NUMERIC, LOWERCASE, UPPERCASE};

	// MST Algorithm
	enum algorithm_t {PRIM, KRUSKAL};

	// Constructors

	// Default - vertices = 50
	Graph();

	// Generates a graph of the specified size
	Graph(const int);

	// Generates a graph from data contained in the specified file
	Graph(string);

	// Destructor
	~Graph();


	// Methods

	// Return the number of vertices
	int V();

	// Return the number of edges
	int E();

	// Return true if vertices are adjacent
	bool adjacent(int, int);

	// Return a list of connected vertices
	list<int>* neighbors(int);

	// Add the specified x->y edge
	void add(int, int);

	// Remove the specified x->y edge
	void remove(int, int);

	// Return the edge value
	int get_edge_value(int, int);

	// Set the edge value
	void set_edge_value(int, int, int);

	// Get graph density
	double get_density();

	// Get the shortest path distance
	int get_shortest_path_distance();

	// Generate the path node list
	void genPathNodeList(vector<int>&, int);

	// Dijkstra shortest-path algorithm
	void getShortestPath(const int, const int);

	// Calculate the minimum-spanning-tree distance
	// An implementation of the Jarnik-Prim algorithm
	void PrimMST();

	// Calculate the minimum-spanning-tree distance
	// An implementation of the Kruskal algorithm
	void KruskalMST();

	// is_connected() function
	bool is_connected(const int);

	// Print the Adjacency Matrix
	void print_matrix(style_t);

	// Print the Edge List
	void print_edge_list(style_t);

	// Print the graph statistics
	void print_stats();

	// Print the Minimum-Spanning-Tree
	void print_MST(style_t, algorithm_t);

	// Print the shortest path
	void print_ShortestPath();

		// Print all output
	void print_graph(style_t, algorithm_t);

};	// end - Graph class

/*==========================================================================*/

// Class methods

Graph::Graph():vertices(50),
		edges(0),
		mst_distance(0),
		shortest_path_distance(0),
		pNeighbors_list(nullptr),
		pMSTEdge_list(nullptr),
		pPath_list(nullptr) {

	// Generate the graph columns
	graph.resize(vertices);

	// Insert the graph rows
	fill(graph.begin(), graph.end(), vector<int>(vertices));

}	// end - Graph()

// Generates a graph of the specified size
// size must be specified to distinguish this from the default constructor
Graph::Graph(const int SIZE):vertices(SIZE),
					  edges(0),
					  mst_distance(0),
					  shortest_path_distance(0),
					  pNeighbors_list(nullptr),
					  pMSTEdge_list(nullptr),
					  pPath_list(nullptr) {

	// Check for a valid size
	if (SIZE < 2)
		return;

	// Generate the graph columns
	graph.resize(SIZE);

	// Insert the graph rows
	fill(graph.begin(), graph.end(), vector<int>(SIZE));

}	// end - Graph(size)

// Generates a graph from data contained in the specified file
//Graph::Graph(string file_name):vertices(0),
Graph::Graph(string file_name):vertices(0),
						edges(0),
						mst_distance(0),
						shortest_path_distance(0),
						pNeighbors_list(nullptr),
						pMSTEdge_list(nullptr),
						pPath_list(nullptr) {


	// Setup a file stream
	ifstream data_file(file_name);
	if (!data_file) {
		cerr << "Couldn't open file: " << file_name << endl;
		return;
	}

	// Define input stream iterators
	istream_iterator<int> input(data_file);
	istream_iterator<int> eos;

	// Get the first line of the file = vertices/edges
	if (input != eos) {
		vertices = *input++;
		edges = *input++;
	}

	// Check for a valid graph
	if (vertices < 2 || edges < (vertices - 1)) {
		cerr << "Invalid Graph:" << endl << endl;
		return;
	}

	// Generate the graph columns
	graph.resize(vertices);

	// Insert the graph rows
	fill(graph.begin(), graph.end(), vector<int>(vertices));

	// Tail, head and distance variables
	int tail, head, distance;

	// Loop through the file
	for (int i = 0; i < edges; i++) {

		// Get the edge values
		tail = *input++;
		head = *input++;
		distance = *input++;

		// Add to the (undirected) graph
		graph[tail-1][head-1] = distance;
		graph[head-1][tail-1] = distance;

	}	// end - while(*input != NULL)

}	// end - read_graph()

// Destructor
Graph::~Graph() {

	// Deallocate the neighboring node list
	if (pNeighbors_list != nullptr)
		delete pNeighbors_list;

	// Deallocate the MST edge list
	if (pMSTEdge_list != nullptr) {
		delete pMSTEdge_list;
	}

	// Deallocate the shortest path node list
	if (pPath_list != nullptr)
		delete pPath_list;

}	// end - ~Graph()


// Methods

// Return the number of vertices
int Graph::V() {
	return vertices;
}

// Return the number of edges
int Graph::E() {
	return edges;
}

// Return true if vertices are adjacent
bool Graph::adjacent(int x, int y) {
	// Check for valid arguments
	if (x < 0 || x >= vertices || y < 0 || y >= vertices)
		return false;
	// Return true if edge exists
	return (graph[x][y] != 0);
}

// Return a list of connected vertices
list<int>* Graph::neighbors(int x) {

	// Check for valid node index
	if (x < 0 || x >= vertices)
		return nullptr;

	// Generate the neighbors list if necessary
	if (pNeighbors_list == nullptr)
		pNeighbors_list = new list<int>;
	else
		// Clear the list
		pNeighbors_list->clear();

	// Add neighbors to the list
	for (auto &y : graph[x]) {
		if (y != 0) {
			pNeighbors_list->push_back(y);
		}
	}

	// return the list
	return pNeighbors_list;
}

// Add the specified x->y edge
void Graph::add(int x, int y) {

	// Check for valid arguments;
	if (x < 0 || x >= vertices || y < 0 || y >= vertices)
		return;

	// Set the x->y value to 1
	graph[x][y] =  1;

	// Increment the number of edges
	edges++;
}

// Remove the specified x->y edge
void Graph::remove(int x, int y) {

	// Check for valid arguments;
	if (x < 0 || x >= vertices || y < 0 || y >= vertices)
		return;

	// If the edge exists decrement the edge count
	if (graph[x][y] != 0)
		edges--;

	// Set the x->y value to 0
	graph[x][y] = 0;
}

// Return the edge value
int Graph::get_edge_value(int x, int y) {

	// Check for valid arguments;
	if (x < 0 || x >= vertices || y < 0 || y >= vertices)
		return 0;

	// Return the x->y edge value
	return graph[x][y];
}

// Set the edge value
void Graph::set_edge_value(int x, int y, int a) {

	// Check for valid arguments;
	if (x < 0 || x >= vertices || y < 0 || y >= vertices)
		return;

	// If the edge doesn't exist increment the edge count
	if (graph[x][y] == 0)
		edges++;

	// Set the x->y value
	graph[x][y] = a;
}

// Get graph density
double Graph::get_density() {

	// Return the graph density
	return (edges * 1.0) / (vertices * vertices);

}

// Get graph density
int Graph::get_shortest_path_distance() {

	// Return the shortest path value
	return shortest_path_distance;

}

// Generate the path node list
void Graph::genPathNodeList(vector<int>& path_list, int node) {

	// Generate if necessary
	if (pPath_list == nullptr)
		pPath_list = new list<int>;
	// Else clear it
	else
		pPath_list->clear();

	// At starting node
	if(node == 0) {
		pPath_list->push_back(0);
	}
	// No path to this node
	else if(path_list.at(node) == -1)
		return;
	// Recurse to next node
	else {
		Graph::genPathNodeList(path_list, path_list.at(node));
		// Put the node into path node list
		pPath_list->push_back(node);
	}

}	// end - genPathNodeList()

// Dijkstra shortest-path algorithm
void Graph::getShortestPath(const int start, const int end) {

	const bool DEBUG = false;

	const int MAX_DIST = 999999;

	// Calculate the graph size
	int size = vertices;

	// Define and initialize the local lists
	vector<bool>  visited(size, false);
	vector<int> node_dist(size, MAX_DIST);

	// Generate a local path node vector
	vector<int>* pNode_list = new vector<int>(size, -1);

	// Set the start node distance to 0
	node_dist[start] = 0;

	// Loop counter
	int count = 0;

	// Loop through the vertices
	while(count < size) {

		int minDistance = MAX_DIST;
		int closestNode = 0;

		// Find the closest adjacent node
		for(int i = 0; i < size; i++) {
			if((!visited[i]) && (minDistance >= node_dist[i])) {
				minDistance = node_dist[i];
				closestNode = i;
			}
		}

		// Indicate this node has been visited
		visited[closestNode] = true;

		if (DEBUG) {
			cout << "count = " << count << endl;
			cout << "closestNode = " << closestNode << endl;
			cout << "minDistance = " << minDistance << endl;
		}

		// Loop through the nodes
		for(int i = 0; i < size; i++) {

			// Get the distance to this node from the start node
			int cur_distance = node_dist[closestNode] + graph[closestNode][i];

			// If the node has not been visited and the distance is not 0
			if (!visited[i] && (graph[closestNode][i] > 0) ) {

				// If this node is closer
				if (node_dist[i] > cur_distance) {

					// Put the current distance into the list
					node_dist[i] = cur_distance;

					// Put the current node into the path list
					pNode_list->at(i) = closestNode;
				}
			}
		}

		// Move to the next node
		count++;
	}

	// Set the shortest path distance
	shortest_path_distance = node_dist[end];
	if (shortest_path_distance == MAX_DIST)
		shortest_path_distance = 0;
	else
		shortest_path_distance -= node_dist[start];

	// Generate the path node list
	genPathNodeList(*pNode_list, end);

	// Test output
	if (DEBUG) {
		cout << "The distances to the other nodes are:" << endl;
		for(int i = start; i <= end; i++) {
			cout << i << " : " << node_dist[i] << endl;
		}
		cout << endl;
		cout << "The path node list is:" << endl;
		for (auto i : *pNode_list) {
			if (i == 0)
				cout << i;
			else
				cout << " -> " << i;
		}
		cout << endl;
	}

}	// end - getShortestPath()

// Calculate the minimum-spanning-tree distance
// An implementation of the Jarnik-Prim algorithm
void Graph::PrimMST() {

	// Initialize the node visited array
	vector<bool> visited(vertices, false);

	// Generate MST edge list if necessary
	if (pMSTEdge_list == nullptr)
		pMSTEdge_list = new list<MSTNode>;
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

						// If this is a smaller (non-zero) distance
						if(graph[from][to] && (graph[from][to] <= min_dist)) {

							// Set as new minimum
							min_dist = graph[from][to];

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
		pMSTEdge_list->push_back(MSTNode(min_from, min_to, min_dist));

		// Increment the MST distance
		mst_distance += min_dist;

		// Increment the number of MST edges
		num_edges += 1;
	}

}	// end - PrimMST()


// Calculate the minimum-spanning-tree distance
// An implementation of the Kruskal algorithm

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

void Graph::KruskalMST() {

	const bool DEBUG = false;

	// The edge list
	list< pair<int, pair<int, int>> > edges;

	// Graph size
	int size = vertices;

	// Generate necessary structures
	vector<int> rank(size, 0);
	vector<int> parent(size);

	// Initialize the parent vector
	for (int i = 0; i < size; ++i)
		parent[i] = i;

	// Generate MST edge list if necessary
	if (pMSTEdge_list == nullptr)
		pMSTEdge_list = new list<MSTNode>;
	else
		pMSTEdge_list->clear();

	// Initialize the total distance
	mst_distance = 0;

	// Initialize the remaining node count
	int remaining = size - 1;

	// Create the edge list
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			if (int cost = graph[row][col])
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
		int u = find_set(parent, edge.second.first);
		int v = find_set(parent, edge.second.second);

		// If they are in the same tree - skip
		if (u == v)
			continue;

		// Merge the trees
		merge_set(rank, parent, u, v);

		// Put this node into the edge list
		pMSTEdge_list->push_back(MSTNode(edge.second.first,
										 edge.second.second,
										 edge.first));

		// Accumulate the total cost
		mst_distance += edge.first;

		// If nothing remaining - exit loop
		if (!--remaining)
			break;
	}

	// If anything remaining - no mst
	if (remaining)
		mst_distance = numeric_limits<int>::infinity();

}	// end - KruskalMST()


// is_connected() function
bool Graph::is_connected(const int SIZE) {

	// Initialize variables
	int old_size = 0;
	int closed_size = 0;

	// Open and closed lists
	vector<bool> open(SIZE, false);
	vector<bool> closed(SIZE, false);

	// Put root into open list
	open[0] = true;

	// Add to closed list
	while (closed_size < SIZE) {
		for (int i = 0; i < SIZE; ++i) {
			old_size = closed_size;
			if (open[i] && (closed[i] == false)) {
				closed[i] = true;
				closed_size++;

				// Add to open list
				for (int j = 0; j < SIZE; ++j)
					open[j] == open[j] || (graph[i][j] != 0);
			}
		}

		// Done?
		if (closed_size == SIZE) {
			// Clean up
			open.~vector();
			closed.~vector();

			return true;
		}
		if (old_size == closed_size) {
			// Clean up
			open.~vector();
			closed.~vector();

			return false;
		}
	}

	// Return
	return false;

}	// end - is_connected()

void Graph::print_matrix(style_t style) {

	// Output the title
	cout << "Adjacency Matrix:" << endl << endl;

	// Output top header line
	cout << "   ";
	int i = 0;
	for (auto x : graph) {
		cout.width(3);
		if (style == NUMERIC)
			cout << i++;
		if (style == LOWERCASE)
			cout << static_cast<char>(97 + i++);
		if (style == UPPERCASE)
			cout << static_cast<char>(65 + i++);
	}
	cout << endl;
	// Output the graph rows
	i = 0;
	for (auto &x : graph){
		cout.width(3);
		// Output vertex index
		if (style == NUMERIC)
			cout << i++;
		if (style == LOWERCASE)
			cout << static_cast<char>(97 + i++);
		if (style == UPPERCASE)
			cout << static_cast<char>(65 + i++);
		// Output vertex values
		for (auto &y : x) {
			cout.width(3);
			cout << y;
		}
		cout << endl;
	}
	cout << endl;

}	// end - print_matrix()

// Print the Edge List
void Graph::print_edge_list(style_t style) {

	// Output the title
	cout << "Edge List:" << endl << endl;

	// Output the rows
	int i = 0;
	for (auto &x : graph) {
		if (style == NUMERIC)
			cout << " " << i++;
		if (style == LOWERCASE)
			cout << " " << static_cast<char>(97 + i++);
		if (style == UPPERCASE)
			cout << " " << static_cast<char>(65 + i++);
		// Output the columns
		int j = 0;
		for (auto &y : x) {
			if (y != 0) {
				if (style == NUMERIC)
					cout << " -> " << j << ":" << y;
				if (style == LOWERCASE)
					cout << " -> "  << static_cast<char>(97 + j) << ":" << y;
				if (style == UPPERCASE)
					cout << " -> "  << static_cast<char>(65 + j) << ":" << y;
			}
			j++;
		}
		cout << endl;
	}
	cout << endl;

}	// end - print_edge_list()

// Print the graph statistics
void Graph::print_stats() {

	cout << endl;

	// Print the number of vertices
	cout << "vertices = " << vertices << endl;

	// Print the number of edges
	cout << "edges = " << edges << endl;

	// Print the graph density
	cout << "density = " << get_density() << endl;

	cout << endl;

}	// end - print_stats()

// Print the Minimum-Spanning-Tree
void Graph::print_MST(style_t style, algorithm_t algorithm) {

	bool first = true;

	// Output the title
	if (algorithm == PRIM)
		cout << "Prim ";
	else
		cout << "Kruskal ";

	cout << "MST Edges and distance:" << endl << endl;

	// Check for an edge list
	if (pMSTEdge_list == nullptr) {
		cout << "distance = " << mst_distance << endl;
		return ;
	}

	// Iterate through the MSTNodes list
	for (auto &i : *pMSTEdge_list) {

		// Get the values
		int from = i.get_from();
		int to   = i.get_to();

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
	cout << " = " << mst_distance << endl;

}	// end - print_MST()

// Print the shortest path node list and distance
void Graph::print_ShortestPath() {

	// print the header
	cout << endl << "Shortest Path:" << endl;

	// Print the nodes
	for (auto i : *pPath_list) {
		if (i == 0)
			cout << i;
		else
			cout << " -> " << i;
	}

	// Print the distance
	cout << " = " << shortest_path_distance;

}	// end - printPath()

// Print all output
void Graph::print_graph(style_t style, algorithm_t algorithm) {

	// Print graph statistics
	print_stats();

	// Print the Adjacency matrix
	print_matrix(style);

	// Print the edge list
	print_edge_list(style);

	// Print the MST nodes and distance
	print_MST(style, algorithm);

	// Print the shortest path nodes and distance
	print_ShortestPath();

}	// end - print_graph()

