package chap26_maxflow;
import java.util.LinkedList;  
import java.util.Queue;  
import java.util.Random;
 /**
  *Ford-Fulkerson算法
  */
public class FordFulkerson {  
    private FlowEdge[] edgeTo;  
    private double value;  
   
    public FordFulkerson(FlowNetwork G, int s, int t) {  
        // 一直增加流量直到无法再增加为止  
        while (hasAugmentingPath(G, s, t)) {  
            // 找出增广路的瓶颈  
            double bottle = Double.POSITIVE_INFINITY;  
            int v = t;  
            while (v != s) {  
                bottle = Math.min(bottle, edgeTo[v].residualCapacityTo(v));  
                v = edgeTo[v].other(v);  
            }  
   
            // 增加整条路径的流量  
            v = t;  
            while (v != s) {  
                edgeTo[v].addResidualFlowTo(v, bottle);  
                v = edgeTo[v].other(v);  
            }  
   
            // 最大流增加  
            value += bottle;  
        }  
    }  
   
    public double value() {  
        return value;  
    }  
   
    // 判断是否有增广路  
    // 有增广路的条件就是存在一条路径，这条路径上所有的边都能增加流量。  
    private boolean hasAugmentingPath(FlowNetwork G, int s, int t) {  
        edgeTo = new FlowEdge[G.V()]; // 注意，这句话是必须要有的。因为每次增广路径都不一样。  
        boolean[] visited = new boolean[G.V()];  
   
        // BFS  
        Queue<Integer> q = new LinkedList<Integer>();  
        q.add(s);  
        visited[s] = true; // 注意：这句话不要遗漏  
        while (!q.isEmpty()) {  
            int v = q.poll();  
   
            // 能够通过的条件是流量能够增加  
            for (FlowEdge e : G.adj(v)) {  
                int w = e.other(v);  
                if (e.residualCapacityTo(w) > 0 && !visited[w]) {  
                    edgeTo[w] = e;  
                    q.add(w);  
                    visited[w] = true;  
                }  
            }  
        }  
   
        // 有增广路的条件就是S点能够到达T点。  
        return visited[t];  
    }  
   
    public static void main(String[] argv) {  
        FlowNetwork g = new FlowNetwork(4);  
        int[] data = {0, 1, r(), 0, 2, r(), 2, 1, r(), 1, 3, r(), 2, 3, r(), 0, 3, r()};  
        for (int i = 0; i < data.length; i += 3) {  
            g.addEdge(new FlowEdge(data[i], data[i + 1], data[i + 2]));  
        }  
        System.out.println(new FordFulkerson(g, 0, 3).value());  
    }  
   
    private static int r() {  
        Random random=new Random();
        return random.nextInt(1000);  
    }  
}  
