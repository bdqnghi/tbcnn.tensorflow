 

import java.util.*;
import java.io.*;
public class PQ225{
	private int[] heapArray;
	private int count;
	private int heapsortComps;

	
	public PQ225(){
		heapArray = new int[25];
		count = 0;
		heapsortComps = 0;
	}

	
	public void ranGen(int N, int LOW, int HIGH){
		
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

	
	public int size(){
		return count;
	}

	
	public void insert(int item){
		if(size() + 1 == heapArray.length) {
			heapArray = checkSize();
		}
		heapArray[++count] = item;
		bubbleUp(count);
	}

	
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

	
	public void makeHeap(){
		for(int i = size()/2; i > 0; i--){
			bubbleDown(i);
		}
	}

	
	private void bubbleUp(int n){
		while(n > 1 && heapArray[n/2] > heapArray[n]){ 
			swap(n/2, n);
			n = n/2;
		}
	}

	
	private int bubbleDown(int n){
		int comp = 0;
		while(2*n <= count){
			int j = 2*n;
			if(j < count && heapArray[j+1] < heapArray[j]){ 
				comp++;
				j++;
			}
			if(heapArray[n] < heapArray[j]){ 
				comp++;
				break;
			}
			swap(n, j);	
			n = j;
		}
		return comp;
	}

	
	public void heapsort(){
		int i = count;
		while(count > 1){
			swap(1, count);
			count--;
			heapsortComps += bubbleDown(1);
		}
		count = i;
	}	

	
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

	
	private void swap (int parent, int child){
		int tmp = heapArray[parent];
		heapArray[parent] = heapArray[child];
		heapArray[child] = tmp;
	}

	
	private int[] checkSize() {
		int[] newHeapArray = new int[heapArray.length * 2];
		for(int i = 1; i <= size(); i++) {
			newHeapArray[i] = heapArray[i];
		}
		return newHeapArray;
	}

	
	private int getIndex(int i){
		return heapArray[i];
	}

	
	private static void printHeap(PQ225 heap){
		for(int i = 1; i <= heap.size(); i++){
			System.out.print(heap.getIndex(i) + " ");
		}
		System.out.println();
	}

	
	private static void printList(int[] arr){
		for(int i = 0; i < arr.length; i++){
			System.out.print(arr[i] + " ");
		}
		System.out.println();
	}

	
	private boolean isSorted(){
		for(int i = 1; i < size(); i++){
			if(heapArray[i] < heapArray[i+1]){
				return false;
			}
		}
		return true;
	}

	
	private int heapsortComps(){
		return heapsortComps;
	}

	
	private void heapsortCompsClear(){
		heapsortComps = 0;
	}

	public static void main(String[] args){
		test();
	}
	
}
