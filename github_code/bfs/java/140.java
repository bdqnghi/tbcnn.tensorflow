package main.graph;

import java.util.LinkedList;
import java.util.Queue;

/*
    Breadth First Traversal (or Search) for a graph is similar to Breadth First Traversal
    of a tree (See method 2 of this post). The only catch here is, unlike trees,
    graphs may contain cycles, so we may come to the same node again.
    To avoid processing a node more than once, we use a boolean visited array.

    For simplicity, it is assumed that all vertices are reachable from the starting vertex.

    http://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/

    http://www.geeksforgeeks.org/applications-of-breadth-first-traversal/

    Applications of Breadth First Traversal
    1) Shortest Path and Minimum Spanning Tree for unweighted graph In unweighted graph,
    the shortest path is the path with least number of edges. With Breadth First, we always
    reach a vertex from given source using minimum number of edges. Also, in case of
    unweighted graphs, any spanning tree is Minimum Spanning Tree and we can use either
    Depth or Breadth first traversal for finding a spanning tree.

    2) Peer to Peer Networks. In Peer to Peer Networks like BitTorrent, Breadth First Search
    is used to find all neighbor nodes.

    3) Crawlers in Search Engines: Crawlers build index using Breadth First. The idea is
    to start from source page and follow all links from source and keep doing same.
    Depth First Traversal can also be used for crawlers, but the advantage with Breadth
    First Traversal is, depth or levels of built tree can be limited.

    4) Social Networking Websites: In social networks, we can find people within a given
    distance ‘k’ from a person using Breadth First Search till ‘k’ levels.

    5) GPS Navigation systems: Breadth First Search is used to find all neighboring locations.

    6) Broadcasting in Network: In networks, a broadcasted packet follows Breadth First
    Search to reach all nodes.

    7) In Garbage Collection: Breadth First Search is used in copying garbage collection
    using Cheney’s algorithm. Refer this and for details. Breadth First Search is preferred
    over Depth First Search because of better locality of reference:

    8) Cycle detection in undirected graph: In undirected graphs, either Breadth First
    Search or Depth First Search can be used to detect cycle. In directed graph, only
    depth first search can be used.

    9) Ford–Fulkerson algorithm In Ford-Fulkerson algorithm, we can either use Breadth
    First or Depth First Traversal to find the maximum flow. Breadth First Traversal is
    preferred as it reduces worst case time complexity to O(VE2).

    10) To test if a graph is Bipartite We can either use Breadth First or Depth First
    Traversal.

    11) Path Finding We can either use Breadth First or Depth First Traversal to find
    if there is a path between two vertices.

    12) Finding all nodes within one connected component: We can either use Breadth First
    or Depth First Traversal to find all nodes reachable from a given node.

    Many algorithms like Prim’s Minimum Spanning Tree and Dijkstra’s Single Source Shortest
    Path use structure similar to Breadth First Search.

    There can be many more applications as Breadth First Search is one of the core algorithm
     for Graphs.

 */
public class BreadthFirstTraversalOrBFSForAGraph {

    public static void main(String[] args){

        int totalNodes = 4;
        Graph graph = new Graph(totalNodes);
        addEdge(graph, 0, 1);
        addEdge(graph, 0, 2);
        addEdge(graph, 1, 2);
        addEdge(graph, 2, 0);
        addEdge(graph, 2, 3);
        addEdge(graph, 3, 3);

        int startingNode = 2;
        System.out.print("BFS traversal of graph with starting node "+ startingNode +" ::: ");
        printGraphUsingBFS(graph, startingNode, totalNodes);
    }

    private static void printGraphUsingBFS(Graph graph, int startingNode, int totalNodes) {

        Queue<Integer> queue = new LinkedList<>();
        boolean visited[] = new boolean[totalNodes];
        queue.add(startingNode);
        while (!queue.isEmpty()){
            int temp = queue.poll();
            System.out.print(temp + " ");
            visited[temp] = true;

            for (int adjNode : graph.adjListArray[temp]){
                if(!visited[adjNode]){
                    queue.add(adjNode);
                }
            }
        }
    }

    private static void addEdge(Graph graph, int src, int dest){

        graph.adjListArray[src].add(dest);
    }
}
