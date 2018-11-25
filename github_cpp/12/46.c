
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


class MSTNode {

private:

	int from;
	int to;
	int distance;

public:

	
	MSTNode():from(0),
			  to(0),
			  distance(0) {
	}

	
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

};	



class Graph {

private:

	
	int vertices;
	
	int edges;

	
	int mst_distance;

	
	int shortest_path_distance;

	
	vector< vector<int> > graph;

	
	list<int>* pNeighbors_list;

	
	list<MSTNode>* pMSTEdge_list;

	
	list<int>* pPath_list;

public:

	
	enum style_t {NUMERIC, LOWERCASE, UPPERCASE};

	
	enum algorithm_t {PRIM, KRUSKAL};

	

	
	Graph();

	
	Graph(const int);

	
	Graph(string);

	
	~Graph();


	

	
	int V();

	
	int E();

	
	bool adjacent(int, int);

	
	list<int>* neighbors(int);

	
	void add(int, int);

	
	void remove(int, int);

	
	int get_edge_value(int, int);

	
	void set_edge_value(int, int, int);

	
	double get_density();

	
	int get_shortest_path_distance();

	
	void genPathNodeList(vector<int>&, int);

	
	void getShortestPath(const int, const int);

	
	
	void PrimMST();

	
	
	void KruskalMST();

	
	bool is_connected(const int);

	
	void print_matrix(style_t);

	
	void print_edge_list(style_t);

	
	void print_stats();

	
	void print_MST(style_t, algorithm_t);

	
	void print_ShortestPath();

		
	void print_graph(style_t, algorithm_t);

};	





Graph::Graph():vertices(50),
		edges(0),
		mst_distance(0),
		shortest_path_distance(0),
		pNeighbors_list(nullptr),
		pMSTEdge_list(nullptr),
		pPath_list(nullptr) {

	
	graph.resize(vertices);

	
	fill(graph.begin(), graph.end(), vector<int>(vertices));

}	



Graph::Graph(const int SIZE):vertices(SIZE),
					  edges(0),
					  mst_distance(0),
					  shortest_path_distance(0),
					  pNeighbors_list(nullptr),
					  pMSTEdge_list(nullptr),
					  pPath_list(nullptr) {

	
	if (SIZE < 2)
		return;

	
	graph.resize(SIZE);

	
	fill(graph.begin(), graph.end(), vector<int>(SIZE));

}	



Graph::Graph(string file_name):vertices(0),
						edges(0),
						mst_distance(0),
						shortest_path_distance(0),
						pNeighbors_list(nullptr),
						pMSTEdge_list(nullptr),
						pPath_list(nullptr) {


	
	ifstream data_file(file_name);
	if (!data_file) {
		cerr << "Couldn't open file: " << file_name << endl;
		return;
	}

	
	istream_iterator<int> input(data_file);
	istream_iterator<int> eos;

	
	if (input != eos) {
		vertices = *input++;
		edges = *input++;
	}

	
	if (vertices < 2 || edges < (vertices - 1)) {
		cerr << "Invalid Graph:" << endl << endl;
		return;
	}

	
	graph.resize(vertices);

	
	fill(graph.begin(), graph.end(), vector<int>(vertices));

	
	int tail, head, distance;

	
	for (int i = 0; i < edges; i++) {

		
		tail = *input++;
		head = *input++;
		distance = *input++;

		
		graph[tail-1][head-1] = distance;
		graph[head-1][tail-1] = distance;

	}	

}	


Graph::~Graph() {

	
	if (pNeighbors_list != nullptr)
		delete pNeighbors_list;

	
	if (pMSTEdge_list != nullptr) {
		delete pMSTEdge_list;
	}

	
	if (pPath_list != nullptr)
		delete pPath_list;

}	





int Graph::V() {
	return vertices;
}


int Graph::E() {
	return edges;
}


bool Graph::adjacent(int x, int y) {
	
	if (x < 0 || x >= vertices || y < 0 || y >= vertices)
		return false;
	
	return (graph[x][y] != 0);
}


list<int>* Graph::neighbors(int x) {

	
	if (x < 0 || x >= vertices)
		return nullptr;

	
	if (pNeighbors_list == nullptr)
		pNeighbors_list = new list<int>;
	else
		
		pNeighbors_list->clear();

	
	for (auto &y : graph[x]) {
		if (y != 0) {
			pNeighbors_list->push_back(y);
		}
	}

	
	return pNeighbors_list;
}


void Graph::add(int x, int y) {

	
	if (x < 0 || x >= vertices || y < 0 || y >= vertices)
		return;

	
	graph[x][y] =  1;

	
	edges++;
}


void Graph::remove(int x, int y) {

	
	if (x < 0 || x >= vertices || y < 0 || y >= vertices)
		return;

	
	if (graph[x][y] != 0)
		edges--;

	
	graph[x][y] = 0;
}


int Graph::get_edge_value(int x, int y) {

	
	if (x < 0 || x >= vertices || y < 0 || y >= vertices)
		return 0;

	
	return graph[x][y];
}


void Graph::set_edge_value(int x, int y, int a) {

	
	if (x < 0 || x >= vertices || y < 0 || y >= vertices)
		return;

	
	if (graph[x][y] == 0)
		edges++;

	
	graph[x][y] = a;
}


double Graph::get_density() {

	
	return (edges * 1.0) / (vertices * vertices);

}


int Graph::get_shortest_path_distance() {

	
	return shortest_path_distance;

}


void Graph::genPathNodeList(vector<int>& path_list, int node) {

	
	if (pPath_list == nullptr)
		pPath_list = new list<int>;
	
	else
		pPath_list->clear();

	
	if(node == 0) {
		pPath_list->push_back(0);
	}
	
	else if(path_list.at(node) == -1)
		return;
	
	else {
		Graph::genPathNodeList(path_list, path_list.at(node));
		
		pPath_list->push_back(node);
	}

}	


void Graph::getShortestPath(const int start, const int end) {

	const bool DEBUG = false;

	const int MAX_DIST = 999999;

	
	int size = vertices;

	
	vector<bool>  visited(size, false);
	vector<int> node_dist(size, MAX_DIST);

	
	vector<int>* pNode_list = new vector<int>(size, -1);

	
	node_dist[start] = 0;

	
	int count = 0;

	
	while(count < size) {

		int minDistance = MAX_DIST;
		int closestNode = 0;

		
		for(int i = 0; i < size; i++) {
			if((!visited[i]) && (minDistance >= node_dist[i])) {
				minDistance = node_dist[i];
				closestNode = i;
			}
		}

		
		visited[closestNode] = true;

		if (DEBUG) {
			cout << "count = " << count << endl;
			cout << "closestNode = " << closestNode << endl;
			cout << "minDistance = " << minDistance << endl;
		}

		
		for(int i = 0; i < size; i++) {

			
			int cur_distance = node_dist[closestNode] + graph[closestNode][i];

			
			if (!visited[i] && (graph[closestNode][i] > 0) ) {

				
				if (node_dist[i] > cur_distance) {

					
					node_dist[i] = cur_distance;

					
					pNode_list->at(i) = closestNode;
				}
			}
		}

		
		count++;
	}

	
	shortest_path_distance = node_dist[end];
	if (shortest_path_distance == MAX_DIST)
		shortest_path_distance = 0;
	else
		shortest_path_distance -= node_dist[start];

	
	genPathNodeList(*pNode_list, end);

	
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

}	



void Graph::PrimMST() {

	
	vector<bool> visited(vertices, false);

	
	if (pMSTEdge_list == nullptr)
		pMSTEdge_list = new list<MSTNode>;
	
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

						
						if(graph[from][to] && (graph[from][to] <= min_dist)) {

							
							min_dist = graph[from][to];

							
							min_from = from;
							min_to = to;
						}
					}
				}
			}
		}

		
		visited[min_to] = true;

		
		pMSTEdge_list->push_back(MSTNode(min_from, min_to, min_dist));

		
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

void Graph::KruskalMST() {

	const bool DEBUG = false;

	
	list< pair<int, pair<int, int>> > edges;

	
	int size = vertices;

	
	vector<int> rank(size, 0);
	vector<int> parent(size);

	
	for (int i = 0; i < size; ++i)
		parent[i] = i;

	
	if (pMSTEdge_list == nullptr)
		pMSTEdge_list = new list<MSTNode>;
	else
		pMSTEdge_list->clear();

	
	mst_distance = 0;

	
	int remaining = size - 1;

	
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			if (int cost = graph[row][col])
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

		
		pMSTEdge_list->push_back(MSTNode(edge.second.first,
										 edge.second.second,
										 edge.first));

		
		mst_distance += edge.first;

		
		if (!--remaining)
			break;
	}

	
	if (remaining)
		mst_distance = numeric_limits<int>::infinity();

}	



bool Graph::is_connected(const int SIZE) {

	
	int old_size = 0;
	int closed_size = 0;

	
	vector<bool> open(SIZE, false);
	vector<bool> closed(SIZE, false);

	
	open[0] = true;

	
	while (closed_size < SIZE) {
		for (int i = 0; i < SIZE; ++i) {
			old_size = closed_size;
			if (open[i] && (closed[i] == false)) {
				closed[i] = true;
				closed_size++;

				
				for (int j = 0; j < SIZE; ++j)
					open[j] == open[j] || (graph[i][j] != 0);
			}
		}

		
		if (closed_size == SIZE) {
			
			open.~vector();
			closed.~vector();

			return true;
		}
		if (old_size == closed_size) {
			
			open.~vector();
			closed.~vector();

			return false;
		}
	}

	
	return false;

}	

void Graph::print_matrix(style_t style) {

	
	cout << "Adjacency Matrix:" << endl << endl;

	
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
	
	i = 0;
	for (auto &x : graph){
		cout.width(3);
		
		if (style == NUMERIC)
			cout << i++;
		if (style == LOWERCASE)
			cout << static_cast<char>(97 + i++);
		if (style == UPPERCASE)
			cout << static_cast<char>(65 + i++);
		
		for (auto &y : x) {
			cout.width(3);
			cout << y;
		}
		cout << endl;
	}
	cout << endl;

}	


void Graph::print_edge_list(style_t style) {

	
	cout << "Edge List:" << endl << endl;

	
	int i = 0;
	for (auto &x : graph) {
		if (style == NUMERIC)
			cout << " " << i++;
		if (style == LOWERCASE)
			cout << " " << static_cast<char>(97 + i++);
		if (style == UPPERCASE)
			cout << " " << static_cast<char>(65 + i++);
		
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

}	


void Graph::print_stats() {

	cout << endl;

	
	cout << "vertices = " << vertices << endl;

	
	cout << "edges = " << edges << endl;

	
	cout << "density = " << get_density() << endl;

	cout << endl;

}	


void Graph::print_MST(style_t style, algorithm_t algorithm) {

	bool first = true;

	
	if (algorithm == PRIM)
		cout << "Prim ";
	else
		cout << "Kruskal ";

	cout << "MST Edges and distance:" << endl << endl;

	
	if (pMSTEdge_list == nullptr) {
		cout << "distance = " << mst_distance << endl;
		return ;
	}

	
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
	
	cout << " = " << mst_distance << endl;

}	


void Graph::print_ShortestPath() {

	
	cout << endl << "Shortest Path:" << endl;

	
	for (auto i : *pPath_list) {
		if (i == 0)
			cout << i;
		else
			cout << " -> " << i;
	}

	
	cout << " = " << shortest_path_distance;

}	


void Graph::print_graph(style_t style, algorithm_t algorithm) {

	
	print_stats();

	
	print_matrix(style);

	
	print_edge_list(style);

	
	print_MST(style, algorithm);

	
	print_ShortestPath();

}	

