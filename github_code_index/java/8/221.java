package Algorithms;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;

public class EditDistance {
	
	public class MatchObj{
		private String bestMatch;
		private int editDistance;
		private int[][] matrix;
		private int m;
		private int n;
		
		public MatchObj(String bestMatch, int editDistance, int[][] matrix, int m, int n) {
			this.bestMatch = bestMatch;
			this.editDistance = editDistance;
			this.matrix = matrix;
			this.m = m;
			this.n = n;
		}
		
		public String getBestMatch() {
			return bestMatch;
		}
		
		public int getEditDistance() {
			return editDistance;
		}
		
		public int[][] getEditMatrix(){
			return matrix;
		}
	
		private void printMatrix() {
			for(int i = 0; i < m; i++) {
				for(int j = 0;j < n;j++) {
					System.out.print(matrix[i][j] + "\t");
				}
					System.out.println();
			   }
	    }	
	}
	
	/*
	 * Finds the string in 'CompareList' closest to 'input'
	 * Given an input String and a String[], this will return an ArrayList of MatchObj objects.
	 * If there is a single 'best match', the returned list will contain a single object.
	*/
	public ArrayList<MatchObj> findBestMatch(String input, String[] CompareList) {
		int min_distance = Integer.MAX_VALUE;
		ArrayList<MatchObj> possible_matches = new ArrayList<MatchObj>();
		
		String s1 = input.toLowerCase();
			
		for(int l = 0; l < CompareList.length; l++) {
			String s2 = CompareList[l].toLowerCase();;
			if((int) s2.charAt(s2.length()-1) == 13 || s2.charAt(s2.length()-1) == '\n') {
				s2 = s2.substring(0, s2.length()-1);
			}
			
			MatchObj match = findEditDistance(s1, s2);
			int d = match.getEditDistance();
			if(d < min_distance) {
				min_distance = d;
				possible_matches.clear();
				possible_matches.add(match);
			}else if(d == min_distance) {
				possible_matches.add(match);
			}
		}
		
		return possible_matches;
	}
	
	/*
	 * Calculated edit distance between String s1 and String s2
	 * Returns the edit distance (bottom-rightmost value of matrix)
	*/
	public MatchObj findEditDistance(String s1, String s2) {
		final int l1 =  s1.length() + 1;
		final int l2 =  s2.length() + 1;
			int[][] M = new int[l1][l2];
			
		/* Initialize Matrix */
		for(int i = 0; i < l1; i++) {
			M[i][0] = i;
		}
		for(int i = 0; i < l2; i++) {
			M[0][i] = i;
		}
		
		for(int i = 1; i < l1; i++) {
			for(int j = 1; j < l2; j++) {
				if(s1.charAt(i-1) == s2.charAt(j-1)){
					M[i][j] = M[i-1][j-1];
				}else {
					M[i][j] = min3(M[i-1][j], M[i-1][j-1], M[i][j-1]) + 1;
				}
			}
		}
		MatchObj m = new MatchObj(s2, M[l1-1][l2-1], M, l1, l2);
		return m;
	}
	
	/*
	 * Used in edit distance algorithm
	 * Returns the minimum of 3 values
	*/
	public static int min3(int one, int two, int three){
		int check_one = Math.min(one, two);
		int check_two = Math.min(check_one, three);
		return check_two;
	}
	
	/*
	 * Used to create list to pass into findBestMatch() if reading from a file
	 * Returns a String[] of each line in the file
	*/
	public String[] splitFileContents(String fileName){
		String contents = "";
		try {
			contents = new String(Files.readAllBytes(Paths.get(fileName)));
		}catch(Exception e) {
			e.printStackTrace();
		}
		String[] list = contents.split("\n");
		return list;
	}
	   
	/*
	 * Creates/writes to 'filename'
	 * The file will contain each a list of "best matches" if the list contains one or more matches
	*/
	   private static void outputToFile(ArrayList<MatchObj> list, String filename) {
	    	try {
	    	File file = new File(filename);
	    	if(!file.exists()) {
	    		file.createNewFile();
	    		return;
	    	}
	    	PrintWriter writer = new PrintWriter(file);
	    	for(int i = 0; i < list.size(); i++) {
	    		if(i > 0) {
	    			writer.println();
	    		}
	    		writer.println(list.get(i).getBestMatch());
	    	}
	    	writer.close();
	    	}catch (IOException e) {
	    		e.printStackTrace();
	    	}
	    }
}
