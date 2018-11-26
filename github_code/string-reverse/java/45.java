package strings;

import java.util.Scanner;

public class JavaStringReverse {

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		String A = sc.next();
		/* Enter your code here. Print output to STDOUT. */
		String solution = "No";
		for (int i = 0; i < A.length(); i++) {
			if (A.charAt(i) == A.charAt(A.length() - i - 1)) {
				solution = "Yes";
			} else {
				solution = "No";
			}
		}
		System.out.println(solution);
		sc.close();
		/*
		 * Other Solution more efficient. String R = new
		 * StringBuilder(A).reverse().toString(); if(A.equals(R))
		 * System.out.println("Yes"); else System.out.println("No");
		 */
	}
}
