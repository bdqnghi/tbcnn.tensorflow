package sorting_and_searching;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;



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

    
    public static void bucketSort(int[] a, int bucketSize) {
        if (a.length == 0) {
            return;
        }

        
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

        
        int noOfBuckets = (maxValue - minValue) / bucketSize + 1;
        List<List<Integer>> buckets = new ArrayList<>(noOfBuckets);
        for (int i = 0; i < noOfBuckets; i++) {
            buckets.add(new ArrayList<>());
        }

        
        for (int i = 0; i < a.length; i++) {
            buckets.get((a[i] - minValue) / bucketSize).add(a[i]);
        }

        
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

    
    public static void bucketSort2(int[] a, int maxVal) {

        
        int[] buckets = new int[maxVal + 1];
        for (int i = 0; i < buckets.length; i++) {
            buckets[i] = 0;
        }

        
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
