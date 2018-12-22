package sortsAndSearches;

import java.util.Arrays;
import java.util.PriorityQueue;

public class BucketSort {

    public static void main(String[] args) {
        int[] input1 = {};
        int[] input2 = {1};
        int[] input3 = {2 , 1};
        int[] input4 = {6, 7 ,2,4,3, 1, 1, 6};
        int[] input5 = {111, 1 , 43, 2 , 5, 7, 0 , -3 , 6, 7 ,2,4 , -7,3, 1, 13 , 1, 6};
        bucketSort(input1);
        bucketSort(input2);
        bucketSort(input3);
        bucketSort(input4);
        bucketSort(input5);
        System.out.println(Arrays.toString(input1));
        System.out.println(Arrays.toString(input2));
        System.out.println(Arrays.toString(input3));
        System.out.println(Arrays.toString(input4));
        System.out.println(Arrays.toString(input5));
    }

    
    
    private static void bucketSort(int[] list) {
        int max = 0;

        
        
        for(int i = 0; i < list.length; i++) {
            max = Math.max(max , list[i]);
        }
        int bucketIncrement = (int)Math.pow(10 , String.valueOf(max).length() - 1);

        
        PriorityQueue<Integer>[] buckets = new PriorityQueue[10];

        
        for(int i = 0; i < list.length; i++) {
            int tempIndex = list[i] / bucketIncrement;
            if(buckets[tempIndex] == null) {
                buckets[tempIndex] = new PriorityQueue<>();
            }
            buckets[tempIndex].add(list[i]);
        }

        
        
        int indexOfList = 0;
        for(int i = 0; i < buckets.length; i++) {
            if(buckets[i] != null) {
                while(!buckets[i].isEmpty()) {
                    list[indexOfList] = buckets[i].poll();
                    indexOfList++;
                }
            }
        }
    }
}
