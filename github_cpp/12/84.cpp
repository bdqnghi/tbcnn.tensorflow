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

class Graph{
	typedef GraphLoader graph;
	typedef pair<double,bool> T;
private:
    AdjList G_L;   
	graph Set;  
	AdjMatrix<T> G_M;   
public:
    Graph()
    Graph(graph& G,int selection=0);   
	void load();
	  
   
	virtual bool IsExistAdj(int node);    
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
	virtual queue<int> Dijkstra(int u);   
	virtual int Prim();    
	virtual int Kruskal(); 
	virtual queue<int> TopologicalSort();  
	virtual queue<int> Bellman_Ford(int u); 
	virtual queue<int> BFT(); 
	virtual queue<int> DFT();  
	virtual queue<int> EulerCycuit();   
	virtual queue<int> CriticalPath();  
	virtual queue<int> MaxFlow();  
};




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
