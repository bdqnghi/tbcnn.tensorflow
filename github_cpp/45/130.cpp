#include <iostream>
#include <queue>
#include <limits>
#include <cstring>
using namespace std;

#define MAX_V 500
#define MAX_E 20000

int c[MAX_V][MAX_V]; // 边(u, v)的容量
int cf[MAX_V][MAX_V]; // 边(u, v)的残留容量
int path[MAX_V]; // 路径数组
int capacity[MAX_V]; // 容量数组
int visited[MAX_V]; // 访问数组
int maxFlow; // 最大流
int S; // 源点
int T; // 汇点
int V; // 图中顶点数

bool findAugmentPath() {
	queue<int> Q; // 先进先出队列
	memset(path, 0, sizeof(int) * MAX_V); // 初始化路径数组为0
	memset(capacity, 0, sizeof(int) * MAX_V); // 初始化容量数组为0
	memset(visited, 0, sizeof(int) * MAX_V); // 初始化访问数组为0
	capacity[S] = INT32_MAX;
	visited[S] = 1;

	Q.push(S); // 队列Q仅含源点s

	while (Q.size() != 0) {
		int u = Q.front();
		Q.pop();

		if (u == T) {
			return true; // 已经找到一条增广路径
		}

		for (int v = 0; v < V; v++) {
			if (cf[u][v] > 0 && visited[v] == 0) {
				// u到v有残留容量，且v未被访问过
				path[v] = u; // 记录路径
				capacity[v] = min(cf[u][v], capacity[u]); // 记录路径上的最小残留容量
				visited[v] = 1;
				Q.push(v);
			}
		}
	}

	return false;
}

int modifyGraph() {
	int flow = capacity[T];
	int now = T;
	while (now != S) {
		int fa = path[now];
		cf[fa][now] = cf[fa][now] - flow;
		cf[now][fa] = cf[now][fa] + flow; // 反向边的残留容量是增加
		now = fa;
	}
	return 0;
}

int Ford_Fulkerson() {
	while (findAugmentPath()) { // 判断是否有增广路径
		maxFlow = maxFlow + capacity[T]; // 最大流增加
		modifyGraph();
	}
	return 0;
}

int main() {
	int n, m;
	cin >> n >> m;
	S = 0;
	T = n - 1;
	V = n;
	int u, v, c;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> c;
		// not just only one input
		cf[u - 1][v - 1] = cf[u - 1][v - 1] + c;
	}
	Ford_Fulkerson();
	cout << maxFlow << endl;
}