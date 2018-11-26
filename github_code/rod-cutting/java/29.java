package DynamicProgramming;

import java.util.ArrayList;
import java.util.List;

/*
 * Similar to Knapsack, SubsetSum, CoinChange
 */

public class RodCutting {
	
	public static void rodCutting(int[] value, int[] cuts, int sumSoFar, String curString, int curValue, List<Integer> maxValue) {
		if(sumSoFar>=cuts[cuts.length-1]) {
			if(sumSoFar==cuts[cuts.length-1]) {
				if(curValue>maxValue.get(0)) {
					maxValue.remove(0);
					maxValue.add(curValue);
				}
				//System.out.println(curString);
			}
			return;
		}
		
		for(int i=0;i<cuts.length;i++) {
			rodCutting(value, cuts, sumSoFar+cuts[i], curString+cuts[i]+"", curValue+value[i], maxValue);
		}
	}
	
	public static int rodCuttingMemo(int[] value, int[] cuts) {
		int[] maxValue = new int[value.length+1];
		maxValue[0] = 0;
		for(int i=1;i<value.length;i++) {
			maxValue[i] = Integer.MIN_VALUE;
		}
		
		/*
		 * If there is only 1 cut i.e 1 element in array than maxValue[1] = value[0] + maxValue[maxLength of rod - currentLength i.e. ((cuts.length/i)-1)-j]
		 */
		for(int i=1;i<=cuts.length;i++) {
			for(int j=1;j<=i;j++) {
				if(maxValue[i]<value[j-1]+maxValue[i-j]) {
					maxValue[i] = value[j-1]+maxValue[i-j];
				}
			}
		}
		
		return maxValue[value.length];
	}
	
	/*
	 * similar to knapsack way
	 */
	public static int rodCuttingMemo1(int[] value, int[] cuts) {
		//number of elements is size of cuts array and sum required is as well the size of cuts array
		int[][] maxValue = new int[cuts.length+1][cuts.length+1];
			
		for(int i=0;i<=cuts.length;i++) {
			maxValue[0][i] = 0;
			maxValue[i][0] = 0;
		}
		
		for(int i=1;i<=cuts.length;i++) {
			for(int j=1;j<=cuts.length;j++) {
				if(cuts[i-1]<=j) {
					maxValue[i][j] = Math.max(maxValue[i-1][j], maxValue[i-1][j-cuts[i-1]]+value[i-1]);
				} else {
					maxValue[i][j] = maxValue[i-1][j];
				}
			}
		}
		
		return maxValue[cuts.length][cuts.length];
	}
	
	public static int rodCuttingMemo2(int[] val, int[] cuts) {
		int[] memo = new int[val.length+1];
		memo[0] = 0;
		
		/*
		 * If there is only 1 cut i.e 1 element in array than maxValue[1] = value[0] + maxValue[maxLength of rod - currentLength i.e. ((cuts.length/i)-1)-j]
		 */
		for(int i=1;i<=cuts.length;i++) {
			for(int j=1;j<i;j++) {
				if(memo[i]<memo[j]+val[i-j-1]) {
					memo[i] = memo[j]+val[i-j-1];
				}
			}
		}
		
		return memo[val.length];
	}
	
	public static void main(String[] args) {	
		int[] cuts = {1, 2, 3, 4, 5, 6, 7, 8};
		int[] value = {1, 5, 8, 9, 10, 17, 17, 20};
		
		List<Integer> maxValue = new ArrayList<Integer>();
		maxValue.add(Integer.MIN_VALUE);
		rodCutting(value, cuts, 0, "", 0, maxValue);
		System.out.println(maxValue.get(0));
		
		System.out.println(rodCuttingMemo(value, cuts));
		System.out.println(rodCuttingMemo1(value, cuts));
		System.out.println(rodCuttingMemo2(value, cuts));
	}
}
