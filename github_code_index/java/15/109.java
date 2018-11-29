package common;

import java.util.HashMap;

/**
 * Rod-Cutting DP algorithms
 */
public class RodCutter {
  public static int cutRodRecurse(int[] p, int n) {
    if (p == null || p.length == 0 || n == 0) {
      return 0;
    }
    int q = Integer.MIN_VALUE;
    for (int i = 0; i < n; i++) {
      q = Math.max(q, p[i] + cutRodRecurse(p, n-i-1));
    }
    return q;
  }

  public static int memoizedCutRod(int[] p, int n) {
    if (p == null || p.length == 0 || n == 0) {
      return 0;
    }
    HashMap<Integer, Integer> cache = new HashMap<>();
    return memoizedCutRodAux(p, n, cache);
  }

  private static int memoizedCutRodAux(int[] p, int n, HashMap<Integer,Integer> cache) {
    int r = cache.getOrDefault(n, 0);
    if (r > 0) {
      return r;
    }
    int q = Integer.MIN_VALUE;
    if (n == 0) {
      q = 0;
    }
    for (int i = 0; i < n; i++) {
      q = Math.max(q, p[i] + memoizedCutRodAux(p, n-i-1, cache));
    }
    cache.put(n, q);
    return q;
  }

  public static int bottomUpCutRod(int[] p, int n) {
    if (p == null || p.length == 0 || n == 0) {
      return 0;
    }
    HashMap<Integer, Integer> cache = new HashMap<>();
    for (int j = 0; j < n; j++) {
      int q = Integer.MIN_VALUE;
      for (int i = 0; i <= j; i++) {
        q = Math.max(q, p[i] + cache.getOrDefault(j-i-1, 0));
      }
      cache.put(j, q);
    }
    return cache.get(n-1);
  }

  public static int enhancedBottomUp(int[] p, int n) {
    if (p == null || p.length == 0 || n == 0) {
      return 0;
    }
    HashMap<Integer, Integer> cache = new HashMap<>();
    for (int j = 0; j < n; j++) {
      int q = Integer.MIN_VALUE;
      for (int i = 0; i <= j; i++) {
        q = Math.max(q, p[i] + cache.getOrDefault(j-i-1, 0));
      }
      cache.put(j, q);
    }
    return cache.get(n-1);
  }
}
