package algo.sort;

import utils.Utility;

/**
 * <b>Insertion sort</b> is another simple to understand sorting algorithm with almost same complexity
 * of <code>O (n ^ 2)</code> as Bubble sort and Selection sort, but has better performance.
 * <p>
 * Here I have written 2 implementation of insertion sort algorithm
 * <ul>
 * <li> <code>sort1(..)</code> method is written, referring from "Algorithms 4th edition" book.
 * <li> <code>sort2(..)</code> method is widely available implementation of the algorithm across the internet, such as geeksforgeeks.com etc.
 * </ul>
 * <p>
 * Here is the <a href="https://www.khanacademy.org/computing/computer-science/algorithms/insertion-sort/a/insertion-sort">best article</a> explaining how insertion sort works
 * 
 * 
 * @author santhosh
 *
 */
public class InsertionSort {

	/**
	 * Here we start with <code>i=1</code> and go on scanning next elements in the array until we reach end of the array. 
	 * The <code>j</code> pointer will be initialized with <code>i</code>, then the elements in position <code>j</code> is compared with the element in its immediate left (<code>j-1</code> ).
	 * if element at <code>j</code> is less, then it is swapped with element at <code>j-1</code>, and <code>j</code> is decremented. 
	 * 
	 * @param arr - The array to be sorted
	 */
	public void sort1(int[] arr) {
		int n = arr.length;
		for(int i=1; i<n;  i++) {
			for(int j=i; j>0 && arr[j] < arr[j-1]; j--) {
				Utility.swap(arr, j, j-1);
			}
		}
	}
	
	/**
	 * In this method, we start with the 2nd element from the left of the array (which is index 1). We call this element <code>key</code>.
	 * We compare <code>key</code> with all the elements on the left of it <code>arr[j]</code>,  and move them 1 position to the right if
	 * we find <code>key < arr[j]</code>. Finally, when we get an element <code>arr[j]</code> such that <code>arr[j] > key</code>, then we
	 * copy <code>key</code> to the next position, that is <code>j+1</code> and proceed further. 
	 * 
	 * @param arr
	 */
	public void sort2(int[] arr) {
		int n = arr.length;
		for(int i=1; i<n; i++) {
			int key = arr[i];
			int j = i-1;
			while(j >= 0 && key < arr[j]) {
				arr[j+1] = arr[j];
				j--;
			}
			arr[j+1] = key;
		}
	}

}
