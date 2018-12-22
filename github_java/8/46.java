
class LevenshteinDistance {
	public static int minimum(int a, int b, int c) {
		if ((a <= b) && (a <= c))
			return a;
		if ((b <= a) && (b <= c))
			return b;
		if ((c <= b) && (c <= a))
			return c;

		return 0;
	}

	public static int distance(String first, String second) {
		int[][] matrix = new int[first.length() + 1][second.length() + 1];

		for (int i = 0; i <= first.length(); i++) {
			for (int j = 0; j <= second.length(); j++) {
				if (j == 0) {
					matrix[i][j] = i;
				} else if (i == 0) {
					matrix[i][j] = j;
				} else {
					matrix[i][j] = 0;
				}
			}
		}

		for (int i = 1; i <= first.length(); i++) {
			for (int j = 1; j <= second.length(); j++) {
				if (first.substring(i-1, i).equals(second.substring(j-1, j))) {
					matrix[i][j] = matrix[i-1][j-1];
				} else {
					matrix[i][j] = minimum(matrix[i-1][j] + 1, matrix[i][j-1] + 1, matrix[i-1][j-1] + 1);
				}
			}
		}

		return matrix[first.length()][second.length()];
	}

	public static void main(String[] args) {
		System.out.println("The distance between 'kitten' and 'sitting' is " + distance("kitten", "sitting"));
		System.out.println("The distance between 'Saturday' and 'Sunday' is " + distance("Saturday", "Sunday"));
	}
}
