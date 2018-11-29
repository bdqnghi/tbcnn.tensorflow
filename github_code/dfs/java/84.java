package ex4_1;

/**
 * Created by zhou on 2017/3/12.
 */
public class DepthFirstSearch extends Search{

    private boolean[] marked;
    private int count;


    public DepthFirstSearch(Graph G, int s) {
        marked = new boolean[G.V()];

    }

    private void dfs(Graph G, int v) {
        marked[v] = true;
        count++;
        for(int w : G.adj(v)) {
            if(!marked(w)) dfs(G, w);
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
