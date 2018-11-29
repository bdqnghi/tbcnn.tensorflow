package com.khaannn.greedy;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * Created by jeff on 10/3/15.
 * Implementation of the rodcutting problem, both dynamic and greedy. Dynamic is the optimal solution.
 * Example:
 * Given a rod of length 52, and positive integers 1, 5, and 10 for the valid
 * sizes of smaller rods, the optimal solution is to divide the rod of length 52 into five
 * pieces of length 10 and two pieces of length 1
 */
public class RodCutting {
    ArrayList<Integer> validCutSizes;
    int rodSize = -1;
    List<Integer> cutList = new ArrayList<>();

    public int[] getPrices() {
        return prices;
    }

    public void setPrices(int[] prices) {
        this.prices = prices;
    }

    public int[] getcList() {
        return cList;
    }

    public void setcList(int[] cList) {
        this.cList = cList;
    }

    int[] prices;
    int[] cList;

    public ArrayList<Integer> getValidCutSizes() {
        return validCutSizes;
    }

    public void setValidCutSizes(ArrayList<Integer> validCutSizes) {
        this.validCutSizes = validCutSizes;
    }

    public int getRodSize() {
        return rodSize;
    }

    public void setRodSize(int rodSize) {
        this.rodSize = rodSize;
    }

    public List<Integer> getCutList() {
        return cutList;
    }

    public void setCutList(List<Integer> cutList) {
        this.cutList = cutList;
    }


    public RodCutting(int[] prices, int rodSize) {
        this.prices = prices;
        this.rodSize = rodSize;
        cList = new int[rodSize + 1];
    }

    /**
     * Runs in O(n^2)
     */
/*    public RodCutting greedyCuts() {and
        if (validCutSizes == null || rodSize == -1) {
            return null;
        }

        //i is a counter that prevents an infinite loop in the case of no valid cuts left
        for (int rodSizeRemainder = rodSize, i = 0; rodSizeRemainder > 0 && i < rodSize; i++) {
            for (Integer validCutSize : validCutSizes) {
                if (rodSizeRemainder - validCutSize >= 0) {
                    cutList.add(validCutSize);
                    rodSizeRemainder -= validCutSize;
                    break;
                }
            }
        }
        return this;
    }*/

    /**
     * Runs in O(n^2)
     */
    public int greedyCuts() {
        if (prices == null || rodSize > prices.length) {
            return -1;
        }


        int maxVal;
        for (int rodSizeRemainder = rodSize; rodSizeRemainder > 0; ) {
            maxVal = Integer.MIN_VALUE;
            for (int j = prices.length -1; j > 0 ; j--) {
                if (prices[j] > maxVal) {
                    cList[rodSizeRemainder] = j;
                    maxVal = prices[j];
                }
            }
            rodSizeRemainder -= maxVal;
        }

        return cList[rodSize];
    }


    public int extendedBottomUpCutRod() {

        int[] lookupTable = new int[rodSize + 1];
        int maxVal;

        for (int j = 1; j <= rodSize; j++) {
            maxVal = Integer.MIN_VALUE;
            for (int i = 1; i <= j; i++) {
                if (maxVal < (prices[i] + lookupTable[j - i])) {
                    maxVal = prices[i] + lookupTable[j - i];
                    cList[j] = i;
                }

            }
            lookupTable[j] = maxVal;
        }
        return lookupTable[rodSize];
    }


    public static void main(String[] args) {
        int rodSize = 52;
        int[] prices = new int[53];
        prices[1] = 1;
        prices[2] = 3;
        prices[3] = 4;

        RodCutting rodCutting = new RodCutting(prices, rodSize);

        System.out.println("\nFor a rod of length " + rodSize);

        System.out.println("Greedy Cuts: " + rodCutting.greedyCuts());
        int[] cList = rodCutting.getcList();
        for (int tmp = rodSize; tmp > 0; ) {
            System.out.println("Cut : " + cList[tmp]);
            tmp -= cList[tmp];
        }


        System.out.println("Extended Bottom Up Cut Rod Solution (max profit):");
        System.out.println(rodCutting.extendedBottomUpCutRod());
        int[] dynamicCutList = rodCutting.getcList();
        for (int tmp = rodSize; tmp > 0; ) {
            System.out.println("Cut : " + dynamicCutList[tmp]);
            tmp -= dynamicCutList[tmp];
        }
    }

}
