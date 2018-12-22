package asgmt4;

import fileutils.FileUtils;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * User: lbhat@damsl
 * Date: 11/10/13
 * Time: 4:41 PM
 */
public class MinimumEditDistanceAligner {
    public static void main (String[] args) {
        List<String> strings = FileUtils.getStringsFromStdIn();
        strings = FileUtils.getNucleotideStringsFromFastaStrings(strings);
        align(strings.get(0), strings.get(1));
    }

    // I is vertical, D is horizontal and M/R is diagonal
    public static void align (String s, String t) {
        int[][] editDistance = new int[s.length() + 1][t.length() + 1];
        for (int i = 0; i <= s.length(); i++)
            editDistance[i][0] = i;
        for (int j = 1; j <= t.length(); j++)
            editDistance[0][j] = j;

        for (int i = 1; i <= s.length(); i++)
            for (int j = 1; j <= t.length(); j++) {
                editDistance[i][j] = EditDistanceComputer.minimum(
                        editDistance[i - 1][j] + 1,
                        editDistance[i][j - 1] + 1,
                        editDistance[i - 1][j - 1]
                                + ((s.charAt(i - 1) == t.charAt(j - 1)) ? 0 : 1));
            }
        System.out.println(editDistance[editDistance.length - 1][editDistance[0].length - 1]);
        printAlignment(getBackTrace(editDistance), s, t);
    }

    public static List<int[]> getBackTrace (int[][] editDistance) {
        List<int[]> trace = new ArrayList<int[]>();
        int i = editDistance.length - 1;
        int j = editDistance[0].length - 1;
        while (true) {
            trace.add(new int[]{i, j});
            if (i == 1 && j == 1) break;
            else if (i == 1 && j > 1) j--;
            else if (j == 1 && i > 1) i--;
            else {
                if (editDistance[i - 1][j] < editDistance[i - 1][j - 1]) {
                    i--;
                } else if (editDistance[i][j - 1] < editDistance[i - 1][j - 1]) {
                    j--;
                } else {
                    i--;
                    j--;
                }
            }
        }
        Collections.reverse(trace);
        return trace;
    }

    public static void printAlignment (List<int[]> backtrace, CharSequence x, CharSequence y) {
        StringBuilder builder = new StringBuilder();
        for (int[] coordinate : backtrace) {
            builder.append(x.charAt(coordinate[0] - 1));
        }
        System.out.println(builder.toString());

        builder = new StringBuilder();
        for (int[] coordinate : backtrace) {
            builder.append(y.charAt(coordinate[1] - 1));
        }
        System.out.println(builder.toString());
    }
}
