package com.angelcraftonomy.solver.main;

public class MainDriver {

	public static void printRuntime(long startTime) {
		long endTime = System.currentTimeMillis();
		long runtime = (endTime - startTime);
		long minutes = (runtime / 1000) / 60;
		long seconds = (runtime / 1000) % 60;
		if (minutes != 0 || seconds != 0)
			System.out.println("Total execution time: " + minutes + " min " + seconds + " sec");
		else
			System.out.println("Total execution time: " + runtime + " milliseconds");
	}

	public static void main(String[] args) {
		long startTime;
		int numMoves = 7;

		// Generate new cube 3x3
		BreadthFirstSearch bfs;
		DepthFirstSearch dfs;
		IterativeDepthFirstSearch idfs;
		Cube cube;

		cube = new Cube();
		System.out.println("Un-mixed State: \n");
		cube.print();

		// Randomize
		cube.randomize(numMoves);
		System.out.println("Random mix: " + cube.getRandomMoves());
		cube.print();

		// Breadth first search uses a queue and runs out of memory quickly but
		// is guaranteed to find the shortest path
		// startTime = System.currentTimeMillis();
		// bfs = new BreadthFirstSearch(cube);
		// bfs.search();
		// printRuntime(startTime);

		// Depth first search is slower that Breadth first search but uses
		// hardly any memory and is not guaranteed to find the shortest path
		// startTime = System.currentTimeMillis();
		// dfs = new DepthFirstSearch(cube, numMoves);
		// dfs.search();
		// printRuntime(startTime);

		// So is there a way to not use the strengths of both while avoiding the
		// weaknesses of both? Yes!
		// Iterative Depth First Search is essentially Breadth First search
		// without a queue (i.e. dramatically reduces memory usage). And is also
		// guaranteed to find the shortest path to the solution!
		// startTime = System.currentTimeMillis();
		// idfs = new IterativeDepthFirstSearch(cube,"");
		// idfs.search();
		// idfs.start();
		// printRuntime(startTime);

		// Start on the given branches
		IterativeDepthFirstSearch idfs_0 = new IterativeDepthFirstSearch(cube, "R");
		idfs_0.start();
		IterativeDepthFirstSearch idfs_1 = new IterativeDepthFirstSearch(cube, "r");
		idfs_1.start();
		IterativeDepthFirstSearch idfs_2 = new IterativeDepthFirstSearch(cube, "L");
		idfs_2.start();
		IterativeDepthFirstSearch idfs_3 = new IterativeDepthFirstSearch(cube, "l");
		idfs_3.start();
		IterativeDepthFirstSearch idfs_4 = new IterativeDepthFirstSearch(cube, "U");
		idfs_4.start();
		IterativeDepthFirstSearch idfs_5 = new IterativeDepthFirstSearch(cube, "u");
		idfs_5.start();
		IterativeDepthFirstSearch idfs_6 = new IterativeDepthFirstSearch(cube, "D");
		idfs_6.start();
		IterativeDepthFirstSearch idfs_7 = new IterativeDepthFirstSearch(cube, "d");
		idfs_7.start();
		IterativeDepthFirstSearch idfs_8 = new IterativeDepthFirstSearch(cube, "F");
		idfs_8.start();
		IterativeDepthFirstSearch idfs_9 = new IterativeDepthFirstSearch(cube, "f");
		idfs_9.start();
		IterativeDepthFirstSearch idfs_10 = new IterativeDepthFirstSearch(cube, "B");
		idfs_10.start();
		IterativeDepthFirstSearch idfs_11 = new IterativeDepthFirstSearch(cube, "b");
		idfs_11.start();
	}

}
