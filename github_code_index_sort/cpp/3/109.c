#include <bits/stdc++.h>
using namespace std;

vector<int> g[500];
int income[500];
int n, m;
queue<int> order, processNext;

void topologicalSort() {
	for(int i=0; i<n; i++)
		if(income[i]==0) processNext.push(i);
	
	while(!processNext.empty()) {
		int x = processNext.front();
		processNext.pop();

		for(int i=0; i<(int)g[x].size(); i++) {
			int v = g[x][i];
			income[v]--;
			if(income[v] == 0) processNext.push(v);
		}


		order.push(x);
	} 
}

int main() {
	cin >> n >> m;

	for(int i=0; i<m; i++) {
		//a -> b
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		income[b]++;
	}

	for(int i=0; i<n; i++) cout << income[i] << " ";
              cout << endl << endl;

	topologicalSort();

	if(order.size() < n) cout << "Circular dependencies" << endl;
	else
		while(!order.empty()) {
			int node = order.front();
			order.pop();
			
			cout << "Visit - " <<  node << endl;
		}

	return 0;
}
