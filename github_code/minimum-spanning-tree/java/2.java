package minimumspanningtree;

/**
 *
 * @author Ahmed El Torky
 */
public class Main {

    private static final int DIM = 7;
    private static final int INF = 99;

    private static int weight[][] = {
        //    1  2   3    4    5    6   7
        /*1*/{0, 3, INF, INF, INF, INF, 5},
        /*2*/ {3, 0, 2, INF, INF, INF, 5},
        /*3*/ {INF, 2, 0, 7, 1, 1, 3},
        /*4*/ {INF, INF, 7, 0, 6, 7, INF},
        /*5*/ {INF, INF, 1, 6, 0, 4, INF},
        /*6*/ {INF, INF, 1, 7, 4, 0, 8},
        /*7*/ {5, 5, 3, INF, INF, 8, 0}
    };

    private static int weight2[][] = {
        {0, 5, 2, 3, INF},
        {5, 0, 4, INF, 3},
        {2, 4, 0, INF, 4},
        {3, INF, INF, 0, INF},
        {INF, 3, 4, INF, 0}
    };

    public static void main(String[] args) {

        MinimumSpanningTree mst = new MinimumSpanningTree(DIM, INF, weight);
        System.out.println("before minimum spanning tree algorithm:");
        System.out.println("---------------------------------------");
        mst.printArray(weight);
        mst.minimumSpanningTree();
        
        System.out.println("\n\n");
        System.out.println("after minimum spanning tree algorithm:");
        System.out.println("--------------------------------------");
        mst.printArray(weight);

    }

}
