/*
  * Name: Noah Boulton
  * Date: Nov 9, 2016
  * Filename: PQ225.java
  * Details: CSC225 Assignment03
  */ 

import java.util.*;
import java.io.*;
public class PQ225{
	private int[] heapArray;
	private int count;
	private int heapsortComps;

	/**
	 * constructor for PQ225 class
	 */
	public PQ225(){
		heapArray = new int[25];
		count = 0;
		heapsortComps = 0;
	}

	/**
	 * Generates N random numbers in the range LOW to HIGH and inserts them 
	 * into the heapArray. Clears and resizes the heapArray to match N.
	 */
	public void ranGen(int N, int LOW, int HIGH){
		/* generates N random numbers in the range Low to High and inserts them
		 * into the heapArray 
		 */
		count = 0;
		heapArray = new int[N+1];
		long seed = System.currentTimeMillis();
		int k = 1;
		Random randNum = new Random(seed);
		while(k < N+1){
			int num = randNum.nextInt();;
			while(num < LOW || HIGH < num){
				num = randNum.nextInt();
			}
			heapArray[k] = num;
			k++;
			count++;
		}
	}

	/**
	 * Returns the number of integers in the heap
	 */
	public int size(){
		return count;
	}

	/**
	 * Inserts an integer into the heap in O(logn) time
	 */
	public void insert(int item){
		if(size() + 1 == heapArray.length) {
			heapArray = checkSize();
		}
		heapArray[++count] = item;
		bubbleUp(count);
	}

	/**
	 * Deletes the smallest integer from the heap in O(logn) time
	 */
	public int deleteMin(){
		if(count > 0){
			int min = heapArray[1];
			swap(1, count);
			count--;
			bubbleDown(1);
			return min;
		}
		return -1;
	}

	/**
	 * Turns the unsorted integer array, heapArray into a heap in O(n)
	 */
	public void makeHeap(){
		for(int i = size()/2; i > 0; i--){
			bubbleDown(i);
		}
	}

	/**
	 * Bubbles an integer up the heap to restore the order property
	 */
	private void bubbleUp(int n){
		while(n > 1 && heapArray[n/2] > heapArray[n]){ 
			swap(n/2, n);
			n = n/2;
		}
	}

	/**
	 * Bubbles an integer down the heap to restore the order property
	 */
	private int bubbleDown(int n){
		int comp = 0;
		while(2*n <= count){
			int j = 2*n;
			if(j < count && heapArray[j+1] < heapArray[j]){ //increment comps
				comp++;
				j++;
			}
			if(heapArray[n] < heapArray[j]){ //increment comps
				comp++;
				break;
			}
			swap(n, j);	
			n = j;
		}
		return comp;
	}

	/**
	 * Sorts the integer array, heapArray, using In Place Heap Sort in O(nlogn).
	 */
	public void heapsort(){
		int i = count;
		while(count > 1){
			swap(1, count);
			count--;
			heapsortComps += bubbleDown(1);
		}
		count = i;
	}	

	/**
	 * Used for testing the heap methods. Prints out to a file named "pq_test.txt".
	 */
	public static void test(){
		try{
			PrintWriter print = new PrintWriter("pq_test.txt");

			print.println("Testing the ranGen, makeHeap, insert, and heapsort metohds.");
			print.println();

			print.println("Making a small heap of size 8.");
			PQ225 heapSmall = new PQ225();
			heapSmall.ranGen(8, 0, 1000000);
			heapSmall.makeHeap();
			heapSmall.heapsort();
			print.print("Checking if the heap is sorted after heapsort: ");
			print.println(heapSmall.isSorted());
			print.println();

			print.println("Making a small heap using the insert method.");
			PQ225 heap = new PQ225();
			heap.insert(5);
			heap.insert(70);
			heap.insert(12);
			heap.insert(4);
			heap.insert(1);
			heap.insert(0);
			heap.insert(55);
			heap.insert(54);
			heap.heapsort();
			print.print("Checking if the heap is sorted after heapsort: ");
			print.println(heap.isSorted());
			print.println();

			print.println("Making a heap of size 100.");
			PQ225 heap100 = new PQ225();
			heap100.ranGen(100, 0, 1000000);
			heap100.makeHeap();
			heap100.heapsort();
			print.print("Checking if the heap is sorted after heapsort: ");
			print.println(heap100.isSorted());
			print.println("Size of the array: " + 100);
			print.println("Comparisons for heapsort: " + heap100.heapsortComps());
			print.println();

			print.println("Making a heap of size 1000.");
			PQ225 heap1000 = new PQ225();
			heap1000.ranGen(1000, 0, 1000000);
			heap1000.makeHeap();
			heap1000.heapsort();
			print.print("Checking if the heap is sorted after heapsort: ");
			print.println(heap1000.isSorted());
			print.println("Size of the array: " + 1000);
			print.println("Comparisons for heapsort: " + heap1000.heapsortComps());
			print.println();

			print.println("Making a heap of size 10000.");
			PQ225 heap10000 = new PQ225();
			heap10000.ranGen(10000, 0, 1000000);
			heap10000.makeHeap();
			heap10000.heapsort();
			print.print("Checking if the heap is sorted after heapsort: ");
			print.println(heap10000.isSorted());
			print.println("Size of the array: " + 10000);
			print.println("Comparisons for heapsort: " + heap10000.heapsortComps());
			print.println();

			print.println("Testing the deleteMin method. Making two equal heaps, sorting one");
			print.println("and repeatedly deleting the min of the other.");
			PQ225 heaptest = new PQ225();
			PQ225 heaptest1 = new PQ225();
			for(int i = 1; i < 11; i++){
				heaptest.insert(i);
				heaptest1.insert(i);
			}
			heaptest.heapsort();
			boolean test = true;
			for(int i = 1; i < 11; i++){
				int k = heaptest1.deleteMin();
				if(k != heaptest.getIndex(11-i)){
					test = false;
				}
			}
			print.println("The deleteMin method should return the same sorted sequence as heapsort.");
			print.println("The sequences are the same: " + test);
			print.println();

			print.println("Testing the efficiency of the heapsort method");
			print.println("by tracking the number of comparisons relative to the size of the heap.");
			print.println();
			PQ225 compGraph = new PQ225();
			for(int i = 1; i <= 1000; i++){
				if(i%10 != 0){
					continue;
				}
				compGraph.heapsortCompsClear();
				compGraph.ranGen(i, 0, 100000000);
				compGraph.makeHeap();
				compGraph.heapsort();
				print.println("Heap of size: " + i);
				print.println("Number of comparisons: " + compGraph.heapsortComps());
				double logn = Math.log10(i);
				print.println("N log N: " + (int)(i*logn));
				print.println();
			}

			print.close();
		} catch (FileNotFoundException e){
			System.out.println("File not found");
		}
	}

	/**
	 * A private method used for swapping two integers in the heap
	 */
	private void swap (int parent, int child){
		int tmp = heapArray[parent];
		heapArray[parent] = heapArray[child];
		heapArray[child] = tmp;
	}

	/**
	 * A private method used to resize the array used to implement the heap
	 */
	private int[] checkSize() {
		int[] newHeapArray = new int[heapArray.length * 2];
		for(int i = 1; i <= size(); i++) {
			newHeapArray[i] = heapArray[i];
		}
		return newHeapArray;
	}

	/**
	 * A private method for returing the integer stored at an index in the array
	 */
	private int getIndex(int i){
		return heapArray[i];
	}

	/**
	 * A private method used for testing the class methods. Prints out the heap array.
	 */
	private static void printHeap(PQ225 heap){
		for(int i = 1; i <= heap.size(); i++){
			System.out.print(heap.getIndex(i) + " ");
		}
		System.out.println();
	}

	/**
	 * A private method used for testing the heapsort method. Prints out an integer array. 
	 */
	private static void printList(int[] arr){
		for(int i = 0; i < arr.length; i++){
			System.out.print(arr[i] + " ");
		}
		System.out.println();
	}

	/**
	 * A private method that checks if an array is sorted. Used for testing the heapsort
	 * method.
	 */
	private boolean isSorted(){
		for(int i = 1; i < size(); i++){
			if(heapArray[i] < heapArray[i+1]){
				return false;
			}
		}
		return true;
	}

	/**
	 * A private method that returns the number of comparisons made by the
	 * heapsort method. 
	 */
	private int heapsortComps(){
		return heapsortComps;
	}

	/**
	 * A private method used to clear the comparisons counter for heapsort.
	 */
	private void heapsortCompsClear(){
		heapsortComps = 0;
	}

	public static void main(String[] args){
		test();
	}
	
}
