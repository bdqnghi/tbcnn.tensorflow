package algs.sort;

import stdlib.StdOut;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Scanner;

import static algs.sort.Sort.*;

public class Shell {
    public static void sort(Comparable[] a) {
        int N = a.length;
        int h = 1;
        while (h < N / 3) h = h * 3 + 1;
        while (h >= 1) {
            for (int i = h; i < N; i++) {
                for (int j = i; j >= h && less(a[j], a[j - h]); j -= h) {
                    exch(a, j, j - h);
                }
            }
            h /= 3;
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("C:\\Users\\qianji\\IdeaProjects\\Algorithms\\src\\words.txt");
        InputStream inputStream = new FileInputStream(file);
        Scanner scanner = new Scanner(inputStream);
        String s = scanner.nextLine();
        String[] a = s.split(" ");
        Shell.sort(a);
        show(a);
    }
}
