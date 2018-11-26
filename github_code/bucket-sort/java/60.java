package Array;
// https://www.programcreek.com/2014/05/leetcode-first-missing-positive-java/
// bucket-sort like algorithm
public class FirstMissingPositive {
	public int firstMissingPositive(int[] A) {
		int n = A.length;
		for (int i = 0; i < n; i++) {
			// when the ith element is not i
			while (A[i] != i) {
				// no need to swap when ith element is out of range [0,n]
				if (A[i] < 0 || A[i] >= n)
					break;
	 
				//handle duplicate elements
				if(A[i]==A[A[i]])
	                    		break;
				// swap elements
				int temp = A[i];
				A[i] = A[temp];
				A[temp] = temp;
			}
		}
	 
		for (int i = 0; i < n; i++) {
			if (A[i] != i)
				return i;
		}
	 
		return n;
	}
}
