package bfs;

import graphReader.GraphReader;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class BreadthFirstSearch {

    private static boolean[] visited;
    private static List<List<Integer>> graph;

    public static void main(String[] args) throws IOException {

        graph = GraphReader.readGraph();
        visited = new boolean[graph.size()];
        for (int vertex = 0; vertex < graph.size(); vertex++) {
            if (!visited[vertex]) {
                bfs(vertex);
                System.out.println();
            }
        }
    }

    private static void bfs(int vertex) {
        List<Integer> queue = new LinkedList<>();
        queue.add(vertex);
        visited[vertex] = true;

        while (queue.size() > 0) {
            int currVertex = queue.remove(0);
            System.out.print(currVertex + " ");
            List<Integer> children = graph.get(currVertex);

            for (Integer child : children) {
                if (!visited[child]) {
                    visited[child] = true;
                    queue.add(child);
                }
            }
        }
    }
}
