package adsa;

public class Rodcutting {
	public static void main(String[] args) {
		int p[] = { 0,1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
		int l[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int[] rev = maxRevenue(p, 6);
		printArray(rev);
	}

	static int[] maxRevenue(int p[], int n) {
		int rev[] = new int[n + 1];
		rev[0] = 0;
		for (int i = 1; i <= n; i++) {
			int q = -1;
			for (int j = 1; j <= i; j++) {
				q = Math.max(q, p[j] + rev[i - j]);
			}
			rev[i] = q;
		}
		return rev;
	}

	public static void printArray(int a[]) {
		for (int i = 0; i < a.length; i++) {
			System.out.print(a[i] + " ");
		}
		System.out.println();
	}
}