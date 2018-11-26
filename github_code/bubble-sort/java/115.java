package BubbleSort;

import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class Bubble {

	public static void bubbleSort(int[] arr) {
		int length = arr.length;
		int k;

		for (int i = length; i >= 0; i--) {
			for (int j = 0; j < length-1; j++) {
				k = j + 1;

				if (arr[j] > arr[k])
					swap(j, k, arr);
			}
			printArray(arr);
		}
	}

	private static void printArray(int[] arr) {
		for (int i = 0; i < arr.length; i++) {
			System.out.print(arr[i] + ", ");
		}
		System.out.println("\n");
	}

	private static void swap(int j, int k, int[] arr) {
		int temp = arr[j];
		arr[j] = arr[k];
		arr[k] = temp;

	}

	public static void main(String[] args) {
		int arr[] = { 5, 1, 2, 5, 4, 6, 7, 5, 3, 45, 0 };
		bubbleSort(arr);
		
	}

}
