import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Levenshtein {

	static int[][] distanceMatrix;
	static int rows;
	static int cols;

	ArrayList<String> path = new ArrayList<String>();
	ArrayList<String> pathWithIndex = new ArrayList<String>();
	int smallSum = 100;

	ArrayList<String> output = new ArrayList<String>();

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String s;
		ArrayList<String> inputString=new ArrayList<String>();
		
		while ((s = in.readLine()) != null) {
			Pattern r = Pattern.compile("[A-Za-z]+");
			Matcher m = r.matcher(s);
			if(m.matches())
			{
				inputString.add(s);
			}
			else {
				System.out.println("Invalid input string");
				System.exit(0);
			}
		}
		String source = inputString.get(0);
		String target = inputString.get(1);

		int srcLen = source.length() + 1;
		int tgtLen = target.length() + 1;

		distanceMatrix = new int[tgtLen][srcLen];

		distanceMatrix(source, target);

		rows = distanceMatrix.length;
		cols = distanceMatrix[0].length;
		
		/*for(int i=0;i<rows;i++) {
			for(int j=0;j<cols;j++) {
				System.out.print(distanceMatrix[i][j]+" ");
			}
			System.out.println();
		}*/

		Levenshtein l = new Levenshtein();
		l.allPaths(0, 0, "", "");
		l.minLength();

		Set<String> pathSet = new HashSet<String>();
		for (String str : l.pathWithIndex) {
			pathSet.add(str);
		}

		for (String str : pathSet) {
			l.getOperations(str, source, target);
		}

		System.out.println("There are total of " + l.output.size() + " sequence(s):");
		for (int i = 0; i < l.output.size(); i++) {
			System.out.println((i + 1) + ")" + " " + l.output.get(i));
		}
	}

	private void getOperations(String path, String source, String target) {

		int maxSteps = distanceMatrix[rows - 1][cols - 1];

		path = path.substring(1);
		String[] indices = path.split("-");
		String finalString = "";
		ArrayList<Character> output = new ArrayList<Character>();
		for (char c : source.toCharArray()) {
			output.add(c);
		}

		for (int k = 0; k < indices.length - 1; k++) {

			StringBuilder sb = new StringBuilder();
			for (Character s : output) {
				sb.append(s);
			}

			String[] temp = indices[k].split("=");
			int i = Integer.parseInt(temp[0]);
			int j = Integer.parseInt(temp[1]);

			String[] temp_1 = indices[k + 1].split("=");
			int i_1 = Integer.parseInt(temp_1[0]);
			int j_1 = Integer.parseInt(temp_1[1]);

			if ((i_1 + j_1) - (i + j) == 1) {
				if (i_1 - i == 0) {
					finalString += " " + sb + " delete " + source.charAt(j_1 - 1) + "->";
					output.remove(i);
					maxSteps--;
				} else {
					finalString += " " + sb + " insert " + target.charAt(i_1 - 1) + "->";
					output.add(i_1 - 1, target.charAt(i_1 - 1));
					maxSteps--;
				}
			} else if ((i_1 + j_1) - (i + j) == 2) {
				if (distanceMatrix[i][j] == distanceMatrix[i_1][j_1]) {
					// finalString += " " + sb + " Keeping " + source.charAt(j_1 - 1) + "->";
					continue;
				} else {
					finalString += " " + sb + " replace " + source.charAt(j_1 - 1) + " by " + target.charAt(i_1 - 1)
							+ "->";
					output.remove(i);
					output.add(i, target.charAt(i_1 - 1));
					maxSteps--;

				}
			}
		}
		StringBuilder sb = new StringBuilder();
		for (Character s : output) {
			sb.append(s);
		}
		if (maxSteps == 0 && sb.toString().contentEquals(target)) {
			this.output.add(finalString.trim() + " " + sb);
		}
	}

	public void allPaths(int currentRow, int currentColumn, String path, String path2) {

		if (currentRow == rows - 1) {
			for (int i = currentColumn; i < cols; i++) {
				path += "-" + distanceMatrix[currentRow][i];
				path2 += "-" + currentRow + "=" + i;
			}
			if (checkValidPath(path)) {
				this.pathWithIndex.add(path2.trim());
			}
			return;
		}
		if (currentColumn == cols - 1) {
			for (int i = currentRow; i < rows; i++) {
				path += "-" + distanceMatrix[i][currentColumn];
				path2 += "-" + i + "=" + currentColumn;
			}
			if (checkValidPath(path)) {
				this.pathWithIndex.add(path2.trim());
			}
			return;
		}
		path = path + "-" + distanceMatrix[currentRow][currentColumn];
		path2 += "-" + currentRow + "=" + currentColumn;
		allPaths(currentRow + 1, currentColumn + 1, path, path2);
		allPaths(currentRow, currentColumn + 1, path, path2);
		allPaths(currentRow + 1, currentColumn, path, path2);
	}

	private boolean checkValidPath(String path) {

		path = path.replaceAll("[a-z]", "");
		int totalSteps = distanceMatrix[distanceMatrix.length - 1][distanceMatrix[0].length - 1];
		int arr[];
		StringTokenizer st = new StringTokenizer(path, "-");
		int last = 0;
		int countTokens = st.countTokens();
		arr = new int[countTokens];
		int i = 0;
		while (st.hasMoreTokens() && i < countTokens) {
			arr[i] = Integer.parseInt(st.nextToken());
			last = arr[i];
			i++;
		}
		if (last == totalSteps && arraySortedOrNot(arr, arr.length) != 0) {
			this.path.add(path);
			return true;
		}
		return false;
	}

	private void minLength() {

		for (String element : path) {
			int tempSum = 0;
			StringTokenizer st = new StringTokenizer(element, "-");
			while (st.hasMoreElements()) {
				tempSum += Integer.parseInt(st.nextToken());
			}
			if (tempSum <= smallSum) {
				smallSum = tempSum;

			}
		}
		ArrayList<String> elementsToBeRetained = new ArrayList<String>();
		ArrayList<String> pathToBeRetainedDir = new ArrayList<String>();

		for (int i = 0; i < path.size(); i++) {
			int tempSum = 0;
			StringTokenizer st = new StringTokenizer(path.get(i), "-");
			while (st.hasMoreElements()) {
				tempSum += Integer.parseInt(st.nextToken());
			}
			if (tempSum == smallSum) {
				elementsToBeRetained.add(path.get(i));
				pathToBeRetainedDir.add(pathWithIndex.get(i));
				continue;
			}
		}
		path = new ArrayList<String>(elementsToBeRetained);
		pathWithIndex = new ArrayList<>(pathToBeRetainedDir);
	}

	private static void distanceMatrix(String source, String target) {

		for(int i=0;i<=target.length();i++) {
			distanceMatrix[i][0] = i;
		}
		for(int i=0;i<=source.length();i++) {
			distanceMatrix[0][i] = i;
		}
		for (int i = 1; i <= target.length(); i++) {
			
			for (int j = 1; j <= source.length(); j++) {
				int cost = indicatorFunction(target.charAt(i - 1), source.charAt(j - 1));
				distanceMatrix[i][j] = min(distanceMatrix[i - 1][j - 1] + cost, distanceMatrix[i - 1][j] + 1,
						distanceMatrix[i][j - 1] + 1);
			}
		}
	}

	private static int indicatorFunction(char a, char b) {
		return a == b ? 0 : 1;
	}

	private static int min(int... numbers) {
		return Arrays.stream(numbers).min().orElse(Integer.MAX_VALUE);
	}

	private static int arraySortedOrNot(int arr[], int n) {
		if (n == 1 || n == 0)
			return 1;

		if (arr[n - 1] < arr[n - 2])
			return 0;
		return arraySortedOrNot(arr, n - 1);
	}
}