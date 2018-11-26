package sedgewick_algo.course2.week2_mst;

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class MinimumSpanningTree {
    MinimumSpanningTree(EdgeWeightedGraph graph){

    }

    public Iterable<Edge> edges(){
        return null;
    }

    public double weight(){
        return 0.0;
    }

    public static void main(String args[]){
        In in = new In(args[0]);
        EdgeWeightedGraph graph = new EdgeWeightedGraph(in);
        MinimumSpanningTree mst = new MinimumSpanningTree(graph);

        for(Edge e : mst.edges()){
            StdOut.print(e);
        }

        StdOut.printf("%.2f\n", mst.weight());
    }
}
