package algorithms.sort;

public class BucketSort {
	public static void bucketSort(int[] array) {
		bucketSort(array, 99);
	}
	
	
    public static void bucketSort(int[] array, int maxVal) {
        int[] bucket = new int[maxVal + 1];			

        
        for (int i = 0; i < array.length; i++)
            bucket[array[i]]++;

        int outPos = 0;
        for (int i = 0; i < bucket.length; i++) { 
        	if (bucket[i] > 0)
            	array[outPos++] = i;
        }
    }
}
