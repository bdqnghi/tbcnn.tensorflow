/*
 * FordFulkerson.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: Mamunul
 */

#include "FordFulkerson.h"

namespace src {
int g[6][6] = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 }, { 0, 4, 0, 0,
		14, 0 }, { 0, 0, 9, 0, 0, 20 }, { 0, 0, 0, 7, 0, 4 },
		{ 0, 0, 0, 0, 0, 0 } };
stack<int> st;
FordFulkerson::FordFulkerson() {
	// TODO Auto-generated constructor stub
	p = vector<int>(6, 0);
	visited = deque<bool>(6, false);
//	**g = new int*[6];
//	g = new int;

}

FordFulkerson::~FordFulkerson() {
	// TODO Auto-generated destructor stub
}

bool FordFulkerson::ford_fulkerson_dfs(int v, int t) {

	st.push(v);

	visited[v] = true;

	while (!st.empty()) {

		int j = st.top();

		st.pop();
		if (j == t)
			return true;

//		cout << "p:" << j << endl;

		for (int i = 0; i < 6; i++) {

			if (g[j][i] > 0 && !visited[i]) {
				visited[i] = true;

				p[i] = j;
				st.push(i);
//				cout << "v:" << i << endl;
//				break;
			}

		}

	}

	return false;

}

int FordFulkerson::ford_fulkerson() {

	int max_flow = 0;
	int s = 0;
	int t = 5;
//	ford_fulkerson_dfs(s, t);
	while (ford_fulkerson_dfs(s, t)) {
//
//		cout << "got" << endl;

		int min_flow = 10000;
		int j = 0;
		for (int i = t; i != s; i = j) {
			j = p[i];
//			cout << "j:"<<j << " i:" << i << endl;
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

} /* namespace src */
