import java.util.Scanner;

class TestClass {
    static void selectionSort(int[] arr, int n) {
        for (int lower = 0; lower < n - 1; lower++) {
            int minIndex = lower, minElement = arr[lower];
            for (int index = lower + 1; index < n; index++) {
                if (arr[index] < minElement) {
                    minElement = arr[index];
                    minIndex = index;
                }
            }
            if (minIndex != lower) {
                int temp = arr[lower];
                arr[lower] = arr[minIndex];
                arr[minIndex] = temp;
            }
        }
    }

    public static void main(String[] args) {
        int[] arr = {31, 41, 59, 26, 41, 58};
        selectionSort(arr, arr.length);
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
    }
}