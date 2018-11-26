package solution;

import java.util.Scanner;

public class TowerOfHanoi {

	
//												
	void towerOfHanoi(int n, char source, char aux, char dest) {
		
		if (n > 0) {	
		
//		move n-1 disc from SOURCE to AUXILIARY using DESTINATION
		towerOfHanoi(n-1, source , dest, aux);
//		remove remaining disc from SOURCE to DEST
		System.out.println("Move disc from "+source+" to "+dest);
//		Move n-1 disc from AUXILIARY to DESTINATION using SOURCE
		towerOfHanoi(n-1, aux, source, dest);
		}
	}
	
	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		int disc;
		System.out.println("Enter the no. of discs: ");
		disc = scan.nextInt();
		TowerOfHanoi tower1 = new TowerOfHanoi();
		tower1.towerOfHanoi(disc, 'A', 'B', 'C');
		
		
	}
	
}
