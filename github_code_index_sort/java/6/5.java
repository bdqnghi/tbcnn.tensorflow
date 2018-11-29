package algorithm.sort;

import java.util.LinkedList;
import java.util.Queue;

public class RadixSort {
	public static void sort(int[] data) {
		int radix = 10;
		int digits = 10;

		// 初始化各个队列
		Queue<Integer>[] queues = new Queue[radix];
		for (int i = 0; i < radix; i++) {
			queues[i] = new LinkedList<Integer>();
		}

		// 取整数的第i位数: (num/factor)%10
		for (int i = 0, factor = 1; i < digits; factor *= radix, i++) {
			// 将各个整数按桶放入
			for (int j = 0; j < data.length; j++) {
				queues[(data[j] / factor) % radix].add(data[j]);
			}

			// 把排好序的从桶中取出来
			for (int k = 0, j = 0; j < radix; j++) {
				while (!queues[j].isEmpty()) {
					data[k++] = queues[j].remove();
				}
			}

		}

	}

	public static void main(String[] args) {

		int len = (int) Math.floor(Math.random() * 15);
		int[] a = new int[len];
		for (int i = 0; i < a.length; i++) {
			a[i] = (int) Math.floor(Math.random() * 21);
			System.out.print(a[i] + ",");
		}
		System.out.println("排序");
		sort(a);
		for (int i = 0; i < a.length; i++) {
			System.out.print(a[i] + ",");
		}
		return;
	}
}
