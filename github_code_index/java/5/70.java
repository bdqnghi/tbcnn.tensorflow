package map;

import java.util.Stack;

@SuppressWarnings("unused")
public class DepthFirstSearch {
    private boolean[] marked;
    private int[] edgeTo;
    private final int s;
    private int count;

    /**
     * 深度优先搜索
     *
     * @param G Graph
     * @param s int
     */
    public DepthFirstSearch(Graph G, int s) {
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        this.s = s;
        dfs(G, s);
    }

    /**
     * 递归调用深度优先搜索
     *
     * @param G Graph
     * @param v int
     */
    private void dfs(Graph G, int v) {
        marked[v] = true;
        count++;
        for (int w : G.adj(v))
            if ((!marked[w])) {
                edgeTo[w] = v;
                dfs(G, w);
            }
    }

    private boolean hasPathTo(int v) {
        return marked[v];
    }

    /**
     * 遍历整棵树
     *
     * @param v int
     * @return Integer
     */
    @SuppressWarnings("Duplicates")
    private Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v)) return null;
        Stack<Integer> path = new Stack<>();
        for (int x = v; x != s; x = edgeTo[x])
            path.push(x);
        path.push(s);
        return path;
    }

    /**
     * 标记该点是否调用dfs()
     *
     * @param w int
     * @return {@code true}   {@link #dfs(Graph, int)}
     */
    public boolean marked(int w) {
        return marked[w];
    }

    /**
     * @return int
     */
    public int count() {
        return count;
    }
}
