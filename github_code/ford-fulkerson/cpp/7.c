#include <bits/stdc++.h>

using namespace std;

const int N = 205;

int t;
int n;

vector<vector<int> >g;
int flow[N][N];
int p[N];

void addEdge(int a, int b, int f)
{
	flow[a][b] += f;
	g[a].push_back(b);
	g[b].push_back(a);
}

void dfs(int u)
{
	for(int i = 0 ; i < (int)g[u].size(); i++)
	{
		int v = g[u][i];
		if(p[v] == -1 && flow[u][v])
		{
			p[v] = u;
			dfs(v);
		}
	}
}

// Função principal do algoritmo
// Retorna qual o fluxo máximo entre os vértices inicial e final
// Parâmetros (_s = vértice inicia, _t = vértice final)
int ford_fulkerson(int _s, int _t)
{
	int maxflow = 0;
	while(1)
	{

		memset(p, -1, sizeof p);
		
		// Executa a busca
		dfs(_s);

		// Verifica se foi encontrado um caminho 
		if(p[_t] == -1)break;
		int id = _t;
		int f = 0x3f3f3f3f;

		// Pega a menor aresta desse caminho
		while(id != _s)
		{
			f = min(flow[p[id]][id],f);
			id = p[id];
		}
		id = _t;
		// Depois retiramos o fluxo das arestas de ida, e somamos o fluxo nas arestas de volta
		while(id != _s)
		{

			flow[p[id]][id] -= f;
			flow[id][p[id]] += f;
			id = p[id];
		}
		maxflow += f;
	}
	return maxflow;
}

int main()
{

	scanf("%d",&t);

	for(int z = 0 ;z < t ; z++)
	{
		
		

		scanf("%d",&n);

		g.assign(n+1, vector<int>());
		memset(flow, 0, sizeof flow);

		for(int i = 1 ; i < n ; i++)
		{
			int x; scanf("%d",&x); 

			for(int j = 0 ; j < x ; j++)
			{
				int a;
				scanf("%d",&a);
				if ( a == n || i == 1 )
	             addEdge( i, a, 1 );
	           else addEdge( i, a, 1000000000 );
			}
		}
		printf("%d\n", mf(1,n));
	}


	return 0;
}