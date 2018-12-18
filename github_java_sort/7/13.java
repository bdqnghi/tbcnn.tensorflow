package task07;

import java.util.Scanner;

public class ShellSort {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);

		int n;
		int[] arr;

		n = s.nextInt();
		arr = new int[n];
		for (int i = 0; i < n; i++) {
			arr[i] = s.nextInt();
		}

		printArray(arr);
		shellSort(arr);
		printArray(arr);
	}

	public static void shellSort(int[] arr) {
		for (int i = 0; i < arr.length - 1;) {
			if (arr[i] <= arr[i + 1]) {
				i++;
			} else {
				swap(arr, i, i + 1);

				if (i > 0) {
					i--;
				}
			}
		}
	}

	public static void swap(int[] arr, int i, int j) {
		int tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
	}

	public static void printArray(int[] arr) {
		for (int i = 0; i < arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.println();
	}
}
