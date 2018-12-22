/*
 * Pseudocode:
 * MERGE(A, p, q, r)
 * n1 = q - p + 1
 * n2 = r - q
 * let L[1..n1 + 1] and R[1..n2 + 1] be new arrays
 * for i = 1 to n1
 * 	L[i] = A[p + i - 1]
 * for j = 1 to n2
 * 	R[j] = A[q + j]
 * L[n1 + 1] = infinity
 * R[n2 + 1] = infinity
 * i = 1
 * j = 1
 * for k = p to r
 * 	if L[i] <= R[j]
 * 		A[k] = L[i]
 * 		i = i + 1
 * 	else A[k] = R[j]
 * 		j = j + 1
 * 
 * MERGE-SORT(A, p, r)
 * if p < r
 * 	q = [(p + r)/2]
 * 	MERGE-SORT(A, p q)
 * 	MERGE-SORT(A, q + 1, r)
 * 	MERGE(A, p, q, r)
 *  
 * Input size: n (dependant on list size)
 * Running time:
 *	As all variable initializations take a constant time, and the for loops
 *	used to fill the L and R arrays take O(n1 + n2) = O(n) time for the merge
 *  procedure.
 *  
 *  For the merge-sort procedure first we assume that the list is of size a power
 *  of 2, making the subproblems of size n/2. Taking into consideration that this
 *  algorithm uses the divide-and-conquer approach:
 *  
 *  T(n) = c				if n = 1,
 *  	 = 2T(n/2) + cn		if n > 1.
 *  
 *  If we view the generation of subproblems as a tree structure, with the original
 *  problem being the root, each recursion is half the size of the previous:
 *  c(n/2) + c(n/2) = cn for the first level, c(n/4) + c(n/4) + c(n/4) + c(n/4) = cn
 *  for the next and so on. From this progression we can derive that there are
 *  2^i nodes, each contributing c(n/2^i) of the cost.
 *  
 */

package com.algorithms.sorting;

/**
 * This is the Merge Sort algorithm based on the pseudocode in Introduction to Algorithms
 * by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 * 
 * Merge Sort uses the divide and conquer strategy which consists of dividing
 * the problem into a number of subproblems which are smaller instances of the
 * same problem, conquering that problem recursively or in a straightforward
 * manner if possible, and combining the solutions of the subproblems to obtain
 * the solution to the whole problem.
 * 
 * This implementation uses a sentinel card (represented by infinity) which 
 * simplifies the code as it is used as an element with a maximum value(to avoid
 * checking for an empty sublist).
 * 
 * @author Peter Jones
 * 
 * @since 1.7
 */

public class MergeSort {

	/**
	 * Prevent initialization
	 */
	private MergeSort() { }
	
	public static void mergeSort(int[] A) {
		mergeSort(A, 0, A.length);
	}
	public static void mergeSort(int[] A, int p, int r) {
		// p will be initialized at the beginning of every list
		if(p < r) {
			int q = ((p + r) / 2);
			mergeSort(A, p, q);
			mergeSort(A, q + 1, r);
			merge(A, p, q, r);
		}
	}
	public static void merge(int[] A, int p, int q, int r) {
		int n1 = q - p,
			n2 = r - q;
		int[] L = new int[n1 + 1],
			  R = new int[n2 + 1];
		
		for(int i = 0; i < n1; i++) {
			L[i] = A[p + i];
		}
		for(int j = 0; j < n2; j++) {
			R[j] = A[q + j];
		}
		// Max value of int represents infinity
		L[n1] = Integer.MAX_VALUE;
		R[n2] = Integer.MAX_VALUE;
		
		int i = 0,
			j = 0;

		for(int k = p; k < r; k++) {
			if(L[i] <= R[j]) {
				A[k] = L[i];
				i++;
			}
			else {
				A[k] = R[j];
				j++;
			}
		}
	}
	
	public static void main(String args[]) {
		int[] b = {5, 2, 4, 7, 1, 3, 2, 6};
		
		mergeSort(b);
		int i = 0;
		while(i < b.length) {
			System.out.print(b[i] + " ");
			i++;
		}
	}
}