package de.carullojabro.sortalgorithms.algorithms;

import java.util.ArrayList;
import java.util.List;



public class Bucketsort implements ISortAlgorithm {

	private List<Integer> list;
	@SuppressWarnings("unchecked")
	private List<Integer>[] aF�cher = new List[10];

	public Bucketsort(List<Integer> list) {
		this.list = list;
	}

	
	public List<Integer> sort() {
		
		initBuckets();

		
		fillBuckets();

		
		fillList();

		return list;
	}

	private void initBuckets() {
		for (int i = 0; i < aF�cher.length; i++) {
			aF�cher[i] = new ArrayList<Integer>();
		}
	}

	private void fillBuckets() {
		for (int wert : list) {
			aF�cher[wert].add(wert);
		}
	}

	private void fillList() {
		list.clear();
		for (int i = 0; i < aF�cher.length; i++) {
			list.addAll(aF�cher[i]);
		}
	}

}