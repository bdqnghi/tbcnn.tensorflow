package ford_fulkerson.java.simple;

/**
 * Created by claas on 7/14/2016.
 * Used to perform the Ford-Fulkerson Algorithm using adjacency matrices.
 * For a faster implementation, see @see ../fast/FordFulkerson.java (using adjacency Lists)
 */
public class FordFulkerson {
    /**
     * Implementation of Ford-Fulkerson using adjacency matrix.
     * It uses O(|V|^2*f) time, where |V| is the number of nodes and f is the maximum flow  of the network.
     * @param graph an adjacency-matrix-representation of the flow graph where (x,y) is the capacity of the edge or 0 if there is no edge.
     * @param from the starting node from which to calculate the flow
     * @param to the ending node to which to calculate the flow
     * @return the flow from node "to" to node "from"
     */
    public static int fordFulkerson(int[][] graph, int from, int to) {
        //TODO
        return 0;
    }
}
