import java.util.*;
import java.lang.*;
import java.io.*;
import java.util.LinkedList;

class MaxFlow
{
    static final int V = 6; //Number of vertices in graph

    /* Returns true if there is a path from source 's' to sink
      't' in residual graph. Also fills parent[] to store the
      path */
    boolean bfs(int rGraph[][], int s, int t, int parent[])
    {

        boolean visited[] = new boolean[V];
        for(int i=0; i<V; ++i)
            visited[i]=false;

        LinkedList<Integer> queue = new LinkedList<Integer>();
        queue.add(s);
        visited[s] = true;
        parent[s]=-1;


        while (queue.size()!=0)
        {
            int u = queue.poll();

            for (int v=0; v<V; v++)
            {
                if (visited[v]==false && rGraph[u][v] > 0)
                {
                    queue.add(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }


        return (visited[t] == true);
    }


    int fordFulkerson(int graph[][], int s, int t)
    {
        int u, v;

        int rGraph[][] = new int[V][V];

        for (u = 0; u < V; u++)
            for (v = 0; v < V; v++)
                rGraph[u][v] = graph[u][v];


        int parent[] = new int[V];

        int max_flow = 0;


        while (bfs(rGraph, s, t, parent))
        {

            int path_flow = Integer.MAX_VALUE;
            for (v=t; v!=s; v=parent[v])
            {
                u = parent[v];
                path_flow = Math.min(path_flow, rGraph[u][v]);
            }


            for (v=t; v != s; v=parent[v])
            {
                u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
            }


            max_flow += path_flow;
        }


        return max_flow;
    }


    public static void main (String[] args) throws java.lang.Exception
    {

              Scanner sc=new Scanner(System.in);
        System.out.println("enter the number of vertices");

       int s=sc.nextInt();
       int graph[][]=new int[s][s];
       for(int i=0;i<s;i++)
       {
          for( int j=0;j<s;j++)
          {
              graph[i][j]=sc.nextInt();
          }
       }
       MaxFlow m=new MaxFlow();
       System.out.println("enter the source and the sink");

 int k=sc.nextInt();
 int l=sc.nextInt();
        System.out.println("The maximum possible flow is " +
                           m.fordFulkerson(graph, k, l));

    }
}
