import base.Question;
import graph.Graph;
import graph.Vertex;

import java.util.*;

public class BreadthFirstSearch implements Question {


    @Override
    public void run() {
        Graph g = new Graph();
        g.addVertex(0, 0);
        g.addVertex(1,1);
        g.addVertex(2,2);

        g.addVertex(3, 3);
        g.addVertex(4, 4);
        g.addVertex( 5, 5 );

        g.addEdge( 0, 5 );
        g.addEdge(1, 2);
        g.addEdge(2, 3);
        g.addEdge( 1, 3);
        g.addEdge(2, 5);
        g.addEdge(2, 4);


        Vertex root = g.findVertex(1);
        bfs(g, root, 6);

        // Will print something like this:
        /*
        V:1,1
          V:3,3
          V:2,2
            V:4,4
            V:5,5
              V:0,0

         */
    }

    /**
     * Find vertex w/ this value.
     * Breadth first search is best implemented using a queue.
     * @param g
     * @param value
     * @return
     */
    public Vertex bfs(Graph g, Vertex root, int value ) {
        Deque<Vertex> Q = new ArrayDeque<>();
        Q.add(root);
        // vertex , parent
        Map<Vertex, Vertex> discoveredList = new HashMap<>();
        discoveredList.put(root, null);

        while(!Q.isEmpty()) {
            Vertex current = Q.pop();
            if(current.getValue() == value) {
                printBFSTree(discoveredList, root, 0);
                return current;
            }
            for(Vertex n: g.neighbors(current)) {
                if(!discoveredList.containsKey(n)){
                    discoveredList.put(n, current);
                    Q.add(n);
                }
            }
        }
        printBFSTree(discoveredList,root,0);
        return null;
    }

    private void printBFSTree(Map<Vertex, Vertex> discoveredList, Vertex root, int depth) {
        // Find vertices w/ root as parent
        for(int i =0;i<depth;i++) System.out.print("  ");
        System.out.print(root);
        System.out.print("\n");
        for(Map.Entry<Vertex,Vertex> entry:  discoveredList.entrySet()) {
            if(entry.getValue()!=null && entry.getValue().equals(root)){
                int newDepth = depth+1;
                printBFSTree(discoveredList, entry.getKey(), newDepth);
            }
        }
    }

}
