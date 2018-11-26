/*
 * MinimumSpanningTree.h
 *
 *  Created on: Apr 26, 2015
 *      Author: brentmitchell
 */

#ifndef MINIMUMSPANNINGTREE_H_
#define MINIMUMSPANNINGTREE_H_
#include "SkewHeap.h"
#include "Edge.h"
#include "DisjointSet.h"
#include "SetNode.h"
#include "Queue.h"
#include <limits.h>

class MinimumSpanningTree {
public:
	MinimumSpanningTree();
	virtual ~MinimumSpanningTree();
	void kruskal(int adjMat[], int dim);
	void prim(int adjMat[], int dim);
private:
	void printMST(Queue<Edge> &q, int dim);
};

MinimumSpanningTree::MinimumSpanningTree() {

}

MinimumSpanningTree::~MinimumSpanningTree() {

}

void MinimumSpanningTree::kruskal(int adjMat[], int dim) {
	SkewHeap<Edge> mlh;
	DisjointSet<int> ds;
	for (int i = 0; i < dim; i++) {
		for (int j = i * dim; j < (i + 1) * dim; j++) {
			ds.makeSet(i * dim + j);
			if (adjMat[j] > 0) {
				Edge e(i, j % dim, adjMat[j]);
				mlh.insert(e);

			}
		}
	}

	std::cout << "Kruskal: ";
	Queue<Edge> q;
	for (int i = 0; i < dim * dim; i++) {
		Edge *e = mlh.deletemin();
		if (e == NULL)
			break;
		SetNode<int> v(e->v);
		SetNode<int> w(e->w);
		if (ds.find(&v) != ds.find(&w)) {
			q.enqueue(*e);
			ds.unionSets(&v, &w);
		}
	}

	printMST(q, dim);

}

void MinimumSpanningTree::prim(int adjMat[], int dim) {
	std::cout << "Prim: ";
	int graph[dim][dim];
	int min = INT_MAX;
	bool visited[dim];

	for (int i = 0; i < dim; i++) {
		visited[i] = false;
		for (int j = i * dim; j < (i + 1) * dim; j++) {
			graph[i][j % dim] = adjMat[j];
			if (graph[i][j % dim] == 0)
				graph[i][j % dim] = min;
		}
	}

	int v = 0, w = 0;
	visited[0] = true;
	Queue<Edge> q;
	for (int a = 0; a < dim - 1; a++) {
		min = INT_MAX;
		for (int i = 0; i < dim; i++) {
			if (visited[i]) {
				for (int j = 0; j < dim; j++) {
					if (!visited[j]) {
						if (min > graph[i][j]) {
							min = graph[i][j];
							v = i;
							w = j;
						}
					}
				}
			}
		}
		visited[w] = true;
		if (v < dim && w < dim) {
			Edge e(v, w, graph[v][w]);
			q.enqueue(e);
		}
	}

	printMST(q, dim);
}

void MinimumSpanningTree::printMST(Queue<Edge> &q, int dim) {
	if (q.getSize() == dim - 1) {
		while (!q.isEmpty()) {
			Edge e = q.dequeue();
			std::cout << "(" << std::min(e.v, e.w) << "," << std::max(e.v, e.w)
					<< ") ";
		}
	} else {
		std::cout << "No Solution!";
	}
	std::cout << std::endl;
}

#endif /* MINIMUMSPANNINGTREE_H_ */

