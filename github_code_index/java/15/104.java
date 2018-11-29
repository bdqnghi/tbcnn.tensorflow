package com.deepak.coreman.ch15;

import java.util.ArrayList;
import java.util.List;

public class RodCutter {

	private int[] price;
	private int cost;

	public void setPrices(int[] price) {
		this.price = price;
	}

	public int cutRodOfLength(int length) {
		if (length == 0)
			return 0;
		else {
			int max = Integer.MIN_VALUE;
			for (int i = 1; i <= length; i++) {
				int currentPrice = price[i - 1] + cutRodOfLength(length - i);
				if (currentPrice > max)
					max = currentPrice;
			}
			return max;

		}
	}

	public OptimalRodCutting cutRodWithRememberingPrice(int length) {
		int[] optimalPrices = new int[length];
		int[] selectedLenghts = new int[length];
		for (int i = 0; i < optimalPrices.length; i++) {
			optimalPrices[i] = -1;
			selectedLenghts[i] = -1;
		}

		int max= cutRodWithRememberingPrice(length, optimalPrices,selectedLenghts);
		OptimalRodCutting optimalRodCutting = new OptimalRodCutting();
		optimalRodCutting.setDiffLengths(selectedLenghts);
		List<Integer> rods = getRods(selectedLenghts);
		optimalRodCutting.setMaxPrice(max - (cost*rods.size()));
		return optimalRodCutting;
		
	}

	private int cutRodWithRememberingPrice(int length, int[] optimalPrices, int[] selectedLenghts ) {
		if (length == 0) {
			return 0;
		} else if (optimalPrices[length - 1] != -1) {
			return optimalPrices[length - 1];
		} else {
			int max = Integer.MIN_VALUE;
			for (int i = 1; i <= length; i++) {
				int currPrice = price[i - 1]
						+ cutRodWithRememberingPrice(length - i, optimalPrices,selectedLenghts);
				if (currPrice > max){
					max = currPrice;
					selectedLenghts[length-1]=i;
				}
					
			}
			optimalPrices[length - 1] = max;
			return max;
		}
	}

	public List<Integer> getRods(int[] diffLengths) {
		List<Integer> rods = new ArrayList<Integer>();
		int length = diffLengths.length;
		while(length>0){
			int rodLength = diffLengths[length-1];
			rods.add(rodLength);
			length=length-rodLength;
		}
		
		return rods;
	}

	public void setCuttingCost(int cost) {
		this.cost = cost;
		
	}

}
