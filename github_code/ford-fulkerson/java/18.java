package com.hackerrank.utils;

/**
 * Created by Rajesh on 11/22/2017.
 */
import java.util.*;

public class FordFulkerson
{
    private int numberOfVertices;

    public FordFulkerson(int numberOfVertices)
    {
        this.numberOfVertices = numberOfVertices;
    }

    public boolean bfs(int source, int goal, int graph[][], int [] path)
    {
        Set<Integer> visited = new HashSet<>();
        Queue<Integer> queue = new LinkedList<>();

        for(int vertex = 0; vertex <= numberOfVertices-1; vertex++)
        {
            path[vertex] = -1;
        }

        queue.add(source);
        path[source] = -1;
        visited.add(source);
        //System.out.println("Path Search started");
        while (!queue.isEmpty())
        {
            Integer element = queue.remove();

            for(int destination=0; destination <= numberOfVertices-1; ++destination)
            {

                if (graph[element][destination] > 0 &&  !visited.contains(destination))
                {
                    path[destination] = element;
                    queue.add(destination);
                    visited.add(destination);
                    if(destination == goal){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    public int fordFulkerson(int graph[][], int source, int destination)
    {
        int u, v;
        int maxFlow = 0;

//        int[][] residualGraph = new int[numberOfVertices + 1][numberOfVertices + 1];
//        for (int sourceVertex = 1; sourceVertex <= numberOfVertices; sourceVertex++)
//        {
//            for (int destinationVertex = 1; destinationVertex <= numberOfVertices; destinationVertex++)
//            {
//                residualGraph[sourceVertex][destinationVertex] = graph[sourceVertex][destinationVertex];
//            }
//        }
        int[][] residualGraph = graph;
        int [] path = null;
        while (bfs(source ,destination, residualGraph, path = new int [numberOfVertices]))
        {
            //System.out.println("Path Found");
            int bottleNeck = Integer.MAX_VALUE;
            for (v = destination; v != source; v = path[v])
            {
                u = path[v];
                bottleNeck = Math.min(bottleNeck, residualGraph[u][v]);
                //System.out.print(v + "<-" + u + " ");
            }
            //System.out.println("");
            for (v = destination; v != source; v = path[v])
            {
                u = path[v];
                residualGraph[u][v] -= bottleNeck;// on forward edge reduced the flow by bottleneck
                residualGraph[v][u] += bottleNeck;// add the backward edge
            }
            maxFlow += bottleNeck;
        }

        return maxFlow;
    }

    public static void main(String...arg)
    {
        int[][] graph;
        int numberOfNodes;
        int source;
        int sink;
        int maxFlow;

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the number of nodes");
        numberOfNodes = scanner.nextInt();
        graph = new int[numberOfNodes + 1][numberOfNodes + 1];

        System.out.println("Enter the graph matrix");
        for (int sourceVertex = 1; sourceVertex <= numberOfNodes; sourceVertex++)
        {
            for (int destinationVertex = 1; destinationVertex <= numberOfNodes; destinationVertex++)
            {
                graph[sourceVertex][destinationVertex] = scanner.nextInt();
            }
        }

        System.out.println("Enter the source of the graph");
        source= scanner.nextInt();

        System.out.println("Enter the sink of the graph");
        sink = scanner.nextInt();

        FordFulkerson fordFulkerson = new FordFulkerson(numberOfNodes);
        maxFlow = fordFulkerson.fordFulkerson(graph, source, sink);
        System.out.println("The Max Flow is " + maxFlow);
        scanner.close();
    }
}