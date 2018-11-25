

#include "../include/FordFulkerson.h"

void printAugPath(int * path, int u, int s, int t) {
    int i = t;
    std::cout << "Caminho de T a S" << std::endl;
    while(true) {
        std::cout << i << ' ';
        if (i == s) 
            break;
        i = path[i];
    }
    std::cout << std::endl;
}


bool findPath(int ** cap, int * path, int u, int s, int t) {
    bool visited[u];
    std::memset(&visited, 0, sizeof(bool) * u);

    std::queue<int> q;
    q.push(s);          
    visited[s] = true;  
    path[s] = -1;       

    while (!q.empty()) { 
        int i(q.front());
        q.pop();

        
        for (int v = 0; v < u; ++v) {
            if (visited[v] == false && cap[i][v] > 0) {
                q.push(v);	    
                path[v] = i;        
                visited[v] = true;    
            }
        }
    }
    

    return (visited[t] == true);
}



void fordFulkerson(int ** cap, int u, int s, int t) {
    unsigned dummy;
    fordFulkerson(cap, u, s, t, dummy);
}

void fordFulkerson(int ** cap, int u, int s, int t, unsigned & max) {
    int i, j;
    int path[u];

    int ** graph = new int * [u];
    for (i = 0; i < u; ++i) {
        graph[i] = new int[u];
        for (j = 0; j < u; ++j)
            graph[i][j] = cap[i][j];
    }

    max = 0;
    
    while (findPath(graph, path, u, s, t)) {
        int incr(INT_MAX); 

        for (i = t; i != s; i = path[i]) {
            j = path[i];
            incr = min(incr, graph[j][i]);
        }

        
        for (i = t; i != s; i = path[i]) {
            j = path[i];
            graph[j][i] -= incr;
            graph[i][j] += incr;
        }

        
        max += incr;
    }

    for (i = 0; i < u; ++i) {
        for (j = 0; j < u; ++j) {
            cap[i][j] = graph[i][j];
        }
    }

    for (i = 0; i < u; ++i) {
        delete[] graph[i];
    }
    delete[] graph;
}
