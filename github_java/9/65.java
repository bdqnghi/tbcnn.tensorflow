// Solution 1: Start at array position 1
/**
 * Refer to
 * http://algs4.cs.princeton.edu/24pq/
 * http://algs4.cs.princeton.edu/24pq/Heap.java.html
 * 
 * Definition. 
 * A binary heap is a set of nodes with keys arranged in a complete heap-ordered binary tree, 
 * represented in level order in an array (not using the first entry).
 * Heap representations
 * In a heap, the parent of the node in position k is in position k/2; and, conversely, the two children 
 * of the node in position k are in positions 2k and 2k + 1. We can travel up and down by doing simple 
 * arithmetic on array indices: to move up the tree from a[k] we set k to k/2; to move down the tree we 
 * set k to 2*k or 2*k+1.
 * The structure we are using in this solution (Start at array position 1, ignore position 0) match this representation
 * e.g
 * 0 1 2 3 4 5 6 7 8 9 10 11
 *   X 
 *     T S 
 *         P L R A 
 *                 M O E E
 * 
 * X is parent of T, S
 * T is parent of P, L  |  S is parent of R, A
 * P is parent of M, O  |  L is parent of E, E
 * 
 * Heapsort. 
 * We can use any priority queue to develop a sorting method. We insert all the keys to be sorted 
 * into a minimum-oriented priority queue, then repeatedly use remove the minimum to remove them all in order. 
 * When using a heap for the priority queue, we obtain heapsort.
 * Focusing on the task of sorting, we abandon the notion of hiding the heap representation of the priority 
 * queue and use swim() and sink() directly. Doing so allows us to sort an array without needing any extra 
 * space, by maintaining the heap within the array to be sorted. Heapsort breaks into two phases: heap construction, 
 * where we reorganize the original array into a heap, and the sortdown, where we pull the items out of the heap 
 * in decreasing order to build the sorted result.
 * 
 * Heap construction. 
 * We can accomplish this task in time proportional to N lg N, by proceeding from left to 
 * right through the array, using swim() to ensure that the entries to the left of the scanning pointer make 
 * up a heap-ordered complete tree, like successive priority queue insertions. A clever method that is much 
 * more efficient is to proceed from right to left, using sink() to make subheaps as we go. Every position 
 * in the array is the root of a small subheap; sink() works or such subheaps, as well. If the two children 
 * of a node are heaps, then calling sink() on that node makes the subtree rooted there a heap.
 * 
 * Sortdown. 
 * Most of the work during heapsort is done during the second phase, where we remove the largest remaining 
 * items from the heap and put it into the array position vacated as the heap shrinks.
 */
public class HeapSort {
	public static void sort(Comparable[] pq) {
		// Build the heap from smallest subheap (parent position at n/2 if valid index 
		// start from 1 in array, at n/2 - 1 if valid index start from 0 in array),
		// rearrange the array (position 0 not used)
		int n = pq.length;
		for(int k = n / 2; k >= 1; k--) {
			sink(pq, k, n);
		}
		// Sort down
		while(n > 1) {
			// At this point, the largest item is stored at the root of the heap. 
			// Replace it with the last item of the heap followed by reducing the 
			// size of heap by 1. Finally, heapify from root of tree each iteration.
			exch(pq, 1, n--);
			sink(pq, 1, n);
		}
	}
	
	// Proceed from right to left, using sink() to make subheaps.
	// Every position in the array is the root of a small subheap.
	public static void sink(Comparable[] pq, int k, int n) {
		while(2 * k <= n) {
			int j = 2 * k;
			// Find the larger one in two children
			if(j < n && less(pq, j, j + 1)) {
				j++;
			}
			// Compare the parent node with larger child
			// If pq[k - 1] > pq[j - 1], then break as
			// it satisfy the rule of heap(parent larger
			// two children), else need to exchange parent
			// and larger child position and assign j to k
			// for next loop
			if(!less(pq, k, j)) {
				break;
			}
			exch(pq, k, j);
			// Set k to j (2 * k) which prepare sequence
			// comparison happen on chain, because original
			// parent at position k exchange to position j,
			// need trace on possible comparison between
			// original parent (position = 2k) and 
			// new children (position = 4k/4k + 1)
			k = j;
		}
	}
	
	public static void exch(Object[] pq, int i, int j) {
		Object swap = pq[i - 1];
		pq[i - 1] = pq[j - 1];
		pq[j - 1] = swap;
	}
	
	// Helper function for comparisons and swaps,
	// indices are "off-by-one" to support 1-based indexing
	public static boolean less(Comparable[] pq, int i, int j) {
		return pq[i - 1].compareTo(pq[j - 1]) < 0;
	}
	
	public static void show(Comparable[] a) {
		for(int i = 0; i < a.length; i++) {
			StdOut.print(a[i]);
		}
	}
	
	public static void main(String[] args) {
		String[] a = {"S", "O", "R", "T", "E", "X", "A", "M", "P", "L", "E"};
		sort(a);
		show(a);
	}
}

// Solution 2: Start at array position 0
/**
 * Refer to
 * http://algs4.cs.princeton.edu/24pq/
 * http://quiz.geeksforgeeks.org/heap-sort/
 */
public class HeapSort {
	public static void sort(Comparable[] pq) {
		int n = pq.length;
		for(int k = n/2 - 1; k >= 0; k--) {
			sink(pq, k, n);
		}
		// For debug to compare whether after heaplify,
		// the heap constructed successful (as same as
		// princeton version)
		show(pq);
		// This step is critical, also refer to
		// http://quiz.geeksforgeeks.org/heap-sort/
		// if not apply "-1" before while loop, we
		// can not handle array index start from 0
		// end at (n - 1).
		n = n - 1;
		while(n > 0) {			
			exch(pq, 0, n--);
			sink(pq, 0, n);
		}
	}
	
	public static void exch(Comparable[] pq, int i, int j) {
		Comparable swap = pq[i];
		pq[i] = pq[j];
		pq[j] = swap;
	}
	
	public static boolean less(Comparable[] pq, int i, int j) {
		return pq[i].compareTo(pq[j]) < 0;
	}
	
	public static void sink(Comparable[] pq, int k, int n) {
		// The condition change from k <= n/2 to k <= n/2 - 1
		// which suitable for start index at 0. This condition
		// actually should match the 1st condition used for
		// construct heap in for loop (int k = n/2 - 1), here
		// we just add additional "<"
		while(k <= n/2 - 1) {
			// The calculation of j is a bigger change than array
			// index start from 1, if the parent index is k in
			// array, the children indexes are 2k and 2k + 1
			// Now as we change to index start from 0, refer to
			// http://quiz.geeksforgeeks.org/heap-sort/
			// if the parent index is k in array, the children
			// indexes are 2k + 1 and 2k + 2
			int j = 2 * k + 1;
			if(j < n - 1 && less(pq, j, j + 1)) {
				j++;
			}
			if(!less(pq, k, j)) {
				break;
			}
			exch(pq, k, j);
			k = j;
		}
	}
	
	public static void show(Comparable[] a) {
		for(int i = 0; i < a.length; i++) {
			StdOut.print(a[i]);
		}
		StdOut.println("");
	}
	
	public static void main(String[] args) {
//		String[] a = {"S", "O", "R", "T", "E", "X", "A", "M", "P", "L", "E"};
		String[] a = {"bed", "bug", "dad", "yes", "zoo",
					  "now", "for", "tip", "ilk", "dim", 
                      "tag", "jot", "sob", "nob", "sky",
                      "hut", "men", "egg", "few", "jay",
                      "owl", "joy", "rap", "gig", "wee",
                      "was", "wad", "fee", "tap", "tar",
                      "dug", "jam", "all", "bad", "yet"};
		sort(a);
		show(a);
	}
}
