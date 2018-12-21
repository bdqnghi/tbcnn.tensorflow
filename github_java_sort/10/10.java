package net.tanpeng.arithmetic.arithmetic4.sort;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


public class Bucket {
    public static void main(String[] args) {
        int[] a = new int[]{5, 2, 4, 6, 7};
        bucketSort(a);
        for (int i : a) {
            System.out.println(i);
        }
    }

    public static void bucketSort(int[] a) {
        int n = a.length;
        
        List<List<Integer>> bucket = new ArrayList<>();
        
        for (int i = 0; i < n; i++) {
            bucket.add(new ArrayList<>());
        }

        
        for (int i = 0; i < n; i++) {
            bucket.get(f(i)).add(a[i]);
        }

        
        for (int i = 0; i < bucket.size(); i++) {
            if (!bucket.get(i).isEmpty())
                Collections.sort(bucket.get(i)); 
        }

        
        int k = 0;
        for (int i = 0; i < bucket.size(); i++) {
            for (int item : bucket.get(i)) {
                a[k++] = item;
            }
        }
    }

    private static int f(int x) {
        return x / 10;
    }


}
