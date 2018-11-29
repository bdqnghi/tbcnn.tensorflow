public class RodCutting {
   static int[] prices = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

   public static int cutRod(int[] prices, int length) {
      if (length == 0) return 0;

      int q = Integer.MIN_VALUE;
      //int q = 0;
      for (int i = 1; i <= length; i++) {
         int tmp = prices[i] + cutRod(prices, length - i);
         if (tmp > q) q = tmp;
      }

      return q;
   }

   public static int cutRodMemoized(int[] prices, int length) {
      // initialize the storage of the results of subproblems
      int[] r = new int[length + 1];
      for (int i = 0; i <= length; i++) {
         r[i] = Integer.MIN_VALUE;
      }

      return cutRodMemoizedAux(prices, length, r);
   }

   public static int cutRodMemoizedAux(int[] prices, int n, int[] results) {
      if (results[n] >= 0) // if the subproblem has been solved
         return results[n];

      int q;
      if (n == 0)
         q = 0;
      else {
         q = Integer.MIN_VALUE;
         for (int i = 1; i <= n; i++) {
            int tmp = prices[i] + cutRodMemoizedAux(prices, n - i, results);
            if (tmp > q) q = tmp;
         }
      }
      results[n] = q;
      return q;
   }

   public static int cutRodBottomUp(int[] prices, int length) {
      int[] r = new int[length + 1];
      r[0] = 0;

      for (int j = 1; j <= length; j++) {
         int q = Integer.MIN_VALUE;
         for (int i = 1; i <= j; i++) {
            int tmp = prices[i] + r[j - i];
            if (tmp > q) q = tmp;
         }
         r[j] = q;
      }
      return r[length]; 
   }

   public static int[][] extendedBottomUpRod(int[] prices, int length) {
      int[] r = new int[length + 1];
      int[] s = new int[length + 1];
      r[0] = 0;

      for (int j = 1; j <= length; j++) {
         int q = Integer.MIN_VALUE;
         for (int i = 1; i <= j; i++) {
            if (q < prices[i] + r[j - i]) {
               q = prices[i] + r[j - i];
               s[j] = i;
            }
         }
         r[j] = q;
      }

      int[][] res = new int[2][length + 1];
      res[0] = r;
      res[1] = s;
      return res;
   }

   public static void main(String[] args) {
      //for (int i = 1; i <= 10; i++) {
      //   System.out.println(i + " itches: " + RodCutting.cutRod(prices, i));
      //}
      int length = Integer.parseInt(args[0]);
      System.out.println(length + " itches (naive): " + 
          RodCutting.cutRod(prices, length));
      System.out.println(length + " itches (DP): " + 
          RodCutting.cutRodMemoized(prices, length));
      System.out.println(length + " ithces (Bottom Up)" + 
          RodCutting.cutRodBottomUp(prices, length));

      int[][] res = RodCutting.extendedBottomUpRod(prices, length);
      for (int i = 0; i <= length; i++) {
         System.out.println(i + " " + res[0][i] + " " + res[1][i]);
      }
   }
}
