package com.nagarro.algorithms.graph;

public final class BFSMain {

    public static void main(final String[] args) {
        final BFS bfs = new BFS(8);
        bfs.addVertex('A');
        bfs.addVertex('B');
        bfs.addVertex('C');
        bfs.addVertex('D');
        bfs.addVertex('E');
        bfs.addVertex('F');
        bfs.addVertex('G');
        bfs.addVertex('H');

        bfs.addEdge(0, 1);
        bfs.addEdge(1, 2);
        bfs.addEdge(1, 7);
        bfs.addEdge(2, 3);
        bfs.addEdge(2, 4);
        bfs.addEdge(4, 5);
        bfs.addEdge(4, 6);
        bfs.addEdge(4, 7);

        bfs.bfs();
    }

}
