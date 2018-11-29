package johnny.dsa.sorting;

public class BucketSort {
    public void bucketSort(int[] nums) {
        if (nums == null || nums.length == 0) {
            return;
        }
        
        // get the max value
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > max) {
                max = nums[i];
            }
        }
        
        // create buckets
        int [] bucket = new int[max + 1];

        // initialize buckets
        for (int i = 0; i < bucket.length; i++) {
            bucket[i] = 0;
        }

        // increment bucket value by one if corresponding element is found
        for (int i = 0; i < nums.length; i++) {
            bucket[nums[i]]++;
        }

        // rebuild array from buckets
        int index = 0;
        for (int i = 0; i < bucket.length; i++) {
            for (int j = 0; j < bucket[i]; j++) {
                nums[index++] = i;
            }
        }
    }
    
    //http://www.geeksforgeeks.org/bucket-sort-2/
    //http://www.javacodex.com/Sorting/Bucket-Sort
}
