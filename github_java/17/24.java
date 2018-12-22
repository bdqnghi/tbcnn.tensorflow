import java.io.FileOutputStream;
import java.io.PrintStream;

/**
 * Class for computing binomial coefficients which uses a memoization table
 * to cache computed results.
 * We can use a Splay tree or a Red-Black tree store table values.
 * All methods and fields are static so no instance needs to be created.
 *
 * @author <a href="mailto:wcochran@vancouver.wsu.edu">Wayne O. Cochran</a>
 */
public class Binomial {

    /*
     * Key class for storing input pair (n,k) for binomial coefficient
     * in symbol table.
     */
    private static class IntPair implements Comparable<IntPair> {
        private int n, k;

        public IntPair(int n, int k) {
            this.n = n;
            this.k = k;
        }

        public int compareTo(IntPair p) {
            int cmp = n - p.n;
            if (cmp == 0)
                cmp = k - p.k;
            return cmp;
        }

        public String toString() {
            return n + "," + k;
        }
    }
        
    /*
     * Memoization table for binomial coefficients.
     */

    private static SplaySymbolTable<IntPair, Long> table =
            new SplaySymbolTable<IntPair, Long>();
    /* XXX
    private static RedBlackTreeSymbolTable<IntPair,Long> table = 
        new RedBlackTreeSymbolTable<IntPair,Long>();
        */

    /*
     * Enable/disable memoization (at compile tile)
     */
    final static boolean memoize = true;

    /**
     * Memoized implementation of (n choose k); Results of intermediate
     * computations are cached in a table (which persists between calls)
     *
     * @param n n >= k >= 0
     * @param k n <= k <= 0
     * @return n choose k
     */
    public static long binomial(int n, int k) {
        if (k == 0 || n == k)
            return 1;
        if (k == 1 || k == n - 1)
            return n;
        if (k > n / 2)
            k = n - k;
        if (memoize) {
            IntPair key = new IntPair(n, k);
            Long v = table.search(key);
            if (v != null)
                return v.longValue();
            long b = binomial(n - 1, k - 1) + binomial(n - 1, k);
            table.insert(key, b);
            return b;
        } else {
            return binomial(n - 1, k - 1) + binomial(n - 1, k);
        }
    }

    private final static boolean even(int n) {
        return (n & 1) == 0;
    }

    private static double power(double b, int n) {
        if (n == 0) return 1;
        if (n == 1) return b;
        double v = power(b, n / 2);
        v *= v;
        return even(n) ? v : v * b;
    }

    /**
     * Probability of exactly k "successes" in n independent trials.
     *
     * @param n number of (independent) trials
     * @param k number of "successes"
     * @param p probability of success on one trial
     * @returns probability between 0 and 1 inclusive.
     */
    public static double probability(int k, int n, double p) {
        if (k > n / 2) {  // f(k,n,p) = f(n-k,n,1-p)
            k = n - k;
            p = 1 - p;
        }
        return binomial(n, k) * power(p, k) * power(1 - p, n - k);
    }

    /**
     * Probability of at least k "successes" in n independent trials.
     * <p>
     * Computes sum for i = 0..k of probability(i,n.p).
     *
     * @param n number of (independent) trials
     * @param k number of "successes"
     * @param p probability of success on one trial
     * @returns probability between 0 and 1 inclusive.
     */
    public static double cumulativeProbabilty(int k, int n, double p) {
        double sum = 0.0;
        for (int i = 0; i <= k; i++)
            sum += probability(i, n, p);
        return sum;
    }

    /**
     * Test method that prints internal tree used by memoization table for
     * evaluation of a sequence of binomial coefficients.
     */
    private static void experiment1() {
    /* XXX
        for (int i = 2; i <= 10; i++) {
            long v = binomial(20, i);
            System.out.println(v);
        }
	*/

        long v = binomial(10, 2);

	/* XXX
 	long v = binomial(10, 2);
	v = binomial(10, 3);
	v = binomial(10, 4);
	v = binomial(10, 5);
	*/

        System.out.println("comparisons=" + table.comparisons + ", rotations=" + table.rotations);
        java.util.Vector<String> serializedTree = table.serialize();
        TreePrinter treePrinter = new TreePrinter(serializedTree);
        treePrinter.fontSize = 12; //16;
        treePrinter.nodeRadius = 12; // 14; //20;
        treePrinter.scalex = 30; // 20; // 50; //50;
        treePrinter.scaley = 40; // 25; //50; // 30; //60;
        try {
            FileOutputStream out = new FileOutputStream("splay-tree-10-choose-2345.svg");
            // XXX FileOutputStream out = new FileOutputStream("splay-tree-20-choose-2-10.svg");
            // XXX FileOutputStream out = new FileOutputStream("red-black-tree.svg");
            PrintStream ps = new PrintStream(out);
            treePrinter.printSVG(ps);
        } catch (Exception e) {
            System.err.println("Error writing SVG file: " + e.getMessage());
        }
    }


    /**
     * Test program used to time the computation of a sequence of
     * binomial coefficients. Current the table is implemented with
     * either a Splay Tree or a Red-Black Tree.
     * The number of comparisons and tree rotations
     * used for insert/search table operations is also given (set up for
     * future comparisons with AVL and Red-Black trees).
     *
     * @param args ignored
     */
    public static void main(String[] args) {
        // XXX experiment1();

        long startTime = System.nanoTime();
        int n = 35; // 35;
        int imax = n / 2;
        for (int i = 2; i <= imax; i++) {
            long v = binomial(n, i);
            System.out.println("binomial(" + n + ", " + i + ") = " + v);
        }
        long endTime = System.nanoTime();
        double seconds = (endTime - startTime) * 1e-9;
        System.out.println("time = " + seconds + " seconds");
        System.out.println("comparisons = " + table.comparisons);
        System.out.println("rotations = " + table.rotations);
        table.printTree("binomial-.svg");
    }

}
