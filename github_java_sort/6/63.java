class RadixSort {
	public static int getMax(int[] nums) {
		int max = 0;
		for (int num : nums) {
			max = Math.max(max, num);
		}
		return max;
	}

	public static void printArray(int[] nums) {
		for (int num : nums) {
			System.out.print(num + " ");
		}
		System.out.println();
	}

	public static void countSort(int[] nums, int exponent) {
		int n = nums.length;
		int[] output = new int[n];
		int[] count = new int[10];

		for (int i = 0; i < n; i++) {
			count[(nums[i]/exponent) % 10]++;
		}

		for (int i = 1; i < 10; i++) {
			count[i] += count[i-1];
		}

		for (int i = n - 1; i >= 0; i--) {
			output[count[ (nums[i]/exponent) % 10] - 1] = nums[i];
			count[(nums[i]/exponent) % 10]--;
		}

		for (int i = 0; i < n; i++) {
			nums[i] = output[i];
		}
	}

	public static void radixSort(int[] nums) {
		int max = getMax(nums);
		for (int exponent = 1; max / exponent > 0; exponent *= 10) {
			countSort(nums, exponent);
		}
	}

	public static void main(String args[]) {
		int[] nums = {170, 45, 75, 90, 802, 24, 2, 66};
		radixSort(nums);
		printArray(nums);
	}
}