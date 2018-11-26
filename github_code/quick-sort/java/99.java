package algs.sort;

import stdlib.StdRandom;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Scanner;

import static algs.sort.Sort.exch;
import static algs.sort.Sort.less;
import static algs.sort.Sort.show;

public class Quick {
    public static void sort(Comparable[] a) {
        StdRandom.shuffle(a);
        sort(a, 0, a.length - 1);
    }

    private static void sort(Comparable[] a, int lo, int hi) {
        if (lo >= hi) return;
        int p = partition(a, lo, hi);
        sort(a, lo, p - 1 );
        sort(a, p + 1, hi);
    }

    private static int partition(Comparable[] a, int lo, int hi) {
        Comparable v = a[lo];
        int i = lo;
        int j = hi + 1;
        while (true) {
            while (less(a[++i], v)) if (i == hi) break;
            while (less(v, a[--j])) ;
            if (j <= i) break;
            exch(a, i, j);
        }
        exch(a, j, lo);
        return j;
    }

    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("C:\\Users\\qianji\\IdeaProjects\\Algorithms\\src\\words.txt");
        InputStream inputStream = new FileInputStream(file);
        Scanner scanner = new Scanner(inputStream);
        String s = scanner.nextLine();
        String[] a = s.split(" ");
        Quick.sort(a);
        show(a);
    }
}
