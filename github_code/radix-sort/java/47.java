package com.zh.algorithm;

/**
 * 本程序实现基数排序
 * 		假设 数组A的长度为n 每个元素有d位数字，其中第1位为最低位，第d位为最高位
 *  RADIX-SORT(A,d)
 *  	for i ← 1 to d
 *  		do use a stable sort to sort array A on digit i
 * @author young
 *
 */
public class RadixSortIml {

	public static void main(String[] args) {
			int[] A = {123,132,111,222,158,100,110};
			int[] sort = radixSort(A,3);
			for(int i = 0;i < sort.length;i++){
				if(i == sort.length - 1)
					System.out.print(sort[i] + "]");
				else
					System.out.print(sort[i]+",");
			}

	}

	/**
	 * 基数排序算法
	 * @param a
	 * 		需要排序的数组
	 * @param i
	 * 		数组中元素的最大位数
	 * @return
	 * 		已经排好序的数组
	 */
	private static int[] radixSort(int[] a, int i) {
		
		for(int j = 1;j <= i;j++)
			countSort(a,j);
		return a;
		
	}

	/**
	 * 基数排序的配套计数排序
	 * @param a
	 * 		需要排序的数组
	 * @param j
	 * 		按第j位进行排序
	 */
	private static void countSort(int[] A,int j) {
				int[] B = new int[A.length];
				int exp = getExp(j);
				//找到A中的最大值建立C数组
				int max = getJMax(A, j);
				int[] C = new int[max + 1];
				//对辅助计数数组C进行初始化
				for(int i = 0 ;i < C.length;i++)
					C[i] =  0;
				//对A中的数据在C中进行统计
				for(int i = 0;i < A.length;i++)
					C[(A[i] / exp) % 10]++;
				//将所有的数据的个数从第二位加到最后一位
				for(int i = 1;i < C.length;i++)
					C[i] += C[i - 1];
				//将数据赋值到B数组  为什么需要倒着排序，正者排就会出现问题
				for(int i = A.length - 1;i >= 0;i--){
					B[C[(A[i] / exp) % 10] - 1] = A[i];  //这里 - 1 的目的是为了解决在C的统计过程中的统计的是个数而这个是index
					C[(A[i] / exp) % 10] --;
				}
				
				for(int i = 0;i < A.length;i++)
					A[i] = B[i];
		
	}

	/**
	 * 获取每一次的除数
	 * @param j
	 * 		位数
	 * @return
	 * 		需要的除数
	 */
	private static int getExp(int j) {
		//获取第j位的除数
				int exp = 1;
				for(int i = 1;i < j;i ++){
					exp *= 10;
				}
		return exp;
	}

	private static int getJMax(int[] a, int j) {
		//获取第j位的除数
		int exp = 1;
		for(int i = 1;i < j;i ++){
			exp *= 10;
		}
		
		//获取最大值
		int max = (a[0] / exp) % 10;
		for( int i = 1; i < a.length;i++)
			if(max < (a[i] / exp) % 10)
				max = (a[i] / exp) % 10;
		return max;
	}

}
