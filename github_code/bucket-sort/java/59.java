package sort;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;

public class Bucket {

    /**
     * 桶排序
     *
     * @param array double array
     * @return sorted array
     */
    private static double[] bucketSort(double[] array) {
        double max = array[0];
        double min = array[0];
        for (int i = 1; i < array.length; i++) {
            if (array[i] > max) max = array[i];
            if (array[i] < min) min = array[i];
        }
        double d = max - min;

        int bucketNum = array.length;

        ArrayList<LinkedList<Double>> bucketList = new ArrayList<>(bucketNum);

        for (double ignored : array) bucketList.add(new LinkedList<>());
        for (double anArray : array) {
            int num = (int) ((anArray - min) * (bucketNum - 1) / d);
            bucketList.get(num).add(anArray);
        }
        bucketList.forEach(Collections::sort);

        double[] sortedArray = new double[array.length];
        int index = 0;

        for (LinkedList<Double> list : bucketList)
            for (double element : list) {
                sortedArray[index] = element;
                index++;
            }

        return sortedArray;
    }

    public static void main(String[] args) {
        double[] array = new double[]{4.12, 6.421, 0.0023, 3.0, 8.122, 4.12, 10.09};
        double[] sortedArray = bucketSort(array);
        System.out.println(Arrays.toString(sortedArray));
    }

}
