package chp03_StacksAndQueues;

import java.util.Stack;

/*
 * In the classic problem of the Towers of Hanoi, 
 * you have 3 rods and N disks of different sizes 
 * which can slide onto any tower
 * 
 * The puzzle starts with disks sorted in ascending 
 * order of size from top to bottom 
 * (eg, each disk sits on top of an even larger one)
 * You have the following constraints: 
 * (A) Only one disk can be moved at a time 
 * (B) A disk is slid off the top of one rod onto the next rod  
 * (C) A disk can only be placed on top of a larger disk 
 * Write a program to move the disks from the first 
 * rod to the last using Stacks
 */
public class TowerOfHanoi {
	private Stack<Integer> disks;
	private int index;
	
	public TowerOfHanoi(int _index) {
		disks = new Stack<Integer>();
		index = _index;
	}
	
	public int index() {
		return index;
	}
	
	public void add(int d) {
		if(!disks.isEmpty() && disks.peek() <= d) {
			System.out.println("Error placing disk " + d);
		} else {
			disks.push(d);
		}
	}
	
	public void moveTop(TowerOfHanoi tower) {
		int top = disks.pop();
		tower.add(top);
		System.out.println("Move disk " + top + " from " + index() + 
				" to " + tower.index());
	}
	
	public void move(int n, TowerOfHanoi dest, TowerOfHanoi buffer) {
		if(n > 0) {
			move(n - 1, buffer, dest);
			moveTop(dest);
			buffer.move(n - 1, dest, this);
		}
	}
	
	public void print() {
		if(disks.size() == 0) {
			System.out.println("null");
			return;
		}
		for(int i : disks) {
			System.out.print(i + " ");
		}
		System.out.print("\n");
	}
	
	public static void main(String[] args) {
		int n = 6;
		TowerOfHanoi[] towers = new TowerOfHanoi[3];
		for(int i = 0; i < 3; i ++) {
			towers[i] = new TowerOfHanoi(i);
		}
		for(int i = n - 1; i >= 0; i--) {
			towers[0].add(i);
		}
		for(TowerOfHanoi t : towers) t.print();
		towers[0].move(n, towers[2], towers[1]);
		for(TowerOfHanoi t : towers) t.print();
	}
}
