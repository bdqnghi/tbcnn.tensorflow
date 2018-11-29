package array;

public class RodCutting {

	public static int profitDP(int[] value, int length) {
		int[] solution = new int[length + 1];
		solution[0] = 0;

		for (int i = 1; i <= length; i++) {
			int max = -1;
			for (int j = 0; j < i; j++) {
				max = Math.max(max, value[j] + solution[i - (j + 1)]);
				solution[i] = max;
			}
		}
		return solution[length];
	}
	public static int profit(int[] value, int length) {
		if (length <= 0)
			return 0;
			// either we will cut it or don't cut it
			int max = -1;
			for(int i=0;i<length;i++)
				max = Math.max(max, value[i] + profit(value, length-(i+1)));			
			return max;		
	}

	public static void main(String[] args) {
		int[] value = { 2, 3, 7, 8, 9 };
		int len = 3;
		System.out.println("Max profit for length is " + len + ":"
				+ profitDP(value, len));

	}

}
