/*
The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) 
from unsorted part and putting it at the beginning.Refer http://geeksquiz.com/selection-sort
Time Complexity: O(n*n) as there are two nested loops.
Auxiliary Space: O(1)
The good thing about selection sort is it never makes more than O(n) swaps and can be useful when memory write is a costly operation.
*/
import java.util.*;

public class SelectionSort{
	public static void main(String[] args) {
		int[] arr = {64,25,12,22,11,45,32};
		System.out.println("Before sorting array is: "+ Arrays.toString(arr));
		selectionSort(arr,arr.length);
		System.out.println("After sorting array is: "+ Arrays.toString(arr));
	}

	public static void selectionSort(int[] a,int n){
		// One by one move boundary of unsorted subarray
		for (int i=0;i<n-1;i++) {
			
			// Find the minimum element in unsorted array
			int min = i;
			for (int j=i+1;j<n;j++) {
				if(a[j]<a[min])
					min = j;
			}

			//swap the found minimum element with the element at current position
			int temp = a[min];
			a[min] = a[i];
			a[i] = temp;
		}
	}
}