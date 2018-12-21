package InterviewBit;

public class ArraysFirstMissingPositiveNumber {
	public static void main(String[] args) {
		int[] arr = {3,4,-1,1};
		
		System.out.println(firstMissingPositiveInt(arr));
	}
	
	 public static int firstMissingPositive(int[] A) {  
		   
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
		   
		   i = 0;  
		   while (i < A.length && A[i] == i+1) 
			   ++i;  
		   return i+1;  
		 }
	 

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