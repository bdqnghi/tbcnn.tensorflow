package com.base.排序;

import org.junit.Test;

/**
 * 希尔排序
 */
public class shellsort {
	int[] a = { 89, 87, 67, 69, 100, 75, 99, 90 };
	
	@Test
	public void shellsort1() {
		int i, j, gap;

		for (gap = a.length / 2; gap > 0; gap /= 2)// 步长
			for (i = 0; i < gap; i++) // 直接插入排序
			{
				for (j = i + gap; j < a.length; j += gap)
					if (a[j] < a[j - gap]) {
						int temp = a[j];
						int k = j - gap;
						while (k >= 0 && a[k] > temp) {
							a[k + gap] = a[k];
							k -= gap;
						}
						a[k + gap] = temp;
					}
			}
		for (i = 0; i < a.length; i++) {
			System.out.print(a[i] + "\t");
		}
	}
}
