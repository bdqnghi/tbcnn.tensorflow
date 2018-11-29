package dp;

public class RodCutting {
	private static int[] rd;
	
	public static int solve_recursive(int[] value, int size) {
		return solve_recursive_helper(value, size);
	}
	
	private static int solve_recursive_helper(int[] value, int size) {
		if(size == 0) {
			return 0;
		}
		
		int maxVal = Integer.MIN_VALUE;
		for(int i = 1; i <= size; i++) {
			if(i <= value.length) {
				maxVal = Math.max(maxVal, value[i-1] + solve_recursive_helper(value, size-i));
			}
		}
		
		return maxVal;
	}
	
	public static int solve_memoized(int[] value, int size) {
		rd = new int[size+1];
		for(int i = 0; i < rd.length; i++) {
			rd[i] = -1;
		}
		
		return solve_memoized_helper(value, size);
	}
	
	private static int solve_memoized_helper(int[] value, int size) {
		if(size == 0) {
			return 0;
		}
		
		if(rd[size] == -1) {
			int maxVal = Integer.MIN_VALUE;
			for(int i = 1; i <= size; i++) {
				if(i <= value.length) {
					maxVal = Math.max(maxVal, value[i-1] + solve_memoized_helper(value, size-i));
				}
				rd[size] = maxVal;
			}
		}
		
		return rd[size];
	}
	
	
		
	public static void main(String[] args) {
		assert RodCutting.solve_recursive(new int[]{1, 5, 8, 9}, 4) == 10;
		assert RodCutting.solve_memoized(new int[]{1, 5, 8, 9}, 4) == 10;
		
		assert RodCutting.solve_recursive(new int[]{1, 5, 8, 9}, 6) == 16;
		assert RodCutting.solve_memoized(new int[]{1, 5, 8, 9}, 6) == 16;
		
		assert RodCutting.solve_recursive(new int[]{1, 5, 8, 9, 10, 17, 17, 20}, 8) == 22;
		assert RodCutting.solve_memoized(new int[]{1, 5, 8, 9, 10, 17, 17, 20}, 8) == 22;
		
	}
}