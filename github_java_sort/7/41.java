package yuan.jin.interviewQuestions.sort;

import java.util.Arrays;


public class Shellsort {

	
	public static void shellSort(int[] a) {
		
		for (int hop = a.length / 2; hop > 0; hop /= 2) {
			
			for (int i = hop; i < a.length; i++) {
				int key = a[i];
				int j = i;
				for (; j >= hop && (a[j - hop] > key); j -= hop)
					a[j] = a[j - hop];
				a[j] = key;
			}
		}
	}
	
	
	public static void shellSort2(int[] a) {
		int N = a.length;
		int h = 1;
		while (h < N/3) h = 3*h + 1;
		while (h >= 1) {
			for (int i = h; i < N; i++)
				for (int j = i; j >= h && a[j] < a[j-h]; j -= h) {
					int t = a[j];
					a[j] = a[j-h];
					a[j-h] = t;
				}
			h = h/3;
		}
	}

	public static void main(String[] args) {
		int[] seq = { 3, 5, 0, 2, 1, 6 };

		shellSort(seq);
		System.out.println(Arrays.toString(seq));
	}

}
