/**
 * Created with IntelliJ IDEA.
 * User: lianyun
 * Date: 14-2-8
 * Time: 上午11:55
 * To change this template use File | Settings | File Templates.
 */
public class DepthFirstSearch implements Search {
    private boolean[] marked;
    private int count;

    public DepthFirstSearch(Graph G, int s){
        marked = new boolean[G.V()];
        dfs(G, s);
    }
    private void dfs(Graph G, int v){
        marked[v] = true;
        count++;
        for (int w : G.adj(v)){
            if (!marked[w]) dfs(G, w);
        }
    }
    @Override
    public boolean marked(int v) {
        return marked[v];
    }

    @Override
    public int count() {
        return count;
    }
}
