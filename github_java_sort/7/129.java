package com.sort.base.shell;

import com.sort.base.ISort;
import com.sort.util.Utils;


public class ShellSort implements ISort {

	@Override
	public <T extends Comparable<T>> void sort(T[] arr, int n) {
		int h = 1;
		while (h < n / 3) {
			h = 3 * h + 1; 
		}
		while (h >= 1) {
			
			
			for (int i = h; i < n; i++) {
				T e = arr[i];
				int j;
				for (j = i; j >= h && Utils.aLb(e, arr[j - h]); j -= h) {
					arr[j] = arr[j - h];
				}
				arr[j] = e;
			}
			h=h/3;
		}
	}
	public static void main(String[] args) {
		Integer [] arr = {1,2,3,4,5,8,2,3};
		new ShellSort().sort(arr, arr.length);
		Utils.printArr(arr, "Shell");
	}
}
