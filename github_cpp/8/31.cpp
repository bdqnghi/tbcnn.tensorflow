/*
Given a set of n jobs with [start time, end time, cost] find a subset so that no 2 jobs overlap and the cost is maximum.
DP+二分:
Sort the intervals based on end time
define p(i) for each interval, giving the biggest end point which is smaller than the start point of i-th interval. Use binary search to obtain nlogn
define d[i] = max(w(i) + d[p(i)], d[i-1]).

initialize d[0] = 0
The result will be in d[n] n- the number of intervals.
Overall complexity O(nlogn)
*/
#include<vector>
#include<string.h>
#include <stdio.h>
#include<iostream>
#include<algorithm>
#include<map>
#include<unordered_map>
#include<unordered_set>

#include<set>
#include<mutex>
#include<thread>
#include<condition_variable>


#include<queue>
#include<list>
#include<limits.h>
#include "leetcode.h"
using namespace std;

typedef unordered_map<int, unordered_set<int> > Graph;
vector<int> topologicalsort(Graph & g) {
	vector<int> ret;
	unordered_set<int> visited;
	function<void(int)> dfs=[&](int i) {
		visited.insert(i);
		for (auto &node: g[i]) 
			if (!visited.count(node)) dfs(node);
		ret.push_back(i);
	};
	for (auto &nnode:g)
		dfs(nnode.first);
	return ret;
}

int main() {
	Graph g {{1,{2,3}},{2,{4,5}},{3,{4}},{4,{6}},{5,{6}},{6,{}}};
	vector<int> ret= topologicalsort(g);
	for (auto& s: ret) cout<<s<<endl;
	// sort_food("  pizza  1 hotdog 2.0", 5);
	// sort_food("pizza 500 hotdog 2.0 ", 5);
	// sort_food(" pizza  500 2.0 ", 5);
	return 0;
}

