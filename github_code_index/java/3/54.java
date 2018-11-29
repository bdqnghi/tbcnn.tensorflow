/*
TowerOfHanoi problem if we want to move N disks from source to destination, then
we first move N-1 disks from source to temp, then move the lowest Nth disk from source to
destination. Then will move N-1 disks from temp to destination
*/

package recursive;
public class TowerOfHanoi {

	public static void towerOfHanoi(int num, char src, char dst, char temp) {
		if (num < 1)
			return;
		
		towerOfHanoi(num - 1, src, temp, dst);
		System.out.println("Move " + num + " disk from peg " + src + " to peg " + dst);
		towerOfHanoi(num - 1, temp, dst, src);
	}

	public static void main(String[] args) {
		int num = 3;
		System.out.println("The sequence of moves in the Tower of Hanoi are : ");
		towerOfHanoi(num, 'A', 'C', 'B');
	}
}
