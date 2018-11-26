import java.io.File;
import java.io.PrintStream;
import java.util.Locale;
import java.util.Scanner;
import java.util.SortedSet;
import java.util.TreeSet;

public class B {

	private static int treeSize(int[][] tree, int cur, int par) {
		int res = 1;
		for (int i = 0; i < tree[cur].length; i++) {
			int child = tree[cur][i];
			if (child != par) {
				res += treeSize(tree, child, cur);
			}
		}
		return res;
	}

	private static int buildBinaryTree(int[][] tree, int cur, int par) {
		int count = tree[cur].length;
		if (par != -1) {
			count--;
		}
		if (count == 0) {
			return 0;
		} else if (count == 1) {
			for (int i = 0; i < tree[cur].length; i++) {
				int child = tree[cur][i];
				if (child != par) {
					return treeSize(tree, child, cur);
				}
			}
			return 0;
		} else {

			int[] size = new int[count];
			int[] build = new int[count];

			int index = 0, tSize = 0;

			for (int i = 0; i < tree[cur].length; i++) {
				int child = tree[cur][i];
				if (child != par) {
					size[index] = treeSize(tree, child, cur);
					build[index] = buildBinaryTree(tree, child, cur);

					tSize += size[index];
					index++;
				}
			}
			int min = tree.length;
			for (int i = 0; i < size.length; i++)
				for (int j = i + 1; j < size.length; j++) {
					int res = build[i] + build[j] + tSize - size[i] - size[j];
					if (res < min)
						min = res;
				}
			return min;
		}

	}

	public static void main(String[] args) throws Exception {
		Locale.setDefault(Locale.US);

		Scanner in = new Scanner(new File("problem.in"));
		PrintStream out = new PrintStream(new File("problem.out"));

		int T = in.nextInt();
		for (int test = 1; test <= T; test++) {
			int n = in.nextInt();
			int[] x = new int[n - 1], y = new int[n - 1], k = new int[n];
			int[][] tree = new int[n][];

			for (int i = 0; i < n - 1; i++) {
				x[i] = in.nextInt() - 1;
				y[i] = in.nextInt() - 1;
				k[x[i]]++;
				k[y[i]]++;
			}
			for (int i = 0; i < n; i++) {
				tree[i] = new int[k[i]];
				int c = 0;
				for (int j = 0; j < x.length; j++) {
					if (x[j] == i) {
						tree[i][c] = y[j];
						c++;
					} else if (y[j] == i) {
						tree[i][c] = x[j];
						c++;
					}
				}
			}
			int min = n;
			for (int i = 0; i < n; i++) {
				int res = buildBinaryTree(tree, i, -1);

				if (res < min)
					min = res;

			}

			out.println("Case #" + test + ": " + min);

		}

	}
}
