package purdue.bowlingapp;

import android.widget.CheckBox;

/**
 * Created by Aaron on 11/19/2017.
 * code adapted from https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/DepthFirstPaths.java.html
 */

public class DepthFirstSearch {
    private boolean[] marked;
    private int[] edgeTo;
    private int count;

    public DepthFirstSearch(Graph g,Boolean[] pins) {
        edgeTo = new int[g.V()];
        marked = new boolean[g.V()];
        dfs(g,pins);
    }

    public DepthFirstSearch(Graph g,CheckBox[] pins) {
        edgeTo = new int[g.V()];
        marked = new boolean[g.V()];
        dfs(g,pins);
    }

    private void dfs(Graph g, Boolean[] pins) {
        for (int i = 0; i < pins.length; i++) {
            if (pins[i]) {
                marked[i] = true;
                for (int w : g.getAdj(i)) {
                    if (!marked[w] && pins[w]) {
                        edgeTo[w] = i;
                        dfs(g, w, pins);
                    }
                }
                return;
            }
        }
    }

    private void dfs(Graph g, int s, Boolean[] pins) {
        marked[s] = true;
        for(int w : g.getAdj(s)) {
            if(!marked[w] && pins[w]) {
                edgeTo[w]=s;
                dfs(g,w,pins);
            }
        }
    }

    private void dfs(Graph g, CheckBox[] pins) {
        for (int i = 0; i < pins.length; i++) {
            if (pins[i].isChecked()) {
                marked[i] = true;
                for (int w : g.getAdj(i)) {
                    if (!marked[w] && pins[w].isChecked()) {
                        edgeTo[w] = i;
                        dfs(g, w, pins);
                    }
                }
                return;
            }
        }
    }

    private void dfs(Graph g, int s, CheckBox[] pins) {
        marked[s] = true;
        for(int w : g.getAdj(s)) {
            if(!marked[w] && pins[w].isChecked()) {
                edgeTo[w]=s;
                dfs(g,w,pins);
            }
        }
    }

    public boolean hasPathTo(int v) {
        return marked[v];
    }
}
