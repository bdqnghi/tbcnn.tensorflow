/*
 * autoor : mxt111
 */
 
#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <cmath>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <chrono>
#include <complex>
#include <utility>


#define distance(a, b) abs(a - b)
#define endl "\n"
#define ll long long int
#define vi vector<int>
#define vll vector<ll>
#define vvi vector < vi >
#define pii pair<int,int>
#define pll pair<long long, long long>
#define mod 1000000007
#define inf 1000000000000000001;
#define all(c) c.begin(),c.end()
#define mp(x,y) make_pair(x,y)
#define mem(a,val) memset(a,val,sizeof(a))
#define eb emplace_back
#define f first
#define s second


using namespace std;

// g++ --std=c++14 -o x.o x.cpp

int spanningTree(unordered_map<int, std::vector<pair<int, int>>> adjList, int start) {

	std::priority_queue<pair<int, int>, std::vector<pair<int, int> >, greater<pair<int, int>> > q;

	int minimumCost = 0;
	std::unordered_map<int, bool> visited;

	q.push(std::make_pair(0, start));

	while(!q.empty()) {
		pair<int, int> p = q.top();
		q.pop();

		int x = p.second;

		if (visited[x]) {
			continue;
		}

		visited[x] = true;

		minimumCost += p.first;

		for(int i = 0; i < adjList[x].size(); ++i) {
			pair<int, int> n = adjList[x][i];
			if (!visited[n.second]) {
				q.push(n);
			}
		}
	}

	return minimumCost;
}

int main() {
	
	std::ios::sync_with_stdio(false);
	int T;
	
	cin>>T;
	
	// cin.ignore(); must be there when using getline(cin, s)
		
	while(T--) {
		int n, e;
		cin >> n >> e;
		unordered_map<int, vector<pair<int, int>>> adjList;

		int start;

		for(int i = 0; i < e; ++i) {
			int a, b, c;
			cin >> a >> b >> c;

			adjList[a].push_back(make_pair(c,b));
			adjList[b].push_back(make_pair(c,a));
			start = a;
		}

		cout << spanningTree(adjList, start);
	}

	return 0;
}