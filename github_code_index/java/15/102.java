package DynamicProgramming.RodCutting;

/**
 * Created by nicholai on 10/6/16.
 *
 * The rod-cutting problem is the following. Given a rod of length n inches and a
 * table of prices p i for i = {1, 2, ... , n} determine the maximum revenue r n obtain-
 * able by cutting up the rod and selling the pieces. Note that if the price p n for a rod
 * of length n is large enough, an optimal solution may require no cutting at all (366)
 *
 */
public class RodCutting {

    int[][] price_length;

    public RodCutting(int[][] price_length){
        this.price_length = price_length;
    }

    public int rodCutRecursive(int length){
        if(length == 0){
            return 0;
        }
        int q = Integer.MIN_VALUE;
        for(int i = 1; i <= length; ++i){
            int cost = this.price_length[1][i] + this.rodCutRecursive(length - 1);
            q = q > cost ? q : cost;
        }
        return q;
    }

    public int rodCutIterative(int length){
        int[] r = new int[length+1];
        r[0] = 0;
        for(int j = 1; j <= length; ++j){
            int q = Integer.MIN_VALUE;
            for(int i = 1; i <= j; ++i){
                int cost = this.price_length[1][i] + r[j - 1];
                q = q > cost ? q : cost;
            }
            r[j] = q;
        }
        return r[length];
    }

}
