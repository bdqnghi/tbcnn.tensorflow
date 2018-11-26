#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<vector<int>> adj;

int init() {
	adj.resize(13);
	adj[0] = { 2 };
	adj[1] = { 2,5 };
	adj[2] = { 0,1,3,6 };
	adj[3] = { 2,7 };
	adj[4] = { 5 };
	adj[5] = { 1,4,6,9 };
	adj[6] = { 2,5,7,10 };
	adj[7] = { 3,6,8,11 };
	adj[8] = { 7 };
	adj[9] = { 5,10 };
	adj[10] = { 6,9,11,12 };
	adj[11] = { 7,10 };
	adj[12] = { 10 };
	return 0;
}

int bfs(int s) {
	vector<bool> visit;
	visit.resize(adj.size());
	for (int i = 0; i < visit.size(); i++) {
		visit[i] = false;
	}
	visit[s] = true;
	queue<int> q;
	q.push(s);
	cout << "The list of vertices visited in order is: " << endl;
	cout << s + 1;
	while (!q.empty()) {
		int v = q.front();
		vector<int> ref = adj[v];
		for (int j = 0; j < ref.size(); j++) {
			if (!visit[ref[j]]) {
				visit[ref[j]] = true;	
				q.push(ref[j]);
				cout << " " << ref[j] + 1;
			}
		}
		q.pop();
	}
	return 0;
}

int shortestpath(int s) {
	vector<int> length;
	length.resize(adj.size());
	for (int i = 0; i < length.size(); i++) {
		length[i] = -1;
	}
	length[s] = 0;
	queue<int> q;
	q.push(s);
	cout << "The shortest path from "<<s+1<<" to other is: " << endl;
	while (!q.empty()) {
		int v = q.front();
		vector<int> ref = adj[v];
		for (int j = 0; j < ref.size(); j++) {
			if (length[ref[j]]== -1) {
				length[ref[j]] = length[v]+1;
				q.push(ref[j]);
				cout << "Length to node " << ref[j]+1 <<" is " <<length[ref[j]]<<endl;
			}
		}
		q.pop();
	}
	return 0;
}

int bfsapp() {
	init();
	bfs(0);
	cout << endl;
	shortestpath(0);

	system("pause");
	return 0;
}