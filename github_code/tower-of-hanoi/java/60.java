package dummy;

import java.util.Scanner;

public class TowerOfHanoi {
	
	public static void towerOfHanoi(int n, char from, char to, char aux) {
		
		if(n==1) {
			System.out.println("Move disc 1 from " + from + " -> " + to);
			return;
		}
		towerOfHanoi(n-1, from, aux, to);
		System.out.println("Move disc " + n + "from " + from + " -> " + to);
		towerOfHanoi(n-1, aux, to, from);
	}

	public static void main(String[] args) {
		
		Scanner s = new Scanner(System.in);
		int n = s.nextInt();
		
		towerOfHanoi(n, 'A', 'B', 'C');
		s.close();
	}

}
