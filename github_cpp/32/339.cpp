//Kruskal's algorithm
#include<iostream>
#include<conio.h>

using namespace std;
struct Edge
{ int src,dest,weight;
};

struct Graph{
	int Vertices,Edges;
	Edge *edge;
};

Graph *createGraph(int v,int e)
{ Graph *graph=new Graph;
  graph->Vertices=v;
  graph->Edges=e;
  graph->edge=new Edge[e];
  
  return graph;
}

struct set{
	int parent;
	int rank;
}Set[];

void makeSet(set Set[],int x,int n)
{ for(int i=0;i<n;i++)
  {
  Set[i].parent=x;
  Set[i].rank=0;
  }
}

int FindSet(set Set[],int i)
{  if (Set[i].parent != i)
        Set[i].parent = FindSet(Set, Set[i].parent);
 
    return Set[i].parent;
}

void Union(set Set[],int x, int y)
{ int rep1=FindSet(Set,x);
  int rep2=FindSet(Set,y);
  
  if(Set[rep1].rank>Set[rep2].rank)
  Set[rep2].parent=rep1;
  else if(Set[rep1].rank<Set[rep2].rank)
  Set[rep1].parent=rep2;
  
  else
  { Set[rep2].parent=rep1;
    Set[rep1].rank=Set[rep1].rank+1;
  }
}

void Kruskal(Graph *graph)
{ int A[20],v;
  cout<<"\nEnter the vertices:\t";
}


