package com.rodcut.model;

import java.util.ArrayList;
import java.util.Collections;

public class RodCuttingCommon {

	private static RodCuttingCommon instance = new RodCuttingCommon();

	private RodCuttingCommon() { }

	public static RodCuttingCommon getInstance() {
		return instance;
	}
	
	public ArrayList<Rod> sortByPriceLengthRatio(ArrayList<Rod> rodList) {
		Collections.sort(rodList);
		Collections.reverse(rodList); // Descending Order
		return rodList;
	}
	
	public double getPricesFromRodsStrategy(ArrayList<Rod> rodList) {
		ArrayList<Rod> maximumRevenueRods = rodList;
		double sum = 0;
		if(maximumRevenueRods == null) {
			return sum;
		}
		for (Rod rod : maximumRevenueRods) {
			sum += rod.getPrice();
		}
		return sum;
	}
	
}