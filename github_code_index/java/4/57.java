package com.aman.sorting;

public class InsertionSort {

	public static void main(String[] args) {
		InsertionSort insertionSort = new InsertionSort();
		int[] input = { 2, 7, 0, 1 };
		insertionSort.insertionSort(input);
		int[] input2 = { 10, 11, 15, 3, 66, 4, 1 };
		insertionSort.insertionSort(input2);
		int[] input3 = { 1, 6, 7, 27, 4, 3, 2 };
		insertionSort.insertionSort(input3);
		int[] input4 = { 10, 25, 8, 2, 1 };
		insertionSort.insertionSort(input4);
		int[] input5 = { 30, 9, 8, 88, 1, 29, 0 };
		insertionSort.insertionSort(input5);
	}

	public void insertionSort(int[] array) {
		int previousIndex;
		int value;
		int i;
		for (i = 0; i < array.length; i++) {
			previousIndex = i - 1;
			value = array[i];
			while ((previousIndex >= 0) && (array[previousIndex] > value)) {
				// need to swap the value
				array[previousIndex + 1] = array[previousIndex];
				previousIndex = previousIndex - 1;
			}
			array[previousIndex + 1] = value;

		}
		System.out
				.println("Printing the sorted Array using the insertion sort");
		for (int j = 0; j < array.length; j++) {
			System.out.print(array[j] + " ");

		}
		System.out.println();
	}
}
