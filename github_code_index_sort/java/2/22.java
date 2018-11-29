package Sorting;

import java.io.File;
import java.io.FileNotFoundException;
import java.math.BigDecimal;
import java.util.Comparator;
import java.util.Scanner;

/**
 * Created by parker on 4/15/18.
 */
public class Merge extends Sort {

    public void sort(Object[] arr, Comparator comparator)
    {
        int low = 0;
        int high = arr.length - 1;

        Object[] aux = new Object[arr.length];

        sort(comparator, arr, aux, low, high);
    }

    private void sort(Comparator c, Object[] arr, Object[] aux, int low, int high)
    {
        if (high <= low)
        {
            return;
        }

        int mid = low + (high - low) / 2;
        sort(c, arr, aux, low, mid);
        sort(c, arr, aux, mid + 1, high);

        if (!less(c, arr[mid + 1], arr[mid]))
        {
            return;
        }

        merge(c, arr, aux, low, mid, high);
    }

    private void merge(Comparator c, Object[] arr, Object[] aux, int low, int mid, int high)
    {
        assert isSorted(c, arr, low, mid);
        assert isSorted(c, arr, mid + 1, high);

        for (int k = low; k <= high; k++)
        {
            aux[k] = arr[k];
        }

        int i = low;
        int j = mid + 1;

        for (int k = low; k <= high; k++)
        {
            if (i > mid)
            {
                arr[k] = aux[j++];
            }
            else if (j > high)
            {
                arr[k] = aux[i++];
            }
            else if (less(c, aux[j], aux[i]))
            {
                arr[k] = aux[j++];
            }
            else
            {
                arr[k] = aux[i++];
            }
        }

        assert isSorted(c, arr, low, high);
    }

    private Boolean isSorted(Comparator c, Object[] arr, int low, int high)
    {
        for (int i = low + 1; i <= high; i++)
        {
            if (less(c, arr[i], arr[i - 1]))
            {
                return false;
            }
        }

        return true;
    }

    public static void main(String[] args) throws FileNotFoundException
    {
        Scanner scanner = new Scanner(new File(args[0]));
        int size = scanner.nextInt();
        Merge merge = new Merge();

        System.out.println("Total Ints: " + size);

        Integer[] unsorted = new Integer[size];
        for (int i = 0; i < size && scanner.hasNextInt(); i++)
        {
            unsorted[i] = scanner.nextInt();
        }

        BigDecimal start = new BigDecimal(System.currentTimeMillis());
        merge.sort(unsorted);
        BigDecimal end = new BigDecimal(System.currentTimeMillis());

        BigDecimal time = (end.subtract(start).divide(new BigDecimal(1000)));
        System.out.println("Sort Time: " + time);
    }
}
