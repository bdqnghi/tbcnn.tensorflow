package net.brian.coding.algorithm.crazyjavaimpl;

import java.util.Arrays;
/**
 * Ͱʽ����
 * ��������һ�ֻ��ڱȽϵ����򷽷�����������֮�����ڣ�
 * a.�������е�����ֵ����һ����ö�ٷ�Χ��
 * ����[9, 5, -1, 8, 5, 7, 3, -3, 1, 3]��ö�ٷ�Χ���ǣ�
 * [-3, -1, 1, 3, 5, 7, 8, 9]һ��8��Ԫ��
 * b.�����ö�ٵķ�Χ����̫�󣬷�����̫��
 * 
 * Ͱʽ����ֻ��Ҫ���ֱ�����
 * ��һ�ֱ����������ݣ�ͳ��ÿ���������������Ͱ�еĸ���
 * �ڶ��ֱ����������¼���ÿ��buckets����Ԫ�ص�ֵ
 * ���ֱ�����Ϳ��Եõ�ÿ���������������������е�λ�ã�Ȼ�󽫸���������һ���Է���ָ��λ�ü���
 * 
 * Ͱʽ����ռ俪���Ƚϴ���Ϊ����Ҫ��������
 * 
 */
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
	//����dataʵ����������������BucketSortDataWrap�Ĵ�С
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
		//arrayLength��¼����������ĳ���
		int arrayLength = data.length;
		BucketSortDataWrap[] tmp = new BucketSortDataWrap[arrayLength];
		//buckets�����൱�ڶ�����max - min��Ͱ��
		//buckets�������ڼ�¼������Ԫ�ص���Ϣ
		int[] buckets = new int[max - min];	
		//����ÿ��Ԫ�������г��ֵĴ���
		for(int i = 0 ; i < arrayLength ; i++)
		{
			//buckets�����¼��BucketSortDataWrap���ֵĴ���
			buckets[data[i].data - min]++;
		}
		System.out.println( Arrays.toString(buckets));
		//���㡰���롱��Ͱ�ڵ�Ԫ�������������е�λ��
		for(int i = 1 ; i < max - min; i++)
		{
			//ǰһ��bucket��ֵ + ��ǰbucket��ֵ -> ��ǰbucket�µ�ֵ
			buckets[i] = buckets[i] + buckets[i - 1];
		}
		//ѭ��������buckets����Ԫ�ؼ�¼�ˡ����롱ǰ������Ͱ�� 
		//�����롱��ǰbucket��Ԫ�ص�������
		//Ҳ��˵��buckets����Ԫ�ص�ֵ�����ˡ����롱��ǰͰ��Ԫ�������������е�λ��
		System.out.println( Arrays.toString(buckets));
		//��data������������ȫ���Ƶ�tmp�����л���������
		System.arraycopy(data, 0, tmp, 0, arrayLength);
		//����buckets�����е���Ϣ���������еĸ�Ԫ�ط�����Ӧ��λ�á�
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