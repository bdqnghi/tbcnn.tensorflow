package net.brian.coding.algorithm.crazyjavaimpl;

import java.util.Arrays;

class BucketSortDataWrap implements Comparable<BucketSortDataWrap>
{
	int data;
	String flag;
	public BucketSortDataWrap(int data, String flag)
	{
		this.data = data;
		this.flag = flag;
	}
	public String toString()
	{
		return data + flag;
	}
	
	public int compareTo(BucketSortDataWrap dw)
	{
		return this.data > dw.data ? 1 
			: (this.data == dw.data ? 0 : -1);
	}
}
public class BucketSort
{
	public static void bucketSort(BucketSortDataWrap[] data 
		, int min , int max)
	{
		System.out.println("��ʼ����");
		
		int arrayLength = data.length;
		BucketSortDataWrap[] tmp = new BucketSortDataWrap[arrayLength];
		
		
		int[] buckets = new int[max - min];	
		
		for(int i = 0 ; i < arrayLength ; i++)
		{
			
			buckets[data[i].data - min]++;
		}
		System.out.println( Arrays.toString(buckets));
		
		for(int i = 1 ; i < max - min; i++)
		{
			
			buckets[i] = buckets[i] + buckets[i - 1];
		}
		
		
		
		System.out.println( Arrays.toString(buckets));
		
		System.arraycopy(data, 0, tmp, 0, arrayLength);
		
		for(int k = arrayLength - 1 ; k >=  0 ; k--)
		{
			data[--buckets[tmp[k].data - min]] = tmp[k];
		}
	}
	public static void main(String[] args)
	{
		BucketSortDataWrap[] data = {
			new BucketSortDataWrap(9 , ""),
			new BucketSortDataWrap(5, ""),
			new BucketSortDataWrap(-1, ""),
			new BucketSortDataWrap(8 , ""),
			new BucketSortDataWrap(5 , "*"),
			new BucketSortDataWrap(7 , ""),
			new BucketSortDataWrap(3 , ""),
			new BucketSortDataWrap(-3, ""),
			new BucketSortDataWrap(1 , ""),
			new BucketSortDataWrap(3 , "*")
		};
		System.out.println("����֮ǰ��\n"
			+ java.util.Arrays.toString(data));
		bucketSort(data , -3 , 10);
		System.out.println("����֮��\n" 
			+ java.util.Arrays.toString(data));
	}
}