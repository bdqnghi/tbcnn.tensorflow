package etc.stringdistance;

public class Main {

	/**
	 * @param d
	 *            2d-matrix
	 * @return pritns d in human-readable form
	 */
	public static String printMatrix(final int[][] d) {
		String s = "";
		for (final int[] element : d) {
			for (final int element2 : element) {
				s += element2 + " ";
			}
			s += "\r\n";
		}
		return s;
	}

	/**
	 * Debug-method to pretty-print the two distances of the input words
	 *
	 * @param input
	 *            words to compare
	 */
	private static void printDistances(final String... input) {
		// actual pairing
		for (int i = 0; i < input.length; i++) {
			for (int j = i + 1; j < input.length; j++) {
				final StringDistance ld = new LevenshteinDistance(input[i], input[j]);
				final StringDistance dld = new DamerauLevenshteinDistance(input[i], input[j]);

				System.out.println(String.format("'%s' vs. '%s':", input[i],
						input[j]));
				System.out.println("Levenshtein-Distance: " + ld.getDistance()
						+ " Transformation-process:");
				System.out.println(ld.getProcessString());
				System.out.println();

				System.out.println("Damerau-Levenshtein-Distance: " + dld.getDistance()
						+ " Transformation-process:");
				System.out.println(dld.getProcessString());

				// System.out.println(ld.toLaTeXString());
			}
		}
	}

	public static void main(final String[] args) {
		printDistances("Fussball", "Football", "Futsal");
		printDistances("Rentner", "Renntier");
		printDistances("people", "pepole");
	}
}
