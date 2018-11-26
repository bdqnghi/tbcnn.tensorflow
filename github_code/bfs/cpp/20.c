//////////////////////////
// Breadth-first search //
//////////////////////////

#include <iostream>
#include <queue>
#include <stdlib.h>
#include <vector>
#include <fstream>
using namespace std;

#define go(i,n) for(int i=0;i<n;i++)
#define rep(i,from,to) for (int i = from; i <= to; i++)


int *dest, *nxt, *head;
int n, k;

// [i] is path from u0; if it equals -1, there's no path
int *breadth_first_search(const int &u0, int* from)
{
	queue<int> vertexes;
	vertexes.push(u0);
	int *vis = static_cast<int*>(malloc((k + 1) * sizeof(*vis))); go(i,k+1) vis[i] = -1;
	vis[u0] = 0;
	from[u0] = 0;
	while (!vertexes.empty())
	{
		int u = vertexes.front();
		vertexes.pop();
		int v = head[u];
		int wave = vis[u] + 1;
//		cout << wave << "\nstart: " << u << " " << dest[v] << "\n";
		while (v != 0)
		{
//			cout << "weight: " << vis[dest[v]] << " " << dest[v] << endl;
			if (vis[dest[v]] == -1) {
				vis[dest[v]] = wave;
				from[dest[v]] = u;
				vertexes.push(dest[v]);
			}
			v = nxt[v];
		}
	}
	return vis;
}


void build_directed_graph()
{
	cin >> n >> k;
	head = static_cast<int*>(calloc(k + 1, sizeof(*head)));
	dest = static_cast<int*>(calloc(n + 1, sizeof(*dest)));
	nxt = static_cast<int*>(calloc(n + 1, sizeof(*nxt)));
	int j = 0;
	go(i, n)
	{
		int u, v;
		cin >> u >> v;

		j++;
		dest[j] = v;
		nxt[j] = head[u];
		head[u] = j;
	}
}

void build_undirected_graph()
{
	cin >> n >> k;
	head = static_cast<int*>(calloc(k + 1, sizeof(*head)));
	dest = static_cast<int*>(calloc(2*n + 1, sizeof(*dest)));
	nxt = static_cast<int*>(calloc(2*n + 1, sizeof(*nxt)));
	int j = 0;
	go(i, n)
	{
		int u, v;
		cin >> u >> v;

		j++;
		dest[j] = v;
		nxt[j] = head[u];
		head[u] = j;

		j++;
		dest[j] = u;
		nxt[j] = head[v];
		head[v] = j;
	}
}

void print_shortest_path(const int* const from, const int &i, int j)
{
	if (i == j) return;
	print_shortest_path(from, i, from[j]);
	cout << from[j] << " -> " << j << endl;
}

int main()
{
#ifdef _DEBUG
	streambuf *console = cin.rdbuf();
	ifstream in("in.txt");
	cout << "DEBUG\n";
	cin.rdbuf(in.rdbuf());
#endif

	// n = the number of edges
	// k = the number of vertexes

//	build_directed_graph();
	build_undirected_graph();

	int *from = static_cast<int*>(malloc((k + 1) * sizeof(*from))); go(i, k + 1)from[i] = -1;
	int *a = breadth_first_search(3, from);

	for (size_t i = 1; i <= k; i++)
		cout << a[i] << " ";
	cout << endl;
	for (size_t i = 1; i <= k; i++)
		cout << from[i] << " ";
	cout << endl;

	print_shortest_path(from, 3, 6);

	free(a);

#ifdef _DEBUG
	cout << "\n----\n";
	cin.rdbuf(console);
	cin.get();
#endif
	return 0;
}
