package bfs.java.simple;

import java.util.PriorityQueue;
import java.util.Queue;

/**
 * Created by claas on 7/10/2016.
 * Used to perform Breadth-First-Search (BFS) using adjacency matrices.
 * For a faster implementation, see @see ../fast/BFS.java (using adjacency Lists)
 */
public class BFS {
    /**
     * Implementation of Breadth-First-Search using adjacency matrix.
     * This returns nothing (yet), it is meant to be a template for whatever you want to do with it,
     * e.g. finding the shortest path in a unweighted graph.
     * This has a runtime of O(|V|^2) (|V| = number of Nodes), for a faster implementation see @see ../fast/BFS.java (using adjacency Lists)
     * @param graph an adjacency-matrix-representation of the graph where (x,y) is true if the the there is an edge between nodes x and y.
     * @param start the node to start from.
     */
    public static void bfs(boolean[][] graph, int start){
        //A Queue to manage the nodes that have yet to be visited
        Queue<Integer> queue = new PriorityQueue<>();
        //Adding the node to start from
        queue.add(start);
        //A boolean array indicating whether we have already visited a node
        boolean[] visited = new boolean[graph.length];
        //(The start node is already visited)
        visited[start] = true;
        //While there are nodes left to visit...
        while(!queue.isEmpty()) {
            int node = queue.remove();
            //...for all neighboring nodes that haven't been visited yet....
            for (int i = 1; i < graph[node].length; i++) {
                if(graph[node][i] && !visited[i]){
                    //Visit it and add it to the queue
                    visited[i] = true;
                    queue.add(i);
                }
            }

        }

    }
}
