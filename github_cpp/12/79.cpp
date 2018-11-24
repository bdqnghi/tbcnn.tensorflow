#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<string>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<cctype>
#include<sstream>
#define PI acos(-1.0) 
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;

/**
*    传递闭包的warshall演算法。
*    Floyd-Warshall:带负权图的每两点间最短路。
*    建立为有向图。
*/

const int inf = 1000000;//假定估计值为1000000
//inf若太大可能会溢出,太小可能会被当成确切的边权,要先估计一下,找一个合适的值
int adj[50][50]; //不连通的两点间为inf
int d[50][50];
int n;
void warshall(){
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			d[i][j] = adj[i][j]==inf?0:1;
	//分别借由k = 0,1,2,3,...,n-1时是否可从i到达j,每次都在上一次的基础上迭代
	for(int k = 0;k < n;k++)
		for(int i = 0;i < n;i++)
			for(int j = 0;j < n;j++)
				d[i][j] = d[i][j]||(d[i][k]&&d[k][j]);
}
void floyd_warshall(){
	//warshall改一下松弛条件就是了
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			d[i][j] = adj[i][j];
	for (int i=0; i<n; i++) d[i][i] = 0; //初始条件稍有不同
	
	for(int k = 0;k < n;k++)
		for(int i = 0;i < n;i++)
			for(int j = 0;j < n;j++)	
					d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
}
int main(){
	int m;
	printf("how many nodes and edges?(<50) ");
	scanf("%d%d",&n,&m);
	for(int i = 0;i < n;i++)fill(adj[i],adj[i]+n,inf);
	printf("Now give me adjagency relationship.\n");
	for(int i = 0;i < m;i++){
		int u,v,val;
		scanf("%d%d%d",&u,&v,&val);
		adj[u][v] = val;
	}
	printf("warshall algorithm gives:\n");
	warshall();
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++)
			cout << d[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	printf("While Floy-Warshall algorithm gives:\n");
	floyd_warshall();
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++)
			cout << d[i][j] << " ";
		cout << endl;
	}
	return 0;
}


