package algorithms.dynamicprog;

import java.util.ArrayList;
import java.util.List;

import lombok.Getter;
import lombok.Setter;

/**
 * Created by Chen Li on 2018/7/20.
 */
@Getter
@Setter
public class BestRodCutting {

  private List<Integer> cuts;
  private Double totalPrice;

  public BestRodCutting copy(){
    BestRodCutting c = new BestRodCutting();
    c.totalPrice = this.totalPrice;
    c.cuts = new ArrayList<>(this.cuts);
    return c;
  }

  public static final BestRodCutting zero() {
    BestRodCutting c = new BestRodCutting();
    c.setTotalPrice(0d);
    List<Integer> list = new ArrayList<>();
    c.setCuts(list);
    return c;
  }

  public static final BestRodCutting noCut(double price) {
    BestRodCutting c = new BestRodCutting();
    c.setTotalPrice(price);
    List<Integer> list = new ArrayList<>();
    list.add(1);
    c.setCuts(list);
    return c;
  }
}
