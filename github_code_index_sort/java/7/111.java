/**
 * http://en.wikipedia.org/wiki/Shellsort
 * http://www.sorting-algorithms.com/shell-sort
 * Shellsort is an in-place comparison sort. It can be seen as either a generalization
 * of sorting by exchange (bubble sort) or sorting by insertion (insertion sort). The
 * method starts by sorting elements far apart from each other and progressively
 * reducing the gap between them. Starting with far apart elements can move some
 * out-of-place elements into position faster than a simple nearest neighbor
 * exchange.
 * It is not stable but adaptive. Time complexity is O(n^(3/2))
 */
package main;

/**
 * @author yu
 * 
 */
public class ShellSort {
	public int[] sort(int num[]) {
		// gap length, that determines stubs
		int h = 1;
		// <O(n^(3/2)) by Knuth,1973>: 1, 4, 13, 40, 121, ...
		while (h < num.length / 3)
			h = h * 3 + 1;
		for (; h > 0; h /= 3) {
			// for each stub
			for (int k = 0; k < h; k++) {
				// insertion sort for every stub's elements
				for (int i = h + k; i < num.length; i += h) {
					int j = i;
					// use swap instead of move and insert
					while (j >= h && num[j] < num[j - h]) {
						swap(num, j, j - h);
						j -= h;
					}

				}
			}
		}

		return num;
	}

	// XOR swap without using temp integer
	private void swap(int arg[], int i, int j) {
		// when i=j it will be 0
		if (i != j) {
			arg[i] = arg[i] ^ arg[j];
			arg[j] = arg[j] ^ arg[i];
			arg[i] = arg[j] ^ arg[i];
		}
	}
}
