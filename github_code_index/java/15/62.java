package challenges.assorted;

import static com.google.common.truth.Truth.assertThat;

import java.util.List;

import challenges.AbstractCustomTestRunner;

/**
 * Rod cutting dynamic program.
 * 
 * @author Hxkandwal
 *
 */
public class RodCutting extends AbstractCustomTestRunner {
	
	private static RodCutting _instance = new RodCutting();
	
	private RodCutting() {}

	public static int _cutRod(int[] prices) {
	 	int [] maximalArray = new int [prices.length + 1];
	 	
		int maxOverallPrice = -1;
		for (int length = 1; length <= prices.length; length ++) {
			int maxPrice = -1;
			
			// as prices[0] is for length 1, so prices [length - 1] is for price for complete length
			for (int cut = 0; cut < length; cut ++)
				maxPrice = Math.max (maxPrice, (prices [cut] + maximalArray [length - cut - 1]));
			
			maximalArray [length] = maxPrice;
			maxOverallPrice = Math.max (maxOverallPrice, maxPrice);
		}
		
		return maxOverallPrice;
	}
	
	// driver method
	public static void main(String[] args) {
		_instance.runTest(new int[] { 1, 5, 8, 9, 10, 17, 17, 20 }, 22);
		_instance.runTest(new int[] { 2, 5, 7, 8, 0 }, 12);
		_instance.runTest(new int[] { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 }, 30);		
	}

	public void runTest(final int[] prices, final int expectedOutput) {
		List<Object> answers = runAll(getClass(), new Object[] { prices });

		for (Object answer : answers)
			assertThat((Integer) answer).isEqualTo(expectedOutput);
		
		System.out.println("ok!");
	}
	
}
