


#ifndef __DFS_H
#define __DFS_H

#include "graph.h"

namespace Algorithm {

	class DepthFirstSearch {
	public:
		bool is_marked(int v); 
		int count(); 

		DepthFirstSearch(UDGraph &graph, int source);
		~DepthFirstSearch();

	private:
		void dfs(int s);
		bool *marked;
		int n; 
		int cnt;
		UDGraph graph;
	};

	DepthFirstSearch::DepthFirstSearch(UDGraph &graph, int source):graph(graph) {
		n = graph.v();
		cnt = 0;
		marked = new bool[n];

		for (int i = 0; i < n; i++) {
			marked[i] = false;
		}

		dfs(source);
	}

	DepthFirstSearch::~DepthFirstSearch() {
		delete[] marked;
		marked = NULL;
	}

	void DepthFirstSearch::dfs(int s) {
		marked[s] = true;

		vector<int> *res = graph.adj(s);
		if (res == NULL) {
			return;
		}

		for (vector<int>::iterator itr = res->begin(); itr != res->end(); itr++) {
			if (!marked[*itr]) {
				dfs(*itr);
				cnt++;
			}
		}
	}

	bool DepthFirstSearch::is_marked(int v){
		return marked[v];
	}

	int DepthFirstSearch::count() {
		return cnt;
	}
}

#endif