/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Chapter18Review;

import java.util.Scanner;

/**
 *
 * @author dsli
 */
public class TowerOfHanoi {
    public static int runs = 0;
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("Enter number of disks: ");
        int n = input.nextInt();
        
        //Find the solution recursively
        System.out.println("The moves are: ");
        moveDisks(n, 'A', 'B', 'C');
        System.out.println("The method runs " + runs + " times.");
    }
    //The method for finding the solution to move n disks from fromTower to toTower with auxTower
    public static void moveDisks(int n, char fromTower, char toTower, char auxTower) {
        runs++;
        if (n == 1) //Stopping condition
            System.out.println("Move disk " + n + " from " + fromTower + " to " + toTower);
        else {
            moveDisks(n - 1, fromTower, auxTower, toTower);
            System.out.println("Move disk " + n + " from " + fromTower + " to " + toTower);
            moveDisks(n - 1, auxTower, toTower, fromTower);
        }
    }
}
