# Algorithms
import java.io.*;
import java.util.*;

class Edge
{
    int v;
    int weight;
}

class Graph{
    
    int V;
    ArrayList<Edge> Edges[];
    Stack stack=new Stack();
    boolean visited[];
	Graph(int v)
	{
	    V=v;
	    visited=new boolean[V];
	    Edges=new ArrayList[V];
	    for(int i=0;i<V;i++)
	    Edges[i]=new ArrayList<Edge>();
	  
	 
	}
	
public void	AddEdge(int a,int b,int weight)
	{
	    Edge edge=new Edge();
	    edge.v=b;
	    edge.weight=weight;
	    Edges[a].add(edge);
	    
	}
	
	public Stack TopologicalSort()
	{
	    
	 for(int i=0;i<V;i++)
	 { 
	     if(visited[i]==false)
	     Topological(i);

	 }
	    
	    return stack;
	    
	}
	public void Topological(int v)
	{
	    visited[v]=true;

	    for(int i=0;i<Edges[v].size();i++)
	    {
	        int u=Edges[v].get(i).v;
	        if(visited[u]==false)
	        Topological(u);
	         
	    }
	    stack.push(v);
	}
	
}
class Main
{
    public static void main(String args[])
    {
        Scanner scan = new Scanner(System.in);
        
        
        
        int n= scan.nextInt();
        Graph graph=new Graph(n);

        int e=scan.nextInt();
         
          for(int i=0;i<e;i++)
          {
             graph.AddEdge(scan.nextInt(),scan.nextInt(),scan.nextInt());
              
          }
          Stack stack=graph.TopologicalSort();
          
          while (stack.empty()==false)
            System.out.print(stack.pop() + " ");
   }
        
    }
    
    
