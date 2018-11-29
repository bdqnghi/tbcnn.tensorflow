package dynamicProg;

import java.util.Arrays;

/**
 * given prices for rod of various lengths, get the maximum value you can get
 * eg : [1,2,,5,6
 */
public class CuttingRod {

    public static void main(String args[]){
        int[] price = {3,5,8,9,10,20,22,25};
        System.out.println(maxValue(price));
    }

    //0 based index
    public static int maxValue(int price[]){
        int max[] = new int[price.length+1];
        for(int i=1; i <= price.length; i++){
            for(int j=i; j <= price.length; j++){
                max[j] = Math.max(max[j], max[j-i] + price[i-1]);
            }
        }
        System.out.println(Arrays.toString(max));
        return max[price.length];
    }
}
