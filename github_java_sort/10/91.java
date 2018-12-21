package com.thoughtworks.fjw.bucketsortfalternative;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class BucketSortTask extends RecursiveTask<int[]> {

	private static final long serialVersionUID = 1L;

	private final int[] arrayToSort;
	private final int nofBuckets;
	private int bucketToExamine = -1;
	private int[] bucket;

	public BucketSortTask(final int[] arrayToSort, final int nofBuckets, final int bucketToExamine) {
		this.arrayToSort = arrayToSort;
		this.nofBuckets = nofBuckets;
		this.bucketToExamine = bucketToExamine;
	}

	public BucketSortTask(final int[] arrayToSort, final int nofBuckets) {
		this(arrayToSort, nofBuckets, -1);
	}

	
	@Override
	protected int[] compute() {
		if (bucketToExamine >= 0) {
			
			prepareAndFillBucket();
			Arrays.sort(bucket);

			return bucket;
		}

		
		List<BucketSortTask> tasks = createBucketSortTasks();
		for (BucketSortTask task : tasks) {
			task.fork();
		}

		
		int[] merged = new int[arrayToSort.length];
		int bucketCount = 0;
		for (BucketSortTask bucketSortTask : tasks) {
			int[] bucket = bucketSortTask.join();
			for (int element : bucket) {
				if (element != -1) {
					merged[bucketCount++] = element;
				}
			}
		}

		
		return merged;
	}

	List<BucketSortTask> createBucketSortTasks() {
		List<BucketSortTask> tasks = new ArrayList<BucketSortTask>();
		for (int bucket = 0; bucket < nofBuckets; bucket++) {
			BucketSortTask bucketSortTask = new BucketSortTask(arrayToSort, nofBuckets, bucket);
			tasks.add(bucketSortTask);
		}

		return tasks;
	}

	private void prepareAndFillBucket() {
		int maxElementToSort = getMaxIntFromArray(arrayToSort);

		bucket = new int[arrayToSort.length];

		int bucketRangeStart = bucketToExamine * (int) Math.ceil((double) maxElementToSort / nofBuckets);
		int bucketRangeEnd = (bucketToExamine + 1) * (int) Math.ceil((double) maxElementToSort / nofBuckets);
		if (bucketToExamine + 1 == nofBuckets) {
			bucketRangeEnd++;
		}

		int bucketElementCount = 0;

		for (int elementToSort : arrayToSort) {
			if (elementToSort >= bucketRangeStart && elementToSort < bucketRangeEnd) {
				bucket[bucketElementCount] = elementToSort;
			} else {
				bucket[bucketElementCount] = -1;
			}

			bucketElementCount++;
		}
	}

	int getMaxIntFromArray(final int[] array) {
		int max = array[0];
		for (int l : array) {
			if (max < l) {
				max = l;
			}
		}

		return max;
	}

}
