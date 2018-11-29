package praktikum.blatt8;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 * EditDistance
 * 
 * @author Lukas Potthast, Hendrik Schmieding, Tim Raven
 * @version 0.0.0.2
 * @time 01.06.2015 23:12
 */

public class EditDistance {
	
	/**
	 * Entrance point.
	 * @param args Program arguments
	 */
	public static void main(String[] args) {
//		args = new String[3];
//		args[0] = "baacda";
//		args[1] = "abace";
//		args[2] = "-o";
		
//		args = new String[2];
//		args[0] = "res/blatt8/data.txt";
//		args[1] = "-o";
		
		//No arguments
		if(args.length == 0) {
			System.out.println("Error: No program arguments specified!\nProgram terminates...");
			return;
		}
		
		//First argument is a correct path
		File textFile = new File(args[0]);
		if(textFile.isFile()) {
			if(args.length > 1 && args[args.length - 1].equals("-o"))
				processTextFile(textFile, true);
			else
				processTextFile(textFile, false);
			return;
		}
		
		//Only one (invalid!) argument exists
		if(args.length == 1) {
			System.out.println("Error: First argument is not, but was supposed to be, a valid file! No further arguments found.\nProgram terminates...");
			return;
		}
		
		//First argument was not a path & there is one more argument
		if(args.length == 2) {
			System.out.println(distance(args[0], args[1], false));
		}
		
		//First argument was not a path & there are more arguments
		if(args.length == 3) {
			if(args[2].equals("-o")) 
				distance(args[0], args[1], true);
			else
				System.out.println(distance(args[0], args[1], false));
		}
	}
	
	private static void processTextFile(final File textFile, final boolean additionalOutput) {
		ArrayList<String> strings = new ArrayList<>();
		
		int lineCount = 0;
		
		//Create a BufferedReder to read the text file (try-with-resources)
		try(BufferedReader intervalReader = new BufferedReader(new FileReader(textFile))) {
			
			String line;
			//Read line by line and add the data to an array list
			while((line = intervalReader.readLine()) != null) {
				strings.add(line);
				lineCount++;
			}
		
		//Catch possible exceptions
		} catch(final FileNotFoundException fnfe) {
			System.err.println("processTextFile: Error: Given path does not corrspond to a valid file!");
			return;
		} catch (IOException e) {
			System.err.println("processTextFile: An I/O error occured in line " + (lineCount + 1) + "!");
			return;
		}
		
		//Call the levenshtein distance algorithm with the read data
		for(int i = 0; i < strings.size() - 1; i += 2) {
			if(additionalOutput) {
				distance(strings.get(i), strings.get(i + 1), true);
				System.out.print("\n\n");
			} else
				System.out.println(distance(strings.get(i), strings.get(i + 1), false));
		}
		
		//If the amount of string objects (=lines) was odd
		if(strings.size() % 2 == 1) {
			if(additionalOutput)
				distance(strings.get(strings.size() - 1), "", true);
			else
				System.out.println(distance(strings.get(strings.size() - 1), "", false));
		}
	}

	/**
	 * Calculates the Levenshtein-Distance for the two given strings.
	 * @param a String A
	 * @param b String B
	 * @return Levenshtein-Distance
	 */
	public static int distance(final String a, final String b, final boolean additionalOutput) {
		int[][] helper = new int[a.length() + 1][b.length() + 1];
		
		//Set first column to incrementing values
		for(int i = 0; i < helper.length; i++)
			helper[i][0] = i;
		
		//Set first row to incrementing values
		for(int j = 0; j < helper[0].length; j++)
			helper[0][j] = j;
		
		//Fill matrix
		for(int i = 1; i < helper.length; i++) {
			for(int j = 1; j < helper[0].length; j++) {
				
				//do nothing (characters are equal)
				if(a.charAt(i - 1) == b.charAt(j - 1))
					helper[i][j] = helper[i - 1][j - 1];
				else
					helper[i][j] = minimum(helper[i - 1][j]     + 1, //deletion
										   helper[i]    [j - 1] + 1, //insertion
										   helper[i - 1][j - 1] + 1);//substitution
			}
		}
		
		//Output
		if(additionalOutput)
			printEditOperations(a, b, helper);
		
		return helper[helper.length - 1][helper[0].length - 1];
	}
	
	/**
	 * Prints the necessary operations to convert string A into string B into the currently standard output stream.
	 * @param a String A
	 * @param b String B
	 * @param helper int[][] helper-array
	 */
	private static void printEditOperations(final String a, final String b, final int[][] helper) {
		System.out.println("Loesung fuer \"" + a + "\" --> \"" + b + "\" mit Gesamtkosten " + helper[helper.length - 1][helper[0].length - 1] + ":");
		System.out.println("=====================================================");
		
		int i = helper.length - 1;
		int j = helper[0].length - 1;
		int step = 1;
		StringBuilder copy = new StringBuilder(a);
		
		while(i >= 0 && j >= 0) {
			
			if(i > 0 && helper[i - 1][j] + 1 == helper[i][j]) {
				copy.deleteCharAt(i - 1);
				System.out.println(step++ + ") Kosten 1: Loesche " + a.charAt(i - 1) + " an Position " + i + "  -->  " + copy.toString());
				i--;
				continue;
			}
			
			if(j > 0 && helper[i][j - 1] + 1 == helper[i][j]) {
				copy.insert(i, b.charAt(j - 1));
				System.out.println(step++ + ") Kosten 1: Fuege " + b.charAt(j - 1) + " an Position " + i + " ein  -->  " + copy.toString());
				j--;
				continue;
			}
			
			if(i > 0 && j > 0 && helper[i - 1][j - 1] + 1 == helper[i][j]) {
				copy.setCharAt(i - 1, b.charAt(j - 1));
				System.out.println(step++ + ") Kosten 1: Ersetze " + a.charAt(i - 1) + " durch " + b.charAt(j - 1) + " an Position " + i + "  -->  " + copy.toString());
				i--; j--;
				continue;
			}
			
			if(i > 0 && j > 0 && helper[i - 1][j - 1] == helper[i][j]) {
				copy.setCharAt(i - 1, b.charAt(j - 1));
				System.out.println(step++ + ") Kosten 0: Ersetze " + a.charAt(i - 1) + " durch " + b.charAt(j - 1) + " an Position " + i + "  -->  " + copy.toString());
				i--; j--;
				continue;
			}
			
			if(i == 0 && j == 0)
				break;
		}
	}
	
	/**
	 * Returns the minimum of the three given values using multiple Math.min() function calls.
	 * @param arg1 Argument 1
	 * @param arg2 Argument 2
	 * @param arg3 Argument 3
	 * @return minimum of these
	 */
	private static int minimum(final int arg1, final int arg2, final int arg3) {
		return Math.min(arg1, Math.min(arg2, arg3));
	}
	
//	/**
//	 * Prints the twi dimensional helper array in the currently active standard output stream.
//	 * @param a String A
//	 * @param b String B
//	 * @param helper int[][] helper-array
//	 */
//	private static void printHelperArray(final String a, final String b, final int[][] helper) {
//		System.out.println("Helper matrix:");
//		System.out.print("\t\"\"\t");
//		for(int i = 0; i < b.length(); i++)
//			System.out.print(b.charAt(i) + "\t");
//		System.out.print("\n");
//		
//		for(int i = 0; i < helper.length; i++) {
//			if(i == 0)
//				System.out.print("\"\"\t");
//			else
//				System.out.print(a.charAt(i-1) + "\t");
//			
//			for(int j = 0; j < helper[0].length; j++) {
//				System.out.print(helper[i][j] + "\t");
//			}
//			System.out.print("\n");
//		}
//	}
	
}
