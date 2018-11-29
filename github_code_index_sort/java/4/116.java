package com.indef.sorting;

public class HeapSort {

	private int[] listToSort;
	int heapSize;
	
	public void sort(int[] listToSort){
		if(listToSort == null || listToSort.length == 0){
			return;
		}
		this.listToSort = listToSort;
		heapSize = listToSort.length;
		
		//create map heap from the input array
		buildMaxHeap();
		
		//while heap has more than one elements left to be sorted
		while(heapSize > 1){
			/*swap the first and last element from map heap as the first
			 * element should be the highest value in the max heap
			 * 
			 * Also, reduce the heap size as last element is in sorted
			 * position and needs to be taken out of consideration for
			 * further sorting
			*/ 
			swap(0,--heapSize);
			//however, now that first element and last element
			//have been swapped, make sure that heap confirms to
			//max heap property. so call heapify
			heapify(0);
		}
		
		//printAsHeap();
		System.out.println("Sorted Array using Heap Sort");
		for(int num : listToSort){
			System.out.print(num + " ");
		}
	}
	
	/**
	 * This method is called after first element in max heap
	 * is swapped with last element and heap size is reduced by
	 * one for further sorting
	 */
	private void heapify(int nodeIndex){
		
		int index = nodeIndex;
		int leftChildIndex = 2*index + 1;
		int rightChildIndex = 2*index + 2;
		int swapWithIndex = -1;
		
		System.out.println("index=" + index + ", leftChildIndex=" + leftChildIndex +
				", rightChildIndex=" + rightChildIndex);
		
		if(index <= heapSize - 1 
			&& 
		(leftChildIndex <= heapSize - 1 || rightChildIndex <= heapSize -1)){
			
			swapWithIndex = findSwapWithIndex(index, leftChildIndex, rightChildIndex);
			
			if(swapWithIndex > -1){
				swap(index, swapWithIndex);
				heapify(swapWithIndex);
			}	
		}
	}
	
	private void buildMaxHeap(){
		//number of nodes(with children) given current heapSize = heapSize/2
		int leftChildIndex = 0;
		int rightChildIndex = 0;
		int swapWithIndex = -1;
		for(int i = (heapSize/2)-1; i >= 0; i--){
			//re-initialise swapWithIndex
			swapWithIndex = -1;
			//left child index of node @index i
			leftChildIndex = 2*i + 1;
			//right child index of not @index i
			rightChildIndex = 2*i + 2;
			
			swapWithIndex = findSwapWithIndex(i, leftChildIndex, rightChildIndex);
			
			if(swapWithIndex > -1){
				swap(i, swapWithIndex);
			}
		}
		System.out.println("Printing max-heap for size: " + heapSize);
		printAsHeap();
	}
	
	private int findSwapWithIndex(int nodeIndex, 
							int leftChildIndex,
							int rightChildIndex){
		
		int swapWithIndex = -1;
		
		if(rightChildIndex <= heapSize - 1){
			
			if(listToSort[nodeIndex] < listToSort[leftChildIndex] 
				|| 
				listToSort[nodeIndex] < listToSort[rightChildIndex]){
				
				if(listToSort[rightChildIndex] >= listToSort[leftChildIndex]){
					swapWithIndex = rightChildIndex;
				}else{
					swapWithIndex = leftChildIndex;
				}
			}
			
		}else{
			//else node @index nodeIndex has only left child
			if(listToSort[nodeIndex] < listToSort[leftChildIndex]){
				swapWithIndex = leftChildIndex;
			}
		}
		
		return swapWithIndex;
	}
	
	private void swap(int swapFromIndex, int swapWithIndex){
		
		System.out.println("swapFrom[" + swapFromIndex + "], swapWith[" + swapWithIndex + "]");
		
		int temp = listToSort[swapFromIndex];
		listToSort[swapFromIndex] = listToSort[swapWithIndex];
		listToSort[swapWithIndex] = temp;
	}
	
	private void printAsHeap(){
		int index = 0;
		int level = 1;
		int itemIndex = 0;
		//int heapDepth = heapDepth(heapSize);
		while(itemIndex < listToSort.length){
			for(int i=index; i<(index+level) && itemIndex < listToSort.length; i++){				
				System.out.print(" " + listToSort[itemIndex]);				
				itemIndex++;
			}
			System.out.println();
			index += level;
			level = level*2;
		}
	}
	
	private int heapDepth(int heapSize){
		int heapDepth = 0;
		int level = 1;
		while(heapSize > 0){
			heapSize = heapSize - level;
			heapDepth++;
			level = level*2;
		}
		
		//System.out.println("Heap Depth is: " + heapDepth);
		
		return heapDepth;
	}
	
	public static void main(String[] args) {
		//int[] listToSort = {54,26,93,17,77,31,44,55,20};
		int[] listToSort = {54,26,93,17};
		HeapSort hSort = new HeapSort();
		hSort.sort(listToSort);
	}
	
	static class HeapSort2{
		
	}
}
