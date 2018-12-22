package quicksort;

import java.util.Arrays;
import java.util.Random;

/**
 * Zack Wiseman 
 * 09/23/2016 
 * Homework 4: Data Structures 
 * Quicksort and Randomized Quicksort
 *
 * This program will implement quicksort and randomized quicksort on a given
 * array defined in the main/testing class.A helper method named partition will
 * help the recursive methods quicksort and randomized quicksort determine the
 * correct position of the values.both versions of quicksort will choose a pivot
 * value and place the pivot in the correct position of the array with values
 * greater being after and lesser being before.
 *
 * @author zacharywiseman
 */
public class Quicksort {

    /**
     * Method to sort an array recursively using the divide and conquer method
     * taking worst case Θ(n^2) runtime average case Θ(n*log(n)) time and best
     * case Θ(n*log(n)) time with the runtime being dependant on the choice of
     * pivot.
     *
     * @param A input array
     * @param p
     * @param r
     */
    public void quicksort(int A[], int p, int r) {
        if (p < r) { // base case of empty cells 
            int q = partition(A, p, r);
            quicksort(A, p, q - 1);
            quicksort(A, q + 1, r);
        }
    }//quicksort

    /**
     * Method to implement quicksort with a random choice of pivot.
     *
     * @param A input array
     * @param p first element of the subproblem
     * @param r pivot choice
     */
    public void randomizedQuicksort(int[] A, int p, int r) {
        if (p < r) {//basecase of empty cells
            Random rand = new Random();
            int x = rand.nextInt(A.length);//arbitrary array index
            swap(A, x, r);//random index with chosen index
            int q = partition(A, p, r);
            randomizedQuicksort(A, p, q - 1);//recursive case
            randomizedQuicksort(A, q + 1, r);//recursive case
        }
    }//randomizedQuicksort

    /**
     * Helper method that divides the problem into subproblems that will also
     * swap to put the pivot choice in the right place in the subproblem.
     *
     * @param A input array
     * @param p first element of the subproblem
     * @param r pivot choice
     * @return
     */
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
    }//partition

    /**
     * Method to swap 2 elements in an array.
     *
     * @param A the array to use
     * @param i first element to swap
     * @param j the element i is swapped with
     */
    private void swap(int A[], int i, int j) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }//swap

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        /**
         * ******************* Test Arrays *******************************
         */
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

        /**
         * ****************** Testing Implementation ************************
         */
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
    }//main method
}//Quicksort
