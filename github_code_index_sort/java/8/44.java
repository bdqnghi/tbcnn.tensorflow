package coursera.algorithms.course1.week3;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;


public class QuickSortJava {

    static int counter;

    public static void main(String... args) throws IOException {
//        int[] a = {3, 8, 2, 5, 1, 4, 7, 6};
//        quickSort(a, 0, a.length - 1);
//        System.out.println(Arrays.toString(a));

        File f = new File("src/main/resources/algorithms/quicksort.txt");

        System.out.println(f.getAbsolutePath() + " : " + f.exists());

        int[] a = loadInputArray(f);
        System.out.println(a.length);
        quickSort(a);
        System.out.println(Arrays.toString(a));
        System.out.println(counter);
    }

    private static int[] loadInputArray(File file) throws IOException {
        List<Integer> list = Files.lines(file.toPath())
                .map(String::trim)
                .filter(s -> !"".equals(s))
                .map(Integer::parseInt)
                .collect(Collectors.toList());

        int[] res = new int[list.size()];
        for (int i = 0; i < res.length; i++) {
            res[i] = list.get(i);
        }
        return res;
    }


    public static void quickSort(int[] a) {
        counter = 0;
        quickSort(a, 0, a.length - 1);
    }

    public static void quickSort(int[] a, int begin, int end) {

        if (end - begin <= 1) return;

        counter += (end - begin);
        int pivotIndex = partition(a, begin, end);

        quickSort(a, begin, pivotIndex - 1);
        quickSort(a, pivotIndex + 1, end);
    }


    public static int partition(int[] a, int l, int r) {
        int p = a[l];
        int i = l + 1;
        for (int j = l + 1; j <= r; j++) {
            if (a[j] < p) {
                swap(a, j, i);
                i++;
            }
        }

        int newPivotIndex = i - 1;
        swap(a, l, newPivotIndex);
        return newPivotIndex;
    }

    private static void swap(int[] a, int i, int j) {
        int buf = a[i];
        a[i] = a[j];
        a[j] = buf;
    }


}
