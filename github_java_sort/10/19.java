package com.odoni.algorithms.sort.bucket;

import com.odoni.algorithms.sort.Sort;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class BucketSort implements Sort {

	public int[] sort(int[] arrayToSort) {
		int max = getMaxFromArray(arrayToSort);
		Map<Integer, Integer> bucketMap = new HashMap<>();
		for (int i = 0; i <= max; i++) {
			bucketMap.put(i, 0);
		}
		for (int i = 0; i < arrayToSort.length; i++) {
			bucketMap.put(arrayToSort[i], bucketMap.get(arrayToSort[i])+1);
		}
		int sortedArrayIndex = 0;
		for (Map.Entry<Integer, Integer> entry: bucketMap.entrySet()) {
			for (int i = 0; i < entry.getValue(); i++) {
				arrayToSort[sortedArrayIndex++] = entry.getKey();
			}
		}
		return arrayToSort;
	}

	protected int getMaxFromArray(int[] arrayToSort) {
		List<Integer> numbers = Arrays.stream(arrayToSort).boxed().collect(Collectors.toList());
		return numbers.stream().mapToInt(Integer::intValue).max().getAsInt();
	}
}
