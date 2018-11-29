
public class Sort_QuickSort {
	public static void main(String[] args) {
		int arr[] = {12, 11, 13, 5, 6, 7};
		quickSort(arr, 0, arr.length-1);
		
		for(int i = 0; i < arr.length; i++)
			System.out.println(arr[i]);
	}
	
	//O(nlogn) avg and O(n^2) worst
	public static void quickSort(int[] arr, int left, int right) {
		if(left < right) {
			int index = partition(arr, left, right);
			
			quickSort(arr, left, index - 1);
			quickSort(arr, index + 1, right);
		}
	}
	
	public static int partition(int[] arr, int left, int right) {
		int pivot = arr[(left + right) / 2];
		
		while(left <= right) {
			//find element on left that should be on the right
			while(arr[left] < pivot) {
				left++;
			}
			
			//find element on right that should be on the left
			while(arr[right] > pivot) {
				right--;
			}
			
			//swap elements and move left and right indices
			if(left <= right) {
				int temp = arr[left];
				arr[left] = arr[right];
				arr[right] = temp;

				left++;
				right--;;
			}
		}
		
		return left;
	}
}
