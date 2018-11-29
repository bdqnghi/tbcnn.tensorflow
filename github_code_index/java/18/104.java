/**
 * Created by tang on 10/23/14.
 */
public class SelectionSort extends RandomArray {

    public SelectionSort(int n) {
        super(n);
    }

    public void sort() {
        for (int i = 0; i < numbers.length; i++) {
            int minIndex = i;

            for (int j = i + 1; j < numbers.length; j++) {
                if (numbers[j] < numbers[minIndex]) {
                    minIndex = j;
                }
            }

            int temp = numbers[i];
            numbers[i] = numbers[minIndex];
            numbers[minIndex] = temp;
        }
    }

    public static void main(String [] args) {
        SelectionSort selectionSort = new SelectionSort(10);

        selectionSort.printNumbers();
        selectionSort.sort();
        selectionSort.printNumbers();
    }
}
