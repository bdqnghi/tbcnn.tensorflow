/*
Kruskal's MST Algorithm
-----------------------
Kruskal's algorithm is a minimum-spanning-tree algorithm which
 finds an edge of the least possible weight that connects any 
 two trees in the forest.[1] It is a greedy algorithm in graph 
 theory as it finds a minimum spanning tree for a connected 
 weighted graph adding increasing cost arcs at each step.
-----------------------
Time Complexity : O(m*logn)
Space Complexity : O(n)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;

struct edge{
	int start, end;
	int weight;
	bool operator <(const edge &e) const{
		return (weight < e.weight);
	}
};

struct edge edges[100];

struct node{
	int parent;
	int rank;
};

struct node disjoint_set_union[100];

void makeset(int x){
	disjoint_set_union[x].parent = x;
	disjoint_set_union[x].rank = 0;
}

int find(int x){
	if (disjoint_set_union[x].parent == x){
		return x;
	}
	disjoint_set_union[x].parent = find(disjoint_set_union[x].parent);
	return disjoint_set_union[x].parent;
}

void join(int x, int y){
	int x_root = find(x);
	int y_root = find(y);
	if (x_root == y_root){
		return ;
	}
	if (disjoint_set_union[x_root].rank < disjoint_set_union[y_root].rank){
		disjoint_set_union[x_root].parent = y_root;
	} else if (disjoint_set_union[x_root].rank > disjoint_set_union[y_root].rank){
		disjoint_set_union[y_root].parent = x_root;
	} else{
		disjoint_set_union[y_root].parent = x_root;
		disjoint_set_union[x_root].rank++;
	}
}

int kruskal(){
	int returned = 0, num_components = n;
	for (int i = 0; i < n; i++){
		makeset(i);
	}
	sort(edges, edges + m);
	for (int i = 0; i < m and num_components > 1; i++){
		if (find(edges[i].start) != find(edges[i].end)){
			join(edges[i].start, edges[i].end);
			returned += edges[i].weight;
			num_components--; 
		}
	}
	if (num_components > 1){
		return -1;
	}
	return returned;
}
