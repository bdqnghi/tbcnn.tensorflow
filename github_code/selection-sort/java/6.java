/*
6.20 (Revise selection sort) In Section 6.11.1, you used selection sort to sort an array.
The selection-sort method repeatedly finds the smallest number in the current
array and swaps it with the first. Rewrite this program by finding the largest num-
ber and swapping it with the last. Write a test program that reads in ten double
numbers, invokes the method, and displays the sorted numbers.
 */

public class JP0620 {
    public static void main(String[] args) {
        // Initialize the list
        double[] myList = new double[10];

        java.util.Scanner input = new java.util.Scanner(System.in);

        System.out.println("Enter ten numbers: ");
        for (int i = 0; i < myList.length; i++) {
            myList[i] = input.nextDouble();
        }

        // Sort the list
        selectionSort(myList);

        // Print the sorted list
        System.out.println();
        System.out.println("The list after selection-sort is: ");
        printList(myList);
    }

    /** Method for printing numbers */
    static void printList(double[] list) {
        for (int i = 0; i < list.length; i++)
            System.out.print(list[i] + "  ");
        System.out.println();
    }

    /** Method for sorting the numbers */
    static void selectionSort(double[] list) {
        double currentMin;
        int currentMinIndex;

        for (int i = 0; i < list.length; i++) {
            // Find the smallest in the list
            currentMin = list[i];
            currentMinIndex = i;

            for (int j = i + 1; j < list.length; j++) {
                if (currentMin > list[j]) {
                    currentMin = list[j];
                    currentMinIndex = j;
                }
            }

            // Swap list[i] with list[currentMinIndex] if necessary;
            if (currentMinIndex != i) {
                list[currentMinIndex] = list[i];
                list[i] = currentMin;
            }
        }
    }
}
