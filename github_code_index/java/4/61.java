package Sorting;

import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigDecimal;
import java.util.Comparator;
import java.util.Scanner;

/**
 * Created by parker on 4/10/18.
 */
public class Insertion extends Sort{

    public void sort(Object[] a, Comparator comparator)
    {
        for (int i = 1; i < a.length; i++)
        {
            for (int j = i; j >= 1; j--)
            {
                if (less(comparator, a[j], a[j - 1]))
                {
                    exchange(a, j, j - 1);
                }
                else
                {
                    break;
                }
            }
        }
    }

    public static void main(String[] args) throws FileNotFoundException
    {
        Scanner scanner = new Scanner(new File(args[0]));
        int size = scanner.nextInt();
        Sort sort = new Insertion();

        System.out.println("Total Ints: " + size);

        Integer[] unsorted = new Integer[size];
        for (int i = 0; i < size && scanner.hasNextInt(); i++)
        {
            unsorted[i] = scanner.nextInt();
        }

        BigDecimal start = new BigDecimal(System.currentTimeMillis());
        sort.sort(unsorted);
        BigDecimal end = new BigDecimal(System.currentTimeMillis());

        BigDecimal time = (end.subtract(start).divide(new BigDecimal(1000)));
        System.out.println("Sort Time: " + time);
    }
}
