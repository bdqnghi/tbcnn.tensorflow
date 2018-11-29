package sorts;

import java.util.Arrays;

/**
 * Created by Chris Keyser on 3/17/2016.
 * radix sort implementation
 * currently can't handle negative numbers
 */
public class RadixSort {
    public static int[] sort(int[] arr) {
        int max = getMax(arr);

        for(int exp = 1; max / exp > 0; exp *= 10) {
            countSort(arr, exp);
        }

        return arr;
    }

    // A function to do counting sort of arr[] according to
    // the digit represented by exp.
    // taken from http://www.geeksforgeeks.org/radix-sort/
    // because I couldn't figure out the parts at 52 or 57
    private static void countSort(int[] arr, int exp)
    {
        int output[] = new int[arr.length]; // output array
        int i;
        int count[] = new int[10];
        Arrays.fill(count,0);

        // Store count of occurrences in count[]
        for (i = 0; i < arr.length; i++)
            count[ (arr[i]/exp)%10 ]++;

        // Change count[i] so that count[i] now contains
        // actual position of this digit in output[]
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];

        // Build the output array
        for (i = arr.length - 1; i >= 0; i--)
        {
            output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
            count[ (arr[i]/exp)%10 ]--;
        }

        // Copy the output array to arr[], so that arr[] now
        // contains sorted numbers according to current digit
        for (i = 0; i < arr.length; i++)
            arr[i] = output[i];
    }

    /**
     * helper function to get the largest number in
     */
    private static int getMax(int[] arr) {
        int max = Integer.MIN_VALUE;

        for(int n : arr) {
            if (n > max) max = n;
        }

        return max;
    }
}
