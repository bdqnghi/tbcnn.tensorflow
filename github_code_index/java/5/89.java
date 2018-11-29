package algoritms.graph;

import algoritms.utilityclasses.Graph;

import java.util.Stack;

/**
 * Created by Sigora on 27.10.2015.
 */
public class DFS {
    public static void main(String[] args) {
        Graph<Integer> g = new Graph<>(4);

        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 2);
        g.addEdge(2, 0);
        g.addEdge(2, 3);
        g.addEdge(3, 3);

        DFS dfs = new DFS();
        System.out.println("Recursive");
        dfs.DFSRecursive(2, g);
        System.out.println("Iterative");
        dfs.DFSIterative(2, g);

    }

    private void DFSRecursive(int v, Graph<Integer> g){
        boolean [] visited = new boolean[g.getVertexNumber()];

        DFSRecursive(v, visited, g);
    }

    private void DFSRecursive(int v, boolean [] visited, Graph<Integer> g){
        visited[v] = true;
        System.out.println("Visited vertex " + v);

        g.getAdjList(v).stream().filter(adj -> !visited[adj]).forEach(adj -> {
            DFSRecursive(adj, visited, g);
        });
    }

    private void DFSIterative(int v, Graph<Integer> g){
        boolean [] visited = new boolean[g.getVertexNumber()];

        visited[v] = true;
        Stack<Integer> stack = new Stack<>();
        stack.push(v);

        while (!stack.isEmpty()){
            v = stack.pop();
            System.out.println("Visited vertex " + v);
            for(int adj : g.getAdjList(v)){
                if(!visited[adj]){
                    visited[adj] = true;
                    stack.push(adj);
                }
            }
        }
    }


}
