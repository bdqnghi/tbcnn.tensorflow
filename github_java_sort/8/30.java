
public class Sort_QuickSort {
	public static void main(String[] args) {
		int arr[] = {12, 11, 13, 5, 6, 7};
		quickSort(arr, 0, arr.length-1);
		
		for(int i = 0; i < arr.length; i++)
			System.out.println(arr[i]);
	}
	
	
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
			
			while(arr[left] < pivot) {
				left++;
			}
			
			
			while(arr[right] > pivot) {
				right--;
			}
			
			
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
