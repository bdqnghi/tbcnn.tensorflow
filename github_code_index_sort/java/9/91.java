package com.algo.sorting;

public class SelectionSortJava {

	static int intmin = Integer.MAX_VALUE;

	public static void print(int numbers[]) {
		for (int i = 0; i < numbers.length - 1; i++) {
			System.out.print(numbers[i] + " ");
		}
	}

	public static int[] swap(int numbers[], int i, int j) {
		int temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
		return numbers;
	}

	public static int[] sort(int numbers[]) {
		int currentMin = intmin;
		int currentindex = -1;
		for (int i = 0; i < numbers.length - 1; i++) {
			for (int j = i; j < numbers.length; j++) {
				if (numbers[j] < currentMin) {
					currentMin = numbers[j];
					currentindex = j;
				}
			}
			numbers = swap(numbers, i, currentindex);
			currentindex = -1;
			currentMin = intmin;
		}
		return numbers;
	}

	public static void main(String[] args) {
		int numbers[] = new int[] { 24, 67, 89, 24, 5, 7, 456, 789, 34, 98, -1 };
		int num[] = sort(numbers);
		print(num);
	}
}
