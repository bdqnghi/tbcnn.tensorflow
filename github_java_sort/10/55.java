package leetcode;


public class FirstMissingPositive {
	public int firstMissingPositive(int[] A) {
		if (A == null || A.length == 0)
			return 1;

		
		int n = A.length;
		for (int i = 0; i < n; i++) {
			while (A[i] != i + 1) {
				if (A[i] <= 0 || A[i] > n || A[i] == (A[A[i] - 1]))
					break;
				
				int temp = A[A[i] - 1];
				A[A[i] - 1] = A[i];
				A[i] = temp; 
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
