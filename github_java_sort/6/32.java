
package search_sort;

public class RadixSort {
    public int[] countSort(int[] data, int exp, int b) {
        int[] output = new int[data.length];
        int[] count = new int[b];
        for (int i = 0; i < data.length; i++) {
            count[(data[i] / exp) % b]++;
        }
        for (int i = 1; i < b; i++) {
            count[i] += count[i - 1];
        }
        for (int i = data.length - 1; i >= 0; i--) {
            output[count[(data[i] / exp) % b] - 1] = data[i];
            count[(data[i] / exp) % b]--;
        }
        return output;
    }

    public int[] radixSort(int[] data, int b) {
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < data.length; i++) {
            max = Math.max(max, data[i]);
        }
        for (int exp = 1; max / exp > 0; exp *= b) {
            data = countSort(data, exp, b);
        }
        return data;
    }

    public static void main(String[] args) {
        RadixSort test = new RadixSort();
        int[] output = test.radixSort(new int[] { 170, 45, 75, 82, 24, 0, 66 }, 6);
        for (int i = 0; i < output.length; i++) {
            System.out.println(output[i]);
        }
    }
}
