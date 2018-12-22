package com.utilitybelt.algorithmics;

import java.util.Arrays;
import java.util.Comparator;

public class Sort {

	// *******************************************************
	// Merge-Sort
	// *******************************************************

	public static void mergeSort(int[] array) {
		sort(array, 0, array.length - 1);
	}

	static void sort(int arr[], int l, int r) {
		if (l < r) {
			int m = (l + r) / 2;
			sort(arr, l, m);
			sort(arr, m + 1, r);
			merge(arr, l, m, r);
		}
	}

	private static void merge(int arr[], int l, int m, int r) {
		int n1 = m - l + 1, n2 = r - m;
		int[] left = Arrays.copyOfRange(arr, l, l + n1);
		int[] right = Arrays.copyOfRange(arr, m + 1, m + 1 + n2);

		int i = 0, j = 0, k = l;
		while (i < n1 && j < n2) {
			if (left[i] <= right[j]) {
				arr[k] = left[i];
				i++;
			} else {
				arr[k] = right[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			arr[k] = left[i];
			i++;
			k++;
		}

		while (j < n2) {
			arr[k] = right[j];
			j++;
			k++;
		}
	}

	public static void mergeSort(float[] array) {
		sort(array, 0, array.length - 1);
	}

	static void sort(float arr[], int l, int r) {
		if (l < r) {
			int m = (l + r) / 2;
			sort(arr, l, m);
			sort(arr, m + 1, r);
			merge(arr, l, m, r);
		}
	}

	private static void merge(float arr[], int l, int m, int r) {
		int n1 = m - l + 1, n2 = r - m;
		float[] left = Arrays.copyOfRange(arr, l, l + n1);
		float[] right = Arrays.copyOfRange(arr, m + 1, m + 1 + n2);

		int i = 0, j = 0, k = l;
		while (i < n1 && j < n2) {
			if (left[i] <= right[j]) {
				arr[k] = left[i];
				i++;
			} else {
				arr[k] = right[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			arr[k] = left[i];
			i++;
			k++;
		}

		while (j < n2) {
			arr[k] = right[j];
			j++;
			k++;
		}
	}

	public static void mergeSort(double[] array) {
		sort(array, 0, array.length - 1);
	}

	static void sort(double arr[], int l, int r) {
		if (l < r) {
			int m = (l + r) / 2;
			sort(arr, l, m);
			sort(arr, m + 1, r);
			merge(arr, l, m, r);
		}
	}

	private static void merge(double arr[], int l, int m, int r) {
		int n1 = m - l + 1, n2 = r - m;
		double[] left = Arrays.copyOfRange(arr, l, l + n1);
		double[] right = Arrays.copyOfRange(arr, m + 1, m + 1 + n2);

		int i = 0, j = 0, k = l;
		while (i < n1 && j < n2) {
			if (left[i] <= right[j]) {
				arr[k] = left[i];
				i++;
			} else {
				arr[k] = right[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			arr[k] = left[i];
			i++;
			k++;
		}

		while (j < n2) {
			arr[k] = right[j];
			j++;
			k++;
		}
	}

	public static void mergeSort(short[] array) {
		sort(array, 0, array.length - 1);
	}

	static void sort(short arr[], int l, int r) {
		if (l < r) {
			int m = (l + r) / 2;
			sort(arr, l, m);
			sort(arr, m + 1, r);
			merge(arr, l, m, r);
		}
	}

	private static void merge(short arr[], int l, int m, int r) {
		int n1 = m - l + 1, n2 = r - m;
		short[] left = Arrays.copyOfRange(arr, l, l + n1);
		short[] right = Arrays.copyOfRange(arr, m + 1, m + 1 + n2);

		int i = 0, j = 0, k = l;
		while (i < n1 && j < n2) {
			if (left[i] <= right[j]) {
				arr[k] = left[i];
				i++;
			} else {
				arr[k] = right[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			arr[k] = left[i];
			i++;
			k++;
		}

		while (j < n2) {
			arr[k] = right[j];
			j++;
			k++;
		}
	}

	public static void mergeSort(long[] array) {
		sort(array, 0, array.length - 1);
	}

	static void sort(long arr[], int l, int r) {
		if (l < r) {
			int m = (l + r) / 2;
			sort(arr, l, m);
			sort(arr, m + 1, r);
			merge(arr, l, m, r);
		}
	}

	private static void merge(long arr[], int l, int m, int r) {
		int n1 = m - l + 1, n2 = r - m;
		long[] left = Arrays.copyOfRange(arr, l, l + n1);
		long[] right = Arrays.copyOfRange(arr, m + 1, m + 1 + n2);

		int i = 0, j = 0, k = l;
		while (i < n1 && j < n2) {
			if (left[i] <= right[j]) {
				arr[k] = left[i];
				i++;
			} else {
				arr[k] = right[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			arr[k] = left[i];
			i++;
			k++;
		}

		while (j < n2) {
			arr[k] = right[j];
			j++;
			k++;
		}
	}
	
	public static <T extends Comparable<T>> void mergeSort(T[] array) {
		sort(array, 0, array.length - 1);
	}

	static <T extends Comparable<T>> void sort(T arr[], int l, int r) {
		if (l < r) {
			int m = (l + r) / 2;
			sort(arr, l, m);
			sort(arr, m + 1, r);
			merge(arr, l, m, r);
		}
	}

	private static <T extends Comparable<T>>  void merge(T arr[], int l, int m, int r) {
		int n1 = m - l + 1, n2 = r - m;
		T[] left = Arrays.copyOfRange(arr, l, l + n1);
		T[] right = Arrays.copyOfRange(arr, m + 1, m + 1 + n2);

		int i = 0, j = 0, k = l;
		while (i < n1 && j < n2) {
			if (left[i].compareTo(right[j]) <= 0) {
				arr[k] = left[i];
				i++;
			} else {
				arr[k] = right[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			arr[k] = left[i];
			i++;
			k++;
		}

		while (j < n2) {
			arr[k] = right[j];
			j++;
			k++;
		}
	}
	
	public static <T> void mergeSort(T[] array, Comparator<T> comperator) {
		sort(array, 0, array.length - 1, comperator);
	}

	static <T> void sort(T arr[], int l, int r, Comparator<T> comperator) {
		if (l < r) {
			int m = (l + r) / 2;
			sort(arr, l, m, comperator);
			sort(arr, m + 1, r, comperator);
			merge(arr, l, m, r, comperator);
		}
	}

	private static <T>  void merge(T arr[], int l, int m, int r, Comparator<T> comperator) {
		int n1 = m - l + 1, n2 = r - m;
		T[] left = Arrays.copyOfRange(arr, l, l + n1);
		T[] right = Arrays.copyOfRange(arr, m + 1, m + 1 + n2);

		int i = 0, j = 0, k = l;
		while (i < n1 && j < n2) {
			if (comperator.compare(left[i], right[j]) <= 0) {
				arr[k] = left[i];
				i++;
			} else {
				arr[k] = right[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			arr[k] = left[i];
			i++;
			k++;
		}

		while (j < n2) {
			arr[k] = right[j];
			j++;
			k++;
		}
	}

	
	// *******************************************************
	// Quick-Sort
	// *******************************************************

	public static void quickSort(int[] array) {

	}

	public static void quickSort(float[] array) {

	}

	public static void quickSort(double[] array) {

	}

	public static void quickSort(short[] array) {

	}

	public static void quickSort(long[] array) {

	}

	public static <T extends Comparable<?>> void quickSort(T[] array) {

	}

	public static <T> void quickSort(T[] array, Comparator<T> comperator) {

	}

	// *******************************************************
	// Insertion-Sort
	// *******************************************************

	/**
	 * Sorting an array of integers according to the <i>Insertion-Sort
	 * algorithm</i> after calling this function the given array will be sorted
	 * in ascending order
	 * 
	 * @param array
	 *            - int array to be sorted
	 */
	public static void insertionSort(int[] array) {
		if (array.length <= 1)
			return;
		int size = array.length;
		int key;
		for (int i = 1; i < size; i++) {
			key = array[i];
			int j = i - 1;
			while (j >= 0 && key < array[j]) {
				array[j + 1] = array[j];
				j -= 1;
			}
			array[j + 1] = key;
		}
	}

	/**
	 * Sorting an array of floats according to the <i>Insertion-Sort
	 * algorithm</i> after calling this function the given array will be sorted
	 * in ascending order
	 * 
	 * @param array
	 *            - float array to be sorted
	 */
	public static void insertionSort(float[] array) {
		if (array.length <= 1)
			return;
		int size = array.length;
		float key;
		for (int i = 1; i < size; i++) {
			key = array[i];
			int j = i - 1;
			while (j >= 0 && key < array[j]) {
				array[j + 1] = array[j];
				j -= 1;
			}
			array[j + 1] = key;
		}
	}

	/**
	 * Sorting an array of doubles according to the <i>Insertion-Sort
	 * algorithm</i> after calling this function the given array will be sorted
	 * in ascending order
	 * 
	 * @param array
	 *            - double array to be sorted
	 */
	public static void insertionSort(double[] array) {
		if (array.length <= 1)
			return;
		int size = array.length;
		double key;
		for (int i = 1; i < size; i++) {
			key = array[i];
			int j = i - 1;
			while (j >= 0 && key < array[j]) {
				array[j + 1] = array[j];
				j -= 1;
			}
			array[j + 1] = key;
		}
	}

	/**
	 * Sorting an array of short according to the <i>Insertion-Sort
	 * algorithm</i> after calling this function the given array will be sorted
	 * in ascending order
	 * 
	 * @param array
	 *            - short array to be sorted
	 */
	public static void insertionSort(short[] array) {
		if (array.length <= 1)
			return;
		int size = array.length;
		short key;
		for (int i = 1; i < size; i++) {
			key = array[i];
			int j = i - 1;
			while ((j >= 0) && (key < array[j])) {
				array[j + 1] = array[j];
				j -= 1;
			}
			array[j + 1] = key;
		}
	}

	/**
	 * Sorting an array of longs according to the <i>Insertion-Sort
	 * algorithm</i> after calling this function the given array will be sorted
	 * in ascending order
	 * 
	 * @param array
	 *            - long array to be sorted
	 */
	public static void insertionSort(long[] array) {
		if (array.length <= 1)
			return;
		int size = array.length;
		long key;
		for (int i = 1; i < size; i++) {
			key = array[i];
			int j = i - 1;
			while (j >= 0 && key < array[j]) {
				array[j + 1] = array[j];
				j -= 1;
			}
			array[j + 1] = key;
		}
	}

	/**
	 * Sorting an array of Comparables according to the <i>Insertion-Sort
	 * algorithm</i> after calling this function the given array will be sorted
	 * in ascending order
	 * 
	 * @param array
	 *            - int array to be sorted
	 */
	public static <T extends Comparable<T>> void insertionSort(T[] array) {
		if (array.length <= 1)
			return;
		int size = array.length;
		T key;
		for (int i = 1; i < size; i++) {
			key = array[i];
			int j = i - 1;
			while (j >= 0 && key.compareTo(array[j]) == -1) {
				array[j + 1] = array[j];
				j -= 1;
			}
			array[j + 1] = key;
		}
	}

	/**
	 * Sorting an array of integers according to the <i>Insertion-Sort
	 * algorithm</i> after calling this function the given array will be sorted
	 * in ascending order
	 * 
	 * @param array
	 *            - int array to be sorted
	 */
	public static <T> void insertionSort(T[] array, Comparator<T> comperator) {
		if (array.length <= 1)
			return;
		int size = array.length;
		T key;
		for (int i = 1; i < size; i++) {
			key = array[i];
			int j = i - 1;
			while (j >= 0 && comperator.compare(key, array[j]) == -1) {
				array[j + 1] = array[j];
				j -= 1;
			}
			array[j + 1] = key;
		}
	}
}
