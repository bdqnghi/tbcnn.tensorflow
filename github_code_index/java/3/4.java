import java.util.*;
public class TowerOfHanoi {
	public static void main(String[] args) {
		Tower[] towers = new Tower[3];
		for (int i = 0; i < 3; i++) {
			towers[i] = new Tower(i);
		}
		for (int i = 0; i <= 6; i++) {
			towers[0].add(6 - i);
		}
		towers[0].MoveDisks(6, towers[2], towers[1]);
	}
}
class Tower {
	Stack<Integer> slides;
	int index;
	public Tower(int index) {
 		slides = new Stack<>();
 		this.index = index;
	}
	public void add(int n) {
		if (slides.isEmpty() || slides.peek() > n) {
			slides.push(n);
		} else {
			System.out.println("illegal operation");
		}
	}
	public void MoveTopTo(Tower destination) {
		int t = slides.pop();
		destination.add(t);
	}
	public void MoveDisks(int n, Tower destination, Tower buffer) {
		if (n <= 0) {
			return;
		}
		MoveDisks(n - 1, buffer, destination);
		System.out.println("move " + (n - 1) + "from " + this.index + " to " + destination.index);
		MoveTopTo(destination);
		buffer.MoveDisks(n - 1, destination, this);
	}
}