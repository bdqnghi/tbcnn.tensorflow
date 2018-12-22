import java.util.Stack;

public class TowerOfHanoi {
	private static Stack[] poles;

	public static void main(String[] args) {
		poles = new Stack[3];
		poles[0] = new Stack<Integer>();
		poles[1] = new Stack<Integer>();
		poles[2] = new Stack<Integer>();

		poles[0].push(5);
		poles[0].push(4);
		poles[0].push(3);
		poles[0].push(2);
		poles[0].push(1);
		moveTower(5, 0, 2, 1);
		printPoles();
	}

	//I can't actually believe the algorithm is this simple
	private static void moveTower(int height, int fromPole, int toPole, int withPole) {
		if (height >= 1) {
			moveTower(height - 1, fromPole, withPole, toPole);
			moveDisk(fromPole, toPole);
			moveTower(height - 1, withPole, toPole, fromPole);
		}
	}

	private static void moveDisk(int fromPole, int toPole) {
		poles[toPole].push(poles[fromPole].pop());
	}

	private static void printPoles() {
		for (int i = 0; i < 3; i++) {
			System.out.println("POLE " + i);
			if (poles[i].size() == 0)
				System.out.println(" ");
			else 
				printPole(i);
		}
	}

	private static void printPole(int pos) {
		int size = poles[pos].size();
		for (int i = 0; i < size; i++) {
			StringBuilder sb = new StringBuilder();
			int bound = (Integer)poles[pos].pop();
			for (int j = 0; j < bound; j++) {
				sb.append("*");
			}
			System.out.println(sb.toString());
		}
	}
}