// Question Link: http://www.geeksforgeeks.org/dynamic-programming-set-8-matrix-chain-multiplication/

package dp;
import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class MatrixChainMultiplication {
    public static int minCostOfMultiplication(int[] arr)
    {
        int N = arr.length-1;
        int cost[][] = new int[N][N];
        for(int len = 1; len <= N; len++)
        {
            for(int i = 0; i < N - len + 1; i++)
            {
                int j = i + len - 1;
                if(len==1)
                {
                    cost[i][j] = 0;
                }
                else if(len == 2)
                {
                    cost[i][j] = arr[i]*arr[i+1]*arr[j+1];
                }
                else
                {
                    cost[i][j] = Integer.MAX_VALUE;
                    for(int k = i+1; k <= j; k ++)
                    {
                        int pcost = arr[i]*arr[k]*arr[j+1] + cost[i][k-1] + cost[k][j];
                        if(pcost < cost[i][j])
                        {
                            cost[i][j] = pcost;
                        }
                    }
                }
            }
        }
        return cost[0][N-1];
    }
    public static void main(String[] args)
    {
        int[] arr1 = {40, 20, 30, 10, 30};
        System.out.println(minCostOfMultiplication(arr1));
        int[] arr2 = {10, 20, 30, 40, 30};
        System.out.println(minCostOfMultiplication(arr2));
        int[] arr3 = {10, 20, 30};
        System.out.println(minCostOfMultiplication(arr3));
    }
}
