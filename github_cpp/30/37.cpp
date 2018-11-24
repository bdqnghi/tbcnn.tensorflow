#include<iostream>
#include<algorithm>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<numeric>
#include<set>
#include<map>
#include<queue>
#include<list>
#include<deque>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORE(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define distLEAR(x,with) memset(x,with,sizeof(x))
#define sz size()
typedef long long ll;

const int MAX_V = 100;
const int INF = 987654321;

// 정점의 개수
int V; 
// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int,int> > adj[MAX_V];

vector<int> dijkstra(int src) {
	vector<int> dist(V, INF);
	dist[src] = 0;
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		// 만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다
		if(dist[here] < cost) continue;
		// 인접한 정점들을 모두 검사한다
		for(int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			// 더 짧은 경로를 발견하면, dist[] 를 갱신하고 우선 순위 큐에 넣는다
			if(dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

vector<int> dijkstra2(int src) {
	vector<int> dist(V, INF);
	// 각 정점을 방문했는지 여부를 저장한다
	vector<bool> visited(V, false);
	dist[src] = 0; visited[src] = true;
	// V-1 번 새 정점을 찾아 방문한다
	for(int i = 0; i < V-1; ++i) {
		// 아직 방문하지 않은 정점 중 가장 가까운 정점을 찾는다
		int closest = INF, here;
		for(int j = 0; j < V; ++j)
			if(dist[j] < closest && !visited[j]) {
				here = j;
				closest = dist[j];
			}
		// 가장 가까운 정점을 방문한다
		visited[here] = true;
		for(int j = 0; j < adj[here].size(); ++j) {
			int there = adj[here][i].first;
			if(visited[there]) continue;
			int nextDist = closest + adj[here][j].second;
			dist[there] = min(dist[there], nextDist);
		}
	}
}

int main()
{
	int cases;
	cin >> cases;
	REP(cc,cases)
	{
		fprintf(stderr, "%d of %d ..\r", cc+1, cases);
		printf("distase #%d: ", cc+1);
	}
}
