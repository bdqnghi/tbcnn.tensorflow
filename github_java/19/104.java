package sorting_and_searching;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 * Time Complexity: best and average case: O(n + k) where k is number of buckets
 * worst-case O(n^2).
 *
 * Space Complexity: O(n+k)
 *
 * There are two main variants of bucket sort: 1) Where there is a bucket for
 * each value and 2) Where buckets hold several values.
 *
 * @author Harshit
 */
public class BucketSort {

    public static void main(String[] args) {
        int[] a = {15, 13, 10, 8, 7, 11, 10, 5, 6, 9, 6, 12};
        int default_bucket_size = 5;
        System.out.println("Before: " + Arrays.toString(a));
        bucketSort(a, default_bucket_size);
        System.out.println("After:  " + Arrays.toString(a));

        int[] b = {5, 3, 0, 2, 4, 1, 0, 5, 2, 3, 1, 4};
        int maxVal = 5;
        System.out.println("Before: " + Arrays.toString(b));
        bucketSort2(b, maxVal);
        System.out.println("After:  " + Arrays.toString(b));
    }

    /**
     * This method implements the 2 variant of bucket sort where buckets holds
     * several values. This is more commonly used in practice.
     *
     * Ref: http://www.growingwiththeweb.com/2015/06/bucket-sort.html Ref2:
     * http://www.geeksforgeeks.org/bucket-sort-2/ for decimals
     *
     * @param a
     * @param bucketSize
     */
    public static void bucketSort(int[] a, int bucketSize) {
        if (a.length == 0) {
            return;
        }

        // Determine minimum and maximum values from an array.
        int maxValue = a[0];
        int minValue = a[0];
        for (int i = 0; i < a.length; i++) {
            if (a[i] > maxValue) {
                maxValue = a[i];
            }
            if (a[i] < minValue) {
                minValue = a[i];
            }
        }

        // Initialize buckets
        int noOfBuckets = (maxValue - minValue) / bucketSize + 1;
        List<List<Integer>> buckets = new ArrayList<>(noOfBuckets);
        for (int i = 0; i < noOfBuckets; i++) {
            buckets.add(new ArrayList<>());
        }

        // Distribute input array values into buckets
        for (int i = 0; i < a.length; i++) {
            buckets.get((a[i] - minValue) / bucketSize).add(a[i]);
        }

        // Sort each buckets and place back into input array
        int index = 0;
        for (int i = 0; i < buckets.size(); i++) {
            Integer[] bucketArray = new Integer[buckets.get(i).size()];
            bucketArray = buckets.get(i).toArray(bucketArray);
            Arrays.sort(bucketArray);
            for (Integer elem : bucketArray) {
                a[index++] = elem;
            }
        }
    }

    /**
     * This method implements the 1 variant of bucket sort where there is a
     * bucket for each value of an array.
     *
     * Ref: http://www.javacodex.com/Sorting/Bucket-Sort
     *
     * @param a
     * @param maxVal
     */
    public static void bucketSort2(int[] a, int maxVal) {

        // Initialize buckets
        int[] buckets = new int[maxVal + 1];
        for (int i = 0; i < buckets.length; i++) {
            buckets[i] = 0;
        }

        // Increase count for each value of an array into our bucket/count array.
        for (int i = 0; i < a.length; i++) {
            buckets[a[i]]++;
        }

        int index = 0;
        for (int i = 0; i < buckets.length; i++) {
            for (int j = 0; j < buckets[i]; j++) {
                a[index++] = i;
            }
        }
    }
}
