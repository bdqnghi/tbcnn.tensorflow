package algs21;
import stdlib.*;


public class Shell {

    
    public static <T extends Comparable<? super T>> void sort(T[] a) {
        final int N = a.length;

        
        int h = 1;
        while (h < N/3) h = 3*h + 1;

        while (h >= 1) {
            
            for (int i = h; i < N; i++) {
                for (int j = i; j >= h && less(a[j], a[j-h]); j -= h) {
                    exch(a, j, j-h);
                }
            }
            assert isHsorted(a, h);
            h /= 3;
        }
        assert isSorted(a);
    }



    

    
    private static <T extends Comparable<? super T>> boolean less(T v, T w) {
        ops++;
        return (v.compareTo(w) < 0);
    }

    
    private static <T> void exch(T[] a, int i, int j) {
        ops++;
        final T swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }


    
    private static <T extends Comparable<? super T>> boolean isSorted(T[] a) {
        for (int i = 1; i < a.length; i++)
            if (less(a[i], a[i-1])) return false;
        return true;
    }

    
    private static <T extends Comparable<? super T>> boolean isHsorted(T[] a, int h) {
        for (int i = h; i < a.length; i++)
            if (less(a[i], a[i-h])) return false;
        return true;
    }

    
    private static <T> void show(T[] a) {
        for (T element : a) {
            StdOut.println(element);
        }
    }

    private static long ops;
    private static double time;
    private static void countops (int N) {
        final Integer[] a = new Integer[N];
        
        for (int i = 0; i < a.length; i++) a[i] = StdRandom.uniform (N);
        
        
        

        ops = 0;
        final Stopwatch sw = new Stopwatch ();
        sort (a);
        time = sw.elapsedTime ();
        if (! isSorted (a)) throw new Error ();
        
    }
    public static void main(String[] args) {
        int N = 2000;
        countops (N);
        
        double prevOps = ops;
        double prevTime = time;
        for (int i=0; i<40; i++) {
            N *= 2;
            countops (N);
            StdOut.printf("%8d %10d %5.1f [%5.3f %5.3f]\n", N, ops, ops/prevOps, time, time/prevTime);
            prevOps = ops;
            prevTime = time;
        }
    }

    
    public static void bookMain(String[] args) {
        
        

        
        
        StdIn.fromFile ("data/words3.txt");

        final String[] a = StdIn.readAllStrings();
        sort(a);
        show(a);
    }

}
