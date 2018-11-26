import java.util.Scanner;

/**
 * 最大流问题测试类
 * Created by hongjiyao_2014150120 on 16-12-6.
 */
public class MaxFlow {

    private static final int V = 6;             // 点的个数

    public static void main(final String[] args) {

        FlowNetwork flowNetwork = new FlowNetwork(V);

        Scanner in = new Scanner(System.in);

        double capacity;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                capacity = in.nextDouble();
                if (capacity > 0) {
                    FlowEdge e = new FlowEdge(i, j, capacity);
                    flowNetwork.addEdge(e);
                }
            }
        }

        FordFulkerson fordFulkerson = new FordFulkerson(flowNetwork, 0, V - 1);

        System.out.println("最大流量：" + fordFulkerson.value());
    }
}
