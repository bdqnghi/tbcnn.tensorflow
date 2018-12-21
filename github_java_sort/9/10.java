package sorting;

public class SelectionSort {

    private void selectionSort(int array[]) {

        for (int i = 0; i < array.length - 1; i++) {
            int min_index = i;
            for (int j = i + i; j < array.length; j++) {
                if (array[min_index] > array[j]) {
                    min_index = j;
                }
            }
            int temp = array[min_index];
            array[min_index] = array[i];
            array[i] = temp;
        }

    }

    private void printSortedArray(int arr[]) {
        for (int anArr : arr) {
            System.out.print(anArr + " ");
        }
    }

    public static void main(String[] args) {
        SelectionSort selectionSort = new SelectionSort();
        int[] array = {64, 25, 12, 22, 11};

        selectionSort.selectionSort(array);
        selectionSort.printSortedArray(array);

    }
}
