#include <stdio.h>

using namespace std;

const int nmax = 111;
const long long maximum = 2147483647;
long long D[nmax][nmax], W[nmax][nmax], P[nmax][nmax];

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n=0;
	scanf("%d\n", &n);
	for(int i = 1; i < nmax; i++)
		for(int j = 1; j < nmax; j++)
			if(i == j) W[i][j] = 0;
				else W[i][j] = maximum;
	int  u,v;
	long  long w;
	while(scanf("%d%d%I64d", &u, &v, &w)>0){
		W[u][v] = w;
		W[v][u] = w;
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			D[i][j] = W[i][j];
	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				if(D[i][k] + D[k][j] < D[i][j])
					D[i][j] = D[i][k] + D[k][j];
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++)
			if(D[i][j] == maximum)
				printf("-1 ");
			else
				printf("%I64d ", D[i][j]);
		printf("\n");
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			P[i][j] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(D[i][j] < W[i][j]){
				long long m = maximum;
				int t = 0;
				for(int k = 1; k <= n; k++)
					if(D[i][j] == D[i][k] + D[k][j] && k != j && k != i && D[k][j] < m){
						m = D[k][j];
						t = k;
					}
				P[i][j] = t;
			}
	printf("\n");
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++)
			printf("%d ",P[i][j]);
		printf("\n");
	}
	return 0;
}
