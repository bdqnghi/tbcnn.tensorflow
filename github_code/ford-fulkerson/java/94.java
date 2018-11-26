/**
 * Created with IntelliJ IDEA.
 * User: dogeyes
 * Date: 13-1-16
 * Time: 上午10:49
 * To change this template use File | Settings | File Templates.
 */
public class FordFulkerson{
    private boolean[] marked;
    private FlowEdge[] edgeTo;
    private double value;

    public FordFulkerson(FlowNetwork G, int s, int t)
    {
        while (hasAugmentingPath(G, s, t))
        {
            double bottle = Double.POSITIVE_INFINITY;
            for(int v = t; v != s; v = edgeTo[v].other(v))
            {
                bottle = Math.min(bottle, edgeTo[v].residualCapacityTo(v));
            }
            for(int v = t; v != s; v = edgeTo[v].other(v))
            {
                edgeTo[v].addResidualFlowTo(v,bottle);
            }
            value += bottle;
        }
    }

    private boolean hasAugmentingPath(FlowNetwork G, int s, int t)
    {
        marked = new boolean[G.V()];
        edgeTo = new FlowEdge[G.V()];
        Queue<Integer> q = new Queue<Integer>();
        q.enqueue(s);
        marked[s] = true;
        while (!q.isEmpty())
        {
            int v = q.dequeue();
            for(FlowEdge e: G.adj(v))
            {
                int w = e.other(v);
                if(!marked[w] && e.residualCapacityTo(w) != 0)
                {
                    q.enqueue(w);
                    edgeTo[w] = e;
                    marked[w] = true;
                }
            }
        }
        return marked[t];
    }

    public double value() {return value;}
    public boolean inCut(int v) {return marked[v];}
    public static void main(String[] args)
    {
        In in = new In("tinyFN.txt");
        FlowNetwork G = new FlowNetwork(in);
        StdOut.println(G);

        FordFulkerson fordFulkerson = new FordFulkerson(G, 0, G.V() - 1);

        StdOut.println(fordFulkerson.value);

        for(int v = 0; v < G.V(); ++v)
        {
            StdOut.println(v + ":\n");
            for(FlowEdge e : G.adj(v))
                StdOut.println("    " + e);
        }
    }
}
