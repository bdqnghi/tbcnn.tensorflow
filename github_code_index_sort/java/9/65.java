import java.util.Arrays;

public class Sort_SelectionSort {
    public static void main(String[] args) {

        // Алгоритъмът намира най-малкия елемент в списъка
        // и го разменя с първия елемент.
        // Работи бързо, когато масивът е сортиран или почти сортиран.

        int [] array = {3, 144, 1, -33, 4, 0, 9, 25, 4, 1};
        SelectionSort(array);

        System.out.println(Arrays.toString(array));;
    }
    public static void SelectionSort(int[] array) {
        for (int i = 0; i < array.length; i++) {
            int min = array[i];
            int minIndex = i;
            for (int j = i; j < array.length; j++) {
                if (array[j] < array[minIndex]) {
                    min = array[j];
                    minIndex = j;
                }
            }
            swap(array, i, minIndex);
        }
    }
    public static void swap(int[] array, int ind1, int ind2) {
        int temp = array[ind1];
        array[ind1] = array[ind2];
        array[ind2] = temp;
    }
}