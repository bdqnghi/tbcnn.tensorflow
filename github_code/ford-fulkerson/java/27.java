package vnreal.evaluations.metrics.utils;

import java.util.LinkedList;

import java.util.Queue;

import java.util.Scanner;

 
/**
 * This class calculates the maximum flow of a network by using the ford 
 * fulkerson algorithm.
 * 
 * @author baskefab
 *
 */
public class FordFulkerson

{

    private int[] parent;

    private Queue<Integer> queue;

    private int numberOfVertices;

    private boolean[] visited;

 

    public FordFulkerson(int numberOfVertices)

    {

        this.numberOfVertices = numberOfVertices;

        this.queue = new LinkedList<Integer>();

        parent = new int[numberOfVertices + 1];

        visited = new boolean[numberOfVertices + 1];                

    }

 

    public boolean bfs(int source, int goal, int graph[][])

    {

        boolean pathFound = false;

        int destination, element;

 

        for(int vertex = 1; vertex <= numberOfVertices; vertex++)

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

 

            while (destination <= numberOfVertices)

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

 

    public int fordFulkerson(int graph[][], int source, int destination)

    {

        int u, v;

        int maxFlow = 0;

        int pathFlow;

 

        int[][] residualGraph = new int[numberOfVertices + 1][numberOfVertices + 1];

        for (int sourceVertex = 1; sourceVertex <= numberOfVertices; sourceVertex++)

        {

            for (int destinationVertex = 1; destinationVertex <= numberOfVertices; destinationVertex++)

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

 
/*
    public static void main(String...arg)

    {

        int[][] graph;

        int numberOfNodes;

        int source;

        int sink;

        int maxFlow;
        
        
        int nodeNumber = 8;
        int[] nodei = {0,1,2,3,4,5,5,5,5,6,7,8};
        int[] nodej = {0,4,3,4,5,1,2,6,8,7,4,4};
        
        int[][] matrix = new int[nodeNumber][nodeNumber];
        matrix = retransform(nodei, nodej, nodeNumber);
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                    System.out.print(matrix[i][j] + " ");
                    if (j == matrix[i].length -1 ) {
                            System.out.println();
                    }
            }
        }
        int number = 5;
        int[][] matrix2 = {{0,0,0,0,0,0},{0,0,0,1,0,0},{0,0,0,1,0,0},
                    {0,1,1,0,1,1},{0,0,0,1,0,0},{0,0,0,1,0,0}};//ATTENTION first row/column 0!!
        maxFlow = edgeConnectivity(matrix2, number);
        System.out.println(maxFlow);

 

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

    }*/
    
    public static int[][] retransform(int[] nodei, int[] nodej, int nodeNumber) {
            int[][] matrix = new int[nodeNumber][nodeNumber];
            
            for (int i = 1; i < nodei.length; i++) {
                    
                    matrix[nodei[i]-1][nodej[i]-1] = 1;
                    matrix[nodej[i] - 1][nodei[i] - 1] = 1;
            }
            return matrix;
    }
    
    
    public static boolean isEdge(int nodei[], int nodej[], int i, int j) {
            boolean isEdge = false;
            for (int a = 1; a < nodei.length; a++) {
                    if ((nodei[a] == i && nodej[a] == j) || (nodei[a] == j && nodej[a] == i)) {
                            isEdge = true;
                    }
            }
            return isEdge;
    }
    
    /**
     * This method calculates the edge connectivity.
     * @param matrix the matrix representing the network.
     * @param numberOfNodes the number of nodes of the network.
     * @return the edge connectivity.
     */
    public static int edgeConnectivity(int[][] matrix, int numberOfNodes)
    {
                
      int k = numberOfNodes;
      int source = 1;
      
      for (int sink = 2; sink <=numberOfNodes; sink++) {
              FordFulkerson fordFulkerson = new FordFulkerson(numberOfNodes);

          int maxFlow = fordFulkerson.fordFulkerson(matrix, source, sink);
          if (maxFlow < k) {
          k = maxFlow;
        }
      }
      return k;
    }
    

}