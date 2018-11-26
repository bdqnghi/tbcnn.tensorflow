import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.TreeMap;
import java.util.TreeSet;

public class B {

	public static void main(String[] args) throws IOException {

		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));

		String dat[] = in.readLine().split(" ");

		int r = Integer.parseInt(dat[0]);
		int c = Integer.parseInt(dat[1]);

		while (r != 0 && c != 0) {

			boolean[][] seats = new boolean[r][c + 1];

			int p = Integer.parseInt(in.readLine());

			for (int i = 0; i < p; i++) {
				dat = in.readLine().split(" ");

				int row = dat[0].charAt(0) - 'A';
				int column = Integer.parseInt(dat[0].substring(1, dat[0].length()));

				if (dat[1].equals("-")) {
					column--;
				}

				seats[row][column] = true;

			}

			int z = Integer.parseInt(in.readLine());

			TreeSet<seat> pos = new TreeSet<>();

			for (int i = 0; i < z; i++) {
				String lin = in.readLine();
				pos.add(new seat(lin.charAt(0), Integer.parseInt(lin.substring(1, lin.length()))));
			}

			boolean posible = true;

			for (seat s : pos) {
				if (!seats[s.r][s.c-1]) {
					seats[s.r][s.c-1] = true;
				}else if (!seats[s.r][s.c]) {
					seats[s.r][s.c] = true;
				}else {
					posible = false;
					break;
				}
			}

			if (posible) {
				out.write("YES\n");
			} else {
				out.write("NO\n");
			}

			// for (boolean[] lin : seats) {
			// for (boolean v : lin) {
			// System.out.print(v + " ");
			// }
			// System.out.println("");
			// }
			//
			// System.out.println("");

			dat = in.readLine().split(" ");

			r = Integer.parseInt(dat[0]);
			c = Integer.parseInt(dat[1]);

		}

		out.close();

	}

	static class seat implements Comparable<seat> {

		int r;
		int c;

		public seat(char r, int c) {
			this.r = r - 'A';
			this.c = c;
		}

		@Override
		public int compareTo(seat o) {
			return this.r != o.r ? this.r - o.r : this.c - o.c;
		}

		@Override
		public String toString() {
			return (char) r + "" + c + "";
		}

	}

}
