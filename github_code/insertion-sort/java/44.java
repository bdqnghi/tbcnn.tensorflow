package com.bidhutkarki.sort;

/*
 * Idea:
 * Loop over positions in the array, starting with index 1. 
 * Each new position is like the new card handed to you by the dealer, 
 * and you need to insert it into the correct place in the sorted subarray to the left of that position.
 * URL : https://www.khanacademy.org/computing/computer-science/algorithms/insertion-sort/a/insertion-sort
 * 
 * InPlace: YES
 * Stable: Yes
 * Complexity: Worst case: O(n^2) Best Case: O(n), "Almost sorted" case: O(n)
 */
public class InsertionSort implements Sorting {
	
	public static void main(String[] args) {
		new InsertionSort().test();
	}

	@Override
	public void sort(int[] arr) {
		for(int i=1; i<arr.length; i++) {
			int value = arr[i];
			int j;
			for(j=i-1; j>=0 && value < arr[j]; j--) {
					arr[j+1] = arr[j];
			}
			arr[j+1] = value;
		}
		
	}
}
