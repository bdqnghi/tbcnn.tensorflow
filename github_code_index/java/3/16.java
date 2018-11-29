package yuown.learn.others;

public class TowerOfHanoi {

	
	static int step = 0; 
	public static void main(String[] args) {
		move(3, 'A', 'C', 'B');
	}

	private static void move(int numberOfDiscs, char from, char to, char inter) {
		if (numberOfDiscs == 1) {
			step++;
			System.out.println(step + " - Moving Disc " + numberOfDiscs + " from " + from + " to " + to);
		} else {
			move(numberOfDiscs - 1, from, inter, to);
			step++;
			System.out.println(step + " - Moving Disc " + numberOfDiscs + " from " + from + " to " + to);
			move(numberOfDiscs - 1, inter, to, from);
		}
	}

}
