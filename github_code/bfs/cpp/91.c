#include <iostream>
#include <list>

using namespace std;

// Represents a directed graph with a adjacency list
class Graph{

	int num_of_vertices;
	list<int>* adjacency_list;

	public:

		// Constructor
		Graph(int num_of_vertices);

		// Add edge between v1 and v2 vertices
		void add_edge(int v1, int v2);

		// BFS traversal from given vertice
		void BFS(int vertice);
};

Graph::Graph(int num_of_vertices){
	this->num_of_vertices = num_of_vertices;
	adjacency_list = new list<int>[num_of_vertices];
}

void Graph::add_edge(int v1, int v2){
	adjacency_list[v1].push_back(v2);
}

void Graph::BFS(int vertice){

	// A bool array indicates a given vertice is visited or not
	bool visited[this->num_of_vertices];

	// Initialize the bool array
	for(int i = 0; i < this->num_of_vertices; i++)
		visited[i] = false;

	// For BFS traversal a queue is required
	// First from a given vertice adjacent vertices are added to queue
	// then one by one adjacent vertices of the added vertices added to queue
	list<int> queue;

	// Mark the current vertice as visited and add to the queue
	visited[vertice] = true;
	queue.push_back(vertice);

	// Let's traverse the graph
	while(!queue.empty()){

		// Deque next node
		int current_node = queue.front();
		cout << current_node << "->";
		queue.pop_front();

		for(list<int>::iterator it = this->adjacency_list[current_node].begin();
			it != this->adjacency_list[current_node].end(); it++){

			if(visited[*it] == false){
				visited[*it] = true;
				queue.push_back(*it);
			}
		}
	} 
}

int main(){

	Graph a_graph(5);

	a_graph.add_edge(0, 1);
	a_graph.add_edge(0, 2);
	a_graph.add_edge(1, 2);
	a_graph.add_edge(1, 4);
	a_graph.add_edge(2, 0);
	a_graph.add_edge(2, 3);
	a_graph.add_edge(3, 3);
	a_graph.add_edge(4, 3);

	a_graph.BFS(2);

	return 0;
}

