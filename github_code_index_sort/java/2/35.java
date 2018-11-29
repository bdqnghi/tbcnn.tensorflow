package keeyeong.codility.others;

import java.util.Arrays;

public class MergeSortSort {
	/*
	 * I forgot to save this one so this is purely from memory!
	 */

	/*
	 * The solution I came up with that should be correct. I was misled by their
	 * sample input!
	 */
	int solution(int[] times) {
		Arrays.sort(times);
		int result = 0;
		for (int i : times) {
			result = result + (result + i);
		}
		return result;
	}

	/*
	 * The solution I submitted which got me 0 points :( Well at least i think
	 * this was it?
	 */
	int solutionBad(int[] times) {
		Arrays.sort(times);
		int result = 0;
		for (int i = 1; i <= times.length; i++) {
			result = times[i - 1] + (i * result);
		}
		return result;
	}
}
