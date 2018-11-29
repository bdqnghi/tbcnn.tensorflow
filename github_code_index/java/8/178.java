import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;

/**
 * EditDistance.java
 *
 * Problem: Given two strings, find the least
 * expensive match-up for them.
 *
 * Costs: Insert a gap = 2
 *        Letter mismatch = 1
 *        Letter match = 0
 *
 * @author tsteinke
 *
 */

public class EditDistance {
	public static void main(String[] args) {
    if(args.length == 0) {
      System.out.println("Provide the filename!");
      return;
    }

    // Input the transactions
    Scanner input;
    try {
      input = new Scanner(new File(args[0]));
    }
    catch(FileNotFoundException e) {
      e.printStackTrace();
      return;
    }

    String sequences[] = new String[2];
    sequences[0] = input.next();
    sequences[1] = input.next();

    computeEditDistance(sequences, args.length > 1 && args[1].equals("--no-tb"));
  }

  public static void computeEditDistance(String[] sequences, boolean noTraceback) {
    int[][] distanceTable = new int[sequences[0].length() + 1][sequences[1].length() + 1];
    for(int j = 0; j < distanceTable[0].length; j ++)
      distanceTable[0][j] = 2 * j;
    for(int i = 0; i < distanceTable.length; i ++)
      distanceTable[i][0] = 2 * i;

    for(int i = 1; i < distanceTable.length; i ++)
      for(int j = 1; j < distanceTable[0].length; j ++)
        distanceTable[i][j] = -1;

    int ndx[] = new int[] { sequences[0].length(), sequences[1].length() };
    computeEditDistance(distanceTable, sequences, ndx);
    System.out.println("Edit Distance = " + distanceTable[sequences[0].length()][sequences[1].length()]);

    if(noTraceback == true)
      return;

    // Traceback time
    // Start at the end, so ndx
    ArrayList<String> traceback = new ArrayList<String>();
    while(ndx[0] > 0 && ndx[1] > 0) {
      // Check for equality first
      char firstLetter = sequences[0].charAt(ndx[0] - 1);
      char secondLetter = sequences[1].charAt(ndx[1] - 1);
      if(firstLetter == secondLetter) {
        traceback.add(0, firstLetter + " " + secondLetter + " 0");
        ndx[0] --;
        ndx[1] --;
      }
      else {
        // Figure out where we came from
        int myScore = distanceTable[ndx[0]][ndx[1]];
        if(distanceTable[ndx[0] - 1][ndx[1] - 1] + 1 == myScore) {
          traceback.add(0, firstLetter + " " + secondLetter + " 1");
          ndx[0] --;
          ndx[1] --;
        }
        // This means that we skipped over sequences[1][ndx[1]]
        else if(distanceTable[ndx[0] - 1][ndx[1]] + 2 == myScore) {
          traceback.add(0, firstLetter + " - 2");
          ndx[0] --;
        }
        // Otherwise we skipped over the first sequence
        else {
          traceback.add(0, "- " + secondLetter + " 2");
          ndx[1] --;
        }
      }
    }

    // Endings
    while(ndx[0] > 0) {
      traceback.add(0, sequences[0].charAt(ndx[0] - 1) + " - 2");
      ndx[0] --;
    }
    while(ndx[1] > 0) {
      traceback.add(0, "- " + sequences[1].charAt(ndx[1] - 1) + " 2");
      ndx[1] --;
    }

    // Display
    for(String trace : traceback) {
      System.out.println(trace);
    }
  }

  public static void computeEditDistance(int[][] distanceTable, String sequences[], int ndx[]) {
    // We'll need this in either case
    if(distanceTable[ndx[0] - 1][ndx[1] - 1] < 0)
      computeEditDistance(distanceTable, sequences, new int[] { ndx[0] - 1, ndx[1] - 1 });

    // If last symbols are equal, add 0 to A[0..n-2] and B[0..m-2]
    if(sequences[0].charAt(ndx[0] - 1) == sequences[1].charAt(ndx[1] - 1)) {
      distanceTable[ndx[0]][ndx[1]] = distanceTable[ndx[0] - 1][ndx[1] - 1];
    }
    // No match? Two options:
    // Take one point penalty for a mismatch and add that to A[0..n-2] and B[0..m-2]
    // Orrr take a two point penalty for the min of A[0..n-2
    else {
      // Compute the two-penalty options
      if(distanceTable[ndx[0]][ndx[1] - 1] < 0)
        computeEditDistance(distanceTable, sequences, new int[] { ndx[0], ndx[1] - 1 });

      if(distanceTable[ndx[0] - 1][ndx[1]] < 0)
        computeEditDistance(distanceTable, sequences, new int[] { ndx[0] - 1, ndx[1] });

      distanceTable[ndx[0]][ndx[1]] = Math.min(distanceTable[ndx[0] - 1][ndx[1] - 1] + 1,
        Math.min(distanceTable[ndx[0] - 1][ndx[1]], distanceTable[ndx[0]][ndx[1] - 1]) + 2);
    }
  }
}

