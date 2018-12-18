package com.thoughtworks.fjw.bucketsortalternativewithlists;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class BucketSortTask extends RecursiveTask<List<Integer>> {

	private static final long serialVersionUID = 1L;

	private final List<Integer> listToSort;
	private final int nofBuckets;
	private int bucketToExamine = -1;
	private List<Integer> bucket;

	public BucketSortTask(final List<Integer> arrayToSort, final int nofBuckets, final int bucketToExamine) {
		listToSort = arrayToSort;
		this.nofBuckets = nofBuckets;
		this.bucketToExamine = bucketToExamine;
	}

	public BucketSortTask(final List<Integer> arrayToSort, final int nofBuckets) {
		this(arrayToSort, nofBuckets, -1);
	}

	
	@Override
	protected List<Integer> compute() {
		if (bucketToExamine >= 0) {
			
			prepareAndFillBucket();
			Collections.sort(bucket);

			return bucket;
		}

		
		List<BucketSortTask> tasks = createBucketSortTasks();
		for (BucketSortTask task : tasks) {
			task.fork();
		}

		
		List<Integer> merged = new LinkedList<Integer>();
		for (BucketSortTask bucketSortTask : tasks) {
			List<Integer> bucket = bucketSortTask.join();
			for (int element : bucket) {
				if (element != -1) {
					merged.add(element);
				}
			}
		}

		
		return merged;
	}

	List<BucketSortTask> createBucketSortTasks() {
		List<BucketSortTask> tasks = new ArrayList<BucketSortTask>();
		for (int bucket = 0; bucket < nofBuckets; bucket++) {
			BucketSortTask bucketSortTask = new BucketSortTask(listToSort, nofBuckets, bucket);
			tasks.add(bucketSortTask);
		}

		return tasks;
	}

	private void prepareAndFillBucket() {
		int maxElementToSort = Collections.max(listToSort);

		bucket = new LinkedList<Integer>();

		int bucketRangeStart = bucketToExamine * (int) Math.ceil((double) maxElementToSort / nofBuckets);
		int bucketRangeEnd = (bucketToExamine + 1) * (int) Math.ceil((double) maxElementToSort / nofBuckets);
		if (bucketToExamine + 1 == nofBuckets) {
			bucketRangeEnd++;
		}

		for (int elementToSort : listToSort) {
			if (elementToSort >= bucketRangeStart && elementToSort < bucketRangeEnd) {
				bucket.add(elementToSort);
			} else {
				bucket.add(-1);
			}
		}
	}

}
