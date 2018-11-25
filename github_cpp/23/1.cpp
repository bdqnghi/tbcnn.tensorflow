#include <algorithm>
#include <cstring>
 
#define NODES 100
#define INFTY 1000000000
 
int nodes, cap[NODES][NODES], flow[NODES][NODES];
 
bool srcside[NODES];
 
struct {
	int node, parent, mincap;
} kew[NODES];
 
int low, high;
 
int initbfs(int source, int target) {
	memset(srcside, 0, sizeof srcside);
	srcside[source] = true;
 
	kew[0].node = source;
	kew[0].parent = -1;
	kew[0].mincap = INFTY;
 
	low = 0;
	high = 1;
 
	return target;
}
 
bool bfs(int target) {
	int from, to;
 
	while (low < high && (from = kew[low].node) != target) {
		for (to = 0; to < nodes; ++to) {
			if (!srcside[to] && cap[from][to] > flow[from][to]) {
				srcside[to] = true;
 
				kew[high].node = to;
				kew[high].parent = low;
				kew[high].mincap = min(kew[low].mincap, cap[from][to] - flow[from][to]);
 
				++high;
			}
		}
 
		++low;
	}
 
	return low < high;
}
 
int maxflow(int source, int target) {
	int i, j, res = 0;
 
	memset(flow, 0, sizeof flow);
	while (bfs(initbfs(source, target))) {
		res += kew[low].mincap;
		for (i = low; i > 0; i = j) {
			j = kew[i].parent;
			flow[kew[j].node][kew[i].node] += kew[low].mincap;
			flow[kew[i].node][kew[j].node] -= kew[low].mincap;
		}
	}
 
	return res;
}
