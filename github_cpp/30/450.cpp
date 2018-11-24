#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <cstring>
#define pii pair<int, int>
#define ll long long int
#define loop(i, n) for(i=0; i<n; i++)
#define loopab(i, a, b) for(i=a; i<b; i++)
#define pb push_back
#define mk make_pair
using namespace std;
#define mx 100
int n, m;
vector<vector<int> > vec, wt;
int arr[mx];

struct cmp {
	bool operator()(pii a, pii b) {
		return a.second < b.second;
	}
};

void dijkstra(int s) {
	priority_queue<pii, vector<pii>, cmp> pq; //by default max priority queue
	pq.push(mk(s, 0));
	int i, u, v, w;
	for(i=0; i<n; i++)
		arr[i] = INT_MAX;
	arr[s] = 0;
	pii pr;
	
	while(!pq.empty()) {
		pr = pq.top();
		u = pr.first;
		pq.pop();
		for(i=0; i<vec[u].size(); i++) {
			v = vec[u][i];
			if(arr[v] > arr[u] + wt[u][i]) {
				arr[v] = arr[u] + wt[u][i];
				pq.push(mk(v, arr[v]));
			}
		}
	}
}

void print(int arr[mx], int n) {
	int i;
	for(i=0; i<n; i++)
		if(arr[i] == INT_MAX)
			cout<<-1<<" ";
		else
			cout<<arr[i]<<" ";
	cout<<endl;
}

int main()
{
	int i, j, x, y, w, s;
	cin>>n>>m;
	vec.resize(n);
	wt.resize(n);
	for(i=0; i<m; i++) {
		cin>>x>>y>>w;
		vec[x-1].pb(y-1);
		wt[x-1].pb(w);
	}
	cin>>s;
	dijkstra(s);
	print(arr, n);
	return 0;
}
