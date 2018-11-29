package com.company;

import java.util.*;

/**
 * Created by volodyko on 14.02.17.
 */
public class BFSMain {
    public static void main(String[] args) {
        BFS bfs = new BFS();

        bfs.addVertex("S");
        bfs.addVertex("A");
        bfs.addVertex("B");
        bfs.addVertex("C");
        bfs.addVertex("D");


        bfs.addEdege(bfs.getVertex("S"), bfs.getVertex("A"));
        bfs.addEdege(bfs.getVertex("S"), bfs.getVertex("B"));
        bfs.addEdege(bfs.getVertex("S"), bfs.getVertex("C"));
        bfs.addEdege(bfs.getVertex("A"), bfs.getVertex("D"));
        bfs.addEdege(bfs.getVertex("B"), bfs.getVertex("D"));
        bfs.addEdege(bfs.getVertex("C"), bfs.getVertex("D"));

        bfs.bfs();

    }

}
