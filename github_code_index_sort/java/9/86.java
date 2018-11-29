package com.sort;

import java.util.Arrays;

/**
 * 
 * @author zlf
 * ѡ������
 * ѡ������(Selection-sort)��һ�ּ�ֱ�۵������㷨��
 * ���Ĺ���ԭ����������δ�����������ҵ���С����Ԫ�أ�
 * ��ŵ��������е���ʼλ�ã�Ȼ���ٴ�ʣ��δ����Ԫ���м���Ѱ����С����Ԫ�أ�
 * Ȼ��ŵ����������е�ĩβ���Դ����ƣ�ֱ������Ԫ�ؾ�������ϡ� 
 *
 */
public class SelectSort {

	public static int[] sort(int[] a){
		int len = a.length;
		for(int i =0; i<len; i++){
			int idx=i;
			for(int j=i+1; j<len; j++){
				if(a[j]<a[idx]) idx=j;
				System.out.print(j+",");
			}
			int tmp=a[i];
			a[i]=a[idx];
			a[idx]=tmp;	
			System.out.println(Arrays.toString(a));
		}
		return a;
	}
	
	public static void main(String[] args) {
		int[] arr={31,8,21,5,10,7,4,2};
		int[] arr2=sort(arr);
//		System.out.println(Arrays.toString(arr2));
	}
	
}
