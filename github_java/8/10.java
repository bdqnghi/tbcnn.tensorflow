import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Scanner;

class EditDistance {
    public static int EditDistance(String s, String t) {
        char[] sChars = s.toCharArray();
        char[] tChars = t.toCharArray();

        int[][] distance = new int[sChars.length + 1][tChars.length + 1];
        for (int i = 0; i <= sChars.length; i++) {
            distance[i][0] = i;
        }
        for (int j = 0; j <= tChars.length; j++) {
            distance[0][j] = j;
        }

        for (int j = 1; j <= tChars.length; j++) {
            for (int i = 1; i <= sChars.length; i++) {
                int ins = distance[i][j - 1] + 1;
                int del = distance[i - 1][j] + 1;
                int mat = distance[i - 1][j - 1];
                int mis = distance[i - 1][j - 1] + 1;
                if (sChars[i-1] == tChars[j-1])
                    distance[i][j] = Collections.min(new ArrayList<>(Arrays.asList(ins, del, mat)));
                else
                    distance[i][j] = Collections.min(new ArrayList<>(Arrays.asList(ins, del, mis)));
            }
        }

        return distance[sChars.length][tChars.length];
    }

    public static void main(String args[]) {
        Scanner scan = new Scanner(System.in);

        String s = scan.next();
        String t = scan.next();

        System.out.println(EditDistance(s, t));
    }

}
