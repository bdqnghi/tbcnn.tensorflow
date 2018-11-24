/*
 * Version 
 * Author: WildfootW
 * GitHub: github.com/Wildfoot
 * Copyright (C) 2018 WildfootW All rights reserved.
 *
 */

// Wrong Answer

#include <iostream>
#include <ctime>

#define INF 2147483647
#define EPS 1e-9

using namespace std;

//  Spanning Tree
//      A spanning tree of the graph is a tree that contains all vertices in the graph
//  Minimum Spanning Tree
//      Spanning Tree with minimum cost
//
//- Kruskal’s Algorithm     O(E lgE)
//      1. sort the edges with their cost
//      2. start at minimum edge. if the nodes connect with the edge is not connected, select the edge.
//
//- Prim’s Algorithm        O(V ^ 2) | With Binary-Heap O( (V+E) lgV )
//      1. select a start node
//      2. find the edge has one side connected with the tree(start node) which has minimum cost, connected it.
//
//- Compare
//      Kruskal’s algorithm may form a forest during the process.
//      Prim’s algorithm only maintain a tree during the process.

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    clog << "Time used = " << (double)clock() / CLOCKS_PER_SEC << endl;
    return 0;
}

