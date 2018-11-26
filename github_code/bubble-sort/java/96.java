import java.util.Arrays;
import java.util.Scanner;

public class Sort_BubbleSort {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        // Може да се използва за малки множества или за множества,
        // където има елементи близо до очакваното си място.
        // Сравнява първия и втория елемент,
        // и ако първият е по-голям от втория, ги разменя.
        //най-добър вариант N итерации.
        //среден и най-лош N квадрат - стабилен

        int n = Integer.parseInt(scanner.nextLine());
        int[] array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = scanner.nextInt();
        }
        BubbleSort(array);
        System.out.println(Arrays.toString(array));
    }
    public static void BubbleSort(int[] array) {
        for (int j = 0; j < array.length; j++) {
            boolean isSwapped = false;
            for (int i = 0; i < array.length - 1 - j; i++) {
                if (array[i] > array[i + 1]) {
                    swap(array, i, i + 1);
                    isSwapped = true;
                }
            }
            if (!isSwapped)
                return;
        }
    }
    public static void swap(int[] array, int index1, int index2) {
        int temp = array[index1];
        array[index1] = array[index2];
        array[index2] = temp;
    }
}
