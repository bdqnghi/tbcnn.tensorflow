package com.basicsort;

import java.util.Arrays;

/**
 * 
 * @author beta
 *插入排序
 */
public class Insertionsort {
	
	public static void sort(int[] arr) {
		for(int i=1;i<arr.length;i++) {
			for(int j=i;j>0;j--) {
				if(arr[j]<arr[j-1]) {
					int temp = arr[j];
					arr[j] = arr[j-1];
					arr[j-1] = temp;
				}else {
					break;
				}
			}
		}
	}
	
	//插入排序优化
	public static void sort2(int[] arr) {
		for(int i=0;i<arr.length;i++) {
			int j = i;
			int temp = arr[i];
			for(;j>0&&arr[j-1]>temp;j--) {
				arr[j] = arr[j-1];
			}
			arr[j] = temp;
		}
	}
	
	public static void main(String[] args) {
		int[] arr = SortTestHelp.generateRandomArray(10, 1, 100);
		System.out.println(Arrays.toString(arr));
		sort2(arr);
		System.out.println(Arrays.toString(arr));
	}
}
