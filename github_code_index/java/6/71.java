import java.util.Arrays;

/*
	pseudocode:

	Merge-Sort(A, p, r)
		if p < r
			q = (p + r) / 2
			Merge-Sort(A, p, q)
			Merge-Sort(A, q + 1, r)
			Merge(A, p, q, r)

	Note: Use a helper array to copy the array ahead, reuse the space

	Time complexity: T(n) = 2T(n/2) + O(n) -> O(nlogn)
		Divide: O(i) each time, n division in total -> O(n)
		Merge: O(n) each time, log(n) merge in total -> O(nlogn)
	Space complexity: O(n) copy array
					  O(logn) call stack

	Merge Sort is available for external sort: sort each chunk that fits in RAM, and merge chunks together
	
*/

public class MergeSort {
	public static void main(String[] args) {
		int[] A = null;
		MergeSort.mergeSort(A);
		System.out.println(Arrays.toString(A));

		A = new int[]{1,2,3,4,5};
		MergeSort.mergeSort(A);
		System.out.println(Arrays.toString(A));

		A = new int[]{5,4,3,2,1};
		MergeSort.mergeSort(A);
		System.out.println(Arrays.toString(A));

		A = new int[]{5,3,4,7,2,1,6};
		MergeSort.mergeSort(A);
		System.out.println(Arrays.toString(A));
	}
	public static void mergeSort(int[] A) {
		if (A == null || A.length == 0) {
			return;
		}
		int[] helper = Arrays.copyOf(A, A.length);
		divideAndMerge(A, 0, A.length - 1, helper);
	}
	public static void divideAndMerge(int[] A, int l, int r, int[] helper) {
		if (l >= r) {
			return;
		}
		int mid = (l + r) / 2;
		divideAndMerge(A, l, mid, helper);
		divideAndMerge(A, mid + 1, r, helper);
		merge(A, l, mid, r, helper);
	}
	public static void merge(int[] A, int l, int mid, int r, int[] helper) {
		int ind1 = l, ind2 = mid + 1, ind = l;
		while (ind1 <= mid && ind2 <= r) {
			if (helper[ind1] < helper[ind2]) {
				A[ind++] = helper[ind1++];
			} else {
				A[ind++] = helper[ind2++];
			}
		}
		while (ind1 <= mid) {
			A[ind++] = helper[ind1++];
		}
		for (int i = l; i <= r; i++) {
			helper[i] = A[i];
		}
	}
}