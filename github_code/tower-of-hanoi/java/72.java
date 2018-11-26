package javaTowerOfHanoi;

/* Tower of Hanoi example in Java
 * 
 *       |      |      |
 *      _|_     |      |
 *     __|__    |      |
 *    ___|___   |      |
 *   ====|======|======|=====
 *       A      B      C
 */

import java.util.Scanner;

public class TowerOfHanoi {
	
	public static void Hanoi(int m, char a, char b, char c) {
		
		if(m > 0) {
			Hanoi(m-1,a,c,b);
			System.out.println("Move disc from " + a + " to " + c);
			Hanoi(m-1,b,a,c);
		}
	}
	
	public static void main(String[] args){
		
		Scanner h = new Scanner(System.in);
		int n;
		System.out.print("How many discs : ");
		n = h.nextInt();
		Hanoi(n, 'A', 'B', 'C');
		
		
	}

}

/* Output
 How many discs : 3
Move disc from A to C
Move disc from A to B
Move disc from C to B
Move disc from A to C
Move disc from B to A
Move disc from B to C
Move disc from A to C
 */