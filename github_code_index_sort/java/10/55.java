package leetcode;

/**
 * A bucket sort! Traverse the array twice.
 * 
 * O(n) / O(1)
 * 
 * @author yiluo
 *
 */
public class FirstMissingPositive {
	public int firstMissingPositive(int[] A) {
		if (A == null || A.length == 0)
			return 1;

		// bucket sort
		int n = A.length;
		for (int i = 0; i < n; i++) {
			while (A[i] != i + 1) {
				if (A[i] <= 0 || A[i] > n || A[i] == (A[A[i] - 1]))
					break;
				// the swap process is a bucket-sort
				int temp = A[A[i] - 1];
				A[A[i] - 1] = A[i];
				A[i] = temp; // A[i] should be changed later
			}
		}

		for (int i = 0; i < n; i++) {
			if (A[i] != (i + 1))
				return i + 1;
		}
		return n + 1;
	}
	
	public static void main(String args[]) {
		FirstMissingPositive solution = new FirstMissingPositive();
		int[] A = {2, 1};
		System.out.println(solution.firstMissingPositive(A));
	}
}
