/**
 *
 * Given a weighted, undirected and connected graph. The task is to find the sum of weights of  the edges of the Minimum Spanning Tree. You need to complete the function spanningTree which takes a graph g as its argument and returns an integer denoting the sum of weights of the edges of the Minimum Spanning Tree.

    Input:
        The first line of input contains an integer T denoting the no of test cases . Then T test cases follow. The first line of each test case contains two integers n,e denoting the no of nodes and no of edges. Then in the next line are E*3 space separated values a b w where a,b denotes an edge from a to b and w is the weight of the edge.

    Output:
        For each test case in a new line print the sum of weights of  the edges of the Minimum Spanning Tree formed of the graph.

*
* Constraints:
    1<=T<=10
    1<=n,e<=100
    1<=w<=1000

*/

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <limits>
using namespace std;


int minKey(std::unordered_set<int>& visited, std::unordered_map<int, int>& nodeDistance) {
    std::unordered_map<int, int>::iterator it = nodeDistance.begin();
    std::unordered_set<int>::iterator vit;
    int minIdx = 1;
    int minValue = std::numeric_limits<int>::max();
    for (; it != nodeDistance.end(); ++it) {
        vit = visited.find(it->first);
        if (vit == visited.end()) {
            if (it->second < minValue) {
                minValue = it->second;
                minIdx = it->first;
            }
        }
    }
    return minIdx;
}


void updateDistance(vector <pair<int, int> > g[], int src, std::unordered_map<int, int>& nodeDistance) {
    vector<pair<int, int> > adjacentNodes = g[src];
    for (vector<pair<int, int> >::iterator it = adjacentNodes.begin(); it != adjacentNodes.end(); ++it) {
        nodeDistance[it->first] = it->second;
    }
}


int spanningTree(vector <pair<int,int> > g[], int MAX)
{
	//Your code here
    int N = MAX;
    int weights = 0;
    std::unordered_set<int> visited;
    std::unordered_map<int, int> nodeDistance;
    for (int i = 1; i <= N; ++i) {
        nodeDistance.insert(std::make_pair(i, std::numeric_limits<int>::max()));  
    }

    nodeDistance[1] = 0;
    int count = 0;
    while (visited.size() != N) {
        int nextNode = minKey(visited, nodeDistance);
        visited.insert(nextNode);
        weights += nodeDistance[nextNode];
        //cout << "next: " << nextNode << ", weights: " << weights << endl;
        updateDistance(g, nextNode, nodeDistance);
    }

    return weights;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, E;
        cin >> N >> E;
        vector<pair<int, int> > g[N + 1];
        while (E--) {
            int a, b, w;
            cin >> a >> b >> w;
            g[a].push_back(std::make_pair(b, w));
            g[b].push_back(std::make_pair(a, w));
        }

        int weights = spanningTree(g, N);
        cout << weights << endl;
    }

    return 0;
}


