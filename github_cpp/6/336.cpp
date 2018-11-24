#include <stdio.h>
#include <vector>

using namespace std;

struct edge{
	int u;
	int v;
	int w;
};

const int nmax = 111;
int n;
vector<edge> Adj;
int ans[nmax*nmax*nmax];
int Path[nmax], Parent[nmax], Distance[nmax];

void Bellman_Ford(int s);

int main(void){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d\n", &n);
	int u, v, w;
	while(scanf("%d%d%d", &u, &v, &w)>0){
		edge a;
		a.u = u;
		a.v = v;
		a.w = w;
		Adj.push_back(a);
		a.u = v;
		a.v = u;
		Adj.push_back(a);
	}
	Bellman_Ford(n);
	int k = -1;
	for (int i = 1; i < n; i++){
		if	(!Path[i]){
			printf("no path\n");
		} else {
			k++;
			int j = Parent[i];
			ans[k] = i;
			while(j != n){
				k++;
				ans[k] = j;
				j = Parent[j];
				if(j == 0 || k > nmax * nmax * 100) break;
			}
			if(!j || k > nmax * nmax * 100) {
				printf("no path\n");
			} else {
				k++;
				ans[k] = n;
				for (int i = k; i >= 0; i--)
					printf("%d " , ans[i]);
				for(int i = k; i >= 0; i--)
					ans[i] = 0;
				k = -1;
				printf("\n");
			}
		}
	}
	return 0;
}

void Bellman_Ford(int s){
	for (int i = 1; i <= n; i++){
		Distance[i] = 2000083646;
		Parent[i] = 0; 
	}
	Distance[s] = 0;
	for (int k = 1; k <= n - 1; k++){
		for (int i = 0; i < Adj.size(); i++){
			if(Distance[Adj[i].v] > Adj[i].w + Distance[Adj[i].u]){
				Path[Adj[i].v] = 1;
				Distance[Adj[i].v] = Distance[Adj[i].u] + Adj[i].w;
				Parent[Adj[i].v] = Adj[i].u;
			}
		}
	}
}
