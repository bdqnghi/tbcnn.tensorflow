

#include "FordFulkerson.h"

namespace src {
int g[6][6] = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 }, { 0, 4, 0, 0,
		14, 0 }, { 0, 0, 9, 0, 0, 20 }, { 0, 0, 0, 7, 0, 4 },
		{ 0, 0, 0, 0, 0, 0 } };
stack<int> st;
FordFulkerson::FordFulkerson() {
	
	p = vector<int>(6, 0);
	visited = deque<bool>(6, false);



}

FordFulkerson::~FordFulkerson() {
	
}

bool FordFulkerson::ford_fulkerson_dfs(int v, int t) {

	st.push(v);

	visited[v] = true;

	while (!st.empty()) {

		int j = st.top();

		st.pop();
		if (j == t)
			return true;



		for (int i = 0; i < 6; i++) {

			if (g[j][i] > 0 && !visited[i]) {
				visited[i] = true;

				p[i] = j;
				st.push(i);


			}

		}

	}

	return false;

}

int FordFulkerson::ford_fulkerson() {

	int max_flow = 0;
	int s = 0;
	int t = 5;

	while (ford_fulkerson_dfs(s, t)) {



		int min_flow = 10000;
		int j = 0;
		for (int i = t; i != s; i = j) {
			j = p[i];

			min_flow = min(min_flow, g[j][i]);

		}

		for (int i = t; i != s; i = j) {
			j = p[i];
			g[j][i] -= min_flow;
			g[i][j] += min_flow;
		}

		cout << "min:" << min_flow << endl;
		max_flow += min_flow;

		p = vector<int>(6, 0);

		visited = deque<bool>(6, false);
	}

	return max_flow;
}

} 
