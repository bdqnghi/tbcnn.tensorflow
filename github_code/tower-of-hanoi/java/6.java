package algorithms.hb.problems.recursiveproblems.towersofhanoi;

import test.algorithms.hb.problems.recursiveproblems.towersofhanoi.TowerOfHanoiBuilder;

public class App {

	public static void main(String[] args) {

		// TowerOfHanoi algorithm = new TowerOfHanoi();
		// algorithm.solveHanoiProblem(3, 'A', 'B', 'C');

		final Plate SMALL_PLATE = new Plate(3);
		final Plate MEDIUM_PLATE = new Plate(2);
		final Plate LARGE_PLATE = new Plate(1);
		final TowerOfHanoiBuilder TOWER_OF_HANOI_BUILDER = new TowerOfHanoiBuilder();

		TowerOfHanoi towerOfHanoi = TOWER_OF_HANOI_BUILDER.withPlate(LARGE_PLATE).withPlate(MEDIUM_PLATE).withPlate(SMALL_PLATE).build();
		towerOfHanoi.solveHanoiProblem(3);

	}
}
