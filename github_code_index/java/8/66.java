package dynamic.programming.geeksforgeeks;

import java.util.Scanner;

public class EditDistance {
    public static void main(String args[])  {
        Scanner sc = new Scanner(System.in);
        String str1 = sc.next();
        String str2 = sc.next();
        int recursiveEditDistance = calculateEditDistanceRecursive(str1 , str2,
                str1.length() - 1, str2.length() - 1);
        int dpEditDistance = calculateEditDistanceDP(str1 , str2 , str1.length()  , str2.length());

        System.out.println(recursiveEditDistance);
        System.out.println(dpEditDistance);
    }

    private static int calculateEditDistanceDP(String str1, String str2, int length1, int length2) {
        int editDistanceDP[][] = new int[length1 + 1][length2 + 1];
        editDistanceDP[0][0] = 0;
        for ( int i = 1 ; i <= length1 ; i++)
            editDistanceDP[length1][0] = length1;

        for ( int i = 1 ; i <= length2 ; i++)
            editDistanceDP[0][length2] = length2;

        for ( int i = 1 ; i <= length1 ; i++)    {
            for ( int j = 1; j <= length2 ; j++)    {
                if ( str1.charAt(i-1) == str2.charAt(j-1))
                    editDistanceDP[i][j] = editDistanceDP[i-1][j-1];
                else
                    editDistanceDP[i][j] = 1 + Math.min(editDistanceDP[i-1][j],
                            (Math.min(editDistanceDP[i-1][j-1], editDistanceDP[i][j-1])));
            }
        }

        return editDistanceDP[length1][length2];
    }

    private static int calculateEditDistanceRecursive(String str1, String str2, int length1, int length2) {
        if (length1 == 0)
            return length2;

        if (length2 == 0)
            return length1;

        if ( str1.charAt(length1) == str2.charAt(length2))  {
            return calculateEditDistanceRecursive(str1, str2, length1 - 1 , length2 - 1);
        }

        else    {
            return 1 + Math.min(calculateEditDistanceRecursive(str1, str2, length1, length2 - 1),
                    Math.min(calculateEditDistanceRecursive(str1,str2, length1-1 , length2),
                    calculateEditDistanceRecursive(str1, str2, length1-1,length2-1)));
        }
    }
}
