package mysolutions.dp;

public class RodCutting {

	int[] prices;
	int[] cache;

	public RodCutting(int[] prices) {
		this.prices = prices;
		this.cache = new int[prices.length];
	}

	public int cutRecursive() {
		int max = 0;
		for (int i = 0; i < prices.length; i++) {
			int ans = cutRecursiveHelper(prices[i], prices.length
					- (i + 1));
			if (ans > max) {
				max = ans;
			}
		}
		return max;
	}

	private int cutRecursiveHelper(int totalSoFar, int remainingLength) {
		if (remainingLength == 0) {
			return totalSoFar;
		}

		if (remainingLength < 0) {
			return 0;
		}

		int max = 0;
		for (int i = 0; i < prices.length; i++) {
			if (remainingLength - (i + 1) >= 0) {
				int ans = cutRecursiveHelper(totalSoFar + prices[i],
						remainingLength - (i + 1));
				if (ans > max) {
					max = ans;
				}
			}
		}
		return max;
	}
	
	public int cutRecursive2(int remainingLength) {
		
		if ( cache[remainingLength-1] != 0 ) {
			return cache[remainingLength-1];
		}
		
		int max = prices[remainingLength-1];
		for(int i=1;i<remainingLength;i++) {
			int leftPrice = cutRecursive2(i);
			int rightPrice = cutRecursive2(remainingLength-i);
			int ans = leftPrice+rightPrice;
			if ( ans > max ) {
				max = ans;
			}
		}
		
		cache[remainingLength-1] = max;
		
		return max;
	}
	
	public int cutRecursive3(int n) {
		
		if ( n <= 0 ) {
			return 0;
		}
		
		if ( cache[n-1] != 0 ) {
			return cache[n-1];
		}
		
		int max = Integer.MIN_VALUE;
		for(int i=0;i<n;i++) {
			max = Math.max(max, prices[i] + cutRecursive3(n-(i+1)));
		}
		
		cache[n-1] = max;
		return max;
	}
	
	public int cutIterative() {
		int[] val = new int[prices.length+1];
		val[0] = 0;
		
		for(int i=1; i<=prices.length;i++) {
			int max = Integer.MIN_VALUE;
			for(int j=0;j<i;j++) {
				max = Math.max(max, prices[j] + val[i-j-1]);
			}
			val[i] = max;
		}
		return val[prices.length];
	}
	
	static void testRecursive() {
		int[] prices = new int[] { 1, 5, 8, 9, 10, 17, 17, 20 };
		//prices = new int[]{1,5,8,9};
		RodCutting rc = new RodCutting(prices);
		long start = System.nanoTime();
		int max = rc.cutRecursive();
		long end = System.nanoTime();
		System.out.println("recursive max=" + max + ", time=" + (end - start));
	}
	
	static void testRecursive2() {
		int[] prices = new int[] { 1, 5, 8, 9, 10, 17, 17, 20 };
		//prices = new int[]{1,5,8,9};
		RodCutting rc = new RodCutting(prices);
		long start = System.nanoTime();
		int max = rc.cutRecursive2(prices.length);
		long end = System.nanoTime();
		System.out.println("recursive2 max=" + max + ", time=" + (end - start));
	}
	
	static void testRecursive3() {
		int[] prices = new int[] { 1, 5, 8, 9, 10, 17, 17, 20 };
		//prices = new int[]{1,5,8,9};
		RodCutting rc = new RodCutting(prices);
		long start = System.nanoTime();
		int max = rc.cutRecursive3(prices.length);
		long end = System.nanoTime();
		System.out.println("recursive3 max=" + max + ", time=" + (end - start));
	}
	
	static void testIterative() {
		int[] prices = new int[] { 1, 5, 8, 9, 10, 17, 17, 20 };
		//prices = new int[]{1,5,8,9};
		RodCutting rc = new RodCutting(prices);
		long start = System.nanoTime();
		int max = rc.cutIterative();
		long end = System.nanoTime();
		System.out.println("iterative max=" + max + ", time=" + (end - start));
	}

	public static void main(String[] args) {
		testRecursive();
		testRecursive2();
		testRecursive3();
		testIterative();
	}
}