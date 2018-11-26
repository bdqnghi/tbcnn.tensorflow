/**
 * 
 */
package yasarcan;

/**
 * @author yasarcan
 * 
 */
public class RodCutting {

	// static int[] prices={0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

	static int cutRod(int[] prices, int size) {

		if (size == 0)
			return 0;
		int best = Integer.MIN_VALUE;
		for (int cutIndex = 1; cutIndex <= size; cutIndex++)
			best = Math.max(best, prices[cutIndex] + cutRod(prices, (size - cutIndex)));

		return best;
	}

	static int cutRodMemoized(int[] prices, int size) {
		int[] bestPrices = new int[size+1];
		for (int i = 0; i <= size; i++) {
			bestPrices[i] = Integer.MIN_VALUE;
		}

		return MemoizedCutRodHelper(prices, size, bestPrices);
	}

	static int MemoizedCutRodHelper(int[] prices, int size, int[] bestPrices) {
		int best;
		if (bestPrices[size] >= 0) {
			return bestPrices[size];
		} else if (size == 0) {
			best = 0;
		} else {
			best = Integer.MIN_VALUE;
		}
		for (int i = 1; i <= size; i++) {
			best = Math.max(best, prices[i] + MemoizedCutRodHelper(prices, size - i, bestPrices));
			bestPrices[size] = best;
		}
		return best;

	}
	
	static int BottomUp(int[] prices, int size){
		int[] bestPrices = new int[size+1];
		//int best;
		bestPrices[0]=0;
		for (int i = 1; i <= size; i++) {
			int best=Integer.MIN_VALUE;
			for (int cutIndex = 1; cutIndex <= i; cutIndex++) 
				best=Math.max(best, prices[cutIndex]+ bestPrices[i-cutIndex]);	
				bestPrices[i]=best;	
		}
		return bestPrices[size];
		
	}

	static void timeCompare(int[] prices, int size) {
		long startTime = System.nanoTime();
		RodCutting.cutRod(prices, size);
		long estimatedTime1 = System.nanoTime() - startTime;
		long startTime2 = System.nanoTime();
		RodCutting.cutRodMemoized(prices, size);
		long estimatedTime2 = System.nanoTime() - startTime2;
		long startTime3 = System.nanoTime();
		RodCutting.BottomUp(prices, size);
		long estimatedTime3 = System.nanoTime() - startTime3;
		

		System.out.println("When size is " + size + ", time is "
				+ estimatedTime1 + " for Top-Down, " + estimatedTime2
				+ " for Memoized  and "+estimatedTime3+" for Bottom Up.");
	}
}
