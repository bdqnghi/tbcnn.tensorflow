package com.yesun.sample.sort;

import java.util.Arrays;

/**
 * sample JavaHeapSort.java
 * Description:堆排序，原理：从后面开始建堆并排序，堆顶为最大值；将最大堆顶取出，置换堆尾，堆大小减一；如此重复；
 * 1、建堆
 * 2、排序n-1次，保证堆顶为整个二叉树最大值
 * 3、置换堆顶和堆尾，堆大小--
 * 
 * 
 * 
 * 1.0 YESUN Aug 9, 2013 5:35:37 PM Create.
 * ChangeLog:
 */
public class JavaHeapSort {

	private static int[] sort = new int[] { 73, 22, 93, 43, 55, 14, 28, 65, 39, 81, 33, 100 };

	private static void buildMaxHeapify(int[] data) {
		//没有子节点的才需要创建最大堆，从最后一个的父节点开始
		int startIndex = getParentIndex(data.length - 1);
		//从尾端开始创建最大堆，每次都是正确的堆
		for (int i = startIndex; i >= 0; i--) {
			maxHeapify(data, data.length, i);
			System.out.println(Arrays.toString(sort));
		}
		
	}

	/**
	 * 创建最大堆
	 * @param data
	 * @param heapSize 需要创建最大堆的大小，一般在sort的时候用到，因为最多值放在末尾，末尾就不再归入最大堆了
	 * @param index 当前需要创建最大堆的位置
	 */
	private static void maxHeapify(int[] data, int heapSize, int index) {
		// 当前点与左右子节点比较
		int left = getChildLeftIndex(index);
		int right = getChildRightIndex(index);

		int largest = index;
		if (left < heapSize && data[index] < data[left]) {
			largest = left;
		}
		if (right < heapSize && data[largest] < data[right]) {
			largest = right;
		}
		//得到最大值后可能需要交换，如果交换了，其子节点可能就不是最大堆了，需要重新调整
		if (largest != index) {
			int temp = data[index];
			data[index] = data[largest];
			data[largest] = temp;
			maxHeapify(data, heapSize, largest);//调整其子节点，递归
		}
	}

	/**
	 * 排序，最大值放在末尾，data虽然是最大堆，在排序后就成了递增的
	 * @param data
	 */
	private static void heapSort(int[] data) {
		//末尾与头交换，交换后调整最大堆
		for (int i = data.length - 1; i > 0; i--) {
			int temp = data[0];
			data[0] = data[i];
			data[i] = temp; //将堆顶（最大值）交换到堆尾，然后二叉树-1，继续从0开始调整二叉树，使得最大值浮到堆顶			
			maxHeapify(data, i, 0); 
			System.out.println(Arrays.toString(sort));
		}
	}

	/**
	 * 父节点位置
	 * @param current
	 * @return
	 */
	private static int getParentIndex(int current) {
		return (current - 1) >> 1;
	}

	/**
	 * 左子节点position 注意括号，加法优先级更高
	 * @param current
	 * @return
	 */
	private static int getChildLeftIndex(int current) {
		return (current << 1) + 1;
	}

	/**
	 * 右子节点position
	 * @param current
	 * @return
	 */
	private static int getChildRightIndex(int current) {
		return (current << 1) + 2;
	}

	private static void print(int[] data) {
		int pre = -2;
		for (int i = 0; i < data.length; i++) {
			if (pre < (int) getLog(i + 1)) {
				pre = (int) getLog(i + 1);
				System.out.println();
			}
			System.out.print(data[i] + " |");
		}
	}

	/**
	 * 以2为底的对数
	 * @param param
	 * @return
	 */
	private static double getLog(double param) {
		return Math.log(param) / Math.log(2);
	}

	/**
	 * Description:
	 * @param args
	 * 1.0 YESUN Aug 9, 2013 5:02:36 PM Create.
	 * ChangeLog:
	 */
	public static void main(String[] args) {
		buildMaxHeapify(sort);

		System.out.println("build:"+Arrays.toString(sort));
		heapSort(sort);
//		print(sort);
		

	}

}
