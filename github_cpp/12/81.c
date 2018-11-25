


#include <iostream>
using namespace std;
const int NoOfVertax = 9;
void PrintDistanceFromNode(int src ,int distance[NoOfVertax], int parentNode[NoOfVertax]);
void MinimumSpanningTreePrimsAlgo(int graph[NoOfVertax][NoOfVertax], int startNode);

void main()
{
	cout<<"\n Program Started *** "<<__FILE__<<endl;

	
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

