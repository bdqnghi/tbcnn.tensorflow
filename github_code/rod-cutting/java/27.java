/**
 * Created by Priyank Agrawal on 11/22/2016.
 *
 * Cutting rod problem by Dynamic programming approach
 *
 * To find the optimal way to cut a rod to maximize its price
 * using dynamic programming
 *
 * Time complexity is O(n^2)
 * Space complexity is O(n)
 */
public class CuttingRod {

    public static void main(String[] args){
        int rodLength = 5;
        int[] price = {0,2,3,5,6,8};            //prices for rod length 0,1,2,3,4,5 respectively
        CuttingRod cR = new CuttingRod();
        int maxPrice = cR.maxPrice(rodLength, price);
        System.out.printf("The maximum price after cutting rod of length %d is: "+maxPrice,rodLength);
    }

    int maxPrice(int rodLength, int[] price){
        int[] maxPrices = new int[rodLength+1];
        maxPrices[0] = 0;                       //price for rod length 0 is also 0
        for(int i=1;i<=rodLength;i++){
            maxPrices[i] = price[1]*i;          //price for rod length is 1
        }
        for(int i=2;i<price.length;i++){        //prices starting from rod length 2
            for(int j=i;j<=rodLength;j++){      //rod length should at-least be same as rod length cut available
                maxPrices[j] = Math.max(maxPrices[j],maxPrices[j-i]+maxPrices[i-1]);
            }
        }
        return maxPrices[rodLength];
    }

}