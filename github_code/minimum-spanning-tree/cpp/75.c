/*
https://www.geeksforgeeks.org/?p=27455
Greedy Algorithms | Set 5 (Prim�s Minimum Spanning Tree (MST))
We have discussed Kruskal�s algorithm for Minimum Spanning Tree. 
Like Kruskal�s algorithm, Prim�s algorithm is also a Greedy algorithm. 

The idea behind Prim�s algorithm is simple, 
a spanning tree means all vertices must be connected. 
So the two disjoint subsets (discussed above) of vertices must be connected 
to make a Spanning Tree. And they must be connected with 
the minimum weight edge to make it a Minimum Spanning Tree.


Time Complexity of the above program is O(V^2). 
If the input graph is represented using adjacency list, 
then the time complexity of Prim�s algorithm can 
be reduced to O(E log V) with the help of binary heap. 

TODO --		Prim�s algorithm using priority_queue in STL		https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
*/


#include <iostream>
using namespace std;
const int NoOfVertax = 9;
void PrintDistanceFromNode(int src ,int distance[NoOfVertax], int parentNode[NoOfVertax]);
void MinimumSpanningTreePrimsAlgo(int graph[NoOfVertax][NoOfVertax], int startNode);
//===========================================
void main()
{
	cout<<"\n Program Started *** "<<__FILE__<<endl;

	/* Let us create the example graph discussed above */
   int graph[NoOfVertax][NoOfVertax] =	{ {0, 4, 0, 0, 0, 0, 0, 8, 0},
										  {4, 0, 8, 0, 0, 0, 0, 11, 0},
										  {0, 8, 0, 7, 0, 4, 0, 0, 2},
										  {0, 0, 7, 0, 9, 14, 0, 0, 0},
										  {0, 0, 0, 9, 0, 10, 0, 0, 0},
										  {0, 0, 4, 14, 10, 0, 2, 0, 0},
										  {0, 0, 0, 0, 0, 2, 0, 1, 6},
										  {8, 11, 0, 0, 0, 0, 1, 0, 7},
										  {0, 0, 2, 0, 0, 0, 6, 7, 0}
										 };
  
    MinimumSpanningTreePrimsAlgo(graph, 0);

	cout<<"\n\n======================================== \n\n";
	MinimumSpanningTreePrimsAlgo(graph, 4);
	
	cout<<"\n Program Ended"<<endl;
}
//=======================================================================================
int findMinimumPathNode_Prim(bool visited[NoOfVertax] , int distance[NoOfVertax])
{
	int minDist = INT_MAX;
	int min_index = -1;
	for(int u =0 ; u < NoOfVertax ; ++u)
	{
		if(  (visited[u] == false)  && ( distance[u] < minDist) )	{
			minDist = distance[u] ; 
			min_index = u;
		}
	}
	return  min_index;
}

void MinimumSpanningTreePrimsAlgo(int graph[NoOfVertax][NoOfVertax], int startNode)
{
	int parent[NoOfVertax];
	bool isVisited[NoOfVertax];
	int distance[NoOfVertax];
	for (int u = 0 ; u< NoOfVertax ; ++u) 	{
		parent[u] = -1;
		isVisited[u] = false;
		distance[u] = INT_MAX;
	}
	distance[startNode] = 0;

	for(int count = 0 ; count < NoOfVertax ; ++count)
	{
		int u = findMinimumPathNode_Prim(isVisited,distance);
		if(u != -1 )	{
			isVisited[u] = true;
			for( int v = 0 ; v < NoOfVertax ; ++v)	{
				if( (isVisited[v] == false) && (graph[u][v] > 0 ) && (graph[u][v] < distance[v])  ) {
					parent[v] = u;
					distance[v] = graph[u][v];
				}
			}
		}
	}

	PrintDistanceFromNode(startNode, distance, parent);
}

void PrintDistanceFromNode(int src ,int distance[NoOfVertax], int parentNode[NoOfVertax])
{
	cout<<"\n\n ****  start node = "<<src << endl;
	for( int v = 0 ; v < NoOfVertax ; ++v)
	{
		cout <<"\n\n dest["<< v << "], Minimum distance = "<<distance[v]<<"\t || ";
		int parent = v;
		while( parent != -1 )
		{
			cout<<parent<<" -> ";
			parent = parentNode[parent];
		}
	}
}

/*
 Program Started *** Prim-Minimum-Spanning-Tree-Graph-algo.cpp


 ****  start node = 0


 dest[0], Minimum distance = 0   || 0 ->

 dest[1], Minimum distance = 4   || 1 -> 0 ->

 dest[2], Minimum distance = 8   || 2 -> 1 -> 0 ->

 dest[3], Minimum distance = 7   || 3 -> 2 -> 1 -> 0 ->

 dest[4], Minimum distance = 9   || 4 -> 3 -> 2 -> 1 -> 0 ->

 dest[5], Minimum distance = 4   || 5 -> 2 -> 1 -> 0 ->

 dest[6], Minimum distance = 2   || 6 -> 5 -> 2 -> 1 -> 0 ->

 dest[7], Minimum distance = 1   || 7 -> 6 -> 5 -> 2 -> 1 -> 0 ->

 dest[8], Minimum distance = 2   || 8 -> 2 -> 1 -> 0 ->
 Program Ended
Press any key to continue . . .


*/