package com.graph;



import java.util.*;

public class TopologicalSort {
  private int V;
  private LinkedList<Integer> adj[];

  //Constructor
  TopologicalSort(int v) {
    V = v;
    adj = new LinkedList[v];
    for (int i = 0; i < v; ++i)
      adj[i] = new LinkedList();
  }

  // Function to add an edge into the graph
  void addEdge(int v, int w) {
    adj[v].add(w);
  }

  // A recursive function used by topologicalSort
  void topologicalSortUtil(int s, boolean visited[],
                           Stack stack)
  {
    // Mark the current node as visited.
    visited[s] = true;
    Integer n;

    // Recur for all the vertices adjacent to this
    // vertex
    Iterator<Integer> i = adj[s].iterator();
    while (i.hasNext())
    {
      n = i.next();
      if (!visited[n])
        topologicalSortUtil(n, visited, stack);
    }

    // Push current vertex to stack which stores result
    stack.push(new Integer(s));
  }

  // The function to do Topological Sort. It uses
  // recursive topologicalSortUtil()
  void topologicalSort()
  {
    Stack stack = new Stack();

    // Mark all the vertices as not visited
    boolean visited[] = new boolean[V];
    // Call the recursive helper function to store
    // Topological Sort starting from all vertices
    // one by one
    for (int i = 0; i < V; i++)
      if (visited[i] == false)
        topologicalSortUtil(i, visited, stack);

    // Print contents of stack
    while (stack.empty()==false)
      System.out.print(stack.pop() + " ");
  }

  public static void main(String args[]) {
    // Create a graph given in the above diagram
    TopologicalSort g = new TopologicalSort(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    System.out.println("Following is a Topological " +
        "sort of the given graph");
    g.topologicalSort();
  }


}
