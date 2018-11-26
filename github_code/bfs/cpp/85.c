/*
* BFS Algorithm.
* Breadth-first search (BFS) is an algorithm for traversing or searching tree or graph data structures. 
* It starts at the tree root (or some arbitrary node of a graph, sometimes referred to as a 'search key')
* and explores the neighbor nodes first, before moving to the next level neighbors.
* BFS was invented in the late 1950s by E. F. Moore, who used it to find the shortest path out of a maze,
* and discovered independently by C. Y. Lee as a wire routing algorithm (published 1961).
*/
#include "BFS.h"
using namespace std;

/*
* BFS constructor.
*/
BFS::BFS(string filePath):Graph(filePath)
{
	for(unsigned long i=0; i<this->vertexsNum; i++)
	{
		this->visited.push_back(false);
	}
}

/*
* Clean visit record.
*/
void BFS::cleanVisitRecord(void)
{
	for(vector<bool>::iterator iter=this->visited.begin(); iter!=this->visited.end(); ++iter)
	{
		(*iter)=false;
	}
}


/*
* Breadth-First-Search.
* Fake code:
* A non-recursive implementation of BFS:
 1 Breadth-First-Search(Graph, root):
 2 
 3     for each node n in Graph:            
 4         n.distance = INFINITY        
 5         n.parent = NIL
 6 
 7     create empty queue Q      
 8 
 9     root.distance = 0
10     Q.enqueue(root)                      
11 
12     while Q is not empty:        
13     
14         current = Q.dequeue()
15     
16         for each node n that is adjacent to current:
17             if n.distance == INFINITY:
18                 n.distance = current.distance + 1
19                 n.parent = current
20                 Q.enqueue(n)
*/
void BFS::goBFS(unsigned long startVertex)
{
	this->cleanVisitRecord();
	queue<unsigned long> Q;
	Q.push(startVertex);
	this->visited[startVertex]=true;
	cout<<"Visit:"<<startVertex<<endl;
	while(!Q.empty())
	{
		unsigned long rowIndex=0;
		unsigned long columnIndex=0;
		rowIndex=Q.front();
		Q.pop();
		for(columnIndex=0; columnIndex<this->vertexsNum; columnIndex++)
		{
			if(this->adjacentMatrix[rowIndex][columnIndex]!=0 && this->visited[columnIndex]==false)
			{
				cout<<"Visit:"<<columnIndex<<endl;
				this->visited[columnIndex]=true;
				Q.push(columnIndex);
			}
		}
	}
}