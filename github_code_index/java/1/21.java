package hongke.interview.algorithms.graph;

import hongke.interview.datastructure.graph.Digraph;

import java.util.*;

/**
 * Created by hongke on 12/6/14.
 */
public class BreadthFirstSearch {
    private static final int INFINITY = Integer.MAX_VALUE;
    private boolean[] marked;  // marked[v] = is there an s->v path?
    private int[] edgeTo;      // edgeTo[v] = last edge on shortest s->v path
    private int[] distTo;      // distTo[v] = length of shortest s->v path
    private Digraph dg;

    BreadthFirstSearch(Digraph dg, int s) {
        this(dg.V());
        Arrays.fill(distTo, INFINITY);
        this.dg = dg;
        bfs(s);
    }

    BreadthFirstSearch(Digraph dg, int... sources) {
        this(dg.V());
        Arrays.fill(distTo, INFINITY);
        this.dg = dg;
        bfs(sources);
    }

    BreadthFirstSearch(int V) {
        marked = new boolean[V];
        edgeTo = new int[V];
        distTo = new int[V];
        Arrays.fill(distTo, INFINITY);
    }

    private void bfs(int s) {
        Deque<Integer> queue = new ArrayDeque<Integer>();
        queue.add(s);
        marked[s] = true;
        distTo[s] = 0;
        while (queue.isEmpty()) {
            int v = queue.poll();
            for (Integer w : dg.adj(v)) {
                if (!marked[w]) {
                    queue.add(w);
                    marked[w] = true;
                    distTo[w] = distTo[v] + 1;
                    edgeTo[w] = v;
                }
            }
        }
    }

    private void bfs(int ...sources) {
        Deque<Integer> queue = new ArrayDeque<Integer>();
        for (int s : sources) {
            queue.add(s);
            marked[s] = true;
            distTo[s] = 0;
        }
        while (queue.isEmpty()) {
            int v = queue.poll();
            for (Integer w : dg.adj(v)) {
                if (!marked[w]) {
                    queue.add(w);
                    marked[w] = true;
                    distTo[w] = distTo[v] + 1;
                    edgeTo[w] = v;
                }
            }
        }
    }

    public int distTo(int w) {
        return distTo[w];
    }

    public boolean hasPathTo(int w) {
        return marked[w];
    }

    public Iterable<Integer> pathTo(int w) {
        if (!marked[w]) return null;
        Deque<Integer> path = new ArrayDeque<Integer>();
        while (distTo[w] != 0) {
            path.addFirst(edgeTo[w]);
            w = edgeTo[w];
        }
        path.addFirst(w);
        return path;
    }

    public static BreadthFirstSearch bfs(Digraph dg, int v) {
        assert dg != null;
        assert v >= 0 && v < dg.V();
        return new BreadthFirstSearch(dg, v);
    }


    public static BreadthFirstSearch bfs(Digraph dg, int ...sources) {
        assert dg != null;
        for (int s : sources) {
            assert s >= 0 && s < dg.V();
        }
        return new BreadthFirstSearch(dg, sources);
    }
}
