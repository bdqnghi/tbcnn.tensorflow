package sort;

import java.util.ArrayList;
import java.util.Collections;

public class BucketSort {

	public static void main(String[] args) {
		
		test();
	}
	
	
	
	public static int[] bucketSort(int[] input, int bucketCount) {
		if (input == null || input.length <= 1) {
			return input;
		}
		int[] output = new int[input.length];
		int lowerBound = Integer.MAX_VALUE;
		int upperBound = Integer.MIN_VALUE;
		for (int i = 0; i < input.length; i++) {
			upperBound = Math.max(upperBound, input[i]);
			lowerBound = Math.min(lowerBound, input[i]);
		}
		
		double interval = (double)(upperBound - lowerBound + 1)/bucketCount;

		ArrayList<ArrayList<Integer>> buckets = new ArrayList<ArrayList<Integer>>();
		
		
		for (int i = 0; i < bucketCount; i++) {
			ArrayList<Integer> line = new ArrayList<Integer>();
			buckets.add(line);
		}
		for (int i = 0; i < input.length; i++) {	
			int pos = (int) ((input[i] - lowerBound)/interval);
			buckets.get(pos).add(input[i]);
		}
		
		
		for (int i = 0; i < bucketCount; i++) {
			Collections.sort(buckets.get(i));
		}
		int pointer = 0;
		for (int i = 0; i < bucketCount; i++) {
			for (int j = 0; j < buckets.get(i).size(); j++) {
				output[pointer] = buckets.get(i).get(j);
				pointer ++;
			}
		}
		return output;
	}
	
	public static void test() {
		int[] input = {95, 9, 95, 87, 8, 81, 18, 54, 57, 53, 92, 15, 38, 24, 8, 56, 29, 69, 64 ,66 };
		int bucketCount = 3;
		int[] output = bucketSort(input, bucketCount);
		
		for (int i = 0; i < output.length; i++) {
			System.out.print(output[i] + " ");
		}
		System.out.println();
		
		
	}
	
	
	
	
	

}
