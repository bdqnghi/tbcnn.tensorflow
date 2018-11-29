package dp;

import lombok.extern.slf4j.Slf4j;

import java.util.HashMap;
import java.util.Map;

@Slf4j
public class RodCutting {
  public static void main(String[] args) {
    Integer[] prices = {0,1,5,8,9,10,17,17,20,24,30};

    for(int i = 1; i < prices.length; i++) {
      int n = i; // length

      RodCutting rodCutting = new RodCutting();
      Integer maxPrice = rodCutting.recursiveNonOptimal(prices, n);
      log.info("recursiveNonOptimal : for n = {}, maxPrice = {}", n, maxPrice);

      Integer topDownAns = rodCutting.recursiveTopDown(prices, n);
      log.info("topDownAns : for n = {}, maxPrice = {}", n, topDownAns);

      Integer bottomUpAns = rodCutting.bottomUpDP(prices, n);
      log.info("bottomUpAns : for n = {}, maxPrice = {}", n, bottomUpAns);

      log.info("\n\n");
    }
  }

  private Integer bottomUpDP(Integer[] prices, int n) {
    Integer[] maxAns = new Integer[n+1];
    maxAns[0] = 0;
    int currMax = 0 ;
    for(int i = 1 ; i <= n ; i++){
      currMax = Integer.MIN_VALUE;
      for( int j = 1; j <= i ; j++){
        currMax = Math.max(currMax, prices[j] + maxAns[i-j]);
      }
      maxAns[i] = currMax;
    }

    return maxAns[n];
  }

  private Integer recursiveNonOptimal(Integer[] prices, int n) {
    if(n == 0){
      return 0;
    }

    int maxPrice = Integer.MIN_VALUE;
    for( int i = 1 ; i <= n ; i++){
      maxPrice = Math.max(maxPrice, prices[i] + recursiveNonOptimal(prices, n-i));
    }

    return maxPrice;
  }

  private Integer recursiveTopDown(Integer[] prices, int n) {
    return recursiveTopDown(prices, n, new HashMap<>());
  }

  private Integer recursiveTopDown(Integer[] prices, int n, Map<Integer, Integer> solutionMap) {
    if(solutionMap.containsKey(n))
      return solutionMap.get(n);

    if(n == 0){
      return 0;
    }

    int maxPrice = Integer.MIN_VALUE;
    for( int i = 1 ; i <= n ; i++){
      maxPrice = Math.max(maxPrice, prices[i] + recursiveTopDown(prices, n-i, solutionMap));
    }

    solutionMap.put(n, maxPrice);
    return maxPrice;
  }

}
