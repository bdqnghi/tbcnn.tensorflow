package uk.ac.cam.ch.wwmm.ptc.experimental;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Random;

import uk.ac.cam.ch.wwmm.oscar3.terms.TermSets;

public class Selection {

	static int swaps;
	
	public static void swap(List l, int index1, int index2) {
		if(index1 == index2) return;
		swaps++;
		Object tmp = l.get(index1);
		l.set(index1, l.get(index2));
		l.set(index2, tmp);
	}
	
	public static int partition(List<Comparable> l, int left, int right, int pivotIndex) {
		Comparable pivotValue = l.get(pivotIndex);
		swap(l, right, pivotIndex);
		int storeIndex = left;
		for(int i=left;i<right;i++) {
			if(l.get(i).compareTo(pivotValue) < 0) {
				swap(l, i, storeIndex);
				storeIndex++;
			}
		}
		swap(l,right,storeIndex);
		return storeIndex;
	}
	
	public static void quickSort(List l) {
		quickSort((List<Comparable>)l, 0, l.size() - 1, new Random());
	}
	
	public static void quickSort(List<Comparable> l, int left, int right, Random r) {
		if(left >= right) return;
		if(left+1 == right) {
			if(l.get(left).compareTo(l.get(right)) > 0) swap(l, left, right);
			return;
		}
		int pivot = partition(l, left, right, left + 0);//r.nextInt(right-left+1));
		quickSort(l, left, pivot-1, r);
		quickSort(l, pivot+1, right, r);
	}

	public static void partialQuickSort(List l, int n) {
		swaps = 0;
		partialQuickSort((List<Comparable>)l, n, 0, l.size() - 1, null);//new Random());
		//System.out.println("Swaps: " + swaps);
	}

	
	public static void partialQuickSort(List<Comparable> l, int n, int left, int right, Random r) {
		if(left >= right) return;
		if(left+1 == right) {
			if(l.get(left).compareTo(l.get(right)) > 0) swap(l, left, right);
			return;
		}
		int pivot = partition(l, left, right, left + 0);//r.nextInt(right-left+1));
		if(n == pivot) {
			
		} else if(n < pivot) {
			partialQuickSort(l, n, left, pivot-1, r);
		} else {
			//quickSort(l, left, pivot-1, r);
			partialQuickSort(l, n, pivot+1, right, r);			
		}
	}
	
	
	
	//public static List lowestN(List<Comparable> l, int n) {
	//	
	//}
	
	
	
	
	public static void main(String [] args) {
		Random r = new Random(0);
		List<String> nList = new ArrayList<String>(TermSets.getUsrDictWords());
		System.out.println(nList.size());
		//Collections.shuffle(nList, r);
		//Collections.sort(nList, Collections.reverseOrder());
		
		/*long time = System.currentTimeMillis();
		quickSort(nList);
		System.out.println(System.currentTimeMillis() - time);
		for(int i=0;i<nList.size()-1;i++) {
			if(nList.get(i).compareTo(nList.get(i+1)) > 0) {
				System.out.println(nList.get(i) + "\t" + nList.get(i+1));
			}
		}*/
		int n = 4000;
		long time = System.currentTimeMillis();
		partialQuickSort(nList, n);
		List<String> topN = nList.subList(0, n);
		//quickSort(topN);
		//Collections.sort(topN);
		System.out.println(System.currentTimeMillis() - time);
		System.out.println(topN.toString().hashCode());
		
		
		/*for(int i=0;i<10;i++) {
			time = System.currentTimeMillis();
			String [] ss = nList.toArray(new String[0]);
			//List<String> foo = new ArrayList<String>(nList.toArray(new String[0]));
			ss[10] = "foo";
			System.out.println(System.currentTimeMillis()-time);
		}*/
		
		for(n=2;n<nList.size()/2;n*=2) {
			long pqstime = 0;
			long pqtime = 0;
			long hpqstime = 0;
			long tswaps = 0;
			for(int i=0;i<100;i++) {
				r = new Random(i);
				Collections.shuffle(nList, r);
				List<String> nList2 = new ArrayList<String>(nList);
				List<String> nList3 = new ArrayList<String>(nList);
						time = System.currentTimeMillis();
				partialQuickSort(nList, n);
				topN = nList.subList(0, n);
				tswaps += swaps;
				quickSort(topN);
				pqstime += System.currentTimeMillis() - time;
				time = System.currentTimeMillis();
				topN = new ArrayList<String>(n);
				PriorityQueue<String> pq = new PriorityQueue<String>(nList2);
				for(int j=0;j<n;j++) topN.add(pq.poll());
				pqtime += System.currentTimeMillis() - time;
				
				time = System.currentTimeMillis();
				Random rr = new Random();
				partialQuickSort((List)nList3, n, 0, (nList3.size()/2)-1, rr);
				partialQuickSort((List)nList3, n, (nList3.size()/2), nList3.size()-1, rr);
				List<String> results = new ArrayList<String>(n * 2);
				results.addAll(nList3.subList(0, n));
				results.addAll(nList3.subList(nList3.size()/2, nList3.size()/2+n));
				partialQuickSort(results, n);
				topN = results.subList(0, n);
				quickSort(topN);
				hpqstime += System.currentTimeMillis() - time;
			}
			
			System.out.println(n + "\t" + pqstime + "\t" + pqtime + "\t" + hpqstime + "\t" + tswaps + "\t" + (tswaps * 1.0 / nList.size()));
		}
	}
	
}
