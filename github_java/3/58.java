package com.test.stackandqueue;

public class TowerOfHanoi {

    public int noOfDisks;
    public Stack<Integer>[] towers = new Stack[3];

    public TowerOfHanoi(int noOfDisks) {
        this.noOfDisks = noOfDisks;
        for (int i = 0; i < 3; i++) {
            towers[i] = new Stack<Integer>();
        }
    }

    public void pushDisksIntoFirstStack() {
        for (int i = noOfDisks; i > 0; i--) {
            towers[0].push(i);
        }
    }

    public void display() {
        System.out.println("  A  |  B  |  C");
        System.out.println("---------------");
        for (int i = noOfDisks - 1; i >= 0; i--) {
            System.out.print(String.valueOf(towers[0].pop()));
        }
    }

    public static void main(String[] args) {
        TowerOfHanoi towerOfHanoi = new TowerOfHanoi(3);
    }
}
