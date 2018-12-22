import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

/**
 * The class implements inefficient, but correct, sorting according to the
 * comparison defined in the comparator.
 * 
 * @author elenam
 * 
 */

public class Radix {

	public static void main(String[] args) throws InterruptedException {
		if (args.length < 2) {
			System.out
					.println("Please run with two command line arguments: input and output file names");
			System.exit(0);
		}

		String inputFileName = args[0];
		String outFileName = args[1];
		
		String[] data = readInData(inputFileName);
		
		String [] toSort = data.clone();
		
		sort(toSort);  // JVM warmup
		
		toSort = data.clone();
		
		Thread.sleep(10); //to let other things finish before timing; adds stability of runs

		long start = System.currentTimeMillis();
		
		sort(toSort);
		
		long end = System.currentTimeMillis();
		
		System.out.println(end - start);

		writeOutResult(toSort, outFileName);
	}

	private static String[] readInData(String inputFileName) {
		ArrayList<String> input = new ArrayList<String>();
		Scanner in;
		try {
			in = new Scanner(new File(inputFileName));
			while (in.hasNext()) {
				input.add(in.next());
			}
			in.close();

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

		// System.out.println(input);

		return input.toArray(new String[0]); // convert to array of strings
	}

	// YOUR SORTING METHOD GOES HERE: (you may call other methods and use other classes). 
	private static void sort(String[] toSort) {
		int length = toSort.length;
		String[] other = new String[length];
		
		/* index 10 */
		// the array should have indexes 48 to 57
		int[] counts = new int[58];
		// count up the digits
		for (int i = 0; i < length; i++) {
			counts[toSort[i].charAt(10)]++;
//			counts[57]++;
		}
		// adjust counts for 0 indexing
		counts[48]--;
		// get a cumulative sum of the counts
		for (int i = 49; i < 58; i++) {
			counts[i] += counts[i - 1];
		}
		// copy into other array
		for (int i = length - 1; i > -1; i--) {
			other[counts[toSort[i].charAt(10)]--] = toSort[i];
//			other[counts[57]--] = toSort[i];
		}
		
		/* index 9 */
		// the array should have indexes 48 to 57
		counts = new int[58];
		// count up the digits
		for (int i = 0; i < length; i++) {
			counts[other[i].charAt(9)]++;
//			counts[57]++;
		}
		// adjust counts for 0 indexing
		counts[48]--;
		// get a cumulative sum of the counts
		for (int i = 49; i < 58; i++) {
			counts[i] += counts[i - 1];
		}
		// copy into other array
		for (int i = length - 1; i > -1; i--) {
			toSort[counts[other[i].charAt(9)]--] = other[i];
//			toSort[counts[57]--] = other[i];
		}
		
		
	}

	private static void writeOutResult(String[] sorted, String outputFilename) {
		try {
			PrintWriter out = new PrintWriter(outputFilename);
			for (String str : sorted) {
				out.println(str);
			}
			out.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}