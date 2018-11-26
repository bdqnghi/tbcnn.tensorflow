package com.test.prs.algorithms.dynamicprogramming;

public class RodCuttingProblem {
    private int lengthOfRod;
    private int[] prices;

    public RodCuttingProblem(final int lengthOfRod, final int[] prices) {
        this.lengthOfRod = lengthOfRod;
        this.prices = prices;
    }

    public void solve(){
        int[][] dpTable = new int[prices.length][lengthOfRod+1];
        for (int i = 1; i < prices.length; i++) {
            for (int j = 1; j < lengthOfRod +1; j++) {
                if (i<=j){
                    dpTable[i][j] = Math.max(dpTable[i-1][j], prices[i] + dpTable[i][j-i]);// take max of not taking
                    // or taking the current piece
                }
                else
                {
                    dpTable[i][j] = dpTable[i-1][j];
                }
            }
        }

        System.out.println("Max profit :: "+" Rs "+dpTable[prices.length-1][lengthOfRod]);
        showResults(dpTable);
    }

    private void showResults(final int[][] dpTable) {
        for (int i = prices.length-1,j = lengthOfRod; i > 0 ;) {
            if (dpTable[i][j]!=0 && dpTable[i][j]!=dpTable[i-1][j]){
                System.out.println("Make cut of "+i+" m");
                j = j - i;
            }
            else
                i--;
        }
    }

    public static void main(String[] args) {
        int[] prices = {0,2,5,7,3};
        int lengthOfRod = 5;
        RodCuttingProblem rodCuttingProblem = new RodCuttingProblem(lengthOfRod, prices);
        rodCuttingProblem.solve();
    }
}
