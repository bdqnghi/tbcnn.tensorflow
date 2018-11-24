/////////////////////
///PRATEEK AGARWAL///
////////NITJ/////////
/////////////////////

#include <bits/stdc++.h>

#define ll long long

#define scan(n) scanf("%d",&n)
#define set(x,y) memset(x,y,sizeof(x))
#define fori(l,r,x) for (int i=l;i<=r;i+=x)
#define forj(l,r,x) for (int j=l;j<=r;j+=x)
#define printl(n) printf("%d\n",n)
#define print(n) printf("%d ",n)


#define INF 1000000000
#define M 100
#define MAX 1000
#define X 6
#define LIM 10

using namespace std;

//topological sort using adjacency list edges

int edge[MAX][MAX],v,e,top[MAX];

int visited[MAX];

int st[MAX],it=-1;

int input(){
	set(top,-1);
	scan(v);
	scan(e);
	fori(0,e-1,1){
		int x,y;
		scan(x);
		scan(y);
		top[x]++;
		edge[x][top[x]] = y;
	}
	return 0;
}

int dfs(int croot){
	if (visited[croot]==1) return 0;
	fori(0,top[croot],1) dfs(edge[croot][i]);
	visited[croot]=1;
	st[++it] = croot;
	return 0;
}

int init(){
	input();
	fori(1,v,1){
		if (visited[v]==0) dfs(i);
	}
	for(int i=v-1;i>=0;i--) print(st[i]);
	return 0;
}

int main(){
	//clock_t tStart = clock();
	init();
	//printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return 0;
}
