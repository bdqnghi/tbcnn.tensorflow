// Given a graph which represents a flow network where every edge has
// a capacity, find the maximum flow possible from node s to node t
public static int fordFulkerson(int[][] graph, int s, int e) {
    // Number of nodes in the graph
    int n = graph.length;

    // Residual Graph which indicates additional possible
    // flow, aka remaining space in paths
    int[][] residualGraph = new int[n][n];

    // At the start the additional possible flow is the
    // current values of the graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            residualGraph[i][j] = graph[i][j];

    // Array used by the BFS to store the current path
    int[] parent = new int[n];

    // To store the answer, there is no flow initially
    int maxFlow = 0;

    // While there is still a path from the source to the end
    while (fordFulkersonBFS(residualGraph, s, e, parent)) {

        // Determine the minimum flow value out of each node
        // which is the maximum flow available in the path
        int pathFlow = Integer.MAX_VALUE;
        for (int i = e; i != s; i = parent[i]) {
            int parentIndex = parent[i];
            pathFlow = Math.min(pathFlow, residualGraph[parentIndex][i]);
        }

        // Update residual capacities of the edges and
        // reverse edges along the path
        for (int i = e; i != s; i = parent[i]) {
            int parentIndex = parent[i];
            residualGraph[parentIndex][i] -= pathFlow;
            residualGraph[i][parentIndex] += pathFlow;
        }

        // Add path flow to the overall maximum flow
        maxFlow += pathFlow;
    }
    return maxFlow;
}

public static boolean fordFulkersonBFS(int[][] residualGraph, int s, int e, int[] parent) {
    // Number of nodes in the graph
    int n = residualGraph.length;
    // Array to mark nodes as visited
    boolean[] visited = new boolean[n];
    // Queue to handle the BFS
    Queue < Integer > queue = new LinkedList < Integer > ();

    // Add the starting node to the queue and
    // as the initial parent in the path
    queue.add(s);
    visited[s] = true;
    parent[s] = -1;

    // While there are still nodes left to visit
    while (!queue.isEmpty()) {
        // Index of the node to process
        int index = queue.poll();
        for (int i = 0; i < n; i++)
            if (!visited[i] && residualGraph[index][i] > 0) {
                // Queue every unvisited node with additional
                // flow available from the current node
                queue.add(i);
                parent[i] = index;
                visited[i] = true;
            }
    }
    // If we were able to visit the end node
    // then there is still a path
    return visited[e];
}
