package me.fycus;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Quick extends SortExample{

	private static int partition(Comparable[] a, int lo, int hi) {
		int i = lo;
		int j = hi + 1;
		while(true) {
			while(less(a[++i],a[lo])) if(i == hi) break;
			while(less(a[lo],a[--j])) if(j == lo) break;
			exchange(a,i,j);
			if(i >= j) break;
		}
		exchange(a,lo,i);
		return i;
	}
	
	public static void sort(Comparable[] a) {
		sort(a,0,a.length-1);
	}
	
	public static void sort(Comparable[] a, int lo, int hi) {
		if(lo >= hi) return;
		int i = partition(a,lo,hi);
//		sort(a,lo,i);  StackOverflowError! a[i] has been in the right position! If you do like this, the recursion will not end!
		sort(a,lo,i-1);
		sort(a,i+1,hi);
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		File file = new File(args[0]);
		Scanner in = new Scanner(file);
		String s = in.nextLine();
		String[] a = s.split("\\s+");
		show(a);
		sort(a);
		show(a);
	}
	
}
