package com.redmond.coding.sort;

import java.util.ArrayList;
import java.util.List;

import com.redmond.coding.GeneralUtils;

public class BucketSort implements Sort{
	
	public int bucketSize = 100;
	public Sort sort = new BubbleSort();
	
	public BucketSort() {
		
	}
	
	public BucketSort(int bucketSize) {
		super();
		this.bucketSize = bucketSize;
	}
	
	public BucketSort(int bucketSize, Sort sort) {
		super();
		this.bucketSize = bucketSize;
		this.sort = sort;
	}

	public void sort(int[] values) {
		
		List<List<Integer>> buckets = new ArrayList<List<Integer>>();
		
		for (int value : values) {
			int bucket = value / bucketSize;
			if (buckets.size() <= bucket) {
				for (int size = buckets.size();size <= bucket;size++) {
					buckets.add(null);
				}
			}
			List<Integer> mybuckets = buckets.get(bucket);
			if (mybuckets == null) {
				mybuckets = new ArrayList<Integer>();
				buckets.set(bucket, mybuckets);
			}
			mybuckets.add(value);
		}
		
		int i = 0;
		for (List<Integer> bucket : buckets) {
			if (bucket == null) {
				continue;
			}
			
			if (bucket.size() == 1) {
				values[i++] = bucket.get(0);
			} else {
				int[] myvalues = new int[bucket.size()];
				for (int j = 0;j<bucket.size();j++) {
					myvalues[j] = bucket.get(j);
				}
				
				sort.sort(myvalues);
				for (int j = 0;j<bucket.size();j++) {
					values[i++] = myvalues[j];
				}
			}
		}
	}

	public static void main(String[] args) {
		
		Sort sort = new BucketSort();

		{
			int[] test = { 4, 6, 2, 10, 5 };
			sort.sort(test);
			System.out.println("res = " + GeneralUtils.toString(test));
		}

		{
			int[] test = { 1, 300, 4, 6, 7, 100, 2, 10, 5, 10102, 0, 504 };
			sort.sort(test);
			System.out.println("res = " + GeneralUtils.toString(test));
		}

		{
			int[] test = { 1, 300, 4, 6, 7, 100, 2, 10, 5, 10102, 0, 504, 80,
					34, 28 };
			sort.sort(test);
			System.out.println("res = " + GeneralUtils.toString(test));
		}

		{
			int[] test = { 1, 300, 4, 6, 7, 100, 2, 10, 5, 10102, 0, 504, 80,
					34, 28, 50000 };
			sort.sort(test);
			System.out.println("res = " + GeneralUtils.toString(test));
		}
		
		{
			int[] test = new int[10000];
			for (int i = 0;i<test.length;i++) {
				test[i] = 100;
			}
			sort.sort(test);
			System.out.println("res = " + GeneralUtils.toString(test));
		}

	}
}
