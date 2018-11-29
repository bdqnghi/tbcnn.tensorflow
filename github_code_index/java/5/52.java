package graph;

public class DFS {

    public static void main(String[] args) {
        Graph_AdjacencyList graph = new Graph_AdjacencyList(4);

        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(1, 2);
        graph.addEdge(2, 0);
        graph.addEdge(2, 3);
        graph.addEdge(3, 3);

        dfs(graph, 2, 4);
    }

    private static void dfs(Graph_AdjacencyList graph, int start, int noOfNodes) {

        boolean[] visited = new boolean[noOfNodes];

        dfsRecursive(graph, start, noOfNodes, visited);
    }

    private static void dfsRecursive(Graph_AdjacencyList graph, int start, int noOfNodes, boolean[] visited) {

    	// Mark visited
        visited[start] = true;

        System.out.println(start + " ");

        // Recurse all the vertices adjacent to this vertex
        for (int v : graph.getAdjacencyList()[start]) {
            if ( !visited[v] ) {
                dfsRecursive(graph, v, noOfNodes, visited);
            }
        }
    }


}
