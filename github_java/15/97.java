package DP;

/**
 * Created by dheeraj on 12/25/14.
 */
public class RodCutting {
    private int[] priceArray;
    //for tabulating  data
    private int[] maxArray;

    private RodCutting(int[] prices){
        this.priceArray = prices;
        this.maxArray = new int[prices.length];
        for(int a =0;a<prices.length;a++){
            maxArray[a] = 0;
        }
        maxArray[1] = priceArray[1];
    }

    private int maxValue(){
        for(int x=2;x<maxArray.length;x++){
            maxArray[x] = findMax(x);
        }
        return maxArray[maxArray.length-1];
    }

    private int findMax(int index){
        int max = 0;
        for(int k =1;k<=index;k++){
            max = Math.max(max,priceArray[k]+maxArray[index-k]);
        }
        return max;
    }

    public static void main(String[] args){
        int[] prices = {0, 3/*1*/, 5,   8,   9,  10,  17,  17,  20};
        RodCutting rodCutting = new RodCutting(prices);
        System.out.println(rodCutting.maxValue());
    }


}
