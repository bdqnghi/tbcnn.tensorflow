#include<iostream>
#include<cstdlib>
#include "Graph.h"
#include "../Data_Processors/AdjList.h"
#include "../Data_Processor/GraphLoader.h"
using namespace std;
class Digraph:public Graph{
    typedef GraphLoader graph;
private:
    AdjList G_L;
public:
    void load(graph& g,int selection=0);
    bool IsExistAdj(int node);    
	double operator()(int start,int end);
	int first_vertex(int u);
	int next_vertex(int u,int v);
    bool is_strongly_connected();
	int Vertex();
	int InDegree(int u);
	int OutDegree(int u);
	void set_tag(int start,int end);
	bool get_tag(int start,int end);
    virtual queue<int> Dijkstra(int u);   
	virtual int Prim();    
	virtual int Kruskal(); 
	virtual queue<int> TopologicalSort();  
	virtual queue<int> Bellman_Ford(int u); 
	queue<int> BFT(); 
	queue<int> DFT();  
	virtual queue<int> CriticalPath();  
	virtual queue<int> MaxFlow();  
};
int Digraph::first_vertex(int node){
	List<double> list=G_L[node];
	return ((list.head())->next)->vertex;
}
int Digraph::next_vertex(int node,int adj){
	Node<double>* p=(G_L[node]).head();
	while(p!=NULL){
		if(p->vertex==adj){
			p=p->next;
			break;
		}
		else{
			p=p->next;
		}
	}
	return p->vertex;
}
int Diraph::InDegree(int u){
	map<int,map<int,double> >::iterator it;
	List<double> candidate;
	Node<double>* N;
	int count=0;
	for(int it=G_L.begin();it!=G_L.end();++it){
		candidate=it->second;
		N=(candidate.head())->next;
		while(N!=NULL){
			if(N->vertex!=u){
				N=N->next;
			}
			else{
				count++;
				break;
			}
		}
	}
	return count;
}
int Digraph::OutDegree(int u){
	List<double> candidate=G_L[u];
	Node<double>* N=(candidate.head())->next;
	int count=0;
	while(N!=NULL){
		count++;
	}
	return count;
}
void Digraph::set_tag(int start,int end){
	List<double> candidate=G_L[start];
	Node<double> p=(candidate.head())->next;
	while(p!=NULL){
		if(p->vertex!=end){
			p=p->next;
		}
		else{
			p->tag=true;
			break;
		}
	}
}
bool Digraph::get_tag(int start,int end){
	List<double> candidate=G_L[start];
	Node<double> p=(candidate.head())->next;
	while(p!=NULL){
		if(p->vertex!=end){
			p=p->next;
		}
		else{
			break;
		}
	}
	return p->tag;
}
#include "GraphAlgorithms.h"