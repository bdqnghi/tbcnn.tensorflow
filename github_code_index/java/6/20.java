
public class Sort_MergeSort {
	public static void main(String[] args) {
		int arr[] = {12, 11, 13, 5, 6, 7};
		mergesort(arr);
	}
	
	//O(nlogn) in avg and worst case
	public static void mergesort(int[] array) {
		int[] helper = new int[array.length];
		sort(array, helper, 0, array.length -1);
	}
	
	public static void sort(int[] array, int[] helper, int low, int high) {
		if(low < high) {
			int middle = (low + high) / 2;
			sort(array, helper, low, middle); //sort left
			sort(array, helper, middle+1, high); //sort right
			merge(array, helper, low, middle, high); //merge
		}
	}
	
	public static void merge(int[] array, int[] helper, int low, int middle, int high) {
		//copy both halves into a helper array
		for(int i = low; i <= high; i++) {
			helper[i] = array[i];
			System.out.println(helper[i]);
		}
		
		int helperLeft = low;
		int helperRight = middle+1;
		int current = low;
		
		//Iterate through the helper array.
		//Compared the left and right half, copying back the smaller 
		//element from the two halves into the original array.
		while(helperLeft <= middle && helperRight <= high) {
			if(helper[helperLeft] <= helper[helperRight]) {
				array[current] = helper[helperLeft];
				helperLeft++;
			}
			else {
				array[current] = helper[helperRight];
				helperRight++;
			}
			current++;
		}
		
		//copy rest of the left side of the array into the target array
		int remaining = middle - helperLeft;
		for(int i = 0; i <= remaining; i++) {
			array[current + i] = helper[helperLeft + i];
		}
	}
}
