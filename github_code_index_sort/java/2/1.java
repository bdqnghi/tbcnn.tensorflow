package dennis.learning.sort;

import java.util.Arrays;

public class MergeSort {
	public static void main(String args[]) {
		MergeSort mergeSort = new MergeSort();
		Integer[] arrayToSort = { 0, 5, 1, 2, 4, 3, 9, 8, 6, 7, 2 };
		mergeSort.mergeSort(arrayToSort, 0, arrayToSort.length);
		System.out.println(Arrays.asList(arrayToSort));
		arrayToSort = new Integer[] {0,1,2,3,4,6,7,8,9};
		mergeSort.mergeSort(arrayToSort, 0, arrayToSort.length);
		System.out.println(Arrays.asList(arrayToSort));
		arrayToSort = new Integer[] {9,8,7,6,5,4,3,2,1,0};
		mergeSort.mergeSort(arrayToSort, 0, arrayToSort.length);
		System.out.println(Arrays.asList(arrayToSort));
	}

	public void mergeSort(Integer[] arrayToSort, int low, int high) {
		if (high - low <= 1) {
			return;
		}
		int mid = low + (high - low) / 2;
		Integer[] part = new Integer[high - low];
		mergeSort(arrayToSort, low, mid);
		mergeSort(arrayToSort, mid, high);
		merge(arrayToSort, low, mid, high, part);
		
	}
	public Integer[] merge(Integer[] arrayToSort, int low, int mid, int high, Integer[] part) {
		int first = low;
		int second = mid;
		int mergeIndex = 0;
		while (first < mid && second < high) {
			if (arrayToSort[first] <= arrayToSort[second])
			{
				part[mergeIndex] = arrayToSort[first];
				first++;
			} else {
				part[mergeIndex] = arrayToSort[second];
				second++;
			}
			mergeIndex++;
		}
		//Add remaining elements
		while (first < mid) {
			part[mergeIndex] = arrayToSort[first];
			first++;
			mergeIndex++;
		}
		while (second < high) {
			part[mergeIndex] = arrayToSort[second];
			second++;
			mergeIndex++;
		}
		//Replace elements in existing array
		mergeIndex = 0;
		for (int count = low; count < high; count++)
		{
			arrayToSort[count] = part[mergeIndex];
			mergeIndex++;
		}
		return part;
	}
}
