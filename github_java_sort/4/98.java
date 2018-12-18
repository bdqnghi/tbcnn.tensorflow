
package org.terrier.sorting;

import com.facebook.fb303.FacebookService.aliveSince_args;


public class HeapSortInt
{

	
	private static int buildMaxHeap(int[] A, int[] B, int[] C)
	{
		final int heapSize = A.length;
		for (int i = heapSize / 2; i > 0; i--)
			maxHeapify(A, B, C, i, heapSize);
		return heapSize;
	}

	private static int buildMaxHeap(int[] A, int[] B, int[] C, int[] D)
	{
		final int heapSize = A.length;
		for (int i = heapSize / 2; i > 0; i--)
			maxHeapify(A, B, C, D, i, heapSize);
		return heapSize;
	}

	private static int buildMaxHeap(int[][] A)
	{
		final int heapSize = A[0].length;
		for (int i = heapSize / 2; i > 0; i--)
			maxHeapify(A, i, heapSize);
		return heapSize;
	}

	
	private static int buildMaxHeap(int[] A, int[] B)
	{
		final int heapSize = A.length;
		for (int i = heapSize / 2; i > 0; i--)
			maxHeapify(A, B, i, heapSize);
		return heapSize;
	}

	private static int buildMaxHeap(String[] A, int[] B)
	{
		final int heapSize = A.length;
		for (int i = heapSize / 2; i > 0; i--)
			maxHeapify(A, B, i, heapSize);
		return heapSize;
	}

	
	public static void ascendingHeapSort(int[] A, int[] B, int[] C)
	{
		int heapSize = buildMaxHeap(A, B, C);

		
		int tmpDouble;
		int tmpInt;
		int tmpShort;

		for (int i = A.length; i > 0; i--)
		{
			
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

	
	public static void ascendingHeapSort(int[] A, int[] B, int[] C, int[] D)
	{
		int heapSize = buildMaxHeap(A, B, C, D);

		
		int tmpDouble;
		int tmpInt;
		int tmpShort;

		for (int i = A.length; i > 0; i--)
		{
			
			tmpDouble = A[i - 1];
			A[i - 1] = A[0];
			A[0] = tmpDouble;

			tmpInt = B[i - 1];
			B[i - 1] = B[0];
			B[0] = tmpInt;

			tmpShort = C[i - 1];
			C[i - 1] = C[0];
			C[0] = tmpShort;

			tmpShort = D[i - 1];
			D[i - 1] = D[0];
			D[0] = tmpShort;

			heapSize--;
			maxHeapify(A, B, C, D, 1, heapSize);
		}
	}

	
	public static void ascendingHeapSort(int[] A, int[] B)
	{
		int heapSize = buildMaxHeap(A, B);

		
		int tmpDouble;
		int tmpInt;
		

		for (int i = A.length; i > 0; i--)
		{
			
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

	public static void ascendingHeapSort(String[] A, int[] B)
	{
		int heapSize = buildMaxHeap(A, B);

		
		String tmpDouble;
		int tmpInt;
		

		for (int i = A.length; i > 0; i--)
		{
			
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

	
	public static void descendingHeapSort(int[] A, int[] B)
	{
		ascendingHeapSort(A, B);
		reverse(A, B, A.length);
	}

	
	public static void ascendingHeapSort(int[][] A)
	{
		int heapSize = buildMaxHeap(A);

		

		int tmpInt;
		

		for (int i = A[0].length; i > 0; i--)
		{
			
			for (int j = 0; j < A.length; j++)
			{
				tmpInt = A[j][i - 1];
				A[j][i - 1] = A[j][0];
				A[j][0] = tmpInt;
			}

			heapSize--;
			maxHeapify(A, 1, heapSize);
		}
	}

	
	public static void descendingHeapSort(int[] A, int[] B, int[] C)
	{
		HeapSortInt.ascendingHeapSort(A, B, C);
		reverse(A, B, C, A.length);
	}

	

	public static void descendingHeapSort(int[] A, int[] B, int[] C, int[] D)
	{
		HeapSortInt.ascendingHeapSort(A, B, C, D);
		reverse(A, B, C, D, A.length);
	}

	
	public static void ascendingHeapSort(int[] A, int[] B, int[] C,
	        int topElements)
	{
		int heapSize = buildMaxHeap(A, B, C);
		int end = A.length - topElements;

		
		int tmpDouble;
		int tmpInt;
		int tmpShort;

		for (int i = A.length; i > end; i--)
		{
			
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

	
	private static void reverse(final int[] A, final int[] B, final int[] C,
	        final int topElements)
	{
		
		final int length = A.length;
		final int elems = 
		topElements > length / 2 ? length / 2 : topElements;
		
		

		int j;
		
		int tmpDouble;
		int tmpInt;
		int tmpShort;

		for (int i = 0; i < elems; i++)
		{
			j = length - i - 1;
			
			tmpDouble = A[i];
			A[i] = A[j];
			A[j] = tmpDouble;
			tmpInt = B[i];
			B[i] = B[j];
			B[j] = tmpInt;
			tmpShort = C[i];
			C[i] = C[j];
			C[j] = tmpShort;
		}
	}

	
	private static void reverse(final int[] A, final int[] B,
	        final int topElements)
	{
		
		final int length = A.length;
		final int elems = 
		topElements > length / 2 ? length / 2 : topElements;
		
		

		int j;
		
		int tmpDouble;
		int tmpInt;
		

		for (int i = 0; i < elems; i++)
		{
			j = length - i - 1;
			
			tmpDouble = A[i];
			A[i] = A[j];
			A[j] = tmpDouble;
			tmpInt = B[i];
			B[i] = B[j];
			B[j] = tmpInt;
			
		}
	}

	private static void reverse(final int[] A, final int[] B, final int[] C,
	        final int[] D, final int topElements)
	{
		
		final int length = A.length;
		final int elems = 
		topElements > length / 2 ? length / 2 : topElements;
		
		

		int j;
		
		int tmpDouble;
		int tmpInt;
		int tmpShort;

		for (int i = 0; i < elems; i++)
		{
			j = length - i - 1;
			
			tmpDouble = A[i];
			A[i] = A[j];
			A[j] = tmpDouble;
			tmpInt = B[i];
			B[i] = B[j];
			B[j] = tmpInt;
			tmpShort = C[i];
			C[i] = C[j];
			C[j] = tmpShort;
			tmpShort = D[i];
			D[i] = D[j];
			D[j] = tmpShort;
		}
	}

	
	public static void descendingHeapSort(final int[] A, final int[] B,
	        final int[] C, final int topElements)
	{
		ascendingHeapSort(A, B, C, topElements);
		reverse(A, B, C, topElements);
	}

	
	private static void maxHeapify(final int[] A, final int[] B, final int[] C,
	        final int i, final int heapSize)
	{
		final int l = 2 * i;
		final int r = 2 * i + 1;

		int largest = (l <= heapSize && A[l - 1] > A[i - 1]) ? l : i;
		
		
		
		
		if (r <= heapSize && A[r - 1] > A[largest - 1])
			largest = r;

		
		int tmpDouble;
		int tmpInt;
		int tmpShort;

		if (largest != i)
		{
			tmpDouble = A[largest - 1];
			A[largest - 1] = A[i - 1];
			A[i - 1] = tmpDouble;
			tmpInt = B[largest - 1];
			B[largest - 1] = B[i - 1];
			B[i - 1] = tmpInt;
			tmpShort = C[largest - 1];
			C[largest - 1] = C[i - 1];
			C[i - 1] = tmpShort;
			maxHeapify(A, B, C, largest, heapSize);
		}
	}

	private static void maxHeapify(final int[] A, final int[] B, final int[] C,
	        final int[] D, final int i, final int heapSize)
	{
		final int l = 2 * i;
		final int r = 2 * i + 1;

		int largest = (l <= heapSize && A[l - 1] > A[i - 1]) ? l : i;
		
		
		
		
		if (r <= heapSize && A[r - 1] > A[largest - 1])
			largest = r;

		
		int tmpDouble;
		int tmpInt;
		int tmpShort;

		if (largest != i)
		{
			tmpDouble = A[largest - 1];
			A[largest - 1] = A[i - 1];
			A[i - 1] = tmpDouble;
			tmpInt = B[largest - 1];
			B[largest - 1] = B[i - 1];
			B[i - 1] = tmpInt;
			tmpShort = C[largest - 1];
			C[largest - 1] = C[i - 1];
			C[i - 1] = tmpShort;

			tmpShort = D[largest - 1];
			D[largest - 1] = D[i - 1];
			D[i - 1] = tmpShort;

			maxHeapify(A, B, C, D, largest, heapSize);
		}
	}

	
	private static void maxHeapify(final int[] A, final int[] B, final int i,
	        final int heapSize)
	{
		final int l = 2 * i;
		final int r = 2 * i + 1;

		int largest = (l <= heapSize && A[l - 1] > A[i - 1]) ? l : i;
		
		
		
		
		if (r <= heapSize && A[r - 1] > A[largest - 1])
			largest = r;

		
		int tmpDouble;
		int tmpInt;
		

		if (largest != i)
		{
			tmpDouble = A[largest - 1];
			A[largest - 1] = A[i - 1];
			A[i - 1] = tmpDouble;
			tmpInt = B[largest - 1];
			B[largest - 1] = B[i - 1];
			B[i - 1] = tmpInt;
			maxHeapify(A, B, largest, heapSize);
		}
	}

	private static void maxHeapify(final String[] A, final int[] B,
	        final int i, final int heapSize)
	{
		final int l = 2 * i;
		final int r = 2 * i + 1;

		int largest = (l <= heapSize && A[l - 1].compareToIgnoreCase(A[i - 1]) > 0) ? l
		        : i;
		
		
		
		
		if (r <= heapSize && A[r - 1].compareToIgnoreCase(A[largest - 1]) > 0)
			largest = r;

		
		String tmpDouble;
		int tmpInt;
		

		if (largest != i)
		{
			tmpDouble = A[largest - 1];
			A[largest - 1] = A[i - 1];
			A[i - 1] = tmpDouble;
			tmpInt = B[largest - 1];
			B[largest - 1] = B[i - 1];
			B[i - 1] = tmpInt;
			maxHeapify(A, B, largest, heapSize);
		}
	}

	private static void maxHeapify(final int[][] A, final int i,
	        final int heapSize)
	{
		final int l = 2 * i;
		final int r = 2 * i + 1;

		int largest = (l <= heapSize && A[0][l - 1] > A[0][i - 1]) ? l : i;
		
		
		
		
		if (r <= heapSize && A[0][r - 1] > A[0][largest - 1])
			largest = r;

		
		int tmpInt;
		

		if (largest != i)
		{
			for (int j = 0; j < A.length; j++)
			{
				tmpInt = A[j][largest - 1];
				A[j][largest - 1] = A[j][i - 1];
				A[j][i - 1] = tmpInt;
			}
			maxHeapify(A, largest, heapSize);
		}
	}

	
	
	
	
	
	
	
	
	
	
	
	

	
	

	
	
	

	
}
