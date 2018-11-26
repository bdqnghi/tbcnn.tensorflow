import java.util.Scanner;

/**
 This program is used for solving tower of hanoi.

*/
public class towerofhanoi {
	/**
		Recursive method for solving the program
		@Param:
			n: int, number of disc
			start: the Starting Pole
			temp :place to  storing disk temporarily
			end: end: final spot

	*/
	   public void solve(int n, String start, String temp, String end) {
	       if (n == 1) {
	           System.out.println(start + " -> " + end);
	       } else {
	           solve(n - 1, start, end, temp);
	           System.out.println(start + " -> " + end);
	           solve(n - 1, temp, start, end);
	       }
	   }
		
	// Main method to input number of disc.
	   public static void main(String[] args) {
	       towerofhanoi towersOfHanoi = new towerofhanoi();
	       System.out.print("Enter number of discs: ");
	       Scanner scanner = new Scanner(System.in);
	       int discs = scanner.nextInt();
	       towersOfHanoi.solve(discs, "A", "B", "C");
	   }
	}
