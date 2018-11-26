/**
 * Created with IntelliJ IDEA.
 * User: shiwangi
 * Date: 5/1/14
 * Time: 11:37 PM
 * To change this template use File | Settings | File Templates.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class FordFulkerson {
    private int[] parent;
    private Queue<Integer> queue;
    private int numberOfVertices;
    private boolean[] visited;

    public FordFulkerson(int numberOfVertices) {
        this.numberOfVertices = numberOfVertices;
        this.queue = new LinkedList<Integer>();
        parent = new int[numberOfVertices];
        visited = new boolean[numberOfVertices];
    }

    public boolean bfs(int source, int goal, int graph[][]) {
        boolean pathFound = false;
        int destination, element;

        for (int vertex = 0; vertex < numberOfVertices; vertex++) {
            parent[vertex] = -1;
            visited[vertex] = false;
        }

        queue.add(source);
        parent[source] = -1;
        visited[source] = true;

        while (!queue.isEmpty()) {
            element = queue.remove();
            visited[element]=true;
            destination = 1;

            while (destination <numberOfVertices) {
                if (graph[element][destination] > 0 && !visited[destination]) {
                    if(!(parent[element]==0 && destination==numberOfVertices-1)){
                    parent[destination] = element;
                    queue.add(destination);
                   // visited[destination] = true;
                    }
                }
                destination++;
            }
        }
        if (visited[goal]) {
            pathFound = true;
        }
        return pathFound;
    }

    public int fordFulkerson(int graph[][], int source, int destination) {
        int u, v;
        int maxFlow = 0;
        int pathFlow;

        int[][] residualGraph = new int[numberOfVertices ][numberOfVertices];
        for (int sourceVertex = 0; sourceVertex < numberOfVertices; sourceVertex++) {
            for (int destinationVertex = 0; destinationVertex < numberOfVertices; destinationVertex++) {
                residualGraph[sourceVertex][destinationVertex] = graph[sourceVertex][destinationVertex];
            }
        }

        while (bfs(source, destination, residualGraph)) {
            for (v = destination; v != source; v = parent[v]) {
                u = parent[v];
            }
            for (v = parent[destination]; v != source; v = parent[v]) {
                Arrays.fill(residualGraph[v], 0);
                residualGraph[0][v]=0;
                residualGraph[v][destination]=0;
            }
            maxFlow += 1;
        }

        return maxFlow;
    }

    public static void main(String... arg) throws IOException {
        InputStreamReader input = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(input);
        int cases = Integer.parseInt(br.readLine());
        int[][] graph;
        int numberOfNodes;
        int maxFlow;
        int x, y, t;
        for (int i = 0; i < cases; i++) {
            String tokens[] = (br.readLine()).split(" ");
            numberOfNodes = Integer.parseInt(tokens[0]);
            int edges = Integer.parseInt(tokens[1]);
            graph = new int[numberOfNodes + 2][numberOfNodes + 2];
            for (int j = 0; j < edges; j++) {
                String token[] = (br.readLine()).split(" ");
                x = Integer.parseInt(token[0]);
                y = Integer.parseInt(token[1]);
                if (x > y) {
                    t = x;
                    x = y;
                    y = t;
                }
                graph[x][y] = 1;
            }
            Arrays.fill(graph[0], 1);
            graph[0][numberOfNodes+1]=0;
            graph[0][0]=0;
            for(int k=1;k<=numberOfNodes;k++)
                graph[k][numberOfNodes+1]=1;
            FordFulkerson fordFulkerson = new FordFulkerson(numberOfNodes + 2);
            maxFlow = fordFulkerson.fordFulkerson(graph, 0, numberOfNodes + 1);
            System.out.println("The Max Flow is " + maxFlow);
            if (numberOfNodes % 2 != 0) {
                System.out.println("NO");
            } else {
                if (maxFlow == numberOfNodes / 2) {
                    System.out.println("YES");
                } else
                    System.out.println("NO");
            }
        }
    }
}
