/*
 * Renee Ti Chou
 */
/**
 * <code>Heapsort</code> utilizes a binary heap structure to sort data. The time
 * complexity is O(n logn) for best, worst, and average cases.
 * <p>
 * The code is rewritten according to the algorithm provided in the lecture
 * material on Sorting. The <code>insert</code> and <code>delete</code> methods
 * are borrowed from the class <code>PriorityQueue</code> of my last Lab3 source
 * code.
 */
public class Heapsort {

	/**
	 * This method sorts the input array in ascending order.
	 * 
	 * @param arr
	 *            the int array to be sorted
	 * @return the elapsed time for sorting
	 */
	public long sort(int arr[]) {
		long time1, time2;
		int n = arr.length;

		time1 = System.nanoTime();

		/* Build heap */
		for (int i = 1; i < n; i++)
			insert(arr, i);

		/* Make sorted list */
		for (int j = n - 1; j >= 0; j--)
			delete(arr, j);
		time2 = System.nanoTime();

		return (time2 - time1);
	}

	/**
	 * Exchange the two elements in an array.
	 * 
	 * @param arr
	 *            the int array
	 * @param i
	 *            the index of the element
	 * @param j
	 *            the index of the other element
	 */
	private void swap(int[] arr, int i, int j) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

	/**
	 * This private method is used to build the heap.
	 * 
	 * @param arr
	 *            the int array
	 * @param i
	 *            the index of the element to be inserted into the heap
	 */
	private void insert(int arr[], int i) {
		int parent;
		while (i > 0) {
			if (i % 2 == 0)
				parent = i / 2 - 1;
			else
				parent = i / 2;

			/* Heapify */
			if (arr[parent] < arr[i]) {
				swap(arr, parent, i);
				i = parent;
			}
			else
				break;
		} // end while
	}

	/**
	 * This private method extract the largest element from the heap, put it to
	 * the sorted list and reheap the heap.
	 * 
	 * @param arr
	 *            the int array
	 * @param l
	 *            the index of the last element of the heap
	 */
	private void delete(int arr[], int l) {
		int parent, largest, left, right;
		swap(arr, 0, l); // delete the largest element

		/* Heapify */
		largest = 0; // the root node
		parent = largest;
		while (largest <= l / 2 - 1) {
			left = largest * 2 + 1;
			right = left + 1;

			/*
			 * The idea of this piece of code is from:
			 * http://quiz.geeksforgeeks.org/heap-sort/
			 */
			if (left < l && arr[left] > arr[largest])
				largest = left;
			if (right < l && arr[right] > arr[largest])
				largest = right;

			if (largest != parent) {
				swap(arr, largest, parent);
				parent = largest;
				continue;
			}
			else
				break;
		} // end while
	} // end delete
}
