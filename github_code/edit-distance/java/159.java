package test1.dynamic;

import java.util.Arrays;
import java.util.Collections;

/**
 * Created by 1100383 on 2017. 4. 10..
 */


class Solution9 {
    /////////////

    public int minDistance2(String a, String b) {
          n = a.length();
          m = b.length();

        int[][] mat = new int[m + 1][n + 1];

        for (int j = 0; j <= n; j++)
            mat[0][j] = j;
        for (int i = 0; i <= m; i++)
            mat[i][0] = i;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {

                if (b.charAt(i - 1) != a.charAt(j - 1)) {

                    mat[i][j] = Math.min(mat[i - 1][j]+1, mat[i][j - 1]+1);

                    mat[i][j] = Math.min(mat[i][j], mat[i - 1][j - 1] + 1);

                } else {
                    mat[i][j] = mat[i - 1][j - 1];
                }


            }
        }
        return mat[m][n];
    }


    int n,m;
    int[][] mat;
    int editDistance(char []S1,int index1, char []S2,int index2) {
        if( mat[index2][index1] != Integer.MAX_VALUE)
            return mat[index2][index1];

        if (index1 >= n || index2 >= m){
            return Math.max(S1.length - index1,S2.length - index2 );
        }

        if (S1[index1] == S2[index2]) {
            mat[index2][index1] =  editDistance(S1, index1 + 1, S2, index2 + 1);
        } else {
            mat[index2][index1] = Collections.min(Arrays.asList(
                    1 + editDistance(S1, index1 + 1, S2, index2), // Delete S1 char
                    1 + editDistance(S1, index1, S2, index2 + 1), // Insert S2 char
                    1 + editDistance(S1, index1 + 1, S2, index2 + 1) // Replace S1 first char with S2 first char
            ));


        }
        return mat[index2][index1];
    }
    public int minDistance(String a, String b) {
         n = a.length();
         m = b.length();

        if (m == 0 || n ==0)
            return Math.max(m,n);

         mat = new int[m + 1][n + 1];

        for (int i = 0;i <= m; i++)
            for (int j = 0;j <= n; j++)
                mat[i][j] = Integer.MAX_VALUE;

        return  editDistance(a.toCharArray(),0,b.toCharArray(),0);
    }

////////////
}

public class editdistance {
    public static void main(String[] arg) {
        Solution9 sol = new Solution9();

        System.out.println(sol.minDistance("aaa", "a"));


        System.out.println(sol.minDistance("babaaabaaab", "ababaabbab"));
        System.out.println(sol.minDistance2("babaaabaaab", "ababaabbab"));

        System.out.println(sol.minDistance("", ""));
        System.out.println(sol.minDistance("a", ""));
        System.out.println(sol.minDistance("", "b"));


        System.out.println(sol.minDistance("a", "b"));
        System.out.println(sol.minDistance("aa", "a"));

        System.out.println(sol.minDistance("a", "aabba"));
        System.out.println(sol.minDistance("Anshuman", "Antihuman"));

    }
}
