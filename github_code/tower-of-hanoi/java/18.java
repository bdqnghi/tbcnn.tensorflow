package org.beginning.algorithms.recursion;

/**
 * Algorithm for Tower of Hanoi for 3 Disc using Recursion
 *
 * Created by sgholve on 31/3/17.
 */
public class TowerOfHanoi {

    private static int count = 0;
    /**
     * Recursive function for Tower Of Hanoi
     * @param num number of disc
     * @param towerA Source location/tower of disc to be moved
     * @param towerB Auxiliary/Intermediate location/tower to be used for Disc move
     * @param towerC Destination location/tower of the disc to be moved
     */
    public static void towerOfHanoi(int num, int towerA, int towerB, int towerC) {
        if (num > 0) {
            // Move disc 'n-1' from towerA to towerB using towerC
            towerOfHanoi(num - 1, towerA, towerC, towerB);

            System.out.println(String.format("Step %d = Move a Disc [%d] from %d to %d", ++count, num, towerA, towerC));

            // Move disc 'n-1' from towerB to towerC using towerA
            towerOfHanoi(num - 1, towerB, towerA, towerC);
        }
    }

    public static void main(String[] args) {
        towerOfHanoi(4, 1, 2, 3);
    }
}
