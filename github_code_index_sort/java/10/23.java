package algorithm.sorting;

import java.util.Random;

public class BucketSort_I {

	public static int[] bucketsort(int[] a, int maxVal) {
		int[] bucket = new int[maxVal + 1];

		for (int i = 0; i < bucket.length; i++) {
			bucket[i] = 0;
		}

		for (int i = 0; i < a.length; i++) {
			bucket[a[i]]++;
		}

		int outPos = 0;
		for (int i = 0; i < bucket.length; i++) {
			for (int j = 0; j < bucket[i]; j++) {
				a[outPos++] = i;
			}
		}

		return a;
	}

	// printer
	static void printer(int[] sorted_sequence) {
		for (int i = 0; i < sorted_sequence.length; i++)
			System.out.print(sorted_sequence[i] + " ");
	}

	// max in array
	static int maxValue(int[] sequence) {
		int maxValue = 0;
		for (int i = 0; i < sequence.length; i++)
			if (sequence[i] > maxValue)
				maxValue = sequence[i];
		return maxValue;
	}

	public static void main(String args[]) {
		System.out.println("Sorting of randomly generated numbers using BUCKET SORT");
		Random random = new Random();
		int N = 20;
		int[] sequence = new int[N];

		for (int i = 0; i < N; i++)

			sequence[i] = Math.abs(random.nextInt(100));

		int maxValue = maxValue(sequence);

		System.out.println("\nOriginal Sequence: ");
		printer(sequence);

		System.out.println();

		System.out.println("\nSorted Sequence: ");
		printer(bucketsort(sequence, maxValue));
	}

	// http://www.growingwiththeweb.com/2015/06/bucket-sort.html

}
