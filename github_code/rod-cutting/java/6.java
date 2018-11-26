package algorithms.dynamicprog;

import java.util.List;

/**
 * Created by Chen Li on 2018/7/20.
 */
public class SimpleRodCutting implements RodCutting {


  @Override
  public BestRodCutting findBestCuts(List<Double> prices) {
    return doFindCuts(prices.size()-1, prices);
  }

  private BestRodCutting doFindCuts(int n, List<Double> prices) {
    if (n == 0) {
      return BestRodCutting.zero();
    }
    if (n == 1) {
      return BestRodCutting.noCut(prices.get(1));
    }

    double max = -1;
    double current = max;
    BestRodCutting cut = null;
    for (int i = 1; i <= n; i++) {
      try {
        BestRodCutting bestCuttingRemainder = doFindCuts(n - i, prices);
        current = prices.get(i) + bestCuttingRemainder.getTotalPrice();
        if (current > max) {
          max = current;
          cut = bestCuttingRemainder;
          cut.getCuts().add(i);
        }
      } catch (Exception e) {
        e.printStackTrace();
        throw e;
      }

    }
    cut.setTotalPrice(max);
    return cut;
  }
}
