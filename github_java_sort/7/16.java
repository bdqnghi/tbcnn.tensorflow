package interviews.sorts;

import interviews.arrays.Swap;

import java.util.Arrays;
import java.util.Comparator;
import java.util.List;


public class Shellsort {
  public static <E> void f(List<E> list, Comparator<E> comparator) {
    int h = 1;
    while(h < list.size()/3) {  
      h = 3*h + 1;  
    }

    while(h >= 1) {  
      for(int i = h; i < list.size(); i++) {  
        for(int j = i; j >= h && comparator.compare(list.get(j), list.get(j-h)) < 0; j-=h) {
          Swap.f(list, j, j-h);
        }
      }
      h /= 3;
    }
  }

  public static void main(String[] args) {
    f(Arrays.asList("iris", "wine", "pear", "dusk", "bark", "ruby", "sage", "aqua", "rust", "rose",
        "fawn", "onyx", "lava", "buff", "sand", "teal", "lime", "herb", "palm", "mint", "silk",
        "leaf", "pink", "gray"), String.CASE_INSENSITIVE_ORDER);
  }
}
