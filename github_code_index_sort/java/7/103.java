import java.lang.Comparable;

/**
 * An implementation of shell-sort (repeated h-sorts)
 * Uses the Knuth increment sequence of h = 3*h + 1
 */
public class Shell {
    /**
     * Sort an array of comparables
     * 
     * @param a: array to be sorted
     */
    public static void sort(Comparable[] a) {
        int N = a.length;
        // set initial value of h
        int h = 1;
        while (h < N/3) {
            h = 3*h + 1;
        }
        // now do repeated h-sorts
        while (h >= 1) {
            for (int i = h; i < N; i++) {
                for (int j = i; j >= h; j-= h) {
                    if (less(a[j], a[j-h])) {
                        exch(a, j, j-h);
                    }
                }
            }
            h = h / 3;
        }
    }
    
    /*
    Check if an element is lesser than another
    */
    private static boolean less(Comparable p, Comparable q) {
        return p.compareTo(q) < 0;
    }
    
    /*
    Exchange 2 elements in an array
    */
    private static void exch(Comparable[] a, int i, int j) {
        Comparable swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }
}