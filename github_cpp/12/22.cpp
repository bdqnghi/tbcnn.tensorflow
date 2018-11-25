


#include "stdafx.h"
#include <iostream>
using namespace std;

#include "primAlgorithm.h"
#include "kruskalAlgorithm.h"

#include <cstdio>
#include <ctime>
#include <random>
std::random_device rd;     
std::mt19937 rng(rd());    

int main()
{
	std::clock_t start;
	double duration;

	int V = 8;
	struct Graph* graph = createGraph(V);
	addEdge(graph, 0, 1, 14);
	addEdge(graph, 0, 2, 3);
	addEdge(graph, 1, 3, 6);
	addEdge(graph, 1, 5, 5);
	addEdge(graph, 2, 1, 10);
	addEdge(graph, 2, 4, 8);
	addEdge(graph, 3, 5, 4);
	addEdge(graph, 4, 5, 2);
	addEdge(graph, 4, 7, 15);
	addEdge(graph, 5, 6, 9);

	mstConstructPrim(graph, true);

	V = 7;
	int E = 11;
	struct GraphK* graphk = createGraphK(V, E);
	graphk->edge[0].src = 0;
	graphk->edge[0].dest = 1;
	graphk->edge[0].weight = 8;

	graphk->edge[1].src = 0;
	graphk->edge[1].dest = 2;
	graphk->edge[1].weight = 21;

	graphk->edge[2].src = 1;
	graphk->edge[2].dest = 2;
	graphk->edge[2].weight = 14;

	graphk->edge[3].src = 1;
	graphk->edge[3].dest = 3;
	graphk->edge[3].weight = 2;

	graphk->edge[4].src = 2;
	graphk->edge[4].dest = 3;
	graphk->edge[4].weight = 25;

	graphk->edge[5].src = 2;
	graphk->edge[5].dest = 5;
	graphk->edge[5].weight = 17;

	graphk->edge[6].src = 2;
	graphk->edge[6].dest = 4;
	graphk->edge[6].weight = 13;

	graphk->edge[7].src = 3;
	graphk->edge[7].dest = 5;
	graphk->edge[7].weight = 19;

	graphk->edge[8].src = 4;
	graphk->edge[8].dest = 5;
	graphk->edge[8].weight = 5;

	graphk->edge[9].src = 4;
	graphk->edge[9].dest = 6;
	graphk->edge[9].weight = 1;

	graphk->edge[10].src = 5;
	graphk->edge[10].dest = 6;
	graphk->edge[10].weight = 9;

	cout << endl;
	mstContructKruskal(graphk, E, true);

	delete graph;
	delete graphk;
	cout << endl << endl;

	for (int nodeNumber = 10; nodeNumber <= 1000000; nodeNumber *= 10) {
		std::uniform_int_distribution<int> uni(0, nodeNumber - 1);
		cout << "-----------------------------------------" << endl << endl;
		cout << nodeNumber << " elements" << endl;
		struct Graph* graph = createGraph(nodeNumber);
		for (int i = 0; i < nodeNumber*5; i++) {	
			addEdge(graph, uni(rng), uni(rng), uni(rng));
		}

		std::fflush(stdout);
		start = std::clock();
		mstConstructPrim(graph, false);
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		cout << endl << "Prim time: " << duration << endl;
		std::fflush(stdout);

		int E = nodeNumber*2;		
		struct GraphK* graphk = createGraphK(nodeNumber, E);
		
		for (int i = 0; i < E; i++) {
			int src = uni(rng);
			int dst = uni(rng);
			int weight = uni(rng);
			while (src == dst)
				dst = uni(rng);
			
				
			
				graphk->edge[i].src = src;
				graphk->edge[i].dest = dst;
				graphk->edge[i].weight = weight;
			
		}
		

		std::fflush(stdout);
		start = std::clock();
		mstContructKruskal(graphk, E, false);
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		cout << endl << "Kruskal time: " << duration << endl;
		std::fflush(stdout);

		cout << endl;
	}

	cout << endl;
	system("pause");
    return 0;
}

