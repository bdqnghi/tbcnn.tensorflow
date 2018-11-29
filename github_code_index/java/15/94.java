package com.holczer.problems.dp.RodCutting;

public class RodCutting {

  private int[][] dpTable;
  private int lenghtOfRod;
  private int[] prices;

  public RodCutting(int lengthOfRod, int[] prices) {
    this.prices = prices;
    this.lenghtOfRod = lengthOfRod;
    this.dpTable = new int[prices.length + 1][lengthOfRod + 1];
  }

  public void solve() {

    // initialize

    for (int i = 1; i < prices.length; i++) {
      for (int j = 1; j <= lenghtOfRod; j++) {

        if (i <= j) {
          dpTable[i][j] = Math.max(dpTable[i - 1][j], prices[i] + dpTable[i - 1][j - i]);
        } else {
          dpTable[i][j] = dpTable[i - 1][j];
        }

      }
    }
  }

  public void showResult() {

    System.out.println("Optimal profit: $" + dpTable[prices.length - 1][lenghtOfRod]);

    for (int n = prices.length - 1, w = lenghtOfRod; n > 0;) {
      if (dpTable[n][w] != 0 && dpTable[n][w] != dpTable[n - 1][w]) {
        System.out.println("We make cut: " + n + "m");
        w = w - n;
      } else {
        n--;
      }
    }
  }
}
