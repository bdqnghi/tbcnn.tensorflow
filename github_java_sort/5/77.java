package com.sort;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;

public class Bubble {

	public static void main(String[] args) throws IOException {
		
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pw = new PrintWriter(System.out, true);
		
		pw.println("Enter the element of an array on a single line separated by blank space");
		String arrNum[] = br.readLine().split(" ");
	    
		int arr[] = new int [arrNum.length];
		
		for( int i =0 ; i < arrNum.length ; i++){ 
		   arr[i] = Integer.parseInt(arrNum[i]);
		   System.out.print(arr[i]+ " ");
		}
		 System.out.println("");
		 System.out.println("Dispay results in sorted order");
		
		
		arr = bubbleSort(arr);	
		
		for(int x : arr){
			System.out.print(x+ " ");
		}

	}
	
	public static int [] bubbleSort(int arr[]){
		
		int n = arr.length;
		for(int i= n-2 ; i >=0 ; i-- ){
			for(int j = 0 ; j <= i ; j ++){
				
				if(arr[j] > arr[j+1]) 
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
		}
		
		return arr ;
	}
	
}
