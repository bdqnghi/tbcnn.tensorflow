package lecture_20;

import java.util.ArrayList;
import java.util.Arrays;

public class rodCutting {

	// similar to LIS
	public static void main(String[] args) {
		int[] arr = { 0, 3, 5, 6, 15, 10, 25, 12, 24 };
		// maxProfit(1, 8,"", arr, 0);
		// rodcut_sir(arr);
		int[] arr1 = { 2, 3, 5, 6 };
		// changeCoins(arr1, 10);

		changeCoinsPrint(arr1, 10);
	}

	private static void changeCoins(int[] coins, int amount) {
		int[] ret = new int[amount + 1];
		ret[0] = 1;
		ArrayList<String>[] lists = new ArrayList[10];
		for (int i = 0; i < coins.length; i++) {
			int target = coins[i];
			for (int j = target; j < ret.length; j++) {
				if (j - target >= 0) {
					ret[j] += ret[j - target];
					for (int k = 0; k < 10; k++) {
						lists[k] = new ArrayList<>();
					}
				}
			}
		}
		System.out.println(ret[ret.length - 1]);
	}

	private static void changeCoinsPrint(int[] coins, int amount) {
		int[] ret = new int[amount + 1];
		ret[0] = 1;
		ArrayList<ArrayList<Integer>>[] pstrg = new ArrayList[amount + 1];
		
		//Initialising the arraylist
		for (int i = 0; i < ret.length; i++) {
			pstrg[i] = new ArrayList<ArrayList<Integer>>();
			if (i == 0) {
				pstrg[i].add(new ArrayList<Integer>());
			}
		}
		for (int i = 0; i < coins.length; i++) {
			int target = coins[i];
			for (int j = target; j < ret.length; j++) {
				ret[j] += ret[j - target];

				for (int k = 0; k < pstrg[j - target].size(); k++) {
					ArrayList<Integer> newAl = new ArrayList<Integer>(pstrg[j - target].get(k));
					newAl.add(target);
					pstrg[j].add(newAl);
				}
			}
		}
		System.out.println(ret[ret.length - 1]);
		System.out.println(pstrg[pstrg.length - 1]);
	}

	public static void rodcut_sir(int[] arr) {
		int[] profit = new int[arr.length];
		String[] str = new String[arr.length];

		for (int i = 0; i < profit.length; i++) {
			profit[i] = arr[i];
			str[i] = i == 0 ? "" : i + "";
		}

		for (int i = 2; i < profit.length; i++) {
			for (int left = 0, right = i; left <= right; left++, right--) {
				if (profit[left] + profit[right] > profit[i]) {
					profit[i] = profit[left] + profit[right];
					str[i] = str[left] + str[right];
				}
			}

		}
		System.out.println(profit[profit.length - 1]);
		System.out.println(str[profit.length - 1]);
	}

	private static void maxProfit(int cur, int end, String ans, int[] arr, int p) {
		if (cur > end) {
			return;
		}
		if (cur == end) {
			System.out.println(ans + " ");
			return;
		}
		for (int i = 1; i <= end; i++) {
			maxProfit(cur + i, end, ans + i, arr, p + i);
		}
	}
}
