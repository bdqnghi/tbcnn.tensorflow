public class SAP {
    private Digraph G;
    private BreadthFirstDirectedPaths[] bfs;

    // constructor takes a digraph (not necessarily a DAG)
    public SAP(Digraph G) {
        this.G = new Digraph(G);
        bfs = new BreadthFirstDirectedPaths[this.G.V()];
    }

    // length of shortest ancestral path between v and w; -1 if no such path
    public int length(int v, int w) {
        if (v < 0 || v > G.V() - 1) {
            throw new IndexOutOfBoundsException();
        }

        if (w < 0 || w > G.V() - 1) {
            throw new IndexOutOfBoundsException();
        }

        if (bfs[v] == null) {
            bfs[v] = new BreadthFirstDirectedPaths(G, v);
        }

        if (bfs[w] == null) {
            bfs[w] = new BreadthFirstDirectedPaths(G, w);
        }

        int length = Integer.MAX_VALUE;

        for (int i = 0; i < G.V(); i++) {
            if (bfs[v].hasPathTo(i) && bfs[w].hasPathTo(i)) {
                int l = bfs[v].distTo(i) + bfs[w].distTo(i);
                if (l < length) {
                    length = l;
                }
            }
        }

        // save memory
        bfs[v] = null;
        bfs[w] = null;

        if (length != Integer.MAX_VALUE) {
            return length;
        } else {
            return -1;
        }
    }

    // a common ancestor of v and w that participates in a shortest ancestral
    // path; -1 if no such path
    public int ancestor(int v, int w) {
        if (v < 0 || v > G.V() - 1) {
            throw new IndexOutOfBoundsException();
        }

        if (w < 0 || w > G.V() - 1) {
            throw new IndexOutOfBoundsException();
        }

        if (bfs[v] == null) {
            bfs[v] = new BreadthFirstDirectedPaths(G, v);
        }

        if (bfs[w] == null) {
            bfs[w] = new BreadthFirstDirectedPaths(G, w);
        }

        int length = Integer.MAX_VALUE;
        int ancestor = -1;

        for (int i = 0; i < G.V(); i++) {
            if (bfs[v].hasPathTo(i) && bfs[w].hasPathTo(i)) {
                int l = bfs[v].distTo(i) + bfs[w].distTo(i);
                if (l < length) {
                    length = l;
                    ancestor = i;
                }
            }
        }

        // save memory
        bfs[v] = null;
        bfs[w] = null;

        return ancestor;
    }

    // length of shortest ancestral path between any vertex in v and any vertex
    // in w; -1 if no such path
    public int length(Iterable<Integer> v, Iterable<Integer> w) {
        if (v == null || w == null) {
            throw new NullPointerException();
        }

        int length = Integer.MAX_VALUE;
        for (int i : v) {
            for (int j : w) {
                int l = length(i, j);
                if (l != -1 && l < length) {
                    length = l;
                }
            }
        }

        assert length != -1;

        if (length != Integer.MAX_VALUE) {
            return length;
        } else {
            return -1;
        }
    }

    // a common ancestor that participates in shortest ancestral path; -1 if no
    // such path
    public int ancestor(Iterable<Integer> v, Iterable<Integer> w) {
        if (v == null || w == null) {
            throw new NullPointerException();
        }

        int length = Integer.MAX_VALUE;
        int ancestor = -1;

        for (int i : v) {
            for (int j : w) {
                int l = length(i, j);
                if (l != -1 && l < length) {
                    length = l;
                    ancestor = ancestor(i, j);
                }
            }
        }
        assert length != -1;
        return ancestor;
    }

    // do unit testing of this class
    public static void main(String[] args) {
        StdOut.println(args[0]);
        In in = new In(args[0]);
        Digraph G = new Digraph(in);
        SAP sap = new SAP(G);
        while (!StdIn.isEmpty()) {
            int v = StdIn.readInt();
            int w = StdIn.readInt();
            int length   = sap.length(v, w);
            int ancestor = sap.ancestor(v, w);
            StdOut.printf("length = %d, ancestor = %d\n", length, ancestor);
        }
    }
}
