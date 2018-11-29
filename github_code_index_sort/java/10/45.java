package algorithms.sort;

public class BucketSort {
	public static void bucketSort(int[] array) {
		bucketSort(array, 99);
	}
	
	/*
	 * maxVal - maximum value in the array. For the test case array, the largest value is '99' so maxVal in this case is '99'
	 * note: the test data consists of only 10 digits, each separated by 11. This results in 100 buckets only which 10 are
	 *  filled. 
	 */
    public static void bucketSort(int[] array, int maxVal) {
        int[] bucket = new int[maxVal + 1];			// create an array the size of the largest value + 1

        // for every value in array, increment its corresponding bucket
        for (int i = 0; i < array.length; i++)
            bucket[array[i]]++;

        int outPos = 0;
        for (int i = 0; i < bucket.length; i++) { 
        	if (bucket[i] > 0)
            	array[outPos++] = i;
        }
    }
}
