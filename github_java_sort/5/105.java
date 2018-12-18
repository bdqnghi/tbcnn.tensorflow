package edu.wmich.cs3310.MPeter.hw2;


public class ArraySort<T extends Comparable<T>> implements IArraySort<T> {
	
	private Comparable<T>[] tempArr;	
	
	
	@SuppressWarnings("unchecked")
	public ArraySort(int size) {
		tempArr = new Comparable[size];
	}
	
	
	public void bubbleSort(T[] values) {
		for (int i = (values.length - 1); i > 0; i--) {
			for (int j = 0; j < i; j++) {
				
				if (values[j].compareTo(values[j + 1]) > 0) {
					T temp = values[j];
					values[j] = values[j + 1];
					values[j + 1] = temp;
				}
			}
		}
	}

	
	@SuppressWarnings("unchecked")
	public void mergeSort(T[] values, int first, int last) {
		
		if (first < last) {
			int middle = (first + last) / 2;
			
			
			mergeSort(values, first, middle);
			mergeSort(values, (middle + 1), last);
			
			int leftPos = first;
			int rightPos = middle + 1;
			int pos = first;
			
			
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
			
			
			for (int i = first; i <= last; i++) {
				values[i] = (T)tempArr[i];
			}
					
		}
	}
	
	
	public void quickSort(T[] values, int first, int last) {
		int lower = first;
		int upper = last;
		
		T pivot = values[(first + last) / 2];
		
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
		
		
		if (first < upper) {
			quickSort(values, first, upper);
		}
		if (lower < last) {
			quickSort(values, lower, last);
		}
	}
	
	
	public void insertionSort(T[] values) {
		for (int i = 1; i < values.length; i++) {
			for (int j = i; j > 0; j--) {
				
				if (values[j].compareTo(values[j - 1]) < 0) {
					T temp = values[j];
					values[j] = values[j - 1];
					values[j - 1] = temp;
				} else {
				
					break;
				}
			}
		}
	}
	
	
	public void selectionSort(T[] values) {
		for (int i = 0; i < (values.length - 1); i++) {
			T lowest = values[i];
			int lowestPos = i;
			for (int j = i; j < values.length; j++) {
				
				if (values[j].compareTo(lowest) < 0) {
					lowest = values[j];
					lowestPos = j;
				}
			}
			
			T temp = values[i];
			values[i] = lowest;
			values[lowestPos] = temp;
		}
	}
}
