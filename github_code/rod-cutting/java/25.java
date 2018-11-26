package trd.algorithms.DynamicProgramming;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class RodCutting {
	public static final List<Integer> emptyList = new ArrayList<Integer>();
	public static List<Integer> NewClone(List<Integer> src) {
		return src.stream().collect(Collectors.toList());
	}
	public static List<Integer> Cut(Integer[] L, Integer[] V, int length) {
		int maxVal = 0; List<Integer> maxCut = emptyList;
		for (int i = 0; i < L.length; i++) {
			if (L[i] <= length) {
				List<Integer> cutList = Cut(L, V, length - L[i]);
				int thisVal = V[i] + cutList.stream().reduce(0, (a,b)->(a+V[b]));
				if (thisVal > maxVal || (thisVal == maxVal && cutList.size() < maxCut.size())) {
					maxVal = thisVal;
					maxCut = NewClone(cutList);
					maxCut.add(i);
				}
			}
		}
		return maxCut;
	}
	
	public static void main(String[] args) {
		Integer[] L = new Integer[] {1, 2, 3, 4}, V = new Integer[] {2, 5, 7, 8};
		List<Integer> cutList = Cut(L, V, 10);
		System.out.printf("%s = %d\n",
						  cutList.stream().map((a)->L[a]).collect(Collectors.toList()),
						  cutList.stream().reduce(0, (a,b)->(a + V[b])));
	}
}
