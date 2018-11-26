package maximumflow;

/*
Given a graph which represents a flow network where every edge has a capacity. Also given two vertices source ‘s’ and
sink ‘t’ in the graph, find the maximum possible flow from s to t with following constraints:

a) Flow on an edge doesn’t exceed the given capacity of the edge.

b) Incoming flow is equal to outgoing flow for every vertex except s and t.

Ford-Fulkerson Algorithm
The following is simple idea of Ford-Fulkerson algorithm:
1) Start with initial flow as 0.
2) While there is a augmenting path from source to sink.
           Add this path-flow to flow.
3) Return flow.

How to implement the above simple algorithm?
Let us first define the concept of Residual Graph which is needed for understanding the implementation.
Residual Graph of a flow network is a graph which indicates additional possible flow. If there is a path from source
to sink in residual graph, then it is possible to add flow.

Every edge of a residual graph has a value called residual capacity which is equal to original capacity of the edge
minus current flow. Residual capacity is basically the current capacity of the edge.

Let us now talk about implementation details. Residual capacity is 0 if there is no edge between two vertices of
residual graph. We can initialize the residual graph as original graph as there is no initial flow and initially
residual capacity is equal to original capacity.

To find an augmenting path, we can either do a BFS or DFS of the residual graph.
We have used BFS in below implementation. Using BFS, we can find out if there is a path from source to sink. BFS also
builds parent[] array. Using the parent[] array, we traverse through the found path and find possible flow through
this path by finding minimum residual capacity along the path. We later add the found path flow to overall flow.

The important thing is, we need to update residual capacities in the residual graph. We subtract path flow from all
edges along the path and we add path flow along the reverse edges We need to add path flow along reverse edges because
we may later need to send flow in reverse direction.Explaination:-
Back edges are necessary when doing the Ford-Fulkerson algorithm in case the path that you choose ends up not being a
part of the overall flow.

As an example where back edges are necessary, consider this flow network:

    s
   / \
  a   b
   \ / \
    c   d
     \ /
      t
Assume that all edges point forward and that all edges have capacity 1 and that you want to find a flow from s to t.
Suppose on the first iteration of Ford-Fulkerson that you take the path s -> b -> c -> t. At this point,
you've pushed one unit of flow from s to t. If you don't add in any back edges, you're left with this:

    s
   /
  a   b
   \   \
    c   d
       /
      t
There are no more s-t paths, but that doesn't mean you have a max flow. You can push two units of flow from s to t by
sending one along the path s -> a -> c -> t and the other along the path s -> b -> d -> t.

Without any back edges in the residual flow network, you would never discover this other path.



Time Complexity: Time complexity of the above algorithm is O(number of augumenting path * E). We run a loop while there is an
augmenting path. In worst case, we may add 1 unit flow in every iteration. Therefore the time complexity
becomes O(max_flow * E).

The above implementation of Ford Fulkerson Algorithm is called Edmonds-Karp Algorithm. The idea of Edmonds-Karp is to use BFS in Ford Fulkerson implementation as
BFS always picks a path with minimum number of edges. When BFS is used, the worst case time complexity can be reduced to O(VE^2).
The property of BFS is each time an augumented path is chosen, its lenght is greater than or equal to the previous augumented path.

The above implementation uses adjacency matrix
representation though where BFS takes O(V2) time, the time complexity of the above implementation is O(EV3)

This is an important problem as it arises in many practical situations. Examples include, maximizing the transportation with given traffic limits, maximizing packet
flow in computer networks.
 */


import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;

public class FordFulkersonAlgo {

    private int V;

    public FordFulkersonAlgo(int v){
        V = v;
    }

    private boolean bfs(int[][] graph, int s, int t, HashMap<Integer,Integer> childParentMap){
        boolean[] visited = new boolean[V];
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(s);
        visited[s] = true;
        while (!queue.isEmpty()){
            int u = queue.poll();
            for(int v =0; v<V; v++){
                if(graph[u][v] != 0 && !visited[v]){
                    visited[v] = true;
                    queue.offer(v);
                    childParentMap.put(v,u);
                    if(v == t){
                        break;
                    }
                }
            }
        }
        return childParentMap.containsKey(t);
    }

    private int getFlow(HashMap<Integer,Integer> childParentMap, int s, int t, int[][] graph){
        int v = t;
        int flow = Integer.MAX_VALUE;
        while (childParentMap.containsKey(v)){
            int u = childParentMap.get(v);
            flow = Math.min(flow, graph[u][v]);
            v = u;
        }
        return flow;
    }

    public int fordFulkerson(int[][] graph, int s, int t){
        //create a residual graph similar to original graph
        int[][] rGraph = new int[V][V];
        for(int u =0; u< V; u++){
            for(int v =0; v < V; v++){
                rGraph[u][v] = graph[u][v];
            }
        }
        HashMap<Integer,Integer> childParentMap = new HashMap<>();
        int maxFlow = 0;
        while (bfs(rGraph,s,t,childParentMap)){
            int pathFlow = getFlow(childParentMap,s,t,rGraph);
            if(pathFlow != Integer.MAX_VALUE){
                maxFlow += pathFlow;
                int v = t;
                System.out.println("\nAugumented Path:");
                while (childParentMap.containsKey(v)){
                    int u = childParentMap.get(v);
                    rGraph[u][v] -= pathFlow;
                    rGraph[v][u] += pathFlow;
                    System.out.print("(" + u + "," + v + ")" + " ");
                    v = u;
                }
                System.out.print(" flow:" + pathFlow);
            }
            childParentMap.clear();
        }
        return maxFlow;
    }

    public static void main(String[] args) {
        int graph[][] =new int[][] {
                {0, 16, 13, 0, 0, 0},
                {0, 0, 10, 12, 0, 0},
                {0, 4, 0, 0, 14, 0},
                {0, 0, 9, 0, 0, 20},
                {0, 0, 0, 7, 0, 4},
                {0, 0, 0, 0, 0, 0}
        };
        FordFulkersonAlgo m = new FordFulkersonAlgo(graph.length);
        System.out.println("\nThe maximum possible flow is " +
                m.fordFulkerson(graph, 0, 5));
    }
}