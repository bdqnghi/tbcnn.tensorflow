import java.io.*;
import java.util.*;
public class Swamp 
{
	private static int[][] loadSwamp(String infileName, int[] dropInPt) throws Exception 
	{
		Scanner infile = new Scanner(new File(infileName));
		int rows = infile.nextInt();
		int cols = rows;
		dropInPt[0] = infile.nextInt();
		dropInPt[1] = infile.nextInt();
		int[][] swamp = new int[rows][cols];
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				swamp[r][c] = infile.nextInt();
			}
		}
		infile.close();
		return swamp;
	}
	public static void main(String[] args) throws Exception 
	{
		int[] dropInPt = new int[2];
		int[][] swamp = loadSwamp(args[0], dropInPt);
		int row = dropInPt[0], col = dropInPt[1];
		String path = "";
		depthFirstSearch(swamp, row, col, path);
	}
	static void depthFirstSearch(int[][] swamp, int r, int c, String path) 
	{
		path += "[" + r + "," + c + "]";
		if ((r == 0) || (r == swamp.length - 1) || (c == 0) || (c == swamp.length - 1)) {
			System.out.println(path);
			return;
		}
		if (swamp[r - 1][c] == 1) {
			swamp[r][c] = 0;
			depthFirstSearch(swamp, r - 1, c, path);
			swamp[r - 1][c] = 1;
		}
		if (swamp[r - 1][c + 1] == 1) {
			swamp[r][c] = 0;
			depthFirstSearch(swamp, r - 1, c + 1, path);
			swamp[r - 1][c + 1] = 1;
		}
		if (swamp[r][c + 1] == 1) {
			swamp[r][c] = 0;
			depthFirstSearch(swamp, r, c + 1, path);
			swamp[r][c + 1] = 1;
		}
		if (swamp[r + 1][c + 1] == 1) {
			swamp[r][c] = 0;
			depthFirstSearch(swamp, r + 1, c + 1, path);
			swamp[r + 1][c + 1] = 1;
		}
		if (swamp[r + 1][c] == 1) {
			swamp[r][c] = 0;
			depthFirstSearch(swamp, r + 1, c, path);
			swamp[r + 1][c] = 1;
		}
		if (swamp[r + 1][c - 1] == 1) {
			swamp[r][c] = 0;
			depthFirstSearch(swamp, r + 1, c - 1, path);
			swamp[r + 1][c - 1] = 1;
		}
		if (swamp[r][c - 1] == 1) {
			swamp[r][c] = 0;
			depthFirstSearch(swamp, r, c - 1, path);
			swamp[r][c - 1] = 1;
		}
		if (swamp[r - 1][c - 1] == 1) {
			swamp[r][c] = 0;
			depthFirstSearch(swamp, r - 1, c - 1, path);
			swamp[r - 1][c - 1] = 1;
		}
	}
}
