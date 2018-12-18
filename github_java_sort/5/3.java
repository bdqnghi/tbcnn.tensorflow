package chapter07;



import java.util.Arrays;

public class BubbleSort {
    public static void main(String[] args) {
        double[] numbers = {4, 7, 10, 56, 2, 1, 6, 120, 30, 45, 80};
        System.out.println(isSorted(numbers));
        sort(numbers);
        System.out.println(isSorted(numbers));
        System.out.println(Arrays.toString(numbers));
    }

    public static void sort(double... array) {
        boolean wasChanged = false;
        do {
            wasChanged = false;
            for (int i = 1; i < array.length; i++) {
                if (array[i - 1] > array[i]) {
                    swapElements(i -1, i, array);
                    wasChanged = true;
                }
            }
        } while (wasChanged);
    }

    public static void swapElements(int i, int j, double... array) {
        double temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    public static boolean isSorted(double... array) {
        for (int i = 0; i < array.length - 1; i++) {
            if (array[i] > array[i + 1])
                return false;
        }

        return true;
    }
}
