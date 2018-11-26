/*
 * @file FordFulkerson.cpp
 *      
 * @author: Fabio Cruz B. de Albuquerque
 * 
 * @date: 03/31/2015
 */

#include "../include/FordFulkerson.h"

void printAugPath(int * path, int u, int s, int t) {
    int i = t;
    std::cout << "Caminho de T a S" << std::endl;
    while(true) {
        std::cout << i << ' ';
        if (i == s) // se chegou a S (origem)
            break;
        i = path[i];
    }
    std::cout << std::endl;
}

/**
 * Caminho aumentante
 * breath-first search
 */
bool findPath(int ** cap, int * path, int u, int s, int t) {
    bool visited[u];
    std::memset(&visited, 0, sizeof(bool) * u);

    std::queue<int> q;
    q.push(s);          // enfileira origem	
    visited[s] = true;  // marca com visitando
    path[s] = -1;       // origem

    while (!q.empty()) { // enquanto fila nao for vazia
        int i(q.front());
        q.pop();

        // para cada vizinho nao visitado e com residuo maior que zero
        for (int v = 0; v < u; ++v) {
            if (visited[v] == false && cap[i][v] > 0) {
                q.push(v);	    // enfileira
                path[v] = i;        // visitada a partir de i
                visited[v] = true;    // marca como visitando
            }
        }
    }
    //    if (color2[t]) printAugPath(path, u, s, t);

    return (visited[t] == true);
}

/*
 * Algoritmo de ford fulkerson
 */

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
    // enquanto houver caminhos aumentantes
    while (findPath(graph, path, u, s, t)) {
        int incr(INT_MAX); // menor capacidade possível de ser incrementada

        for (i = t; i != s; i = path[i]) {
            j = path[i];
            incr = min(incr, graph[j][i]);
        }

        // aumenta os fluxos e diminui os resíduos
        for (i = t; i != s; i = path[i]) {
            j = path[i];
            graph[j][i] -= incr;
            graph[i][j] += incr;
        }

        // aumenta o fluxo total da rede
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
