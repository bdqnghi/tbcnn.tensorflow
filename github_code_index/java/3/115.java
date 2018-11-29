import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;

class P4132_HanoiTower {
/*
Sample Input
2
1
2

Sample Output
1
A->C
3
A->B
A->C
B->C
*/
	private static PrintWriter pw = null;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		pw = new PrintWriter(System.out, true);

		String textLine;
		int T, t;
		T = Integer.parseInt(br.readLine());
		ArrayList<Integer> nList = new ArrayList<Integer>(T);
		for (t = 0; t < T; t++) {
			if ((textLine = br.readLine()) == null) {
				break;
			}
			nList.add(Integer.valueOf(textLine));
		}
		for (Integer n : nList) {
			pw.printf("%d\n", (1L << n) - 1);
			move_TowerOfHanoi('A', 'B', 'C', n);
		}
		pw.close();
	}

	public static void move_TowerOfHanoi(char A, char B, char C, int n) {
		if (n > 0) {
			move_TowerOfHanoi(A, C, B, n - 1);
			pw.printf("%c->%c\n", A, C);
			move_TowerOfHanoi(B, A, C, n - 1);
		}
	}
}

