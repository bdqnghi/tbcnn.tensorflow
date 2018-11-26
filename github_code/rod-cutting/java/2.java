package com.practice.algo.and.ds.interviewbit;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class DP_RodCutting {

	public static void main(String[] args) {
		DP_RodCutting o = new DP_RodCutting();
		Integer[] a = { 1  , 2 ,5  };
		int n = 8;
		ArrayList<Integer> l = new ArrayList<>(Arrays.asList(a));
		System.out.println(o.cutRod(l));
		
	}

	private int cutRod(int price[],int n) {
		// TODO Auto-generated method stub
		int[] dp = new int[price.length+1];
		dp[1] = price[0];
		
		for(int i = 2;i<=n;i++){
			int res = price[i-1];
			for(int j=1;j<=i/2;j++){
				res = Math.max(res, dp[j]+dp[i-j]);
				//System.out.println(res);
			}
			dp[i]=res;
		}
		return dp[n];
	}

	public List<String> cutRod(List<Integer> a){
		
		List<String> o = new ArrayList();
		if(a.size()==1){
			o.add(Integer.toString(a.get(0)));
			return o;
		}
		
		for(int i=0;i<a.size()-1;i++){
			List<String> s1=cutRod(a.subList(0, i+1));
			List<String> s2=cutRod(a.subList(i+1, a.size()));
			for(String dd:s1){
				for(String de:s2){
					o.add(dd+de);
					o.add(de+dd);
				}	
			}
		}
		return o;
	}
}
