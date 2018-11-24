#include <stdio.h>
#include <vector>
#include <queue>
#include <assert.h>
#include <limits>

std::vector<std::vector<std::pair<int, int>>> adj;

int shortest_path(int from, int to) {
    std::priority_queue<std::pair<int, int>> q;
    std::vector<int> dist(adj.size(), std::numeric_limits<int>::max());
    q.push({0, 0});
    while (!q.empty()) {
        auto tmp = q.top(); q.pop();
        if (dist[tmp.second] <= -tmp.first) continue;
        dist[tmp.second] = -tmp.first;
        if (tmp.second == to) return -tmp.first;
        for (auto x: adj[tmp.second])
            q.push({tmp.first-x.second, x.first});
    }
    return dist[to];
}

int main() {
    FILE *fr, *fw;
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

    int N, A, B;
    assert(3 == fscanf(fr, "%d%d%d", &N, &A, &B));
    adj.resize(N);

    for(int i = 0; i < A + B; i++) {
        int a, b;
        assert(2 == fscanf(fr, "%d%d", &a, &b));
        a--;
        b--;

        int weight = (i >= A) ? 1 : 0;
        adj[a].push_back({b, weight});
        adj[b].push_back({a, weight});
    }

    fprintf(fw, "%d\n", shortest_path(0, N-1));
    fclose(fr);
    fclose(fw);
    return 0;
}

