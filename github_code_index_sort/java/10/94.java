package sorting.noncomparison;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class BucketSort {

    public void sort(Double[] A) {

        int n = A.length;
        List[] B = new ArrayList[n];

        for (int i = 0; i < n; i++)
            B[i] = new ArrayList<>();

        for (int i = 0; i < n; i++)
            B[(int) Math.floor(n * A[i])].add(A[i]);

        for (List b : B)
            Collections.sort(b);

        int i = 0;
        for (List b : B)
            for (Object d : b)
                A[i++] = (Double) d;

    }

    public static void main(String... args) {

        Double[] numbers = {0.15, 0.84, 0.36, 0.99, 0.13, 0.34, 0.91, 0.51};
        BucketSort bucketSort = new BucketSort();
        bucketSort.sort(numbers);

        Arrays.asList(numbers).stream().forEach(System.out::println);

    }


}
