package com.marmoush.javasamples.javase.algorithms.sorting;

import java.util.Arrays;

/**
 * http://www.cs.hmc.edu/~keller/courses/cs60/s98/examples/Sort/bucketsort.java
 *
 * <p>http://www.javacodex.com/Sorting/Bucket-Sort
 *
 * @author jazri
 */
class BucketSort {
  public static void main(String[] args) {
    int[] data = {3, 1, 6};

    System.out.println("Before: " + Arrays.toString(data));
    // sort(data, maxVal);
    bucketSort02(data, 6);
    System.out.println("After:  " + Arrays.toString(data));
  }

  public static void bucketSort01(int a[], int m) {
    int[] buckets = new int[m];
    for (int i = 0; i < m; i++) {
      buckets[i] = 0;
    }
    for (int i = 0; i < a.length; i++) {
      ++buckets[a[i]];
    }
    for (int i = 0, j = 0; j < m; j++) {
      for (int k = buckets[j]; k > 0; k--) {
        a[i++] = j;
      }
    }
  }

  public static void bucketSort02(int[] a, int maxVal) {
    int[] buckets = new int[maxVal + 1];

    for (int i = 0; i < buckets.length; i++) {
      buckets[i] = 0;
    }

    for (int i = 0; i < a.length; i++) {
      buckets[a[i]]++;
    }

    int pos = 0;
    for (int i = 0; i < buckets.length; i++) {
      for (int j = 0; j < buckets[i]; j++) {
        a[pos++] = i;
        System.out.println(buckets[i] + "---" + pos);
      }
    }
  }

  public static void bucketSort03(int array[]) {
    int min = array[0];
    int max = min;
    for (int i = 1; i < array.length; i++)
      // Find the minimum and maximum
      if (array[i] > max) max = array[i];
      else if (array[i] < min) min = array[i];

    int bucket[] = new int[max - min + 1]; // Create buckets

    for (int i = 0; i < array.length; i++)
      // "Fill" buckets by counting each datum
      bucket[array[i] - min]++;

    int i = 0;
    for (int b = 0; b < bucket.length; b++)
      // "Empty" buckets
      for (int j = 0; j < bucket[b]; j++)
        // back into array by creating one per count
        array[i++] = b + min;
  }
}
