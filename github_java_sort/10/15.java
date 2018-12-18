package homework10;

import java.util.Arrays;

public class BucketSort {

	public static void sort(int[] arr) {
		int maxVal = getMaxVal(arr);
		int[] bucket = new int[maxVal + 1];

		for (int i = 0; i < bucket.length; i++) {
			bucket[i] = 0;
		}

		for (int i = 0; i < arr.length; i++) {
			bucket[arr[i]]++;
		}

		int outPos = 0;
		for (int i = 0; i < bucket.length; i++) {
			for (int j = 0; j < bucket[i]; j++) {
				arr[outPos++] = i;
			}
		}
	}

	private static int getMaxVal(int[] arr) {
		int maxVal = arr[0];
		for (int i = 1; i < arr.length; i++) {
			if (arr[i] > maxVal) {
				maxVal += arr[i];
			}
		}
		return maxVal;
	}
	
	public static void main(String[] args) {
		int[] arr = { 10, 25, 31, 25, 44, 25, 26, 0, 10, 1, 25 };

		System.out.println("Before: " + Arrays.toString(arr));
		sort(arr);
		System.out.println("After:  " + Arrays.toString(arr));
	}

}
