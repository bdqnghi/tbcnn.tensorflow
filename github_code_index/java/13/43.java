package com.Basic.Algorithm;

public class Sort_ShellSort extends CommonUtil{

	/**
	 * 在直接插入排序的基础上，添加了 步长dk
	 * 每次都是跳跃插入
	 * @param 数组a
	 * @param 长度n
	 * @param 步长dk
	 */
	static void ShellInsertSort(int a[], int n, int dk)  
	{  
		for(int i= dk; i<n; ++i){  
			if(a[i] < a[i-dk]){          //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入  
				int j = i-dk;     
				int x = a[i];           //复制为哨兵，即存储待排序元素  
				a[i] = a[i-dk];         //首先后移一个元素  
				while(x < a[j]){     //查找在有序表的插入位置  
					a[j+dk] = a[j];  
					j -= dk;             //下一个位置
					
					if(j<0) break;
				}  
				a[j+dk] = x;            //插入到正确位置  
			}  
			printArray(a, n,i );  
		}  

	}  

	/** 
	 * 先按增量d=n/2
	 * n为要排序数的个数进行希尔排序 
	 * 
	 */  
	static void shellSort(int a[], int n){  
		int dk = n/2;  
		while( dk >= 1  ){  
			ShellInsertSort(a, n, dk);  
			dk = dk/2;  
		}  
	}  
	public static void main(String[] args) {
		int[] a = {3,1,5,7,2,4,9,6};  
		shellSort(a,8);  
		printArray(a,8,8);  
	}

}
