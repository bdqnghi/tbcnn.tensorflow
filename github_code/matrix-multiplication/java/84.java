package com.accolite.problems;

public class matrixChainMultiplication {

	public static void main(String [] args) {
		int [] rows =  {40, 20, 30, 10, 30}   ;
		System.out.println(matrixMul(rows,0,rows.length-1));
		System.out.println(matrixMul2(rows,0,rows.length-2));
	}
	
	public static int matrixMul(int [] arr, int start, int end) {
		int min = Integer.MAX_VALUE;
		int prod = 0;
		if(start >= end-1) {
			return 0;
		}
		else {
			
			for(int i = start+1; i< end ; i++) {
				int left = matrixMul(arr,start,i);
				int right = matrixMul(arr,i,end);			
				prod = left + right + arr[start]*arr[i]*arr[end];
				if(prod < min){
					min = prod;
				}
				
			}
			return min;
		}
	}
	
	public static int matrixMul2(int [] arr, int start, int end) {
		int min = Integer.MAX_VALUE;
		int prod = 0;
		System.out.println(start+"  " +end);
		if(start >= end) {
			return 0;
		}
		else {
			
			for(int i = start; i< end ; i++) {
				int left = matrixMul2(arr,start,i);
				int right = matrixMul2(arr,i+1,end);			
				prod = left + right + arr[start]*arr[i+1]*arr[end+1];
				if(prod < min){
					min = prod;
				}
				
			}
			return min;
		}
		
	}
}
