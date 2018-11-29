package nbcn.termin2.treeBuilder;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

import javax.swing.JFrame;
import javax.swing.Timer;

import nbcn.termin2.shared.RedBlackTree;



public class Main {

	public static final int WINDOW_WIDTH = 1200;
	public static final int WINDOW_HEIGHT = 600;
	
	public static final int RANDOM_LIMIT = 1001;
	
	private static RedBlackTree tree = new RedBlackTree();
	private static VisualTree vis_tree = new VisualTree();
	
	private static Timer t;
	private static JFrame window;
	
	
	public static void main(String[] args) {
		window = new JFrame();
		window.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setLocationRelativeTo(null);
		window.getContentPane().add(vis_tree);
		window.setTitle("Red-Black-Tree mit Zufallswerten zwischen -" + (RANDOM_LIMIT-1) + " und " + (RANDOM_LIMIT-1) + "                 zum Starten / Pausieren klicken");
		window.setVisible(true);

		treeSimulation();
	}
	

	private static void treeSimulation(){
		Random r = new Random();
		
		t = new Timer(1000, new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				long val = r.nextLong() % RANDOM_LIMIT;
				tree.insert(val);
				window.setTitle("Red-Black-Tree mit Zufallswerten zwischen -" + (RANDOM_LIMIT-1) + " und " + (RANDOM_LIMIT-1) + "                 Neu Eingef�gt: " + val);
				vis_tree.repaint();
			}
		});
				
	}
	
	public static RedBlackTree getTree(){
		return tree;
	}
	
	
	public static int getWindowWidth(){
		return window.getWidth();
	}

	public static void toggleRunStatus(){
		if (t.isRunning()){
			t.stop();
		} else {
			t.start();
		}
	}
}
