package com.source.leetcode;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class HeapSort {
	
	
	
	public static void MinHeapUp(int a[],int position){
		int nodeParent=(position-1)/2;
		int temp=a[position];
		while(nodeParent>=0 && position!=0){
			if(a[nodeParent]<=temp)
				break;
			a[position]=a[nodeParent];
			position=nodeParent;
			nodeParent=(position-1)/2;
		}
		a[position]=temp;
	}
	
	public static void MinHeapDown(int a[]){
		int index=a.length-1;
		int i=0,j=0;
		a[i]=a[index];
		int temp=a[i];
		j=2*i+1;
		while(j<a.length-1){
			if(a[j]>a[j+1])
				j=j+1;
			if(a[j]>=temp)
				break;
			a[i]=a[j];
			i=j;
			j=2*i+1;
		}
		a[i]=temp;
	}
	
	public static void printArray(int[] array){
		for (int i : array) {
			System.out.print(i+" ");
		}
		System.out.println();
	}
	
	public static void swapInt(int a,int b){
		int temp=a;
		a=b;
		b=temp;
	}

	public static void main(String[] args) throws Exception {
		
		
		
		int[] array={1,5,2,4,7,3,9};
		int n=array.length;
		HeapSort.printArray(array);
		Heap heap=new Heap();
		heap.MakeMinHeap(array, n);
		HeapSort.printArray(array);
		for(int i=n-1;i>=1;i--){
			int temp=array[i];
			array[i]=array[0];
			array[0]=temp;
			heap.MinHeapDown(array, 0, i);
		}
		HeapSort.printArray(array);
		
	}

}
