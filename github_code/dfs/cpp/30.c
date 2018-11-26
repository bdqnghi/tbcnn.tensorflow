#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;

vector<int> adj[10];
bool visited[10] = {false, };

void DFS(int node)
{
	visited[node] = true;

	cout << node << " ";
	for (int i = 0; i < adj[node].size(); i++)
	{
		//cout << "Size :" << adj[node].size() << "\n";

		if (!visited[adj[node][i]])
		{
			DFS(adj[node][i]);
		}
	}



}

int main()
{
	int V, E;
	cout << "Enter Number of nodes ";
	cin >> V >> E;

	int a, b;
	for (int i = 0; i < E; i++)
	{
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
		
	}
	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
		{
			DFS(i);
		}
	}
	
}