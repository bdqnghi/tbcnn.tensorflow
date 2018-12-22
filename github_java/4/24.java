package sort;

/*
 * Insertion sort algorithm
 * Time complexity:
 * Average case, Worst case - O(n^2)
 * Best case - O(n)
 */
public class Insertionsort {
	private int[] arr;
	
	public Insertionsort(int[] a){
		this.arr = a;
		insertionSort(arr, arr.length);
		printArray(arr);
	}
	private void insertionSort(int[] a, int len) {
		/*
		 * Initially, elements till index 0 are considered sorted. Start from index 1
		 * Expand the sorted sub-set by inserting values from the unsorted sub-set.
		 * 
		 */
		for (int i = 1; i < len; i++) {
			int value = a[i];	//First element in the unsorted subset. This will be inserted to the sorted sub-set
			int position = i;	//Position of unsorted element
			
			/*
			 * Shift all values greater than the value to be inserted, 1 position to the right
			 * Loop will run until a value smaller than current value is found, or the position
			 * reaches 0, in which case the value to be inserted is the smallest.
			 */
			while (position > 0 && a[position-1] > value) {
				a[position] = a[position-1];	//Shift element 1 position to the right
				position--;						//Position to be inserted in is now 1 to the left
			}
			
			//Insert the value in the correct position
			a[position] = value;
		}
	}
	
	private void printArray(int[] a) {
		for (int i = 0; i < a.length; i++) {
			System.out.print(a[i] + " ");
		}
	}
	
	public static void main(String[] args) {
		int[]x = new int[]{7,2,1,9,6,8,5,3,4};

		Insertionsort is = new Insertionsort(x);
	}
}
