package edu.wmich.cs3310.MPeter.hw2;

/**
 * This class is used to sort arrays with a variety of sorting
 * methods, including: Bubble-Sort, Merge-Sort, Quick-Sort,
 * Insertion-Sort, Built-In-Sort, and Selection-Sort.
 *
 * @param <T> Type of array to be sorted
 */
public class ArraySort<T extends Comparable<T>> implements IArraySort<T> {
	// Attributes
	private Comparable<T>[] tempArr;	// Temporary array used in merge-sort
	
	/**
	 * This constructor is simply used to set the size of the
	 * temporary array that is used in merge-sorting.
	 * @param size Size of array being sorted
	 */
	@SuppressWarnings("unchecked")
	public ArraySort(int size) {
		tempArr = new Comparable[size];
	}
	
	/**
	 * This method sorts a passed array using a bubble-sort
	 * sorting method.
	 * @param values Array of values of type T
	 */
	public void bubbleSort(T[] values) {
		for (int i = (values.length - 1); i > 0; i--) {
			for (int j = 0; j < i; j++) {
				// If one value is greater than the next, swap them
				if (values[j].compareTo(values[j + 1]) > 0) {
					T temp = values[j];
					values[j] = values[j + 1];
					values[j + 1] = temp;
				}
			}
		}
	}

	/**
	 * This method sorts a passed array using a bubble-sort
	 * sorting method.
	 * @param values Array of values of type T
	 * @param first Position of first value being sorted
	 * @param last Position of last value being sorted
	 */
	@SuppressWarnings("unchecked")
	public void mergeSort(T[] values, int first, int last) {
		// If more than one value exists in this section of the array...
		if (first < last) {
			int middle = (first + last) / 2;
			
			// Recursively call mergeSort for first and second half
			mergeSort(values, first, middle);
			mergeSort(values, (middle + 1), last);
			
			int leftPos = first;
			int rightPos = middle + 1;
			int pos = first;
			
			// Put values in a temporary array in the correct order
			while ((leftPos <= middle) && (rightPos <= last)) {
				if (values[leftPos].compareTo(values[rightPos]) < 0) {
					tempArr[pos++] = values[leftPos++];
				} else {
					tempArr[pos++] = values[rightPos++];
				}
			}
			
			while (leftPos <= middle) {
				tempArr[pos++] = values[leftPos++];
			}
			
			while (rightPos <= last) {
				tempArr[pos++] = values[rightPos++];
			}
			
			// Transfer sorted values back to original array
			for (int i = first; i <= last; i++) {
				values[i] = (T)tempArr[i];
			}
					
		}
	}
	
	/**
	 * This method sorts a passed array using a quick-sort sorting
	 * method.
	 * @param values Array of values of type T
	 * @param first Position of first value being sorted
	 * @param last Position of last value being sorted
	 */
	public void quickSort(T[] values, int first, int last) {
		int lower = first;
		int upper = last;
		
		T pivot = values[(first + last) / 2];
		// Find two values that are on wrong sides of pivot and swap them
		while (lower <= upper) {
			while (values[lower].compareTo(pivot) < 0) {
				lower++;
			}
			
			while (values[upper].compareTo(pivot) > 0) {
				upper--;
			}
			
			if (lower <= upper) {
				T temp = values[lower];
				values[lower] = values[upper];
				values[upper] = temp;
				lower++;
				upper--;
			}
		}
		
		// Recursively call quickSort for sections above and below pivot value
		if (first < upper) {
			quickSort(values, first, upper);
		}
		if (lower < last) {
			quickSort(values, lower, last);
		}
	}
	
	/**
	 * This method sorts a passed array using an insertion-sort
	 * sorting method.
	 * @param values Array of values of type T
	 */
	public void insertionSort(T[] values) {
		for (int i = 1; i < values.length; i++) {
			for (int j = i; j > 0; j--) {
				// If one value is less than the previous, swap them
				if (values[j].compareTo(values[j - 1]) < 0) {
					T temp = values[j];
					values[j] = values[j - 1];
					values[j - 1] = temp;
				} else {
				// Break once correct position for value is found
					break;
				}
			}
		}
	}
	
	/**
	 * This method sorts a passed array using a selection-sort
	 * sorting method.
	 * @param values Array of values of type T
	 */
	public void selectionSort(T[] values) {
		for (int i = 0; i < (values.length - 1); i++) {
			T lowest = values[i];
			int lowestPos = i;
			for (int j = i; j < values.length; j++) {
				// If lower value than current lowest is found, replace it
				if (values[j].compareTo(lowest) < 0) {
					lowest = values[j];
					lowestPos = j;
				}
			}
			// Put the lowest value found in its proper position
			T temp = values[i];
			values[i] = lowest;
			values[lowestPos] = temp;
		}
	}
}
