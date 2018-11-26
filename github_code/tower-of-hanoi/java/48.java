package Oppgave2;

import java.util.Scanner;

public class TowerOfHanoi {

	static Scanner in;
	static int counts = 0;

	public static void main(String[] args) {

		in = new Scanner(System.in);
		System.out.print("Write amount of discs: ");
		int n = in.nextInt();

		System.out.println("Moves are: ");
		moveDiscs(n, 'A', 'B', 'C');

		System.out.println("Amount of Moves: " + counts);
	}

	private static void moveDiscs(int n, char from, char to, char aux) {
		counts++;
		if (n == 1) {
			System.out.println("Move Disc " + n + " from " + from + " to " + to);
		} else {
			moveDiscs(n - 1, from, aux, to);
			System.out.println("Move Disc " + n + " from " + from + " to " + to);
			moveDiscs(n - 1, aux, to, from);
		}
	}

}
