package com.matthieu.epi;

import java.util.Arrays;

public class LevenshteinDistance implements Solution {
    public static int levenshteinDistance (String a, String b) {
        int [][] distances = new int[a.length()+1][b.length()+1];
        for (int i=0; i<=a.length(); i++)
            distances[i][0] = i;
        for (int i=0; i<=b.length(); i++)
            distances[0][i] = i;

        for (int i=1; i<=a.length(); i++) {
            for (int j=1; j<=b.length(); j++) {
                int offset = (a.charAt(i-1) == b.charAt(j-1))?0:1;
                distances[i][j] = Math.min(Math.min(distances[i-1][j]+1, distances[i][j-1]+1), distances[i-1][j-1]+offset);
            }
        }
        System.out.println("Distances:\n"+ Arrays.deepToString(distances));
        return distances[a.length()][b.length()];

    }

    @Override
    public void solveProblem() {
        String a = "blablabla";
        String b = "abracadabra";

        System.out.println("Distance between ["+a+"] and ["+b+"] is "+levenshteinDistance(a, b));
    }
}
