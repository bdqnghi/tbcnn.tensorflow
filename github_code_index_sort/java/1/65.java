package testing;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Admin on 08-10-2016.
 */
public class insertionsort {
    public static void main(String[] args) {
        int[] x = new int[10];
        int k = 1;
        for (int i = 1; i <= 10; i++) {
            x[i - 1] = (i * k);
            k = k * -1;
        }
        for (int i = 0; i < 10; i++) {
            System.out.print('\t');
            System.out.print(x[i]);
        }
        x = inserSort(x);
        System.out.println();
        for (int i = 0; i < 10; i++) {
            System.out.print('\t');
            System.out.print(x[i]);
        }
    }

    public static int[] inserSort(int[] x) {
        for (int i = 1; i < x.length; i++) {
            int k;
            for (int j = i; j > 0; j--) {
                if (x[j] < x[j - 1]) {
                    k = x[j];
                    x[j] = x[j - 1];
                    x[j - 1] = k;
                }
            }
        }
        return x;
    }
}
