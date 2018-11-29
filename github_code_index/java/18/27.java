package algs.sort;

import stdlib.StdOut;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Scanner;

import static algs.sort.Sort.*;

public class Selection {
    public static void sort(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            int min = i;
            for (int j = i+1; j < a.length; j++)
                if (less(a[j], a[min])) min = j;
            exch(a, min, i);
        }
    }


    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("C:\\Users\\qianji\\IdeaProjects\\Algorithms\\src\\words.txt");
        InputStream inputStream = new FileInputStream(file);
        Scanner scanner = new Scanner(inputStream);
        String s= scanner.nextLine();
        String[] a = s.split(" ");
        Selection.sort(a);
        show(a);
    }
}
