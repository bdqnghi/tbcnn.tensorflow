package Sort;

import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;

/**
 * Created by Srunkyo on 18/1/31.
 */
public class Insertion {
    // 多键数组的比较
    public static void sort(Object[] a, Comparator c){
        int N = a.length;
        for (int i =1; i<N; i++){
            for (int j = i; j > 0 && less(c, a[j], a[j-1]); j--)
                exch(a, j, j-1);
        }
    }

    private static boolean less(Comparator c, Object v, Object w){
        return c.compare(v, w)<0;
    }

    private static void exch(Object[] a, int i, int j){
        Object t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    // 插入排序
    public static void sort(Comparable[] a) {
        int N = a.length;
        for (int i = 1; i < N; i++){
            for (int j = i; j>0 && less(a[j],a[j-1]); j--) {
                exch(a, j-1, j);
            }
        }
    }

    private static boolean less(Comparable v, Comparable w){
        return v.compareTo(w) < 0;
    }

    private static void exch(Comparable[] a, int i, int j){
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    private static void show(Comparable[] a){
        for (int i = 0; i < a.length; i++){
            StdOut.print(a[i] + " ");
        }
        StdOut.println();
    }

    public static boolean isSorted(Comparable[] a){
        for (int i =1; i< a.length; i++)
            if (less(a[i], a[i-1])) return false;
        return true;
    }

    public static void main(String[] args){
        /*
        * 插入排序 */
//        String[] a = StdIn.readAllStrings();
//        sort(a);
//        assert isSorted(a);
//        show(a);

        /*
        * 插入排序比较多键数组*/
        Transaction[] a = new Transaction[4];
        a[0] = new Transaction("Turing   6/17/1990  644.08");
        a[1] = new Transaction("Tarjan   3/26/2002 4121.85");
        a[2] = new Transaction("Knuth    6/14/1999  288.34");
        a[3] = new Transaction("Dijkstra 8/22/2007 2678.40");
        // 默认排序
        StdOut.println("按照默认排序（金额）");
        sort(a);
        for(Transaction i : a){
            StdOut.println(i.toString());
        }
        StdOut.println("按照时间排序");

        // 时间排序
        sort(a, new Transaction.WhenOrder());
        for(Transaction i : a){
            StdOut.println(i.toString());
        }

        StdOut.println("按照姓名排序");
        // 姓名排序
        sort(a, new Transaction.WhoOrder());
        for(Transaction i : a){
            StdOut.println(i.toString());
        }
    }
}
