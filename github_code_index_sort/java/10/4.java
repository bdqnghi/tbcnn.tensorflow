package net.tekrei.sorting.impl;

import java.util.ArrayList;
import java.util.List;

import net.tekrei.sorting.Sort;

/**
 * Bucketsort implementation
 * 
 * @author tekrei
 * 
 *         a sorting algorithm that works by partitioning an array into a number
 *         of buckets.
 * 
 *         Complexity: average and best case O(n+k), worst case O(n^2)
 *
 * @see <a
 *      href="https://en.wikipedia.org/wiki/Bucket_sort">https://en.wikipedia.

 *      org/wiki/Bucket_sort</a> <br/>
 *      <a href="https://en.algoritmy.net/article/41160/Bucket-sort"
 *      >https://en.algoritmy.net/article/41160/Bucket-sort</a>
 * 
 */

public class BucketSort extends Sort {

	private static int BUCKET_COUNT = 10;
	private List<Integer>[] buckets;
	MergeSort ms;

	@SuppressWarnings("unchecked")
	public BucketSort() {
		ms = new MergeSort();
		buckets = new ArrayList[BUCKET_COUNT];
	}

	@Override
	public List<Integer> sort(List<Integer> list) {

		int high = list.get(0);
		int low = list.get(0);
		// find the range of input elements
		for (int i = 1; i < list.size(); i++) {
			if (list.get(i) > high)
				high = list.get(i);
			if (list.get(i) < low)
				low = list.get(i);
		}
		// range of one bucket
		double interval = ((double) (high - low + 1)) / BUCKET_COUNT;
		// initialize the buckets
		for (int i = 0; i < BUCKET_COUNT; i++) {
			buckets[i] = new ArrayList<Integer>();
		}
		// distribute values to the buckets
		for (int i = 0; i < list.size(); i++) {
			buckets[(int) ((list.get(i) - low) / interval)].add(list.get(i));
		}
		// final step: sort each bucket and then merge them
		ArrayList<Integer> sortedList = new ArrayList<Integer>();
		for (int i = 0; i < BUCKET_COUNT; i++) {
			// sort the buckets using merge sort
			buckets[i] = ms.sort(buckets[i]);
			// merge the buckets
			for (int j = 0; j < buckets[i].size(); j++) {
				sortedList.add(buckets[i].get(j));
			}
		}

		return sortedList;
	}

}
