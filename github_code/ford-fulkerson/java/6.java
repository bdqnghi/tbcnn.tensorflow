package inteligenca;

import java.util.LinkedList;
import java.util.Queue;

import logika.MatrikaSosednosti;


/*  Ta koda ni najina!! Kodo sva le priredila najinemu programu.
 *  Najdena na naslovu: 
 *  https://www.sanfoundry.com/java-program-implement-ford-fulkerson-algorithm/
*/ 

public class FordFulkerson
{
    private int[] parent;
    private Queue<Integer> queue;
    private int numberOfVertices;
    private boolean[] visited;
 
    private FordFulkerson(int numberOfVertices)
    {
        this.numberOfVertices = numberOfVertices;
        this.queue = new LinkedList<Integer>();
        parent = new int[numberOfVertices];
        visited = new boolean[numberOfVertices];		
    }
 
    private boolean bfs(int source, int goal, int graph[][])
    {
        boolean pathFound = false;
        int destination, element;
 
        for(int vertex = 0; vertex < numberOfVertices; vertex++)
        {
            parent[vertex] = -1;
            visited[vertex] = false;
        }
 
        queue.add(source);
        parent[source] = -1;
        visited[source] = true;
 
        while (!queue.isEmpty())
        { 
            element = queue.remove();
            destination = 1;
 
            while (destination < numberOfVertices)
            {
                if (graph[element][destination] > 0 &&  !visited[destination])
                {
                    parent[destination] = element;
                    queue.add(destination);
                    visited[destination] = true;
                }
                destination++;
            }
        }
        if(visited[goal])
        {
            pathFound = true;
        }
        return pathFound;
    }
 
    private int fordFulkersonPomozna(MatrikaSosednosti matrika, int source, int destination)
    {
        int u, v;
        int maxFlow = 0;
        int pathFlow;
        int[][] graph = matrika.matrika;
 
        int[][] residualGraph = new int[numberOfVertices ][numberOfVertices];
        for (int sourceVertex = 0; sourceVertex < numberOfVertices; sourceVertex++)
        {
            for (int destinationVertex = 0; destinationVertex < numberOfVertices; destinationVertex++)
            {
                residualGraph[sourceVertex][destinationVertex] = graph[sourceVertex][destinationVertex];
            }
        }
 
        while (bfs(source ,destination, residualGraph))
        {
            pathFlow = Integer.MAX_VALUE;
            for (v = destination; v != source; v = parent[v])
            {
                u = parent[v];
                pathFlow = Math.min(pathFlow, residualGraph[u][v]);
            }
            for (v = destination; v != source; v = parent[v])
            {
                u = parent[v];
                residualGraph[u][v] -= pathFlow;
                residualGraph[v][u] += pathFlow;
            }
            maxFlow += pathFlow;	
        }
 
        return maxFlow;
    }
    
    public static int fordFulkerson(MatrikaSosednosti matrika, int source, int destination) {
    	FordFulkerson tmp = new FordFulkerson(matrika.matrika.length);
    	return tmp.fordFulkersonPomozna(matrika, source, destination);
    }
}
