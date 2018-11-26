#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H
#include<iostream>
#include<cstdlib>
#include<map>
#include<queue>
#include "../Data_Processors/GraphLoader.h"
#include "../Data_Processors/AdjList.h"
#include "../Data_Processors/AdjMatrix.h"
#include "../Data_Processors/List.h"
#include "graph.h"
#include "Digraph.h"
//A class of often-used graph algorithms
using namespace std;
class GraphAlgorithms:public Digraph,public graph{
	typedef double Distance;
private:
	double* distances;
public:
    GraphAlgorithms(); //Constructor: initialize distances. 
	map<int,Distance> Dijkstra(int u);   //Dijkstra Shortest-paths Algorithm
	int Prim();    //Prim's Minimum-spanning-tree Algorithm
	int Kruskal(); //Kruskal's Minimum-spanning-tree Algorithm
	queue<int> TopologicalSort();  //Topological Sort 
	queue<int> Bellman_Ford(int u); //Bellman-Ford Algorithm
	queue<int> EulerCycuit(int u=0);   //Find Euler path
	//selection=0: graph
	//selection=1: di-graph
	queue<int> CriticalPath();  //Find a critical path
	queue<int> MaxFlow();
	void initial(int u); //initialize distances
};
GraphAlgorithms::GraphAlgorithms() {
	distances = new double[this->Vertex()];
}
void GraphAlgorithms::initial(int u){
	for (int i = 0; i < this->Vertex(); i++) {
		if (i != u) { *(distance + i) = -1; }
		else { *(distance + i) = 0; }
	}
}
map<int,double> GraphAlgorithms::Dijkstra(int u) {
	map<int, double> result;
	for (int i = Digraph::first_vertex(u); Digraph::next_vertex(u,i)!=-1; i = Digraph::first_vertex(u, i)) {
		if (i != -1) {
			if (*(distances + i) >*(distances+u)+ Digraph::(u, i)&&*(distances+i)!=-1) {
				*(distances + i) = *(distances + u) + Digraph::(u, i);
			}
			else if(*(distances+i)==-1){
				*(distances+i)=Digraph::(u,i);
			}
			result=Dijkstra(i);
		}
	}
	for (int j = 0; j < this->Vertex(); j++) {
		result.emplace(j, *(distances + j));
	}
	return result;
}
queue<int> GraphAlgorithms::TopologicalSort() {
	queue<int> candidate;
	queue<int> result;
	for (int i = 0; i < this->Vertex(); i++) {
		if (this->InDegree(i) == 0) {
			candidate.push(i);
		}
	}
	for (int i = candidate.front(); candidate.size() != 0;i=candidate.front()) {
		for (int j = Digraph::first_vertex(i); Digraph::next_vertex(i, j) != -1; j = Digraph::next_vertex(i, j)) {
			if (DIgraph::InDegree(j) - 1 == 0) {
				candidate.push(j);
			}
		}
		result.push(i);
		candidate.pop();
	}
	return result;
}
queue<int> GraphAlgorithms::Bellman_Ford(int u){

	
}
int GraphAlgorithms::Prim(){
	
}

queue<int> GraphAlgorithms::CriticalPath(){
	queue<int> candidate;
	queue<int> result;
	queue<int> candidate_u;
	for(int i=0;i<this->Vertex();i++){
		if(this->InDegree(i)==0){
			candidate.push(i);
		}
	}
	for(int u=candidate.front();candidate.size()!=0;u=candidate.front()){
		candidate_u.clear();
		candidate_u.push_back(u);
		initial(u);
		for(j=this->FindFirstVertex(u);this->FindNextVertex(u,j)!=-1;j=this->FindNextVertex(u,j)){
			if(*(distance+j)==-1){
				*(distance+j)=(*this)(u,j);
			}
			else if(*(distance+u)+(*this)(i,j)>*(distance+j)){
				*(distance+j)=*(distance+u)+(*this)(u,j);
				candidate_u.push_back(j);
			}
			if(this->InDegree(j)-1==0){
				candidate.push_back(j);
			}
		}

	}
}
#endif
