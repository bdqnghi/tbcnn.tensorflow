package dynamic.programming.geeksforgeeks;

import java.util.Scanner;

public class RodCutting {
    public static void main(String args[])  {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        int[] length = new int[N];
        int[] prices = new int[N];
        for ( int i = 0 ; i < N ; i++)  {
            length[i] = sc.nextInt();
            prices[i] = sc.nextInt();
        }
        int lengthOfRod = sc.nextInt();

        System.out.println(findMaxPrice(length, prices, lengthOfRod));
    }

    private static int findMaxPrice(int[] length, int[] prices, int lengthOfRod) {
        int dp[] = new int[lengthOfRod+1];
        dp[0] = 0;

        for ( int i = 1 ; i <= lengthOfRod ; i++)   {
            for ( int j = 0 ; j < i && j < prices.length ; j++) {
                dp[i] = Math.max(dp[i], prices[j] + dp[i-(j+1)]);
            }
        }
        return dp[lengthOfRod];
    }
}
