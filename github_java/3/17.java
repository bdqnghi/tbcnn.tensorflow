package a.star.hanoi;

import java.util.LinkedList;
import a.star.algorithm.ProblemNode;

public class TowerOfHanoi extends ProblemNode<TowerOfHanoi> {

	private int[][] towers;
	private int[] emptys;

	public TowerOfHanoi(int[][] towers) {
		this(towers, null);
	}

	public TowerOfHanoi(int[][] towers, TowerOfHanoi goal) {
		this(towers, goal, null);
	}

	public TowerOfHanoi(int[][] towers, TowerOfHanoi goal, int[] emptys) {
		
		super(goal);

		setTowers(towers);
		this.setEmptys(emptys);

		if (emptys == null)
			this.setEmptys(getEmptys());
	}

	@Override
	public int getH() {

		int[] indexInGaolTower;
		int j, k, currentCost = 0, destinationCost = 0;

		for (int tower = 0; tower < this.towers.length; tower++)

			for (int i = 0; i < this.towers[0].length; i++)

				if (this.towers[tower][i] != 0) {

					indexInGaolTower = getIndex(this.towers[tower][i], this.getGoal().towers);

					j = i;

					while (j + 1 < towers[0].length && this.towers[tower][j + 1] != 0) {
						currentCost++;
						j++;
					}

					k = 0;

					if (this.towers[indexInGaolTower[0]][indexInGaolTower[1]] != 0) {

						while (indexInGaolTower[1] + k < towers[0].length
								&& this.towers[indexInGaolTower[0]][indexInGaolTower[1] + k] != 0) {
							destinationCost++;
							k++;
						}
					}
				}

		return currentCost + destinationCost;
	}

	private int[] getIndex(int value, int[][] towers) {

		for (int tower = 0; tower < towers.length; tower++)

			for (int i = 0; i < towers[0].length; i++)

				if (towers[tower][i] == value) {
					int[] index = { tower, i };
					return index;
				}

		return null;
	}

	@Override
	public boolean equal(Object obj) {

		TowerOfHanoi towerOfHanoi = (TowerOfHanoi) obj;

		for (int tower = 0; tower < this.towers.length; tower++)

			for (int i = 0; i < this.towers[0].length; i++)

				if (this.towers[tower][i] != towerOfHanoi.towers[tower][i])
					return false;

		return true;
	}

	@Override
	public LinkedList<ProblemNode<TowerOfHanoi>> successors() {

		LinkedList<ProblemNode<TowerOfHanoi>> neighbours = new LinkedList<ProblemNode<TowerOfHanoi>>();

		// hold move tiles
		int[][] moveTowers;

		int[] lastCells = { towers[0].length + 1, towers[0].length + 1 };

		if (emptys[0] != 0)
			lastCells[0] = towers[0][emptys[0] - 1];

		if (emptys[1] != 0)
			lastCells[1] = towers[1][emptys[1] - 1];

		// move 1st to 2nd
		if (emptys[0] != 0 && emptys[1] != towers[0].length && lastCells[0] < lastCells[1]) {

			moveTowers = cloneTowers();

			moveTowers[0][emptys[0] - 1] = 0;
			moveTowers[1][emptys[1]] = towers[0][emptys[0] - 1];

			int[] em = { emptys[0] - 1, emptys[1] + 1, emptys[2] };

			neighbours.add(new TowerOfHanoi(moveTowers, this.getGoal(), em));
		}

		lastCells[0] = lastCells[1] = towers[0].length + 1;

		if (emptys[0] != 0)
			lastCells[0] = towers[0][emptys[0] - 1];

		if (emptys[2] != 0)
			lastCells[1] = towers[2][emptys[2] - 1];

		// move 1st to 3rd
		if (emptys[0] != 0 && emptys[2] != towers[0].length && lastCells[0] < lastCells[1]) {

			moveTowers = cloneTowers();

			moveTowers[0][emptys[0] - 1] = 0;
			moveTowers[2][emptys[2]] = towers[0][emptys[0] - 1];

			int[] em = { emptys[0] - 1, emptys[1], emptys[2] + 1 };

			neighbours.add(new TowerOfHanoi(moveTowers, this.getGoal(), em));
		}

		lastCells[0] = lastCells[1] = towers[0].length + 1;

		if (emptys[1] != 0)
			lastCells[0] = towers[1][emptys[1] - 1];

		if (emptys[0] != 0)
			lastCells[1] = towers[0][emptys[0] - 1];

		// move 2nd to 1st
		if (emptys[1] != 0 && emptys[0] != towers[0].length && lastCells[0] < lastCells[1]) {

			moveTowers = cloneTowers();

			moveTowers[1][emptys[1] - 1] = 0;
			moveTowers[0][emptys[0]] = towers[1][emptys[1] - 1];

			int[] em = { emptys[0] + 1, emptys[1] - 1, emptys[2] };

			neighbours.add(new TowerOfHanoi(moveTowers, this.getGoal(), em));
		}

		lastCells[0] = lastCells[1] = towers[0].length + 1;

		if (emptys[1] != 0)
			lastCells[0] = towers[1][emptys[1] - 1];

		if (emptys[2] != 0)
			lastCells[1] = towers[2][emptys[2] - 1];

		// move 2nd to 3rd
		if (emptys[1] != 0 && emptys[2] != towers[0].length && lastCells[0] < lastCells[1]) {

			moveTowers = cloneTowers();

			moveTowers[1][emptys[1] - 1] = 0;
			moveTowers[2][emptys[2]] = towers[1][emptys[1] - 1];

			int[] em = { emptys[0], emptys[1] - 1, emptys[2] + 1 };

			neighbours.add(new TowerOfHanoi(moveTowers, this.getGoal(), em));
		}

		lastCells[0] = lastCells[1] = towers[0].length + 1;

		if (emptys[2] != 0)
			lastCells[0] = towers[2][emptys[2] - 1];

		if (emptys[0] != 0)
			lastCells[1] = towers[0][emptys[0] - 1];

		// move 3rd to 1st
		if (emptys[2] != 0 && emptys[0] != towers[0].length && lastCells[0] < lastCells[1]) {

			moveTowers = cloneTowers();

			moveTowers[2][emptys[2] - 1] = 0;
			moveTowers[0][emptys[0]] = towers[2][emptys[2] - 1];

			int[] em = { emptys[0] + 1, emptys[1], emptys[2] - 1 };

			neighbours.add(new TowerOfHanoi(moveTowers, this.getGoal(), em));
		}

		lastCells[0] = lastCells[1] = towers[0].length + 1;

		if (emptys[2] != 0)
			lastCells[0] = towers[2][emptys[2] - 1];

		if (emptys[1] != 0)
			lastCells[1] = towers[1][emptys[1] - 1];

		// move 3rd to 2nd
		if (emptys[2] != 0 && emptys[1] != towers[0].length && lastCells[0] < lastCells[1]) {

			moveTowers = cloneTowers();

			moveTowers[2][emptys[2] - 1] = 0;
			moveTowers[1][emptys[1]] = towers[2][emptys[2] - 1];

			int[] em = { emptys[0], emptys[1] + 1, emptys[2] - 1 };

			neighbours.add(new TowerOfHanoi(moveTowers, this.getGoal(), em));
		}

		return neighbours;
	}

	private int[][] cloneTowers() {

		int[][] clone = new int[this.towers.length][this.towers[0].length];

		for (int tower = 0; tower < this.towers.length; tower++)

			for (int i = 0; i < this.towers[0].length; i++)
				clone[tower][i] = this.towers[tower][i];

		return clone;
	}

	@Override
	public String toString() {

		String board = "_________________\n";

		for (int i = towers[0].length - 1; i >= 0; i--) {
			board += towers[0][i] + "\t" + towers[1][i] + "\t" + towers[2][i] + "\n";
		}
		board += "=================";

		return board;
	}

	@Override
	public boolean isGoal() {
		return equal(getGoal());
	}

	/**
	 * @return the towers
	 */
	public int[][] getTowers() {
		return towers;
	}

	/**
	 * @param towers
	 *            the towers to set
	 */
	private void setTowers(int[][] towers) {
		this.towers = towers;
	}

	/**
	 * @return the goal
	 */
	public TowerOfHanoi getGoal() {
		return this.getGoal();
	}

	private int[] getEmptys() {

		int[] emptys = { 0, 0, 0 };

		for (int tower = 0; tower < towers.length; tower++)

			for (int i = towers[tower].length - 1; i >= 0; i--)

				if (towers[tower][i] != 0) {
					emptys[tower] = i + 1;
					break;
				}

		return emptys;
	}

	/**
	 * @param emptys
	 *            the emptys to set
	 */
	private void setEmptys(int[] emptys) {
		this.emptys = emptys;
	}

}
