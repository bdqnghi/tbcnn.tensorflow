import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Arrays;

import javax.swing.*;

public class MazeGame extends JFrame implements ActionListener {

	static JMenuItem newgame;
	static JMenuItem exit;
	static JMenuItem dfs;
	static JMenuItem bfs;
	static Maze m;
	private Timer t;
	private ActionEvent action;

	public MazeGame() {
		newgame.addActionListener(this);
		exit.addActionListener(this);
		dfs.addActionListener(this);
		bfs.addActionListener(this);
		m = new Maze();
		add(m);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		action = e;
		if (e.getSource().equals(newgame)) {
			Maze.maze = m.getNewMaze();
			repaint();
		}
		if (e.getSource().equals(exit)) {
			System.exit(0);
		}
		if (e.getSource().equals(dfs)) {
			m.refreshMaze();
			SolveByDFS solveByDFS = new SolveByDFS(Maze.maze);
			t = new Timer(50, new TimerListener(solveByDFS));
			t.start();
		}
		if (e.getSource().equals(bfs)) {
			m.refreshMaze();
			SolveByBFS solveByBFS = new SolveByBFS(Maze.maze);
			t = new Timer(50, new TimerListener(solveByBFS));
			t.start();
		}

	}

	public static void main(String[] args) {
		JMenuBar menu = new JMenuBar();
		JMenu game = new JMenu("Maze");
		newgame = new JMenuItem("New Game");
		game.add(newgame);
		exit = new JMenuItem("Exit");
		game.add(exit);
		JMenu solution = new JMenu("Solution");
		dfs = new JMenuItem("DFS Solution");
		bfs = new JMenuItem("BFS Solution");
		solution.add(dfs);
		solution.add(bfs);

		MazeGame f = new MazeGame();
		f.setJMenuBar(menu);

		menu.add(game);
		menu.add(solution);

		// f.setContentPane(new Maze());
		f.setSize(400, 444);
		f.setTitle("Maze Test");
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setLocationRelativeTo(null);
		f.setVisible(true);
		f.setResizable(false);
	}

	class TimerListener implements ActionListener {
		private SolveByDFS solveByDFS;
		private SolveByBFS solveByBFS;

		public TimerListener(SolveByDFS solveByDFS) {
			this.solveByDFS = solveByDFS;
		}

		public TimerListener(SolveByBFS solveByBFS) {
			this.solveByBFS = solveByBFS;
		}

		public void actionPerformed(ActionEvent e) {
			// System.out.println(action.getSource());
			// System.out.println(dfs);
			// System.out.println(action.getSource().equals(dfs));
			if (action.getSource().equals(dfs)) {
				Maze.maze = solveByDFS.getMaze();
				// System.out.println(Arrays.deepToString(Maze.cell));
				if ((solveByDFS.getCol() == solveByDFS.N - 1 && solveByDFS.getRow() == solveByDFS.N - 1)) {
					t.stop();
				}
			}
			if (action.getSource().equals(bfs)) {
				Maze.maze = solveByBFS.getMaze();
				// System.out.println(Arrays.deepToString(Maze.cell));
				if ((solveByBFS.getCol() == solveByBFS.N - 1 && solveByBFS.getRow() == solveByBFS.N - 1)) {
					t.stop();
					t = new Timer(50, new TimerListener2(solveByBFS));
					t.start();
					
				}
				
			}
			repaint();

		}
	}

	class TimerListener2 implements ActionListener {
		private SolveByBFS solveByBFS;

		public TimerListener2(SolveByBFS solveByBFS) {
			this.solveByBFS = solveByBFS;
		}

		public void actionPerformed(ActionEvent e) {
			Maze.maze = solveByBFS.getMaze2();
			// System.out.println(Arrays.deepToString(Maze.cell));
			if ((solveByBFS.getCol() == 0 && solveByBFS.getRow() == 0)) {
				t.stop();
			}
			repaint();
		}
	}

}
