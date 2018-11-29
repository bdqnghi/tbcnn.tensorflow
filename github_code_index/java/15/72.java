package com.swj.algorithms;

import com.google.common.collect.Lists;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * 杠切割问题
 * The rod-cutting problem is the following.Given a rod of length n inches and a table prices p(i) for i D 1, 2..n,
 * determine the maximum revenue rn obtainable by cutting up the rod and selling the pieces.
 * Note that if the price pn for a rod of length n is large enough, an optimal solution may require no cutting at all
 * Created by swj on 2018/1/29.
 */
public class RodCutting {
    //价格的列表 index对应length - 1
    private static final List<Integer> prices = Lists.newArrayList(1, 5, 8, 9, 10,
            17, 17, 20, 24, 30);

    /**
     * 普通递归算法
     * @param length
     * @return
     */
    public static int maxProfit(final int length){
        int profit = (length <= prices.size()) ? prices.get(length - 1) : 0;
        for (int i = 1; i < length; i++){
            int priceWhenCut = maxProfit(i) + maxProfit(length - i);
            if (priceWhenCut > profit) profit = priceWhenCut;
        }
        return profit;
    }

    public static void main(String[] args) {
        System.out.println(maxProfit(9));
        System.out.println(Factorial.maxProfit(9));
    }
}
