package quicksort;

import java.util.Arrays;
import java.util.Random;


public class Quicksort {

    
    public void quicksort(int A[], int p, int r) {
        if (p < r) { 
            int q = partition(A, p, r);
            quicksort(A, p, q - 1);
            quicksort(A, q + 1, r);
        }
    }

    
    public void randomizedQuicksort(int[] A, int p, int r) {
        if (p < r) {
            Random rand = new Random();
            int x = rand.nextInt(A.length);
            swap(A, x, r);
            int q = partition(A, p, r);
            randomizedQuicksort(A, p, q - 1);
            randomizedQuicksort(A, q + 1, r);
        }
    }

    
    private int partition(int A[], int p, int r) {
        int x = A[r];
        int i = p - 1;
        for (int j = p; j < r; j++) {
            if (A[j] <= x) {
                i = i + 1;
                swap(A, i, j);
            }
            swap(A, i + 1, r);
        }
        return i + 1;
    }

    
    private void swap(int A[], int i, int j) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    
    public static void main(String[] args) {
        
        Quicksort sort = new Quicksort();
        int a[] = {1, 2, 5, 3, 4};
        int a1[] = {1, 2, 5, 3, 4};
        int b[] = {10, 20, 1, 3};
        int b1[] = {10, 20, 1, 3};
        int c[] = {5, 100, 119, 50, 6, 20};
        int c1[] = {5, 100, 119, 50, 6, 20};
        int d[] = {20, 50, 100, 75, 25, 15};
        int d1[] = {20, 50, 100, 75, 25, 15};
        int e[] = {70, 80, 1000, 3000, 40, 25, 27, 84, 90, 100};
        int e1[] = {70, 80, 1000, 3000, 40, 25, 27, 84, 90, 100};

        
        System.out.println("Original: ");
        System.out.println(Arrays.toString(a));
        sort.quicksort(a, 0, a.length - 1);
        System.out.println("Quicksort: ");
        System.out.println(Arrays.toString(a));
        sort.randomizedQuicksort(a1, 0, a1.length - 1);
        System.out.println("Randomized Quicksort: ");
        System.out.println(Arrays.toString(a1));
        System.out.println();

        System.out.println("Original: ");
        System.out.println(Arrays.toString(b));
        sort.quicksort(b, 0, b.length - 1);
        System.out.println("Quicksort: ");
        System.out.println(Arrays.toString(b));
        sort.randomizedQuicksort(b1, 0, b1.length - 1);
        System.out.println("Randomized Quicksort: ");
        System.out.println(Arrays.toString(b1));
        System.out.println();

        System.out.println("Original: ");
        System.out.println(Arrays.toString(c));
        sort.quicksort(c, 0, c.length - 1);
        System.out.println("Quicksort: ");
        System.out.println(Arrays.toString(c));
        sort.randomizedQuicksort(c1, 0, c1.length - 1);
        System.out.println("Randomized Quicksort: ");
        System.out.println(Arrays.toString(c1));
        System.out.println();

        System.out.println("Original: ");
        System.out.println(Arrays.toString(d));
        sort.quicksort(d, 0, d.length - 1);
        System.out.println("Quicksort: ");
        System.out.println(Arrays.toString(d));
        sort.randomizedQuicksort(d1, 0, d1.length - 1);
        System.out.println("Randomized Quicksort: ");
        System.out.println(Arrays.toString(d1));
        System.out.println();

        System.out.println("Original: ");
        System.out.println(Arrays.toString(e));
        sort.quicksort(e, 0, e.length - 1);
        System.out.println("Quicksort: ");
        System.out.println(Arrays.toString(e));
        sort.randomizedQuicksort(e1, 0, e1.length - 1);
        System.out.println("Randomized Quicksort: ");
        System.out.println(Arrays.toString(e1));
    }
}
