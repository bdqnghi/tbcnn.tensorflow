package Array;


public class FirstMissingPositive {
	public int firstMissingPositive(int[] A) {
		int n = A.length;
		for (int i = 0; i < n; i++) {
			
			while (A[i] != i) {
				
				if (A[i] < 0 || A[i] >= n)
					break;
	 
				
				if(A[i]==A[A[i]])
	                    		break;
				
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
