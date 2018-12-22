package com.carmatech.algo.sorting;

import static com.carmatech.algo.sorting.SortingUtilities.less;
import static com.carmatech.algo.sorting.SortingUtilities.shuffle;
import static com.carmatech.algo.sorting.SortingUtilities.sink;
import static com.carmatech.algo.sorting.SortingUtilities.swap;

public final class Sorting {
	private Sorting() {
		// Pure utility class, do NOT instantiate.
	}

	/**
	 * Selection sort has a time complexity of O(n^2), and a space complexity of 4 x sizeof(int). It sorts the provided array "in-place".
	 * 
	 * @param array
	 *            Array to sort.
	 */
	public static <T extends Comparable<T>> void selectionSort(final T[] array) {
		final int length = array.length;
		for (int i = 0; i < length; i++) {
			int min = i;
			for (int j = i + 1; j < length; j++)
				if (less(array[j], array[min]))
					min = j;
			swap(array, i, min);
		}
	}

	/**
	 * Insertion sort has a time complexity of O(n^2) in the worst case (sorted in the reverse order), O(n) in the best case (already sorted), and a space
	 * complexity of 3 x sizeof(int). It sorts the provided array "in-place".
	 * 
	 * @param array
	 *            Array to sort.
	 */
	public static <T extends Comparable<T>> void insertionSort(final T[] array) {
		final int length = array.length;
		for (int i = 0; i < length; i++)
			for (int j = i; j > 0; j--)
				if (less(array[j], array[j - 1]))
					swap(array, j, j - 1);
				else
					break;
	}

	/**
	 * Shell-sort using x => 3x+1 h-sort function.
	 * 
	 * @param array
	 *            Array to sort.
	 */
	public static <T extends Comparable<T>> void shellSort(final T[] array) {
		final int length = array.length;

		// Find largest h to sort with lowest granularity first.
		// Typical sequence for h is: 1, 4, 13, 40, 121, etc.
		int h = 1;
		while (h < (length / 3))
			h = 3 * h + 1;

		while (h >= 1) {
			// h-insertion sort:
			for (int i = h; i < length; i++)
				for (int j = i; j >= h; j -= h)
					if (less(array[j], array[j - h]))
						swap(array, j, j - h);
					else
						break;
			h = h / 3;
		}
	}

	public static <T extends Comparable<T>> void mergeSort(final T[] array) {
		@SuppressWarnings("unchecked")
		final T[] tempArray = (T[]) new Comparable<?>[array.length];
		doSort(tempArray, array, 0, array.length - 1);
	}

	private static <T extends Comparable<T>> void doSort(final T[] tempArray, final T[] array, final int lo, final int hi) {
		if (hi <= lo)
			return;
		final int mid = lo + (hi - lo) / 2;
		doSort(tempArray, array, lo, mid);
		doSort(tempArray, array, mid + 1, hi);
		merge(tempArray, array, lo, mid, hi);
	}

	private static <T extends Comparable<T>> void merge(final T[] tempArray, final T[] array, final int lo, final int mid, final int hi) {
        System.arraycopy(array, lo, tempArray, lo, hi - lo + 1);

		// Merge two sub-arrays while keeping all elements sorted:
		int i = lo;
		int j = mid + 1;
		for (int k = lo; k <= hi; k++) {
			if (i > mid)                               array[k] = tempArray[j++];
			else if (j > hi)                           array[k] = tempArray[i++];
			else if (less(tempArray[j], tempArray[i])) array[k] = tempArray[j++];
			else                                       array[k] = tempArray[i++];
		}
	}

	public static <T extends Comparable<T>> void quickSort(final T[] array) {
		shuffle(array);
		quickSort(array, 0, array.length - 1);
	}

	private static <T extends Comparable<T>> void quickSort(final T[] array, final int lo, final int hi) {
		if (hi <= lo)
			return;
		final int pivot = partition(array, lo, hi);
		quickSort(array, lo, pivot - 1);
		quickSort(array, pivot + 1, hi);
	}

	private static <T extends Comparable<T>> int partition(final T[] array, final int lo, final int hi) {
		int i = lo + 1;
		int j = hi;
		while (true) {
			while (less(array[i], array[lo]) && i < hi)
				++i;
			while (less(array[lo], array[j]) && j > lo)
				--j;
			if (!(i < j))
				break;
			swap(array, i, j);
		}
		swap(array, lo, j);
		return j;
	}

	public static <T extends Comparable<T>> void heapSort(final T[] array) {
		int length = array.length;

		// Build heap using bottom-up method:
		for (int k = length / 2; k >= 1; --k)
			sink(array, k, length);

		// Sort down:
		while (length > 1) {
			swap(array, 0, length - 1);
			sink(array, 1, --length);
		}
	}
}
