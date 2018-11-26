#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>
#include "../Data_Processors/GraphLoader.h"
#include "../Data_Processors/AdjList.h"
#include "../Data_Processors/AdjMatrix.h"
#include<cstdlib>
#include<map>
#include<queue>
#define INF 1.7976931348623e+308
using namespace std;
//Graph class
class Graph{
	typedef GraphLoader graph;
	typedef pair<double,bool> T;
private:
    AdjList G_L;   //Adjacent List
	graph Set;  
	AdjMatrix<T> G_M;   //Adjacent Matrix
public:
    Graph()
    Graph(graph& G,int selection=0);   //Constructor
	void load();
	  //Find the first adjacent vertex
   //Find the next adjacent vertex
	virtual bool IsExistAdj(int node);    //Discriminate if the node exist adjacent vertex
	virtual double operator()(int start,int end);
	virtual int first_vertex(int u);
	virtual int next_vertex(int u,int v);
	int Vertex();
	virtual bool is_strongly_connected();
	virtual int InDegree(int u);
	virtual int OutDegree(int u);
	virtual int degree(int u);
	virtual void set_tag(int start,int end);
	virtual bool get_tag(int start,int end);
	virtual queue<int> Dijkstra(int u);   //Dijkstra Shortest-paths Algorithm
	virtual int Prim();    //Prim's Minimum-spanning-tree Algorithm
	virtual int Kruskal(); //Kruskal's Minimum-spanning-tree Algorithm
	virtual queue<int> TopologicalSort();  //Topological Sort 
	virtual queue<int> Bellman_Ford(int u); //Bellman-Ford Algorithm
	virtual queue<int> BFT(); //Breadth-First Traversal
	virtual queue<int> DFT();  //Depth-First Traversal
	virtual queue<int> EulerCycuit();   //Find Euler path
	virtual queue<int> CriticalPath();  //Find a critical path
	virtual queue<int> MaxFlow();  //Find the max flow
};
//selection=0: directed graph
//selection=1: undirected graph
//Initial value: selection=0
//Load a GraphLoader object for parameter
Graph::Graph(){
	G_L=NULL;
	G_M=NULL;
}
Graph::Graph(GraphLoader& g,int selection){
	if(selection==0){
		G_L.build(g);
	}
	else{
		G_M.build(g);
	}
}

//selection=0: directed graph
//selection=1: undirected graph
void load(GraphLoader& g,int selection){
    if(selection==0){
		G_L.build(g);
	}
	else{
		G_M.build(g);
	}
}

#include "Digraph.h"
#include "graph.h"
#endif
