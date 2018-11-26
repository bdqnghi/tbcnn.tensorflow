/**
 * idea: find the maxVal of the array, build 0-maxVal inclusive length array which is maxVal + 1 buckets
 * so each bucket will be either zero element or multiple same elements
 * then collect them together
 * http://www.growingwiththeweb.com/2015/06/bucket-sort.html
 */

import java.util.*;
 
public class BucketSort {
    public static void sort(int[] a) {
        int maxVal = 0;
        for (int i = 0; i < a.length; i++) {
            if (maxVal < a[i]) {
                maxVal = a[i];
            }
        }
        // note, array index, must length of maxVal + 1
        int[] buckets = new int[maxVal + 1];
        for (int i = 0; i < a.length; i++) {
            buckets[a[i]]++;
        }

        int outPos = 0;
        for (int i=0; i<buckets.length; i++) {
            for (int j=0; j<buckets[i]; j++) {
                a[outPos] = i;
                outPos++;
            }
        }
    }

    public static void main(String[] args) {
        int[] data = {5,3,0,2,4,1,0,5,2,3,1,4};
        System.out.println("Before: " + Arrays.toString(data));
        sort(data);
        System.out.println("After:  " + Arrays.toString(data));
    }
}