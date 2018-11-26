package me.fycus;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Heap extends SortExample {

	public static void sink(Comparable[] a, int k, int N) {

	}
	
	public static void sort(Comparable[] a) {
		int N = a.length - 1;
		for(int i = N/2; i >=1 ; i--) {
			sink(a,i,N);
		}
		show(a);
		while(N > 0) {
			exchange(a,N--,1);
			sink(a,1,N);
		}
	}
	
	public static void main(String[] args) throws FileNotFoundException {

		File file = new File(args[0]);
		Scanner in = new Scanner(file);
		String s = in.nextLine();
		String[] a = s.split("\\s+");
		String[] b = new String[a.length + 1];
		for(int i = 0; i < a.length; i++) {
			b[i+1] = a[i];
		}
		sort(b);
		show(b);
	}

}
