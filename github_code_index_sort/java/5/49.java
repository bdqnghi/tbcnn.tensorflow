package Chapter07;

import java.util.Arrays;
import java.util.Scanner;

/**
 * (Bubble sort) Write a sort method that uses the bubble-sort algorithm. The bubble-sort algorithm makes several
 * passes through the array. On each pass, successive neighboring pairs are compared. If a pair is not in order, its
 * values are swapped; otherwise, the values remain unchanged. The technique is called a bubble sort or sinking sort
 * because the smaller values gradually “bubble” their way to the top and the larger values “sink” to the bottom. Write
 * a test program that reads in ten double numbers, invokes the method, and displays the sorted numbers.
 */

public class Ex07_18 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        double[] userInput = new double[5];

        System.out.println("Enter 10 double values:");
        for(int i = 0; i < userInput.length; i++) {
            System.out.print(i + " - ");
            userInput[i] = input.nextDouble();
        }

        bubbleSort(userInput);

        for(double f: userInput) {
            System.out.println(" " + f);
        }
        System.out.println("Numbers sorted using bubble-sort: " + Arrays.toString(userInput));
    }

    public static void bubbleSort(double[] list) {
        for(int i = 0; i < list.length; i++){
            for(int j = 1; j < list.length - 1; j++){
                if(list[j-1] > list[j]){
                    double temp = list[j-1];
                    list[j-1] = list[j];
                    list[j] = temp;
                }
            }
        }
    }
}
