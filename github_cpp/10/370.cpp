#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

vector<vii> AdjList;
vi prev;

int a, b, V, E, s;

void DFS(int s, bool visited[])
{
	visited[s]= true;

	for(int i=0; i<AdjList[s].size(); i++)
	{
		ii v= AdjList[s][i];
		if(!visited[v.first])
		{
			printf("%d ", s);
			DFS(v.first, visited);
		}
	}
}

int main()
{
	scanf("%d %d", &V, &E);
	AdjList.assign(V, vii());
	for(int i=0; i<E; i++)
	{
		scanf("%d %d", &a, &b);
		AdjList[a].push_back(ii(b, 0));
		AdjList[b].push_back(ii(a, 0));
	}

	scanf("%d", &s);

	bool visited[V];
	memset(visited, false, sizeof(visited));

	DFS(s, visited);
}