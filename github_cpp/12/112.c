

#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;


vector<vii> AdjList;


vi taken;


priority_queue<ii> pq;

void process(int);

int main() {

	int tests;   
	int V;       
	int E;       
	int src;     
	int dst;     
	int weight;  
	int mstCost; 

	
	scanf("%d", &tests);

	
	for (int test = 1; test <= tests; test++) {

		
		scanf("%d %d", &V, &E);

		
		AdjList.assign(V, vii()); 

		
		for (int edge = 0; edge < E; edge++) {
			scanf("%d %d %d", &src, &dst, &weight);
			AdjList[src].push_back(ii(dst, weight));
			AdjList[dst].push_back(ii(src, weight));
		}

		
		taken.assign(V, 0);

		
		process(0);
		mstCost = 0;

		
		while (!pq.empty()) {
			ii front = pq.top();
			pq.pop();

			
			dst = -front.second;
			weight = -front.first;

			
			if (!taken[dst]) {

				
				
				mstCost += weight;
				process(dst);
			}
		}

		
		printf("Test %d, minimum spanning tree weight = %d\n", test, mstCost);
	}


	return 0;
}

void process(int vtx) {
	taken[vtx] = 1;
	for (int j = 0; j < AdjList[vtx].size(); j++) {
		ii v = AdjList[vtx][j];
		if (!taken[v.first]) {

			
			
			pq.push(ii(-v.second, -v.first));
		}
	}
}