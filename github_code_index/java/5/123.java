package Graph.dataConstruct.DFS;

import Graph.dataConstruct.Graph.Graph;

public class DepthFirstSearch {
    private boolean[] marked;
    private int count;

    public DepthFirstSearch(Graph graph, int v) {
        count = 0;
        marked = new boolean[graph.getVertex()];
        dFS(graph, v);
    }

    private void dFS(Graph graph, int v) {
        marked[v] = true;
        count++;
        for (int x : graph.adj(v)) {
            if (!marked[x])
                dFS(graph,x);
        }
    }

    public int getCount() {
        return count;
    }

    public boolean getMarked(int v) {
        return marked[v];
    }

}
