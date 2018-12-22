package com.danicuki.introductiontoscala;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class QuickSortJava {

	public static List<Integer> sort(List<Integer> list) {
		if (list.isEmpty()) {
			return list;
		}

		Integer pivot = list.get(0);
		List<Integer> listWithoutPivot = list.subList(1, list.size());

		List<Integer> leftSide = new LinkedList<Integer>();
		for (Integer elem : listWithoutPivot) {
			if (elem <= pivot) {
				leftSide.add(elem);
			}
		}

		List<Integer> rightSide = new LinkedList<Integer>();
		for (Integer elem : listWithoutPivot) {
			if (elem > pivot) {
				rightSide.add(elem);
			}
		}

		List<Integer> result = new ArrayList<Integer>();
		result.addAll(sort(leftSide));
		result.add(pivot);
		result.addAll(sort(rightSide));

		return result;
	}
}
