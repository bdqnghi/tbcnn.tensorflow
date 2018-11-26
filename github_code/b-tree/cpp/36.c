//b.cpp
//By Saul de Nova

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <utility>
#include <vector>

#define TR(container, it) \
	for(typeof(container.begin()) it = container.begin(); it != container.end(); it++)

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 1002;

int N;
list<int> brothers[MAXN];
pii mem[MAXN][MAXN];

bool sorter(const pii &a, const pii &b) {
	return (a.first == b.first ? a.second > b.second : a.first < b.first);
}

pii getTree(int a, int parent) {
	//printf("%d %d\n", a, parent);
	int p = 0;
	int size = brothers[a].size() - 1;
	if(parent == -1) {
		size++;
	}
	if(size <= 0) {
		return make_pair(1, 0);
	}
	pii* sizes = new pii[size];
	int sum = 0;
	TR(brothers[a], brother) {
		if(*brother != parent) {
			sizes[p] = getTree(*brother, a);
			sum += sizes[p].first;
			p++;
		}
	}
	if(size == 1) {
		return make_pair(sum + 1, sum);
	}
	sort(sizes, sizes + size, sorter);
	/*if(parent == -1 && a == 1) {
		for(int i = 0; i < size; i++) {
			printf(">>%d %d\n", sizes[i].first, sizes[i].second);
		}
		printf("\n");
	}//*/
	int toRemove = sizes[p - 1].second + sizes[p - 2].second;
	for(int i = 0; i < size - 2; i++) {
		toRemove += sizes[i].first;
	}
	return make_pair(sum + 1, toRemove);
}

int main(void) {
	int T, a, b;
	scanf("%d", &T);
	for(int t = 0; t < T; t++) {
		scanf("%d", &N);
		for(int i = 0; i < N - 1; i++) {
			scanf("%d%d", &a, &b); 
			brothers[a].push_back(b);
			brothers[b].push_back(a);
		}
		int minRemove = 1E9;
		for(int i = 1; i <= N; i++) {
			int val = getTree(i, -1).second;
			if(minRemove > val) {
				minRemove = val;
				//printf(">%d %d\n", i, val);
			}
			//minRemove = min(minRemove, getTree(i).second);
		}

		printf("Case #%d: %d\n", t + 1, minRemove);

		for(int i = 1; i <= N; i++) {
			brothers[i].clear();
		}
	}
	return 0;
}
