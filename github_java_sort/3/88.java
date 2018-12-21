package DFS;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Stack;

class GraphTopologicalSorting
{
    private int V;   
    private LinkedList<Integer> adj[]; 
 
    
    GraphTopologicalSorting(int v)
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
        
    	GraphTopologicalSorting g = new GraphTopologicalSorting(5);
        g.addEdge(2,3);
        g.addEdge(3,1);
        g.addEdge(1,4);
        g.addEdge(4, 0);
 
        System.out.println("Following is a Topological " +
                           "sort of the given graph");
        g.topologicalSort();
    }
}
