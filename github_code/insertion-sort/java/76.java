import java.util.Arrays;

public class Sort_InsertionSort {
    public static void main(String[] args) {

        // Относително ефективен при малки и почти сортирани списъци
        // Взема всеки елемент един по-един от списъка и го вмъква на
        // съответното си място в нов сортиран списък.

        int[] array = {13, 4, 1, 2, 0, 16, 8, -3, -6};

        InsertionSort(array);
        System.out.println(Arrays.toString(array));

    }
    public static void InsertionSort(int[] array) {
        for (int i = 1; i < array.length; i++) {
            for (int j = i; j > 0; j--) {
                if (array[j] < array[j - 1]) {
                    swap(array, j, j - 1);
                } else
                    break;
            }
        }
    }
    public static void swap(int[] array, int ind1, int ind2) {
        int temp = array[ind1];
        array[ind1] = array[ind2];
        array[ind2] = temp;
    }
}