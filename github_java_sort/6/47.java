package com.zh.algorithm;


public class RadixSortIml {

	public static void main(String[] args) {
			int[] A = {123,132,111,222,158,100,110};
			int[] sort = radixSort(A,3);
			for(int i = 0;i < sort.length;i++){
				if(i == sort.length - 1)
					System.out.print(sort[i] + "]");
				else
					System.out.print(sort[i]+",");
			}

	}

	
	private static int[] radixSort(int[] a, int i) {
		
		for(int j = 1;j <= i;j++)
			countSort(a,j);
		return a;
		
	}

	
	private static void countSort(int[] A,int j) {
				int[] B = new int[A.length];
				int exp = getExp(j);
				
				int max = getJMax(A, j);
				int[] C = new int[max + 1];
				
				for(int i = 0 ;i < C.length;i++)
					C[i] =  0;
				
				for(int i = 0;i < A.length;i++)
					C[(A[i] / exp) % 10]++;
				
				for(int i = 1;i < C.length;i++)
					C[i] += C[i - 1];
				
				for(int i = A.length - 1;i >= 0;i--){
					B[C[(A[i] / exp) % 10] - 1] = A[i];  
					C[(A[i] / exp) % 10] --;
				}
				
				for(int i = 0;i < A.length;i++)
					A[i] = B[i];
		
	}

	
	private static int getExp(int j) {
		
				int exp = 1;
				for(int i = 1;i < j;i ++){
					exp *= 10;
				}
		return exp;
	}

	private static int getJMax(int[] a, int j) {
		
		int exp = 1;
		for(int i = 1;i < j;i ++){
			exp *= 10;
		}
		
		
		int max = (a[0] / exp) % 10;
		for( int i = 1; i < a.length;i++)
			if(max < (a[i] / exp) % 10)
				max = (a[i] / exp) % 10;
		return max;
	}

}
