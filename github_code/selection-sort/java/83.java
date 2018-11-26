package PukyungUniv;

import static org.junit.Assert.assertEquals;

import java.util.Arrays;

import org.junit.Test;

public class Sort_SelectionSort {

    @Test
    public void test() {
        int[] data = { 1, 3, 5, 7, 2, 4, 6, 8 };
        Sort_SelectionSort.sort(data);
        assertEquals(Arrays.toString(new int[] { 1, 2, 3, 4, 5, 6, 7, 8 }), Arrays.toString(data));
    }
    
    public static void sort(int[] data) {
        for (int k = data.length - 1; k > 0; k--) {
            int largestIdx = 0;
            for (int i = 0; i <= k; i++) {
                if (data[i] > data[largestIdx]) {
                    largestIdx = i;
                }
            }
            int tmp = data[k];
            data[k] = data[largestIdx];
            data[largestIdx] = tmp;
        }
    }

}
