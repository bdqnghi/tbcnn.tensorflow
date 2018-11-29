package sort;

public class RadixSort {

	private static void sort(int[] data) {
		// get the maximum
		int max = 0;
		for (int i = 0; i < data.length; i++) {
			if (data[i] > max) {
				max = data[i];
			}
		}

		// get the check time
		int time = 0;
		while (max > 0) {
			max = max / 10;
			time++;
		}

		int radix = 10;

		// represents which fen wei is checking
		for (int i = 0; i < time; i++) {

			// count the fen wei key of each element in the bucket
			int[] buckets = new int[radix];
			for (int j = 0; j < data.length; j++) {
				int key = (data[j] / (int) Math.pow(10, i)) % radix;
				buckets[key]++;
			}

			int[] count = new int[buckets.length];

			// record which position it should be put it the bucket
			for (int k = 1; k < buckets.length; k++) {
				count[k] = count[k - 1] + buckets[k - 1];
			}

			// loop the origin data array, and put each element in the right
			// place of a temp array

			int[] temp = new int[data.length];

			for (int j = 0; j < data.length; j++) {
				int key = (data[j] / (int) Math.pow(10, i)) % radix;
				int position = count[key];
				count[key]++;
				temp[position] = data[j];
			}

			for (int j = 0; j < data.length; j++) {
				data[j] = temp[j];
			}
		}
	}

	private static void LSDsort(int[] data) {
		// get the maximum of the array
		int max = 0;
		for (int i = 0; i < data.length; i++) {
			if (data[i] > max) {
				max = data[i];
			}
		}

		// get the check time
		int time = 0;
		while (max > 0) {
			max = max / 10;
			time++;
		}

		// set the radix, represents the buckets number
		int radix = 10;

		/**
		 * represents which fen wei is checking, it is lsd, so it goes from
		 * right to left
		 */
		for (int i = 0; i < time; i++) {
			// count the fen wei key of each element in the bucket
			/**
			 * In this process, we make the buckets number is one greater than
			 * the radix,and the key should be put one greater in the bucket,
			 * eg. 10 check the first fenwei which is 0, then it should be put
			 * into the number 1 bucket
			 */
			int[] buckets = new int[radix + 1];
			// check every element in the array, and put them into the right
			// bucket and then reset the number of elements in the bucket
			for (int j = 0; j < data.length; j++) {
				int key = (data[j] / (int) Math.pow(10, i)) % radix;
				buckets[key + 1]++;
			}

			/**
			 * record the cumulates of each. eg.bucket[0]=0, bucket[1]=2,
			 * bucket[3]=3, then after this process, the bucket[1]=2,
			 * bucket[3]=5 ..., here means which first position of each bucket
			 * should be put
			 */
			for (int k = 1; k < buckets.length; k++) {
				buckets[k] = buckets[k] + buckets[k - 1];
			}

			// make a temp array to store this fen wei check result
			int[] temp = new int[data.length];

			// loop the origin data array, and put each element in the right
			// place of a temp array
			/**
			 * now the bucket stores the first position should be put for its
			 * radix
			 */
			for (int j = 0; j < data.length; j++) {
				int key = (data[j] / (int) Math.pow(10, i)) % radix;
				int position = buckets[key]++;
				temp[position] = data[j];
			}

			// put the data back to the origin array as this sort order
			for (int j = 0; j < data.length; j++) {
				data[j] = temp[j];
			}
		}
	}

	private static void MSDsort(int[] data) {
		// get the maximum
		int max = 0;
		for (int i = 0; i < data.length; i++) {
			if (data[i] > max) {
				max = data[i];
			}
		}

		// get the check time
		int time = 0;
		while (max > 0) {
			max = max / 10;
			time++;
		}

		int radix = 10;

		// represents which fen wei is checking
		for (int i = 0; i < time; i++) {

			// count the fen wei key of each element in the bucket
			int[] buckets = new int[radix + 1];
			for (int j = 0; j < data.length; j++) {
				int key = (data[j] / (int) Math.pow(10, i)) % radix;
				buckets[key + 1]++;
			}

			// record which position it should be put it the bucket
			for (int k = 1; k < buckets.length; k++) {
				buckets[k] = buckets[k] + buckets[k - 1];
			}

			// loop the origin data array, and put each element in the right
			// place of a temp array

			int[] temp = new int[data.length];

			for (int j = 0; j < data.length; j++) {
				int key = (data[j] / (int) Math.pow(10, i)) % radix;
				int position = buckets[key]++;
				temp[position] = data[j];
			}

			// put the data back to the origin array as this sort order
			for (int j = 0; j < data.length; j++) {
				data[j] = temp[j];
			}
		}
	}

	public static void main(String[] args) {
		int[] a = new int[] { 1, 2, 4, 12, 4, 6, 2, 1, 3, 7743, 2, 0 };
		RadixSort.LSDsort(a);
		for (int i = 0; i < a.length; i++) {

			System.out.print(a[i] + " ");
		}

	}

}
