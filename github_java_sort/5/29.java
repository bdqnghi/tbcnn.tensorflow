import java.util.Scanner;

class TestClass {
    static void bubbleSort(int[] arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int index = n - 1; index >= i + 1; index--) {
                if (arr[index] < arr[index - 1]) {
                    int temp = arr[index];
                    arr[index] = arr[index - 1];
                    arr[index - 1] = temp;
                }
            }
        }
    }

    public static void main(String[] args) {
        int[] arr = {31, 41, 59, 26, 41, 58};
        bubbleSort(arr, arr.length);
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
    }
}