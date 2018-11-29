package dfs;

import graphReader.GraphReader;

import java.io.IOException;
import java.util.List;

public class DepthFirstSearch {

    private static boolean[] visited;
    private static List<List<Integer>> graph;

    public static void main(String[] args) throws IOException {

        graph = GraphReader.readGraph();
        visited = new boolean[graph.size()];

        for (int i = 0; i < graph.size(); i++) {
            if (!visited[i]) {
                dfs(i);
                System.out.println();
            }
        }
    }

    private static void dfs(int vertex) {

        if (!visited[vertex]) {
            visited[vertex] = true;
            List<Integer> children = graph.get(vertex);
            for (int i = 0; i < children.size(); i++) {
                dfs(children.get(i));
            }
            printVertex(vertex);
        }
    }

    private static void printVertex(int vertex) {
        System.out.print(vertex + " ");
    }
}
