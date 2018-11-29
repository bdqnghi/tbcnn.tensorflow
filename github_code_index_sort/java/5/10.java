package net.perfsys.trainees.ascherbakov.task_0.lessonsfrombook;
import java.util.Random;

public class Bubblesort {

    public static void main(String[] args) {
        Random r = new Random();
        int[] num = {23, 32, 43, 54, 65, 98, 5654654, 34224324, 5345345} ;

        bubbleSort(num);

        for (int h = 0; h < num.length; h++)
            System.out.print(num[h]+ " ");


    }

    public static void bubbleSort(int[] numbers) {

        int temp = 0;

        for (int i = 0; i < numbers.length; i++) {
            for (int j = 1; j < (numbers.length - i); j++) {

                if (numbers[j - 1] > numbers[j]) {
                    //swap elements
                    temp = numbers[j - 1];
                    numbers[j - 1] = numbers[j];
                    numbers[j] = temp;

                }
            }
        }
    }
}
