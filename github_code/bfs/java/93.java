package com.test.graph.bfs;

import java.util.LinkedList;
import java.util.Queue;

/**
 * Created by kunal on 06/11/17.
 */
public class BFS {

    public void bfs(final Vertex root) {
        Queue<Vertex> queue = new LinkedList<>();

        if (root != null) {
            root.setVisited(true);
            queue.add(root);

            while (!queue.isEmpty()) {
                Vertex vertex = queue.remove();
                System.out.println(vertex.toString());

                for (Vertex child : vertex.getNeighbourList()) {
                    if(!child.isVisited()){
                        child.setVisited(true);
                        queue.add(child);
                    }       
                }
            }
        }

    }
}
