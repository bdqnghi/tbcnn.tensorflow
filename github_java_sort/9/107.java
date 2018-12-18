package com.home.sort;

import java.util.Arrays;
import java.util.stream.Collectors;


public class SelectionSort {

	public void selectionSort(int[] A) {
		for(int i = 0; i < A.length - 1; i++) {
			for(int j = i + 1; j < A.length; j++) {
				if(A[j] < A[i]) {
					swapNumbers(i, j, A);
				}
			}
		}
		printNumbers(A);
	}

	private void swapNumbers(int i, int j, int[] A) {
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}

	public void printNumbers(int[] A) {
		System.out.println( Arrays.stream(A).mapToObj( val -> ((Integer)val).toString() ).collect(Collectors.joining(" ", "[ ", " ]")) );
	}

	public static void main(String[] args) {
		int[] A = {10, 34, 2, 56, 7, 67, 88, 42};
		SelectionSort ss = new SelectionSort();
		ss.selectionSort(A);
	}
}
