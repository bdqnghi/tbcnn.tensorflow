package com.core.java.algos.recursion;

/*Tried using old logic @abhijeet*/
import java.util.Stack;

public class TowerOfHanoi<T> {

	public void movegUsingStack(int n, Stack<T> from, Stack<T> to, Stack<T> inter, char fromC, char toC, char interC) {
		if (n == 1) {
			Object disc = (Object) from.pop();
			to.push((T) disc);
			System.out.println("Moving object:" + disc + " from " + fromC + " to " + toC);
			return;
		} else {
			movegUsingStack(n - 1, from, inter, to, fromC, interC, toC);
			Object disc = (Object) from.pop();
			System.out.println("Moving object:" + disc + " from " + fromC + " to " + toC);
			to.push((T) disc);
			movegUsingStack(n - 1, inter, to, from, interC, toC, fromC);
			return;
		}
	}

	private void moveUsingChar(int n, char from, char to, char inter) {
		if (n == 1) {
			System.out.println("Moving object:" + n + " from " + from + " to " + to);
		} else {
			moveUsingChar(n - 1, from, inter, to);
			System.out.println("Moving object:" + n + " from " + from + " to " + to);
			moveUsingChar(n - 1, inter, to, from);
		}
	}

	public static void main(String[] args) {
		Stack<Integer> A = new Stack<>();
		Stack<Integer> B = new Stack<>();
		Stack<Integer> C = new Stack<>();
		int n = 5;
		for (int i = n; i > 0; i--) {
			A.push(i);
		}
		TowerOfHanoi<Integer> towerOfHanoi = new TowerOfHanoi<Integer>();
		towerOfHanoi.movegUsingStack(n, A, C, B, 'A', 'C', 'B');
		System.out.println(C.toString());
		System.out.println("Iteration using chars");
		towerOfHanoi.moveUsingChar(n, 'A', 'C', 'B');

	}
}
