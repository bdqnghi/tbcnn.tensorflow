package Sorting;

import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigDecimal;
import java.util.Comparator;
import java.util.Scanner;

/**
 * Created by parker on 4/8/18.
 */
public class Selection extends Sort {

    public void sort(Object[] arr, Comparator comparator)
    {
        for (int i = 0; i < arr.length; i++)
        {
            int min = i;
            for (int j = i + 1; j < arr.length; j++)
            {
                if (less(comparator, arr[j], arr[min]))
                {
                    min = j;
                }
            }

            exchange(arr, i, min);
        }
    }

    public static void main(String[] args) throws FileNotFoundException
    {
        Scanner scanner = new Scanner(new File(args[0]));
        int size = scanner.nextInt();
        Selection selection = new Selection();

        System.out.println("Total Ints: " + size);

        Integer[] unsorted = new Integer[size];
        for (int i = 0; i < size && scanner.hasNextInt(); i++)
        {
            unsorted[i] = scanner.nextInt();
        }

        BigDecimal start = new BigDecimal(System.currentTimeMillis());
        selection.sort(unsorted);
        BigDecimal end = new BigDecimal(System.currentTimeMillis());

        BigDecimal time = (end.subtract(start).divide(new BigDecimal(1000)));
        System.out.println("Sort Time: " + time);
    }
}
