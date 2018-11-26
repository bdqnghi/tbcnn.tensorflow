package recursion;

import java.util.Iterator;
import java.util.Spliterator;
import java.util.function.Consumer;

public class RodCutting implements Iterable {

    // length should be -1, because it's contained in the array
    public static int rodCutting(int[] prices, int length) {

        if (length == 0) return 0;

        int max = prices[length];
        for (int j=1; j <= length; j++) {
            max = Math.max(max, prices[j-1] + rodCutting(prices, length-j));
        }

        return max;
    }

    public static int memoizedRodCutting(int[] prices, int length) {

        if (length == 0) return 0;

        int max = prices[length];
        for (int j=1; j <= length; j++) {
            max = Math.max(max, prices[j-1] + rodCutting(prices, length-j));
        }

        return max;
    }

    @Override
    public Iterator iterator() {
        return null;
    }

    @Override
    public void forEach(Consumer action) {

    }

    @Override
    public Spliterator spliterator() {
        return null;
    }
}
