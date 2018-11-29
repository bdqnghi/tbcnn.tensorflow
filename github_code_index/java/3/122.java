/**Towers of Hanoi
 *Expanded code by Ben Schaeffer, originally from 
 *http://javabypatel.blogspot.in/2015/12/tower-of-hanoi.html
*/
public class TowerH {
	public static int move = 1; // a static field which all methods can access

	public static void MoveDisks(int n, String start, String auxiliary, String end) {
		if (n == 1) {//base case

			// When n==1, it means we are left with only one disk, so directly
			// move it from Source Peg to Destination Peg.
			System.out.println("Move " + move + ": " + start + " -> " + end);
			move++;

		} else {

			// Move (n-1 disk) from Source Peg to Auxiliary Peg
			MoveDisks(n - 1, start, end, auxiliary);

			// Move last nth disk to Destination Peg.
			System.out.println("Move " + move + ": " + start + " -> " + end);
			move++;

			// Move (n-1 disk) from Auxiliary Peg to Destination Peg.
			MoveDisks(n - 1, auxiliary, start, end);
		}
	}

	public static void main(String[] args) {
        final int disks = 2;
		MoveDisks(disks, "Source peg", "Helper peg", "Destination peg");
		//Display friendlier version below
	}
}
