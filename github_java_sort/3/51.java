package algorithms;
import java.io.*;
import java.util.*;
 

public class togologicalsort {
	
	private int V;  
    private LinkedList<Integer> adj[]; 
 
    
    togologicalsort(int v)
    {
        V = v;
        adj = new LinkedList[v];
        for (int i=0; i<v; ++i)
            adj[i] = new LinkedList();
    }
 
    
    void addEdge(int v,int w) { adj[v].add(w); }
 
    
    void topologicalSortUtil(int v, boolean visited[],
                             Stack stack)
    {
        
        visited[v] = true;
        Integer i;
 
        
        Iterator<Integer> it = adj[v].iterator();
        while (it.hasNext())
        {
            i = it.next();
            if (!visited[i])
                topologicalSortUtil(i, visited, stack);
        }
 
        
        stack.push(new Integer(v));
    }
 
    
    void topologicalSort()
    {
        Stack stack = new Stack();
 
        
        boolean visited[] = new boolean[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;
 
        
        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                topologicalSortUtil(i, visited, stack);
 
        
        while (stack.empty()==false)
            System.out.print(stack.pop() + " ");
    }
 
    
    public static void main(String args[])
    {
        
        Graph g = new Graph(6);
        g.addEdge(38, 4);
        g.addEdge(50, 4);
        g.addEdge(38, 5);
        g.addEdge(50, 5);
        g.addEdge(3, 5);
        g.addEdge(4, 56);
        g.addEdge(5, 56);
        g.addEdge(50, 6);
        g.addEdge(6, 7);
        g.addEdge(6, 8);
        g.addEdge(7, 9);
        g.addEdge(3, 7);
        g.addEdge(7, 24);
        g.addEdge(9, 15);
        g.addEdge(24, 15);
 
        System.out.println("Following is a Topological " +
                           "sort of the given graph");
        g.topologicalsort();
    }
}

