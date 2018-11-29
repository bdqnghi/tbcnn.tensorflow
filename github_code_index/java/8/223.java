import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

/**
* Dynamic Programming
*/

public class AlterEdit {
  public static void main(String args[]) {
    Scanner myScanner = new Scanner(System.in);
    String start = myScanner.nextLine();
    String target = myScanner.nextLine();
    int[][] memo = new int[start.length() + 1][target.length() + 1];
    String[][] prev = new String[start.length() + 1][target.length() + 1];
    String[][] chr = new String[start.length() + 1][target.length() + 1];

    // initializes the cost (memo) table to max value ints also fills out the base cases for the table
    for (int i = 0; i < start.length() + 1; i++) {
      for (int j = 0; j < target.length() + 1; j++) {
        memo[i][j] = -Integer.MAX_VALUE;

        if (i == 0 && j != 0) {
          memo[i][j] = j * 2;
          prev[i][j] = i + "," + (j - 1);
          chr[i][j] = "add " + target.charAt(j - 1);

        }
        if (j == 0 && i != 0) {
          memo[i][j] = 2;
          prev[i][j] = (i - 1) + "," + j;
          chr[i][j] = "delete " + start.charAt(i - 1);
        }
        if (i == 0 && j == 0) {
          memo[i][j] = 0;
          prev[i][j] = null;
          chr[i][j] = null;
        }

      }
    }

    // calls edit distance 
    int count = editDistance(start.length(), target.length(), start, target, memo, prev, chr);
    System.out.println(count);
    // prints the result
    print(start.length(), target.length(), start, target, memo, prev, chr);
   
  }

  public static int editDistance(int i, int j, String s1, String s2, int[][] memo, String[][] prev,
      String[][] chr) {
    // base case
    if (i == 0) {
      return memo[i][j];
    }
    if (j == 0) {

      return memo[i][j];
    }
    // calls memoized result
    if (-Integer.MAX_VALUE != memo[i][j]) {
      return memo[i][j];
    }
    // no op change
    if (s1.charAt(i - 1) == s2.charAt(j - 1)) {
      memo[i][j] = editDistance(i - 1, j - 1, s1, s2, memo, prev, chr);
      prev[i][j] = (i - 1) + "," + (j - 1);
      chr[i][j] = null;
      return memo[i][j];
    }
    // accounts for special change cost cases
    int changeCost;
    if ((Character.isUpperCase(s1.charAt(i - 1)) && Character.isUpperCase(s2.charAt(j - 1)))
        || (Character.isLowerCase(s2.charAt(j - 1)) && Character.isLowerCase(s1.charAt(i - 1)))
        || (!Character.isLetter(s2.charAt(j - 1)) || !Character.isLetter(s1.charAt(i - 1)))) {
      changeCost = 1;
    }
    else {
      changeCost = 2;
    }
    int insert = editDistance(i, j - 1, s1, s2, memo, prev, chr) + 2;
    
    // checks for multiple long deletes
    int longDistance = Integer.MAX_VALUE;
    int kCount = 0;
    for (int k = i; k > 0; k--) {
      int tempD = editDistance(k - 1, j, s1, s2, memo, prev, chr);
      if (tempD < longDistance) {
        longDistance = tempD;
        kCount = k - 1;
      }
    }
    longDistance += 2;

    int change = editDistance(i - 1, j - 1, s1, s2, memo, prev, chr) + changeCost;
    int result = 0;
    String index = "";
    String msg = "";
    
    // compares the minimum cost between the adds, deletes and changes
    // also adds the message and previous move to the respective tables
    // also accounts for ties (modify, short delete (1 character), long delete, add)
    if (insert <= longDistance && insert <= change) {
      result = insert;
      index = i + "," + (j - 1);
      msg = "add " + s2.charAt(j - 1);

    }

    if (longDistance <= insert && longDistance <= change) {
      result = longDistance;
      index = kCount + "," + j;
      msg = "delete " + s1.substring(kCount, i);

    }

    if (change <= insert && change <= longDistance) {
      result = change;
      index = (i - 1) + "," + (j - 1);
      msg = "change " + s1.charAt(i - 1) + " to " + s2.charAt(j - 1);
    }
    // adds the best results to the tables
    memo[i][j] = result;
    prev[i][j] = index;
    chr[i][j] = msg;
    System.err.println(result + " " + msg);
    return (result);

  }

  public static void print(int i, int j, String s1, String s2, int[][] memo, String[][] prev,
      String[][] chr) {
    String prevValue = prev[i][j];
    ArrayList<String> temp = new ArrayList<String>();

    if (chr[i][j] != null) {
      temp.add(chr[i][j]);
    }
    while (prevValue != null) {
      String[] parts = prevValue.split(",");
      String iVal = parts[0];
      String jVal = parts[1];
      String msg = chr[Integer.parseInt(iVal)][Integer.parseInt(jVal)];
      // gets the msg from the table
      if (msg != null) {
        temp.add(chr[Integer.parseInt(iVal)][Integer.parseInt(jVal)]);
      }
      // moves onto the next value
      prevValue = prev[Integer.parseInt(iVal)][Integer.parseInt(jVal)];
    }
    for (int k = temp.size() - 1; k >= 0; k--) {
      System.out.println(temp.get(k));
    }

  }

}
