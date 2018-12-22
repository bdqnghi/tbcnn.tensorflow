package geek.livingstone.problems.graphs.undirected;

public class DepthFirstSearch {
  protected boolean[] marked;
  protected int count;

  public DepthFirstSearch(Graph G, int s) {
    marked = new boolean[G.V];
    count = 0;
    dfs(G, s);
  }

  private void dfs(Graph G, int u) {
    marked[u] = true;
    for (int v : G.adj(u))
      if (!marked[v])
        dfs(G, v);
  }

  /**
   * Is u connected to s
   * 
   * @param u
   * @return
   */
  public boolean marked(int u) {
    return marked[u];
  }

  /**
   * How many vertices are connecetd to s
   * 
   * @return
   */
  public int count() {
    return count;
  }
}
