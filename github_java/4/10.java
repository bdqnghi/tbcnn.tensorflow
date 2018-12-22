package code.Kiran.algo;
/**
 * write a program to sort an array using insertion sort.
 * @author Kiran
 * description:Insertion sort iterates through the list by
 * consuming one input element at each repetition, and growing
 * a sorted output list. On a repetition, insertion sort 
 * removes one element from the input data, finds the location
 * it belongs within the sorted list, and inserts it there. 
 * It repeats until no input elements remain.
 */
public class Insertionsort {
	public static void main(String[] args) {
		int[] Array = { 10, 34, 2, 56, 7, 67, 88, 42 };
		insertsort(Array);
		for (int i : Array) {
			System.out.print(i);
		}
	}

	public static int[] insertsort(int[] Array) {

		int temp;
		for (int i = 1; i < Array.length; i++) {
			for (int j = i; j > 0; j--) {
				if (Array[j] < Array[j - 1]) {
					temp = Array[j];
					Array[j] = Array[j - 1];
					Array[j - 1] = temp;
				}
			}
		}
		return Array;
	}
}
