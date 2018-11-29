import java.util.Scanner;
import java.util.List;

public class connectDots {

	static int Count;
	static int m;
	static int n;

	public static void main(String[] args) {

		Scanner in = new Scanner(System.in);
		int temp;

		m = in.nextInt();
		n = in.nextInt();

		int[][] Space;
		Space = new int[m + 2][n + 2];

		for (int i = 0; i < m + 2; i++) {
			for (int j = 0; j < n + 2; j++) {
				if (i == 0 || j == 0 || i == m + 1 || j == n + 1) {
					Space[i][j] = 0;
					continue;
				}

				Space[i][j] = in.nextInt();
			}
		}

		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				if (Space[i][j] == 1) {
					temp = depthFirstSearch(Space, i, j);
					if (Count < temp) {
						Count = temp;
					}
				}
			}
		}

		System.out.println(Count);

	}

	public static int depthFirstSearch(int[][] Space, int i, int j) {

		if (Space[i][j] == 0)
			return 0;
		else {
			Space[i][j] = 0 ;
			return 1 + depthFirstSearch(Space, i + 1, j)
					+ depthFirstSearch(Space, i - 1, j)
					+ depthFirstSearch(Space, i, j + 1)
					+ depthFirstSearch(Space, i, j - 1)
					+ depthFirstSearch(Space, i+1, j+1)
					+ depthFirstSearch(Space, i-1, j-1)
					+ depthFirstSearch(Space, i+1, j-1)
					+ depthFirstSearch(Space, i-1, j+1);
		}

	}

	static void printGrid(int[][] Space) {

		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				System.out.print(Space[i][j] + " ");
			}
			System.out.println();
		}

	}

}
