package dp;

public class RodCutting {

  private int s[];

  public static void main(String[] args) {
    int[] prices = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    RodCutting rc = new RodCutting();
    rc.s = new int[prices.length];
    System.out.println(rc.withMemoization(prices, 4));
    System.out.println(rc.bottomUp(prices, 4));
  }

  public int withMemoization(int[] prices, int length) {
    if (s[length] != 0)
      return s[length];

    if (length == 0)
      return 0;

    int sum = 0;
    for (int i = 0; i < length; i++)
      sum = Math.max(sum, prices[i] + withMemoization(prices, length - (i + 1)));
    s[length] = sum;
    return sum;
  }

  /* Incomplete */
  public int bottomUp(int[] prices, int length) {
    int[] s = new int[length + 1];
    for (int k = 1; k <= length; k++) {
      int sum = 0;
      for (int i = 1; i <= k; i++)
        sum = Math.max(sum, prices[i - 1] + s[k - i]);
      s[k] = sum;
    }
    return s[length];
  }

}
