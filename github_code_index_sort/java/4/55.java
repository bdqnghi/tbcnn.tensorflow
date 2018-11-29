package com.source.leetcode;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class HeapSort {
	
	/*public static void minHeapDown(int[] num,int start,int end){
		int node=start;
		int left=2*node+1;
		int tmp=num[node];
		for(;left<=end;left=2*left+1){
			if(left<end && num[left]<num[left+1]);
		}
	}
	
	public static void heapSort(int[] num){
		
	}*/
	
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
		
		/*int[] array={1,5,2,4,7,3,9};
		//HeapSort.heapSort(array);
		for(int i=array.length-1;i>=1;i--){
			HeapSort.MinHeapDown(array);
		}
		for (int i : array) {
			System.out.print(i+" ");
		}*/
		//HeapSort.MinHeapUp(array,1);
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
		/*System.out.println("a[0] value="+array[0]+" a[n-1] value="+array[n-1]);
		HeapSort.swapInt(array[0], array[n-1]);
		System.out.println("a[0] value="+array[0]+" a[n-1] value="+array[n-1]);
		heap.MinHeapDown(array, 0, n-1);
		HeapSort.printArray(array);
		HeapSort.swapInt(array[0], array[n-2]);
		heap.MinHeapDown(array, 0, n-2);
		HeapSort.printArray(array);*/
	}

}
