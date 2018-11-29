package org.gsu.cs.client;

import org.gsu.cs.sort.BitOperationsRadixSort;
import org.gsu.cs.util.SortUtil;

/**
 * Class to perform analysis on the best base for 2^2 to 2^32
 * 
 * @author vijay
 * 
 */
public class BestBaseRadixSortBitOperations {

	public BestBaseRadixSortBitOperations() {
		super();
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		int power = 1;
		int size = 0;
		int maxPower = 14;
		int noOfLoops = 20;

		// Loop to calculate the size to power of 14
		while (power < maxPower) {

			System.gc();
			size = (int) Math.pow(2.0, power);

			// running the raidx sort for bits of size base radix = 2^base

			for (int base = 2; base <= 32; base = base + 2) {

				long averageRadixSortTime = 0;
				int numberOfPasses = SortUtil.calculateNumberOfPasses(20000,
						base);

				for (int i = 0; i < noOfLoops; i++) {

					// We can run the program for random and also worst case
					// array by switching the comment
					int[] inputArray = SortUtil.generateRandomArray(size);
					// int[] inputArray = SortUtil.worstCaseArrayForSize(size);

					averageRadixSortTime += performRadixSortTrialRuns(size,
							inputArray, base, numberOfPasses);
					System.gc();

				}

				System.out.println(base + "\t" + averageRadixSortTime
						/ noOfLoops);
			}
			power++;
		}

	}

	/**
	 * Runs the radix sort with the ggiven input and returns the execution time
	 * in nano seconds
	 * 
	 * @param size
	 * @param inputArray
	 * @param base
	 * @param numberOfPasses
	 * @return
	 */
	private static long performRadixSortTrialRuns(int size, int[] inputArray,
			int base, int numberOfPasses) {
		long totalTimeForRadixSort = 0;
		long startTime = 0;
		long endTime = 0;

		System.gc();

		// int[] radixSortInputArray = SortUtil.copyArray(inputArray, size);

		startTime = System.nanoTime();
		BitOperationsRadixSort.performRadixSort(inputArray, base);
		endTime = System.nanoTime();

		totalTimeForRadixSort += endTime - startTime;

		return totalTimeForRadixSort;
	}

}
