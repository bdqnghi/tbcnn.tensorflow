#include"DepthFirstSearch.h"
#include<stdlib.h>
#include<iostream>
using namespace std;

DepthFirstSearch::DepthFirstSearch(Graph *G, int v)
{
	N = G->getVertices();
	marked = new bool[N];
	count =0;
	dfs(G, v);
}

void DepthFirstSearch::dfs(Graph *G, int v)
{
	if(marked[v] == true) 
		return;
	marked[v] = true;
	count++;
	Graph::Vertice *vertices = G->getAdj(v);
	while(vertices != NULL)
	{
		int w = vertices->value;
		if(!marked[w])  dfs(G, w);
		vertices = vertices->next;
	}
}

bool DepthFirstSearch::isMarked(int w)
{
	return marked[w];
}

int DepthFirstSearch::getCount()
{
	return count;
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		cout<<"argc != 2"<<endl;
		exit(1);
	}
	Graph *g = new Graph(new In(argv[1]));	
	DepthFirstSearch *dfs = new DepthFirstSearch(g, 9); 
	for(int i=0; i<g->getVertices(); i++)
	{
		cout<<i<<": "<<dfs->isMarked(i)<<endl;
	}
}
