
package org.terrier.sorting;

public class MultiSort {
	
	private static int buildMaxHeap(double[] A, int[] B, short[] C) {
		final int heapSize = A.length;
		for (int i = heapSize/2; i > 0; i--)
			maxHeapify(A, B, C, i, heapSize);
		return heapSize;
	}
	
	private static int buildMaxHeap(int[] A, double[] B, short[] C) {
		final int heapSize = A.length;
		for (int i = heapSize/2; i > 0; i--)
			maxHeapify(A, B, C, i, heapSize);
		return heapSize;
	}
	
	
	public static final void ascendingHeapSort(double[] A, int[] B, short[] C) {
		int heapSize = buildMaxHeap(A, B, C);

		
		double tmpDouble;
		int tmpInt;
		short tmpShort;

		for (int i = A.length; i > 0; i--) {
			
			tmpDouble = A[i - 1];
			A[i - 1] = A[0];
			A[0] = tmpDouble;

			tmpInt = B[i - 1];
			B[i - 1] = B[0];
			B[0] = tmpInt;

			tmpShort = C[i - 1];
			C[i - 1] = C[0];
			C[0] = tmpShort;

			heapSize--;
			maxHeapify(A, B, C, 1, heapSize);
		}
	}
	

	
	public static final void ascendingHeapSort(Comparable<?>[] A, int[] B) {
		int heapSize = buildMaxHeap(A, B);

		
		Comparable<?> tmpDouble;
		int tmpInt;
		
		for (int i = A.length; i > 0; i--) {
			
			tmpDouble = A[i - 1];
			A[i - 1] = A[0];
			A[0] = tmpDouble;

			tmpInt = B[i - 1];
			B[i - 1] = B[0];
			B[0] = tmpInt;

			heapSize--;
			maxHeapify(A, B, 1, heapSize);
		}
	}
	
	
	
	
	
	private static int buildMaxHeap(Comparable<?>[] A, int[] B) {
		final int heapSize = A.length;
		for (int i = heapSize/2; i > 0; i--)
			maxHeapify(A, B, i, heapSize);
		return heapSize;
	}

	@SuppressWarnings("unchecked")
	private static void maxHeapify(@SuppressWarnings("rawtypes") Comparable[] A, int[] B, int i,
			int heapSize) {
		final int l = 2 * i;
		final int r = 2 * i + 1;

		int largest = 
			(l <= heapSize && A[l - 1].compareTo(A[i - 1]) > 0)
				? l
				: i;
		
		
		
		
		if (r <= heapSize &&  A[r - 1].compareTo(A[largest - 1]) > 0)
			largest = r;

		
		Comparable<?> tmpDouble;
		int tmpInt;
		

		if (largest != i) {
			tmpDouble = A[largest - 1];
			A[largest - 1] = A[i - 1];
			A[i - 1] = tmpDouble;

			tmpInt = B[largest - 1];
			B[largest - 1] = B[i - 1];
			B[i - 1] = tmpInt;

			maxHeapify(A, B, largest, heapSize);
		}
	}

	
	public static final void descendingHeapSort(double[] A, int[] B, short[] C) {
		MultiSort.ascendingHeapSort(A, B, C);
		reverse(A, B, C, A.length);
	}
	
	public static final void ascendingHeapSort(double[] A, int[] B, short[] C, int topElements) {
		int heapSize = buildMaxHeap(A, B, C);
		int end = A.length - topElements;

		
		double tmpDouble;
		int tmpInt;
		short tmpShort;


		for (int i = A.length; i > end; i--) {
			
			tmpDouble = A[i - 1];
			A[i - 1] = A[0];
			A[0] = tmpDouble;

			tmpInt = B[i - 1];
			B[i - 1] = B[0];
			B[0] = tmpInt;

			tmpShort = C[i - 1];
			C[i - 1] = C[0];
			C[0] = tmpShort;

			heapSize--;
			maxHeapify(A, B, C, 1, heapSize);
		}
	}
	
	
	public static final void ascendingHeapSort(int[] A, double[] B, short[] C, int topElements) {
		int heapSize = buildMaxHeap(A, B, C);
		int end = A.length - topElements;

		
		double tmpDouble;
		int tmpInt;
		short tmpShort;


		for (int i = A.length; i > end; i--) {
			
			tmpInt = A[i - 1];
			A[i - 1] = A[0];
			A[0] = tmpInt;

			tmpDouble = B[i - 1];
			B[i - 1] = B[0];
			B[0] = tmpDouble;

			tmpShort = C[i - 1];
			C[i - 1] = C[0];
			C[0] = tmpShort;

			heapSize--;
			maxHeapify(A, B, C, 1, heapSize);
		}
	}
	
	
	
	private static void reverse(final double[] A, final int[] B, final short[] C, final int topElements) {
		
		final int length = A.length;
		final int elems = 
			topElements > length/2 
			? length/2 
			: topElements;
		
		


		int j;
		
		double tmpDouble;
		int tmpInt;
		short tmpShort;

		for (int i=0; i<elems; i++) {
			j = length - i - 1;
			
			tmpDouble = A[i]; A[i] = A[j]; A[j] = tmpDouble;
			tmpInt = B[i]; B[i] = B[j]; B[j] = tmpInt;
			tmpShort = C[i]; C[i] = C[j]; C[j] = tmpShort;
		}
	}
	
	public static final void descendingHeapSort(final double[] A, final int[] B, final short[] C, final int topElements) {
		ascendingHeapSort(A, B, C, topElements);
		reverse(A, B, C, topElements);
	}
	
	private static void maxHeapify(final double[] A, final int[] B, final short[] C, final int i, final int heapSize) {
		final int l = 2 * i;
		final int r = 2 * i + 1;

		int largest = 
			(l <= heapSize && A[l - 1] > A[i - 1])
				? l
				: i;
		
		
		
		
		if (r <= heapSize && A[r - 1] > A[largest - 1])
			largest = r;

		
		double tmpDouble;
		int tmpInt;
		short tmpShort;


		if (largest != i) {
			tmpDouble = A[largest - 1];
			A[largest - 1] = A[i - 1];
			A[i - 1] = tmpDouble;
			tmpInt = B[largest - 1];
			B[largest - 1] = B[i - 1];
			B[i - 1] = tmpInt;
			tmpShort = C[largest -1];
			C[largest -1] = C[i - 1];
			C[i - 1] = tmpShort;
			maxHeapify(A, B, C, largest, heapSize);
		}
	}
	
	private static void maxHeapify(final int[] A, final double[] B, final short[] C, final int i, final int heapSize) {
		final int l = 2 * i;
		final int r = 2 * i + 1;

		int largest = 
			(l <= heapSize && A[l - 1] > A[i - 1])
				? l
				: i;
		
		
		
		
		if (r <= heapSize && A[r - 1] > A[largest - 1])
			largest = r;

		
		double tmpDouble;
		int tmpInt;
		short tmpShort;


		if (largest != i) {
			tmpInt = A[largest - 1];
			A[largest - 1] = A[i - 1];
			A[i - 1] = tmpInt;
			tmpDouble = B[largest - 1];
			B[largest - 1] = B[i - 1];
			B[i - 1] = tmpDouble;
			tmpShort = C[largest -1];
			C[largest -1] = C[i - 1];
			C[i - 1] = tmpShort;
			maxHeapify(A, B, C, largest, heapSize);
		}
	}
}
