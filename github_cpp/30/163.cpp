#define PRON "dijkstra"
#include <queue>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 100;
const int MAXM = 100 + 10;
const int INF = 0x3f3f3f3f;

int vex_num, dis[MAXN];
bool vis[MAXN];

struct Edge {
	int to, d;
	Edge * next;
} * head[MAXN], e[MAXM];

void dijkstra(int s) {
	for (int i = 0; i < vex_num; i ++) // 初始化
		vis[i] = false, dis[i] = INF;
	dis[s] = 0, vis[s] = true;

	for (int i = 0; i < vex_num - 1; i ++) {
		int min_dis = INF, v;
		for (int j = 0; j < vex_num; j ++)
			if (min_dis < dis[j] && not vis[j])
				min_dis = dis[j], v = j;

		vis[v] = true;
		for (Edge * p = head[v]; p; p = p -> next)
			if (dis[p -> to] > dis[v] + p -> d && not vis[p -> to])
				dis[p -> to] = dis[v] + p -> d;
	}
}

void dijkstra_2(int s) {
	priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > q;

	for (int i = 0; i < vex_num; i ++) // 初始化
		dis[i] = INF;
	dis[s] = 0, q.push(make_pair(0, s));

	while (not q.empty()) {
		int v = q.top().second;
		q.pop();
		
		for (Edge * p = head[v]; p; p = p -> next)
			if (dis[p -> to] > dis[v] + p -> d && not vis[p -> to]) {
				dis[p -> to] = dis[v] + p -> d;
				q.push(make_pair(dis[p -> to], p -> to));
			}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen(PRON ".in", "r", stdin);
	//freopen(PRON ".out", "w", stdout);
#endif

}
