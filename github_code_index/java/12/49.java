package container;

import java.awt.Point;
import java.util.HashMap;
import java.util.Scanner;

public class Main {

	public Main() {
		// TODO Auto-generated constructor stub
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		HashMap<Point, Integer> map1 = new HashMap<Point, Integer>();
		System.out.println("Input the value of ROW and COL:");
		int maxRow1 = in.nextInt();
		int maxCol1 = in.nextInt();
		System.out.println("Input the number of non-zero elements:");
		int n1 = in.nextInt();
		System.out.println("Input these elements:");
		for (int i = 0; i < n1; i++)
			map1.put(new Point(in.nextInt(), in.nextInt()), in.nextInt());

		// for (int i = 0; i < maxRow1; i++) {
		// for (int j = 0; j < maxCol1; j++) {
		// Point p = new Point(i, j);
		// if (map1.containsKey(p)) {
		// System.out.print(map1.get(p));
		// } else {
		// System.out.print(0);
		// }
		// System.out.printf("%c", j == maxCol1 - 1 ? '\n' : ' ');
		// }
		// }

		HashMap<Point, Integer> map2 = new HashMap<Point, Integer>();
		System.out.println("Input the value of ROW and COL:");
		int maxRow2 = in.nextInt();
		int maxCol2 = in.nextInt();
		System.out.println("Input the number of non-zero elements:");
		int n2 = in.nextInt();
		System.out.println("Input these elements:");
		for (int i = 0; i < n2; i++)
			map2.put(new Point(in.nextInt(), in.nextInt()), in.nextInt());

		if (maxRow1 != maxRow2 || maxCol1 != maxCol2) {
			System.out.println("The Matrix-Addition is invalid.");
		} else {
			System.out.println("Matrix-Addition:");
			for (int i = 0; i < maxRow1; i++)
				for (int j = 0; j < maxCol1; j++) {
					Point p = new Point(i, j);
					Integer v1 = map1.containsKey(p) ? map1.get(p) : 0;
					Integer v2 = map2.containsKey(p) ? map2.get(p) : 0;
					System.out.printf("%d%c", v1 + v2, j == maxCol1 - 1 ? '\n' : ' ');
				}
		}

		if (maxCol1 != maxRow2) {
			System.out.println("The Matrix-Multiplication is invalid.");
		} else {
			System.out.println("Matrix-Multiplication:");
			for (int i = 0; i < maxRow1; i++)
				for (int j = 0; j < maxCol2; j++) {
					int tmp = 0;
					for (int k = 0; k < maxRow2; k++) {
						Point p1 = new Point(i, k);
						Integer v1 = map1.containsKey(p1) ? map1.get(p1) : 0;
						Point p2 = new Point(k, j);
						Integer v2 = map2.containsKey(p2) ? map2.get(p2) : 0;
						tmp += v1 * v2;
					}
					System.out.printf("%d%c", tmp, j == maxCol2 - 1 ? '\n' : ' ');
				}
		}

	}

}
