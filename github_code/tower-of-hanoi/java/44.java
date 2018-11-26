package SortingAlgorithms;

import java.util.Scanner;

public class Tower {

    public static void hanoi (int n,
                              String init,
                              String end,
                              String temp) {
        // stopping condition: move one disk
        if (n == 1) {
            System.out.println("move " + init + " to " + end);
        }
        else {
            // move n-1 disks from init to temp using
            // end for temporary storage (Stage 1 in the handout)
            hanoi(n-1, init, temp, end);

            // move largest disk to end
            System.out.println("move " + init + " to " + end);

            // move n-1 disks from temp to end using
            // init for temporary storage (Stage 3 in the handout)
            hanoi(n-1, temp, end, init);
        }
    }

    public static void main(String[] args) {
        // Run this program like this if the number of disks is 3:
        //   java Tower 3
        
        String begin = "A",
               middle = "B",
               end = "C";
        System.out.println("Enter the number of disks or rings in the tower");
        Scanner scanner = new Scanner(System. in);
        int n = Integer.parseInt(scanner.nextLine());

        System.out.println("The solution for n = " + n);
        hanoi(n, begin, end, middle);
    }

}
