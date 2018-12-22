package queueandstacks.towerofhanoi;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

/**
 * In the classic problem of the Towers of Hanoi, you have 3 rods and N disks of different sizes which can slide onto any tower. The puzzle starts with disks sorted in ascending order of size from top to bottom (e.g., each disk sits on top of an even larger one). You have the following constraints:
 * (A) Only one disk can be moved at a time.
 * (B) A disk is slid off the top of one rod onto the next rod.
 * (C) A disk can only be placed on top of a larger disk.
 * Write a program to move the disks from the first rod to the last using Stacks.
 */
public class TowerOfHanoi {

    public static void main(String[] args) {
        TowerOfHanoi towerOfHanoi = new TowerOfHanoi();
        for (int i = 5; i > 0; i--) {
            towerOfHanoi.stx.get(0).push(i);
        }
        towerOfHanoi.move(0, 2, 5);
        System.out.println();
    }

    List<Stack<Integer>> stx;

    public TowerOfHanoi() {
        stx = new ArrayList<>(4);
        for (int i = 0; i < 3; i++) {
            stx.add(new Stack<Integer>());
        }
    }

    public void move(int fr, int to, int n) {
        int buf = buf(fr, to);
        if (n == 1) {
            moveOne(fr, to, buf);
        } else {
            move(fr, buf, n - 1);
            moveOne(fr, to, buf);
            move(buf, to, n - 1);
        }
    }

    private void moveOne(int fr, int to, int buf) {
        if (stx.get(to).empty() || stx.get(fr).peek() < stx.get(to).peek()) {
            stx.get(to).push(stx.get(fr).pop());
        } else {
            throw new AssertionError();
        }
    }

    private int buf(int fr, int to) {
        switch (fr + to) {
            case 1:
                return 2;
            case 2:
                return 1;
            case 3:
                return 0;
            default:
                throw new IllegalArgumentException("Only supported for 3 stacks");
        }
    }
}

