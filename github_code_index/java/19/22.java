package InterviewBit;

public class ArraysFirstMissingPositiveNumber {
/*	Given an unsorted integer array, find the first missing positive integer.
	Given [1,2,0] return 3,
			[3,4,-1,1] return 2,
			[-8, -7, -6] returns 1
			Your algorithm should run in O(n) time and use constant space.
			http://n00tc0d3r.blogspot.com/2013/03/find-first-missing-positive.html
			https://www.interviewbit.com/problems/first-missing-integer/
*/	public static void main(String[] args) {
		int[] arr = {3,4,-1,1};
		//System.out.println(firstMissingPositive(arr));
		System.out.println(firstMissingPositiveInt(arr));
	}
	
	 public static int firstMissingPositive(int[] A) {  
		   // in-place swap (bucket sort)  
		   int i = 0;  
		   while (i < A.length) {  
		     if (A[i] > 0 && A[i] <= A.length && A[i] != i+1 && A[i] != A[A[i]-1]) {
		       int temp = A[A[i]-1];  
		       A[A[i]-1] = A[i];  
		       A[i] = temp;  
		     } else {  
		       ++i;  
		     }  
		   }  
		   for(Integer k : A){
			   System.out.print(k+ " ");
		   }
		   // find the first positive missing integer  
		   i = 0;  
		   while (i < A.length && A[i] == i+1) 
			   ++i;  
		   return i+1;  
		 }
	 //http://www.programcreek.com/2014/05/leetcode-first-missing-positive-java/
/*	 Your algorithm should run in O(n) time and uses constant space.
	 Analysis
	 This problem can solve by using a bucket-sort like algorithm.
	 Let's consider finding first missing positive and 0 first.
	 The key fact is that the ith element should be i, so we have:
	 i==A[i]
	 A[i]==A[A[i]]*/
	 public static int firstMissingPositiveInt(int[] A) {
		 for(Integer k : A){
			   System.out.print(k+ " ");
		   }
	        int n = A.length;
	 
		for (int i = 0; i < n; i++) {
			while (A[i] != i + 1) {
				if (A[i] <= 0 || A[i] >= n)
					break;

				if (A[i] == A[A[i] - 1])
					break;

				int temp = A[i];
				A[i] = A[temp - 1];
				A[temp - 1] = temp;
			}
		}
	 
		for (int i = 0; i < n; i++) {
			if (A[i] != i + 1) {
				return i + 1;
			}
		}		 
	    	return n + 1;
	}
}