package com.learn.algorithms.sort;

import java.util.Arrays;

public class HeapSortMaxHeap {
	
	
	
	
	private static int getLeftChildIndex(int parentIndex){return 2*parentIndex+1;}
	private static int getRightChildIndex(int parentIndex){return 2*parentIndex+2;}

    
   
   

    
    private static boolean hasLeft(int index,int size){ return getLeftChildIndex(index) < size;}
    private static boolean hasRight(int index,int size){ return getRightChildIndex(index) < size;}
    
    
	
	private static void swap(Comparable[] input,int IndexOne,int IndexTwo){
		Comparable tmp = input[IndexOne];
		input[IndexOne] = input[IndexTwo];
		input[IndexTwo] = tmp;
	}
	
	private static void heapsort(Comparable[] input){
		int size=input.length;
		
		for(int i=size/2-1;i>=0;i--)
		    heapify(input,i,size);
		
		System.out.println("After heapifying\n");
		System.out.println(Arrays.toString(input));
		
	   
	   
	   
	   for(int i = size-1;i>=0;i--){
		   Comparable tmp = input[0];
		   input[0]=input[i];
		   input[i]=tmp;
		   
		   heapify(input,0,i);
	   }
				
	}
	
	
	
	private static void heapify(Comparable[]input,int index,int size){
	   int largestIndex = index;
	   
	   if(hasLeft(index,size) && input[largestIndex].compareTo(input[getLeftChildIndex(index)])<0)
		   largestIndex = getLeftChildIndex(index);
	   
	   if(hasRight(index,size) && input[largestIndex].compareTo(input[getRightChildIndex(index)]) < 0)
		   largestIndex = getRightChildIndex(index);
		   
	   if(largestIndex != index) 
	   {
		   swap(input,index,largestIndex);
		   heapify(input, largestIndex,size);
	   }
		    
	}
	public static void main(String[] args) {
		Integer arr[] = new Integer[]{ 8,7,9,10,3,4,1,12,6,5};
		System.out.println("\nInput array");
		System.out.println(Arrays.toString(arr));
		heapsort(arr);
		System.out.println("\n After sorting \n");
		System.out.println(Arrays.toString(arr));

	}

}
