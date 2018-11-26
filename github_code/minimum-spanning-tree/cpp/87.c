#ifndef MINIMUM_SPANNING_TREE
#define MINIMUM_SPANNING_TREE

#include <bits/stdc++.h>
#include "evaluator.cpp"

using namespace std;

vector<vector<int>> build_adjacency_list(const vector<int> &parents) {
    vector<vector<int>> g(parents.size());
    for (int i = 0; i < parents.size(); ++i) {
        if (parents[i] != -1) {
            g[parents[i]].push_back(i);
        }
    }
    return g;
}

// returns parents for all vertices except the root
vector<int> find_minimum_spanning_tree(const vector<point> &points, int root) {
    vector<int> parents(points.size()), used(points.size()), id(points.size());
    vector<double> min_dists(points.size());
    parents[root] = -1;
    used[root] = 1;
    for (int i = 0; i < points.size(); ++i) {
        min_dists[i] = dist(points[root], points[i]);
        id[i] = root;
    }
    for (int i = 1; i < points.size(); ++i) {
        int to = -1;
        for (int j = 0; j < points.size(); ++j) {
            if (used[j] == 0 && (to == -1 || min_dists[to] > min_dists[j])) {
                to = j;
            }
        }
        parents[to] = id[to];
        used[to] = 1;
        for (int j = 0; j < points.size(); ++j) {
            if (used[j] == 0 && min_dists[j] > dist(points[to], points[j])) {
                min_dists[j] = dist(points[to], points[j]);
                id[j] = to;
            }
        }
    }
    return parents;
}

#endif // MINIMUM_SPANNING_TREE
