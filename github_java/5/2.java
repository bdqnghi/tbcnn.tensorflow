
import java.util.Iterator;

public class DepthFirstSearch {
    private Graph graph;
    //parents in depth first search tree
    private int[] parent;
    //to check if the vertex has been visited
    private boolean[] visited;
    //order in which vertices have been discovered
    private int[] discoverOrder;
    //finish order
    private int[] finishOrder;
    //the index that indicates the discovery order
    private int discoverIndex = 0;
    //index that indicates finishIndex
    private int finishIndex = 0;
    public DepthFirstSearch(Graph graph) {
        int n = graph.getNumV();
        this.graph = graph;
        this.parent = new int[n];
        this.visited = new boolean[n];
        this.discoverOrder = new int[n];
        this.finishOrder = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                depthFirstSearch(i);
            }
        }        
    }
    public void depthFirstSearch(int current) {
        //mark current visited
        visited[current] = true;
        discoverOrder[discoverIndex++] = current;
        //examines each vertex adjacent to the current vertex
        Iterator<Edge> itr = graph.edgeIterator(current);
        while (itr.hasNext()) {
            //find me where the edge adj to our current points (which vertex)
            int neighbor = itr.next().getDest();
            //process neighbor that has not been visited
            if (!visited[neighbor]) {
                //insert current, neighbor into depth first serach tree
                parent[neighbor] = current;
                //recursively apply algorithm starting at enighbor
                depthFirstSearch(neighbor);
            }
        }
        finishOrder[finishIndex++] = current;
    }
    public int[] getDiscoverOrder() {
        return discoverOrder;
    }
    public int[] getFinishOrder() {
        return finishOrder;
    }
}