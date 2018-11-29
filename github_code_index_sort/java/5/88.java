package bubbleSort;

/** 
 * BubbleSort 
 * 
 * Version 1.1
 *  
 * Created 2016/04/10 and Updated 2016/04/26 
 * 
 * @author Renato Souto Maior 
 * 
 * Implementation of BubbleSort with For, While and DoWhlie.
 * 
 */ 

import java.util.Arrays;

public class BubbleSort {

	public static void main(String[] args) {

		BubbleSort sort = new BubbleSort();

		System.out.println("---- BubbleSort with For -----");
		int[] arrayBubbleFor = { 6, 7, 2, 4, 9, 1, 0, 5, 3, 8 };
		sort.bubbleSortFor(arrayBubbleFor);

		System.out.println("--- BubbleSort with While ----");
		int[] arrayBubbleWhile = { 6, 7, 2, 4, 9, 1, 0, 5, 3, 8 };
		sort.bubbleSortWhile(arrayBubbleWhile);

		System.out.println("-- BubbleSort with DoWhile ---");
		int[] arrayBubbleDoWhile = { 6, 7, 2, 4, 9, 1, 0, 5, 3, 8 };
		sort.bubbleSortDoWhile(arrayBubbleDoWhile);
		System.out.println("------------------------------");
	}

	// BubbleSort with For
	public void bubbleSortFor(int[] array) {

		System.out.println(Arrays.toString(array));
		int aux;

		for (int i = array.length; i > 0; i--) {
			for (int j = 0; j < i - 1; j++) {
				if (array[j] > array[j + 1]) {
					aux = array[j];
					array[j] = array[j + 1];
					array[j + 1] = aux;
				}
				System.out.println(Arrays.toString(array));
			}
		}
	}

	// BubbleSort with While
	public void bubbleSortWhile(int[] array) {

		System.out.println(Arrays.toString(array));
		int aux;
		int i = array.length;

		while (i > 0) {
			int j = 0;
			while (j < i - 1) {
				if (array[j] > array[j + 1]) {
					aux = array[j];
					array[j] = array[j + 1];
					array[j + 1] = aux;
				}
				j++;
				System.out.println(Arrays.toString(array));
			}
			i--;
		}
	}

	// BubbleSort with Do While
	public void bubbleSortDoWhile(int[] array) {

		System.out.println(Arrays.toString(array));
		int aux;
		int i = array.length;

		do {
			int j = 0;
			do {
				if (array[j] > array[j + 1]) {
					aux = array[j];
					array[j] = array[j + 1];
					array[j + 1] = aux;
				}
				j++;
				System.out.println(Arrays.toString(array));
			} while (j < (i - 1));
			i--;
		} while (i > 0);
	}
}
