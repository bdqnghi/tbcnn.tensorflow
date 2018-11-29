/**
 * 
 */
package home.algo.recursion;

/**
 * @author smrutis
 *
 */
public class TowerOfHanoi {

	public String move(int numberOfDisks, int fromPeg, int toPeg, int helperPeg) {
		if (1 == numberOfDisks)
			return directMove(numberOfDisks, fromPeg, toPeg);
		else {
			String step = move(numberOfDisks - 1, fromPeg, helperPeg, toPeg);
			step += directMove(numberOfDisks, fromPeg, toPeg);
			step += move(numberOfDisks - 1, helperPeg, toPeg, fromPeg);
			return step;
		}
	}

	private String directMove(int numberOfDisks, int fromPeg, int toPeg) {
		return "\nMove disk " + numberOfDisks + " from peg-" + fromPeg
				+ " to peg-" + toPeg;
	}

	public static void main(String[] args) {
		TowerOfHanoi towerOfHanoi = new TowerOfHanoi();
		String step = towerOfHanoi.move(5, 1, 3, 2);
		System.out.println(step);
	}

}
