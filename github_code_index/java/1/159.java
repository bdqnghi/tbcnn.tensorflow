package cfalcione.cs303.lab10;

import cfalcione.cs303.lab10.Graph.Graph;
import cfalcione.cs303.shared.GraphSearch;

import java.util.*;

public class BreadthFirstSearch extends GraphSearch {


    public BreadthFirstSearch(Graph graph, int startVertex) {
        super(graph, startVertex);
    }

    public void search(int startVertex) {
        initParents();
        markRoot(startVertex);
        Queue<Integer> queue = new LinkedList<>();
        queue.add(startVertex);

        while (!queue.isEmpty()) {
            int next = queue.remove();
            processVertex(queue, next);
        }
    }

    protected void processVertex(Queue<Integer> queue, int vertex) {
        for (int neighbor : graph.neighbors(vertex)) {
            if (visited(neighbor)) continue;
            setParent(neighbor, vertex);
            queue.add(neighbor);
        }
    }
}
