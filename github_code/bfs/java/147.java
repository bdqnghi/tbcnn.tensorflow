import java.util.LinkedList;
import java.util.Queue;

public class BreadthFirstSearch {
    private boolean[] marked;
    private int[] edgeTo;

    public BreadthFirstSearch(Graph G, int s){
        this.marked = new boolean[G.V()];
        this.edgeTo = new int[G.V()];
        bfs(G,s);

    }

    public void bfs(Graph G,int v){
        LinkedList<Integer> queue = new LinkedList<>();
        queue.offer(v);
        marked[v] = true;
        while (!queue.isEmpty()){
            int s = queue.poll();
            for(int w : G.adj(s)){
                if (!marked[w]){
                    edgeTo[w] = s;
                    marked[w] = true;
                    queue.offer(w);
                }
            }
        }
    }

    public static void main(String[] args) {
        int V = 13;
        int E = 13;
        Graph graph = new Graph(V);

        graph.addEdge(0,5);
        graph.addEdge(4,3);
        graph.addEdge(0,1);
        graph.addEdge(9,12);
        graph.addEdge(6,4);
        graph.addEdge(5,4);
        graph.addEdge(0,2);
        graph.addEdge(11,12);
        graph.addEdge(9,10);
        graph.addEdge(0,6);
        graph.addEdge(7,8);
        graph.addEdge(9,11);
        graph.addEdge(5,3);

        BreadthFirstSearch bfs = new BreadthFirstSearch(graph,0);

    }
}
