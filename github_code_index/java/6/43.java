package sort;

import java.util.Arrays;
//http://www.java2novice.com/java-sorting-algorithms/merge-sort/
// http://bigocheatsheet.com/
//http://www.java2novice.com/java-sorting-algorithms/merge-sort/
//

/**
 * 
 * Best O(n log(n)), Average O(n log(n)), Worst O(n log(n)),
 * 
 * Space: O(n), we need temp array
 * 
 * 先局部，再整体， 与 quick sort 思想正好相反
 */
public class MergeSort {
	public static void main(String[] args) {
		int[] A = { 9, 2, 4, 7, 3 };
		sort(A);
		System.out.println(Arrays.toString(A));
	}

	public static void sort(int[] A) {
		int[] temp = new int[A.length];
		int start = 0;
		int end = A.length - 1;
		mergeSort(A, start, end, temp);
	}

	private static void mergeSort(int[] A, int start, int end, int[] temp) {
		if (start >= end) {
			return;
		}

		int mid = start + (end - start) / 2;
		mergeSort(A, start, mid, temp);
		mergeSort(A, mid + 1, end, temp);
		merge(A, start, mid, end, temp);
	}

	private static void merge(int[] A, int start, int mid, int end, int[] temp) {

		int left = start;
		int right = mid + 1;

		/**
		 * NOTE: 容易犯错： you can't set k = 0, this start keep changing
		 * 
		 * k is the start point of A's subarray, k并不总是从0开始， 看下面网页的图解的merge部分，
		 * 更容易明白 http://www.java2novice.com/java-sorting-algorithms/merge-sort/
		 */
		int k = start;

		// merge two sorted subarrays in A to temp array
		while (left <= mid && right <= end) {
			if (A[left] < A[right]) {
				temp[k++] = A[left++];
			} else {
				temp[k++] = A[right++];
			}
		}
		while (left <= mid) {
			temp[k++] = A[left++];
		}
		while (right <= end) {
			temp[k++] = A[right++];
		}

		/**
		 * copy temp back to A, k from start to end
		 * 
		 * ！！！ Note： 像这种之用一个变量指针（i.e k）去同时track两个数组， 推荐用for loop
		 * 
		 * 如果要用while loop, 在循环里不可以写成 A[k++] =
		 * temp[k++];，因为只有一个变量指针k,这样会导致k实际被加了2，结果是不对的，可以参照下面的while 循环写法，k拿出来k++;
		 */
		for (k = start; k <= end; k++) {
			A[k] = temp[k];
		}
		// k = start;
		// while (k <= end) {
		// A[k] = temp[k];
		// k++;
		// }
	}
}
