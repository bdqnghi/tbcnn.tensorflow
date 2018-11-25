#include <iostream>
#include <list>

using namespace std;


class Graph{

	int num_of_vertices;
	list<int>* adjacency_list;

	public:

		
		Graph(int num_of_vertices);

		
		void add_edge(int v1, int v2);

		
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

	
	bool visited[this->num_of_vertices];

	
	for(int i = 0; i < this->num_of_vertices; i++)
		visited[i] = false;

	
	
	
	list<int> queue;

	
	visited[vertice] = true;
	queue.push_back(vertice);

	
	while(!queue.empty()){

		
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

