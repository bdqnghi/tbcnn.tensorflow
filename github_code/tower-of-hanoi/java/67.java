package com.geeksforgeeks.stack;

public class TowerOfHanoi {

    public static void main(String[] args) {
        int disks = 3;
        towerOfHanoi(disks, 'A', 'C', 'B');
    }

    public static void towerOfHanoi(int disk, char fromRod, char toRod, char auxRod) {
        if (disk == 1) {
            System.out.println("Moving Disk 1 : " + fromRod + " =====> " + toRod);
            return;
        }
        towerOfHanoi(disk - 1, fromRod, auxRod, toRod);
        System.out.println("Moving Disk " + disk + " : " + fromRod + " =====> " + toRod);
        towerOfHanoi(disk - 1, auxRod, toRod, fromRod);
    }
}
