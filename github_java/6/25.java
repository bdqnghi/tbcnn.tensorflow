import java.util.*;

/* Java program for Merge Sort */
public class MergeSort {
    // Merges two sub-Arrays A[l..m] and A[m+1..r].
    // l->left most index, r->right most index, m->middle index
    void merge(int A[], int l, int m, int r) {
        // Find sizes of two subArrays to be merged
        int nL = m - l + 1; //for left sub-array
        int nR = r - m; //for right sub-array

        /* create temp Arrays left[] and right[]
        and copy data from main Array */
        int left[] = new int [nL];
        int right[] = new int [nR];

        for (int i = 0; i < nL; ++i)
            left[i] = A[l + i];
        for (int j = 0; j < nR; ++j)
            right[j] = A[m + 1 + j];

        /* Merge the temp Arrays back into A[l..r]*/

        // Initial indexes of first and second sub-Arrays
        int i = 0, j = 0;
        int k = l;  // Initial index of merged sub-array

        /* Comparing left[] and right[], sub-Array with
        smaller element get copy to main Array A[]*/
        while (i < nL && j < nR) {
            if (left[i] <= right[j]) {
                A[k] = left[i];
                i++;
            } else {
                A[k] = right[j];
                j++;
            }
            k++;
        }
        /* Copy remaining elements of left[] if any */
        while (i < nL) {
            A[k] = left[i];
            i++;
            k++;
        }
        /* Copy remaining elements of right[] if any */
        while (j < nR) {
            A[k] = right[j];
            j++;
            k++;
        }
    }

    // Main function that sorts A[l..r] using merge()
    /* l is for left index and r is right index of the
    sub-Array of A to be sorted */
    void merge_sort(int A[], int l, int r) {
        if (l < r) {
            int mid = (l + r) / 2; // Find the middle index

            merge_sort(A, l, mid); //Firstly left half is recursively call
            merge_sort(A , mid + 1, r); // Then right half is recursively call
            merge(A, l, mid, r); // Merge the sorted halves
        }
    }
    // Driver method
    public static void main(String args[]) {
        int Arr[] = {38, 27, 43, 3, 9, 82, 10};

        System.out.println("Unsorted Array:");
        //print unsorted array using Arrays.toString()
        System.out.println(Arrays.toString(Arr));

        //object of class MergeSort
        MergeSort ob = new MergeSort();
        ob.merge_sort(Arr, 0, Arr.length - 1); //merge sort function call

        System.out.println("\nSorted Array:");
        System.out.println(Arrays.toString(Arr)); //print sorted array
    }
}