/**
 * David Lonergan
 * This program solves the Tower of Hanoi puzzle
 * 2^n - 1 moves are required to move n disks.
 * Used textbook, online tower of Hanoi math game and geeksforgeeks video on youtube
 * I worked alone
 * note that the commented out code was past ideas I had
 */

import java.util.Scanner;
public class TowerOfHanoi
{
    public static void main(String[] args)
    {
        int nDisks;
        System.out.print("Enter the number of disks: ");
        Scanner keyboard = new Scanner(System.in);
        nDisks = keyboard.nextInt();
        keyboard.close();

        moveTower(1, 3, nDisks);
    }

    public static void moveDisk(int fromPeg, int toPeg)
    {
        System.out.println("From " + fromPeg + " to " + toPeg);
    }

    public static void moveTower(int fromPeg, int toPeg, int n)
    {
//        if(n==1){
//            System.out.println("From " + fromPeg + " to " + toPeg);
//        }
//        else if(n==2)
//        {
//            System.out.println("From " + fromPeg + " to " + (toPeg-1));
//            moveTower(fromPeg,toPeg,n-1);
//            System.out.println("From " + (fromPeg+1) + " to " + toPeg);
//        }
//        else if(n==3){
//            moveTower(fromPeg,toPeg,n-2);
//            System.out.println("From " + fromPeg + " to " + (toPeg-1));
//            moveTower(toPeg,fromPeg+1,n-2);
//            moveTower(fromPeg,toPeg,n-2);
//            System.out.println("From " + fromPeg + " to " + (fromPeg-1));
//            moveTower(fromPeg+1,toPeg,n-1);
//            moveTower(fromPeg,toPeg,n-2);
//
//        }

//        int aux = 2;
//        int start = fromPeg;
//        int end = toPeg;
//        //first goal is to move n-1 to the aux peg
//        // if n = 1, then move to the final peg
//        // then move the n-1 rings to the final peg - use same
////        method from first step but change the peg conditions
//
//        if(n>1){
//            moveTower(fromPeg,toPeg,n-1);
//        }
//        end--;
//        moveDisk(start,end);
//        end++;
//        int aux = 2;
//        if(n==1)
//            moveDisk(fromPeg,toPeg);
//        else if(n==2){
//            moveTower(fromPeg,aux,n-1);
//            moveDisk(fromPeg,toPeg);
//            moveDisk(aux,toPeg);
//        }
//        else
//            if(n%2==0)
//            moveTower(fromPeg,aux,n-1);
//        else
//            moveTower(fromPeg,toPeg,n-1);
////            moveDisk(fromPeg,toPeg);
////            moveTower(aux,toPeg,n-1);
//        System.out.println(n%2);
        if(n>1) {
//            System.out.println(aux);
            moveTower(fromPeg, (6-(fromPeg+toPeg)), n - 1);
//            System.out.println(aux);
            moveDisk(fromPeg, toPeg);
            moveTower((6-(fromPeg+toPeg)), toPeg, n - 1);
        }
        else{
            moveDisk(fromPeg,toPeg);
        }
    }
}