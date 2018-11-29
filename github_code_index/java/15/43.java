package cormen;

public class RodCutting {

	private static int[] storedValue;
	public static void main(String[] args) {
		
		int[] arr = {1,5,8,9,10,17,17,20,24,30};
		storedValue = new int[arr.length];
		
		int maxValue = findMaxValue(arr, arr.length);
		
		System.out.println("Max Value is: " + maxValue);

	}
	
	private static int findMaxValue(int[] arr, int length) {
		int maxPrice = Integer.MIN_VALUE;
		
		if(length == 0)
			return 0;
		
		if(storedValue[length - 1]  != 0) {
			return storedValue[length - 1];
		}
		
	
		for(int i = 0; i < length; i++) {
			maxPrice = Math.max(maxPrice, arr[i] + findMaxValue(arr, length - i - 1));
		}
		
		storedValue[length-1] = maxPrice;
		return maxPrice;
	}

}
