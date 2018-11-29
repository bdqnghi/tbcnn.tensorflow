import java.util.HashMap;
import java.util.Map;

import com.algorithmhelper.dynamicprogramming.dynamicprogrammingproblems;

public class RodCutting {

  /**
   * Returns the maximum value of the rod obtained with current length n.
   *
   * @param n, the length of the current rod
   * @param values, the values of rod pieces
   * @param memo, the memo table
   * @return the maximum value of the rod obtained with current length n
   */
  private static int rodCutting(int n, int[] values, Map<Integer, Integer> memo) {
    if (n == 0)
      return 0;
    else if (memo.containsKey(n))
      return memo.get(n);

    int result = 0;
    for (int i = 1; i < n; i++)
      result = Math.max(result, values[i] + rodCutting(n - i + 1, values, memo));
    memo.put(n, result);
    return result;
  }

  /**
   * Returns the maximum value of the rod obtained with length n given the values of the individual
   * rod pieces.
   *
   * @param n, the total length of the rod
   * @param values, the values of the rod pieces
   * @return the maximum value of the rod obtained with length n given the values of the individual
   *         rod pieces
   * @throws IllegalArgumentException if values does not have n + 1 elements
   */
  public static int rodCutting(int n, int[] values) {
    if (values.length != n + 1)
      throw new IllegalArgumentException("rodCutting with invalid values");

    Map<Integer, Integer> memo = new HashMap<>();
    return rodCutting(n, values, memo);
  }
}
