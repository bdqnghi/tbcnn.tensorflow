
package org.burstsort4j;


public class Insertionsort {

    private Insertionsort() {
    }

    
    public static <T extends Comparable<? super T>> void sort(T[] arr) {
        if (arr != null) {
            sort(arr, 0, arr.length - 1);
        }
    }

    
    public static <T extends Comparable<? super T>> void sort(T[] arr, int low, int high) {
        if (arr == null || arr.length < 2 || low < 0 || high <= low) {
            return;
        }

        for (int i = low + 1; i <= high; i++) {
            T pivot = arr[i];
            int j = i;
            while (j > low && pivot.compareTo(arr[j - 1]) < 0) {
                arr[j] = arr[j - 1];
                j--;
            }
            arr[j] = pivot;
        }
    }

    
    public static void sort(CharSequence[] strings, int low, int high, int depth) {
        if (strings == null || low < 0 || high <= low || depth < 0) {
            return;
        }
        for (int i = low + 1; i < high; i++) {
            for (int j = i; j > low; j--) {
                int idx = depth;
                char s = idx < strings[j - 1].length() ? strings[j - 1].charAt(idx) : 0;
                char t = idx < strings[j].length() ? strings[j].charAt(idx) : 0;
                while (s == t && idx < strings[j - 1].length()) {
                    idx++;
                    s = idx < strings[j - 1].length() ? strings[j - 1].charAt(idx) : 0;
                    t = idx < strings[j].length() ? strings[j].charAt(idx) : 0;
                }
                if (s <= t) {
                    break;
                }
                CharSequence tmp = strings[j];
                strings[j] = strings[j - 1];
                strings[j - 1] = tmp;
            }
        }
    }
}
