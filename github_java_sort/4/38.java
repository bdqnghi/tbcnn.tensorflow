package com.common;



public class HeapSort {
	
	private int heapSize;
	
	private int l;
	
	private   int r;
	
	private   int largest;
	
	private   double tmpDouble;
	
	private   float tmpFloat;
	
	private   int tmpInt;
	
	private   String tmpString;
	
	
	
	private   void buildMaxHeap(double[] A, int[] B) {
		heapSize = A.length;
		for (int i = (int) Math.floor(heapSize / 2.0D); i > 0; i--)
			maxHeapify(A, B, i);
	}
	
	
	private   void buildMaxHeap(float[] A, int[] B) {
		heapSize = A.length;
		for (int i = (int) Math.floor(heapSize / 2.0D); i > 0; i--)
			maxHeapify(A, B, i);
	}
	
	
	public   void heapSort(double[] A, int[] B) {
		buildMaxHeap(A, B);
		for (int i = A.length; i > 0; i--) {
			tmpDouble = A[i - 1];
			A[i - 1] = A[0];
			A[0] = tmpDouble;
			tmpInt = B[i - 1];
			B[i - 1] = B[0];
			B[0] = tmpInt;
			heapSize--;
			maxHeapify(A, B, 1);
		}
	}
	
	public   void heapSort(double[] A, int[] B, int topElements) {
		buildMaxHeap(A, B);
		final int end = A.length - topElements;
		
		for (int i = A.length; i > end; i--) {
			tmpDouble = A[i - 1];
			A[i - 1] = A[0];
			A[0] = tmpDouble;
			tmpInt = B[i - 1];
			B[i - 1] = B[0];
			B[0] = tmpInt;
			heapSize--;
			maxHeapify(A, B, 1);
		}
	}
	
	private   void maxHeapify(double[] A, int[] B, int i) {
		l = 2 * i;
		r = 2 * i + 1;
		if (l <= heapSize && A[l - 1] > A[i - 1])
			largest = l;
		else
			largest = i;
		if (r <= heapSize && A[r - 1] > A[largest - 1])
			largest = r;
		if (largest != i) {
			tmpDouble = A[largest - 1];
			A[largest - 1] = A[i - 1];
			A[i - 1] = tmpDouble;
			tmpInt = B[largest - 1];
			B[largest - 1] = B[i - 1];
			B[i - 1] = tmpInt;
			maxHeapify(A, B, largest);
		}
	}
	
	
	
	public   void heapSort(float[] A, int[] B) {
		buildMaxHeap(A, B);
		for (int i = A.length; i > 0; i--) {
			tmpFloat = A[i - 1];
			A[i - 1] = A[0];
			A[0] = tmpFloat;
			tmpInt = B[i - 1];
			B[i - 1] = B[0];
			B[0] = tmpInt;
			heapSize--;
			maxHeapify(A, B, 1);
		}
	}
	
	public   void heapSort(float[] A, int[] B, int topElements) {
		buildMaxHeap(A, B);
		final int end = A.length - topElements;
		
		for (int i = A.length; i > end; i--) {
			tmpFloat = A[i - 1];
			A[i - 1] = A[0];
			A[0] = tmpFloat;
			tmpInt = B[i - 1];
			B[i - 1] = B[0];
			B[0] = tmpInt;
			heapSize--;
			maxHeapify(A, B, 1);
		}
	}
	
	private   void maxHeapify(float[] A, int[] B, int i) {
		l = 2 * i;
		r = 2 * i + 1;
		if (l <= heapSize && A[l - 1] > A[i - 1])
			largest = l;
		else
			largest = i;
		if (r <= heapSize && A[r - 1] > A[largest - 1])
			largest = r;
		if (largest != i) {
			tmpFloat = A[largest - 1];
			A[largest - 1] = A[i - 1];
			A[i - 1] = tmpFloat;
			tmpInt = B[largest - 1];
			B[largest - 1] = B[i - 1];
			B[i - 1] = tmpInt;
			maxHeapify(A, B, largest);
		}
	}
	
	
	public   void heapSort(double[] A, String[] B) {
		buildMaxHeap(A, B);
		for (int i = A.length; i > 0; i--) {
			tmpDouble = A[i - 1];
			A[i - 1] = A[0];
			A[0] = tmpDouble;
			tmpString = B[i - 1];
			B[i - 1] = B[0];
			B[0] = tmpString;
			heapSize--;
			maxHeapify(A, B, 1);
		}
	}
	
	
	private   void buildMaxHeap(double[] A, String[] B) {
		heapSize = A.length;
		for (int i = (int) Math.floor(heapSize / 2.0D); i > 0; i--)
			maxHeapify(A, B, i);
	}
	
	
	private   void maxHeapify(double[] A, String[] B, int i) {
		l = 2 * i;
		r = 2 * i + 1;
		if (l <= heapSize && A[l - 1] > A[i - 1])
			largest = l;
		else
			largest = i;
		if (r <= heapSize && A[r - 1] > A[largest - 1])
			largest = r;
		if (largest != i) {
			tmpDouble = A[largest - 1];
			A[largest - 1] = A[i - 1];
			A[i - 1] = tmpDouble;
			tmpString = B[largest - 1];
			B[largest - 1] = B[i - 1];
			B[i - 1] = tmpString;
			maxHeapify(A, B, largest);
		}
	}
}
