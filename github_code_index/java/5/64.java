package com.tbp.search;

import com.tbp.graph.Edge;
import com.tbp.graph.IGraph;

public class DepthFirstSearch implements Search {


    private boolean[] marked;    // marked[v] = is there an s-v path?
    private int count;           // number of vertices connected to s

    /**
     * Computes the vertices in graph <tt>G</tt> that are
     * connected to the source vertex <tt>s</tt>.
     * @param graph the graph
     * @param s the source vertex
     */
    public DepthFirstSearch(IGraph graph, int s) {
        marked = new boolean[graph.V()];
        dfs(graph, s);
    }

    // depth first search from v
    // O(E + V)
    private void dfs(IGraph graph, int v) {
        count++;
        marked[v] = true;
        for (Edge edge : graph.adj(v)) {
            int w = edge.other(v);
            if (!marked[w]) {
                dfs(graph, w);
            }
        }
    }

    /**
     * Is there a path between the source vertex <tt>s</tt> and vertex <tt>v</tt>?
     * @param v the vertex
     * @return <tt>true</tt> if there is a path, <tt>false</tt> otherwise
     */
    @Override
    public boolean marked(int v) {
        return marked[v];
    }

    /**
     * Returns the number of vertices connected to the source vertex <tt>s</tt>.
     * @return the number of vertices connected to the source vertex <tt>s</tt>
     */
    @Override
    public int count() {
        return count;
    }

}
