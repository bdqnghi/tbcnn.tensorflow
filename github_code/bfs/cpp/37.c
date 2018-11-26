//
//  breadthFirstSearch.cpp
//  Rosalind
//
//  Created by John Flanigan on 8/31/16.
//  Copyright © 2016 rosalind. All rights reserved.
//

#include "breadthFirstSearch.hpp"
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>

class Node {
public:
    std::vector<int> adjacencyVector;
    int prev = -1;
    bool visted = false;
};

void breadthFirstSearch() {

    int numberOfVertices, numberOfEdges, to, from;
    
    std::ifstream file;
    file.open ("/Users/johnflanigan/Developer/Rosalind/Rosalind/rosalind_bfs.txt");
    
    file >> numberOfVertices >> numberOfEdges;
    
    std::map<int, Node> verticesMap;
    
    for (int i = 0; i < numberOfEdges; i++) {
        file >> to >> from;
        to--;
        from--;
        verticesMap[to].adjacencyVector.push_back(from);
    }
    
    std::queue<int> queue;
    
    verticesMap[0].visted = true;
    queue.push(0);
    
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        
        while (!verticesMap[v].adjacencyVector.empty()) {
            int w = verticesMap[v].adjacencyVector.back();
            verticesMap[v].adjacencyVector.pop_back();
            if (verticesMap[w].visted == false) {
                verticesMap[w].visted = true;
                verticesMap[w].prev = v;
                queue.push(w);
            }
        }
    }
    
    // Shortest path
    for (int i = 0; i < numberOfVertices; i++) {
        int counter = 0;
        int current = i;
        while(verticesMap[current].prev != -1) {
            current = verticesMap[current].prev;
            counter++;
        }
        if (i != 0 && counter == 0){
            std::cout << -1 << " ";
        } else {
        std::cout << counter << " ";
        }
    }
    
    std::cout << std::endl;
}

