/**
 * Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices 
 * such that for every directed edge uv, vertex u comes before v in the ordering. 
 * Topological Sorting for a graph is not possible if the graph is not a DAG.
 * 
 * 
 *                          Algorithm 
 * We can modify DFS to find Topological Sorting of a graph. 
 * In DFS, we start from a vertex, we first print it and then recursively call DFS for its adjacent vertices. 
 * In topological sorting, we use a temporary stack. 
 * We don’t print the vertex immediately, we first recursively call topological sorting for all its adjacent vertices, 
 * then push it to a stack. 
 * Finally, print contents of stack. 
 * Note that a vertex is pushed to stack only 
 * when all of its adjacent vertices (and their adjacent vertices and so on) are already in stack.
 */

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")

class TopologicalSort {
    int vertices;
    LinkedList<Integer>[] adjacencyList;

    TopologicalSort(int vertices) {

        this.vertices = vertices;
        adjacencyList = new LinkedList[vertices];

        for (int i = 0; i < vertices; i++)
            adjacencyList[i] = new LinkedList<Integer>();
    }

    void addEdge(int v, int w) {
        adjacencyList[v].add(w);
    }

    void TopologicalSortingUtil(int node, boolean[] visited, Stack stack){

            visited[node] = true;

            Iterator<Integer> iterator = adjacencyList[node].listIterator();

            while (iterator.hasNext()) {

                int num = iterator.next();
                if (!visited[num]) {
                    TopologicalSortingUtil(num, visited, stack);
                }
            }
            stack.push(node);
    }

    void TopologicalSorting() {

        System.out.print("Topological Sorting of the Graph : ");

        boolean[] visited = new boolean[vertices];

        Stack<Integer> stack = new Stack<Integer>();

        for(int i=0 ; i<vertices; i++){
            if(!visited[i]){
                TopologicalSortingUtil(i, visited, stack);
            }
        }

        while(!stack.isEmpty()){
            System.out.print(stack.pop()+" ");
        }

        System.out.print("\n");
    }

    public static void main(String[] args) {

        TopologicalSort TopologicalSort = new TopologicalSort(6);

        TopologicalSort.addEdge(5, 2);
        TopologicalSort.addEdge(5, 0);
        TopologicalSort.addEdge(4, 0);
        TopologicalSort.addEdge(4, 1);
        TopologicalSort.addEdge(2, 3);
        TopologicalSort.addEdge(3, 1);

        TopologicalSort.TopologicalSorting();
    }
}