package sorting;

public class QuickSort {

	public static class QuickSortPartitionLast {
		public int[] quickSort(int[] nums) {
			quickSort(nums, 0, nums.length - 1);
			return nums;
		}

		private void quickSort(int[] nums, int low, int high) {
			if (low < high) {
				int pi = partitionLast(nums, low, high);
				quickSort(nums, low, pi - 1);
				quickSort(nums, pi + 1, high);
			}

		}

		private int partitionLast(int[] nums, int low, int high) {
			int pivot = nums[high];
			int i = (low - 1);
			for (int j = low; j <= high - 1; j++) {
				if (nums[j] <= pivot) {
					i++;
					//swap nums[i] and nums[j]
					int temp = nums[i];
					nums[i] = nums[j];
					nums[j] = temp;
				}
			}

			//swap nums[i+1] and nums[high]
			int temp = nums[i + 1];
			nums[i + 1] = nums[high];
			nums[high] = temp;

			return i + 1;
		}
	}

	public static class QuickSortPartitionFirst {
		public int[] quickSort(int[] nums) {
			quickSort(nums, 0, nums.length - 1);
			return nums;
		}

		private void quickSort(int[] nums, int low, int high) {
			if (low < high) {
				int pi = partitionFirst(nums, low, high);
				quickSort(nums, low, pi - 1);
				quickSort(nums, pi + 1, high);
			}

		}

		// this method find the pivot and do the sorting
		private int partitionFirst(int[] list, int first, int last) {
			int pivot = list[first];
			int low = first + 1; // searching forward from pivot'next element
			int high = last;// searching from the end for backward
			while (low < high) {
				// forward searching
				while (low <= high && list[low] < pivot)
					low++;
				// backward searching
				while (low <= high && list[high] >= pivot)
					high--;
				// swap two elements in the list when list[high]<pivot
				if (high > low) {
					int temp = list[high];
					list[high] = list[low];
					list[low] = temp;
				}
			}

			while (high > first && list[high] >= pivot)
				high--;
			// swap pivot
			if (pivot > list[high]) {
				list[first] = list[high];
				list[high] = pivot;
				return high;
			} else {
				return first;
			}
		}
	}
	
	public static void main(String... args){
		int[] nums = InsertionSort.generateRandomArray(17);
//		int[] nums = new int[]{10, 7, 8, 9, 1, 5};
		SortUtils.print(nums);
//		test.swap(nums, 2, 0);
//		test.print(nums);
		QuickSort test = new QuickSort();
//		InsertionSort.print(test.quickSort(nums));
//		InsertionSort.print(test.quickSort_20160628(nums));
//		InsertionSort.print(test.quickSort_pivot_first_20160628(nums));
		SortUtils.print(test.quickSort_pivot_median_20160628(nums));
		
		
	}
	
	int[] quickSort_20160628(int[] nums){
		quickSort_20160628(nums, 0, nums.length-1);
		return nums;
	}

	void quickSort_20160628(int[] nums, int low, int high) {
		if(low < high){
			int pi = partition_20160628(nums, low, high);
			quickSort_20160628(nums, low, pi-1);
			quickSort_20160628(nums, pi+1, high);
		}
	}

	int partition_20160628(int[] nums, int low, int high) {
		int pivot = nums[high];
		int i = low-1;
		for(int j = low; j <= high-1; j++){
			if(nums[j] <= pivot){
				i++;
				
				int temp = nums[i];
				nums[i] = nums[j];
				nums[j] = temp;
			}
		}
		
		int temp = nums[i+1];
		nums[i+1] = nums[high];
		nums[high] = temp;
		return i+1;
	}
	
	//This below method is also accepted on http://www.practice.geeksforgeeks.org/problem-page.php?pid=700151
	int[] quickSort_pivot_first_20160628(int[] nums){
		quickSort_pivot_first_20160628(nums, 0, nums.length-1);
		return nums;
	}

	private void quickSort_pivot_first_20160628(int[] nums, int low, int high) {
		if (low < high) {
			int pi = partition_pivot_first_20160628(nums, low, high);
			quickSort_pivot_first_20160628(nums, low, pi - 1);
			quickSort_pivot_first_20160628(nums, pi + 1, high);
		}
	}

	private int partition_pivot_first_20160628(int[] nums, int low, int high) {
		int pivot = nums[low];
		int i = high+1;
		for(int j = high; j > low; j--){
			if(nums[j] > pivot){
				i--;
				
				int temp = nums[j];
				nums[j] = nums[i];
				nums[i] = temp;
			}
		}
		
		int temp = nums[low];
		nums[low] = nums[i-1];
		nums[i-1] = temp;
		
		return i-1;
	}
	
	int[] quickSort_pivot_median_20160628(int[] nums){
		quickSort_pivot_median_20160628(nums, 0, nums.length-1);
		return nums;
	}

	void quickSort_pivot_median_20160628(int[] nums, int low, int high) {
		if(nums == null || nums.length == 0) return ;
		if(low >= high) return;
		
		int i = low, j = high, mid = (low+high)/2, pivot = nums[mid];
		
		while(i <= j){
			while(nums[i] < pivot) i++;
			while(nums[j] > pivot) j--;
			if(i <= j){
				int temp = nums[i];
				nums[i] = nums[j];
				nums[j] = temp;
				i++;
				j--;
			}
		}
		
		if(low < j) quickSort_pivot_median_20160628(nums, low, j);
		if(i < high) quickSort_pivot_median_20160628(nums, i, high);
	}

}
