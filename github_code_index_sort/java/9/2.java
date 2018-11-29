package aGettingStarted_school;

//Lesson ->https://www.geeksforgeeks.org/selection-sort/
//https://practice.geeksforgeeks.org/problems/selection-sort/1

//6:17 PM 4/10/2018
//7:39 PM 4/10/2018

import java.util.Scanner;

public class GFG_4_SelectionSort {
	void selectionSort(int arr[]) {

		int n = arr.length;
		GfG obj = new GfG();
		for (int i = n - 1; i >= 0; i--) {
			int j = obj.select(arr, i);
			// and place it at beginning
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	void printArray(int arr[]) {
		int n = arr.length;
		for (int i = 0; i < n; i++)
			System.out.print(arr[i] + " ");
		System.out.println();
	}

	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		GFG_4_SelectionSort ss = new GFG_4_SelectionSort();
		System.out.println("Input");
		int t = sc.nextInt();
		while (t > 0) {
			int n = sc.nextInt();
			int arr[] = new int[n];
			for (int i = 0; i < n; i++) {
				arr[i] = sc.nextInt();
			}

			// GfG obj = new GfG();
			ss.selectionSort(arr);

			ss.printArray(arr);
			t--;
		}

	}
}
//(Function Problem)
class GfG {

	// Find the max element in arr and return it's index
	int select(int arr[], int i) {
		// Your code here
		int index_of_max;
		index_of_max = i;
		//linear search
		for (int j = 0; j <= i; j++) {
			if (arr[j] > arr[index_of_max]) {
				index_of_max = j;
			}
		}
		return index_of_max;
	}
}
