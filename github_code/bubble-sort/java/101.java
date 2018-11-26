/**
 * 
 */
package com.learning.basic.sort;

/**
 * @author viap
 * 
 */
public class BubbleSort {

	public int nElement;

	public long[] arrLong;

	BubbleSort(int size) {
		arrLong = new long[size];
		nElement = 0;
	}

	public void insert(int value) {
		arrLong[nElement] = value;
		nElement++;
	}

	public void display() {
		for (int i = 0; i < arrLong.length; i++)
			if (arrLong[i] != 0)
				System.out.println("Values : " + arrLong[i]);
	}

	public void sortValue() {
		int in, out;

		for (out = nElement - 1; out > 0; out--) {
			for (in = 0; in < out; in++) {
				if (arrLong[in] < arrLong[in + 1])
					swap(in, in + 1);
			}
		}
	}

	public void swap(int one, int two) {
		long temp = arrLong[one];
		arrLong[one] = arrLong[two];
		arrLong[two] = temp;
	}

	public void reverse() {
		for (int i = nElement - 1; i >= 0; i--) {
			System.out.println("Reverse Value : " + arrLong[i]);
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int max = 7;

		BubbleSort bubbleSort = new BubbleSort(max);

		bubbleSort.insert(10);
		bubbleSort.insert(40);
		bubbleSort.insert(30);
		bubbleSort.insert(50);
		bubbleSort.insert(20);

		bubbleSort.sortValue();
		System.out.println("After sorting");
		bubbleSort.display();

		System.out.println("Reverse sorting");
		bubbleSort.reverse();

	}
}
