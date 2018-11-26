package c03_stacks_and_queues.p3_4;

import java.util.Stack;

/**
 * Created by sharath on 8/10/14.
 *
 * Problem description:
 * Classic problem of tower of Hanoi.
 * You have 3 towers and N disks of different sizes.
 * Disks can slide onto any towers.
 * Puzzle starts with disks in ascending order from top to bottom on tower 1.
 * Following are the constraints
 * 1. Only one disk can be moved at a time.
 * 2. A disk is slid off the top of one tower onto next.
 * 3. A disk can only be placed on top of larger disk.
 *
 * Write a program to move all disks from tower 1 to 3 using stacks.
 *
 */
public class Tower {

    private int N;

    private Stack<Integer>[] towers;

    @SuppressWarnings("unchecked")
    public Tower(int numOfDisks) {
        N = numOfDisks;
        towers = new Stack[4];
        towers[1] = new Stack<>();
        towers[2] = new Stack<>();
        towers[3] = new Stack<>();

        for(int i = numOfDisks; i > 0; i--) {
            towers[1].push(i);
        }
    }

    public void hanoi(int n, int a, int b, int c) {
        if(n > 0) {
            hanoi(n - 1 , a, c, b);
            towers[c].push(towers[a].pop());
            display();
            hanoi(n - 1, b, a, c);
        }
    }

    public static void main(String[] args) {
        int numDisks = 5;
        Tower t = new Tower(numDisks);
        t.display();
        t.hanoi(numDisks, 1, 2, 3);
    }

    private void display() {
        System.out.println("  A  |  B  |  C");
        System.out.println("---------------");
        for(int i = N - 1; i >= 0; i--)
        {
            String d1 = " ", d2 = " ", d3 = " ";
            try
            {
                d1 = String.valueOf(towers[1].get(i));
            }
            catch (Exception e){
            }
            try
            {
                d2 = String.valueOf(towers[2].get(i));
            }
            catch (Exception e){
            }
            try
            {
                d3 = String.valueOf(towers[3].get(i));
            }
            catch (Exception e){
            }
            System.out.println("  "+d1+"  |  "+d2+"  |  "+d3);
        }
        System.out.println("\n");
    }
}
