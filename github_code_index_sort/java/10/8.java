package sort;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Created by screspi on 3/30/15.
 */
public final class Bucket {

    // count sort
    public static int[] sort(int[] input, int max) {
        int[] buckets = new int[max];

        for (int i : input) {
            buckets[i]++;
        }

        int[] result = new int[input.length];
        int counter = 0;
        for (int j = 0; j < buckets.length; j++) {
            for (int z = 1; z <= buckets[j]; z++) {
                result[counter++] = j;
            }
        }
        return result;
    }

    public static void sort(Integer[] array, int bucketSize) {
        if (array.length == 0) {
            return;
        }

        // Determine minimum and maximum values
        Integer minValue = array[0];
        Integer maxValue = array[0];
        for (int i = 1; i < array.length; i++) {
            if (array[i] < minValue) {
                minValue = array[i];
            } else if (array[i] > maxValue) {
                maxValue = array[i];
            }
        }

        // Initialise buckets
        int bucketCount = (maxValue - minValue) / bucketSize + 1;
        List<List<Integer>> buckets = new ArrayList<List<Integer>>(bucketCount);
        for (int i = 0; i < bucketCount; i++) {
            buckets.add(new ArrayList<Integer>());
        }

        // Distribute input array values into buckets
        for (int i = 0; i < array.length; i++) {
            buckets.get((array[i] - minValue) / bucketSize).add(array[i]);
        }

        // Sort buckets and place back into input array
        int currentIndex = 0;
        for (int i = 0; i < buckets.size(); i++) {
            Integer[] bucketArray = new Integer[buckets.get(i).size()];
            bucketArray = buckets.get(i).toArray(bucketArray);
            Arrays.sort(bucketArray);
            for (int j = 0; j < bucketArray.length; j++) {
                array[currentIndex++] = bucketArray[j];
            }
        }
    }

    public static void main(String... args) {
        int[] array = {4,5,2,7,3,6,6,8,9,1,0};
        System.out.println(Arrays.toString(array));

        System.out.println(Arrays.toString(sort(array,10)));
        Integer[] arrI = new Integer[]{4,5,2,7,3,6,6,8,9,1,0};
        sort(arrI, 3);
        System.out.println(Arrays.toString(arrI));
    }
}
