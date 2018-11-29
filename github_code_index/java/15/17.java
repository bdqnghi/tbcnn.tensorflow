/**
 * The program which solves rod-cutting problem
 * using DynamicProgramming algorithm.
 *
 * 動的計画法の演習
 * 有名なロッド切り出し問題
 *
 * @author chisaton
 * @version Fall 2015
 */
public class DynamicProgramming
{
    /**
     * Finds the maximum total price that can be obtained
     * by cutting a rod of a units long into integer-length pieces
     * if the sale price of a piece i units long is prices[i]
     * for i = 1, 2, ..., n.
     */
   public static int maxTotal(int length, int[ ] prices)
   {
       int table[] = new int[length+1];
       table[0] = 0;
       for(int n = 1; n < length+1; n++)
       {
          int maxValue = 0;
          for(int j = n; j > 0; j--)
          {
              int value = prices[j] + table[n-j];
              if(maxValue < value)
              {
                  maxValue = value;
              }
          }
          table[n] = maxValue;
       }
       return table[length];
   }
}
