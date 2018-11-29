package _SortingAndSeaechingAlgorithms;

import java.util.Arrays;

public class QuickSortJava {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		int[] arr = {3, 44, 38, 5, 47, 15, 3, 36, 26, 27, 2, 46, 4, 19, 50, 48, 50};
		System.out.println(Arrays.toString(arr));
		
		int low = 0;
		int high = arr.length -1;
		
		quickSort(arr, low, high);
		
		System.out.println(Arrays.toString(arr));
		

	}

	public static void quickSort(int[] arr, int low, int high) {
		// TODO Auto-generated method stub
		
		if(arr == null || arr.length == 0){
			return;
		}
		
		if(low > high){
			return;
		}
		
		//make pivot
		
		int middle = low +(high - low)/ 2;
		int pivot = arr[middle];
		
		//make Left <pivot and Right > pivot
		
		int i = low;
		int j = high;
		
		while(i <= j){
			
			while(arr[i] < pivot){
				i++;
			}
			
			while(arr[j] > pivot){
				j--;
			}
			
			if(i <= j){
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				i++;
				j--;
			}
		}
		
		if(low < j){
			quickSort(arr, low, j);
		}
		
		if(high > i){
			quickSort(arr, i, high);
		}
		
	}

}
