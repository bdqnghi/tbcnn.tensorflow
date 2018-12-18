
package LSDA_Assignment1;

import java.util.ArrayList;
import java.util.Collections;

public class bucketsort {


    public static int[] bucketSort ( int[] numbers, int bucketCount){

            if (numbers.length <= 1) return numbers;
            int maxVal = numbers[0];
            int minVal = numbers[0];

            for (int i = 1; i < numbers.length; i++) {
                if (numbers[i] > maxVal) maxVal = numbers[i];
                if (numbers[i] < minVal) minVal = numbers[i];
            }

            double interval = ((double) (maxVal - minVal + 1)) / bucketCount; 
            ArrayList<Integer> buckets[] = new ArrayList[bucketCount];

            for (int i = 0; i < bucketCount; i++) 
                buckets[i] = new ArrayList<Integer>();

            for (int i = 0; i < numbers.length; i++) 
                buckets[(int) ((numbers[i] - minVal) / interval)].add(numbers[i]);

            int k = 0;

            for (int i = 0; i < buckets.length; i++) {

                Collections.sort(buckets[i]); 

                for (int j = 0; j < buckets[i].size(); j++) { 
                    numbers[k] = buckets[i].get(j);
                    k++;
                }
            }

            return numbers;
        }



    static void printArray(int arr[])
    {
        for (int i=0; i<arr.length; i++)
            System.out.print(arr[i] + " ");
        System.out.println();
    }

    public static void main(String args[]) {

            int []numbers = {76,92,12,3,54,86,27,30,10,91,67,3,91,1,65,53,23,230,800,169} ; 

            int bucketCount = 10;
            System.out.println("Array before sort : " );
            printArray(numbers);
            int []arr = bucketSort(numbers,bucketCount);
            System.out.println("Array after Bucket sort");
            printArray(arr);

        }
}

