

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


