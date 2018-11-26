/*
Implementation of Minimum Spanning Tree using Prim's Algorithm
*/

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

// Adjacency list stores destination - weight pairs for each source
vector<vii> AdjList;

// boolean flags used to avoid cycles
vi taken;

// priority queue used to choose shortest edges
priority_queue<ii> pq;

void process(int);

int main() {

	int tests;   // number of tests
	int V;       // number of vertices
	int E;       // number of weighted undirected edges 
	int src;     // source vertex for edge;
	int dst;     // destination vertex for edge;
	int weight;  // weight of edge
	int mstCost; // minimum spanning tree cost

	// read number of tests
	scanf("%d", &tests);

	// process each test
	for (int test = 1; test <= tests; test++) {

		// read number of vertices and edges
		scanf("%d %d", &V, &E);

		// quick way to initialize AdjList with V entries of vii
		AdjList.assign(V, vii()); 

		// read edge data
		for (int edge = 0; edge < E; edge++) {
			scanf("%d %d %d", &src, &dst, &weight);
			AdjList[src].push_back(ii(dst, weight));
			AdjList[dst].push_back(ii(src, weight));
		}

		// initialise boolean array
		taken.assign(V, 0);

		// take vertex 0 and process all edges incident to vertex 0;
		process(0);
		mstCost = 0;

		// repeat until V vertices (E = V - 1 edges) are taken
		while (!pq.empty()) {
			ii front = pq.top();
			pq.pop();

			// negate the id and weight again
			dst = -front.second;
			weight = -front.first;

			// if vertex is not yet connected
			if (!taken[dst]) {

				// take dst and process all edges incident to dst
				// each edge is in pq only once
				mstCost += weight;
				process(dst);
			}
		}

		// output
		printf("Test %d, minimum spanning tree weight = %d\n", test, mstCost);
	}


	return 0;
}

void process(int vtx) {
	taken[vtx] = 1;
	for (int j = 0; j < AdjList[vtx].size(); j++) {
		ii v = AdjList[vtx][j];
		if (!taken[v.first]) {

			// sorting by increasing weight then increasing vertex id
			// negating the values reverses the orer
			pq.push(ii(-v.second, -v.first));
		}
	}
}