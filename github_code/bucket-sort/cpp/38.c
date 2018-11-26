/*******************************************************************************
*
* FileName : BucketSort.cpp
* Comment  : Ͱ�����±ߵ�ʵ������򵥵�һ�ַ���������Ԫ�ز�ͬ��һ��Ͱֻ��һ��Ԫ�أ�
* Version  : 1.0
* Author   : kailiu2013@gmail.com
* Date     : 2014/06/09
*
*******************************************************************************/
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

//Ͱ����ԭ���:http://hxraid.iteye.com/blog/647759

void BucketSort(int array[],int len)
{
	int bucket_num=len;
	int* p_bucketArray=new int[bucket_num];
	for(int i=0;i<bucket_num;i++) //��ʼ��bucketԪ��ֵΪ-1
		p_bucketArray[i]=-1;
	for(i=0;i<len;i++)
		p_bucketArray[array[i]]=array[i];
	int j=0;
	for(i=0;i<bucket_num;i++)
	{
		if(p_bucketArray[i]!=-1)
		{
			if(j<len)
			{
				array[j]=p_bucketArray[i];
				j++;
			}
		}
	}
}

void Print(int array[],int length)
{
	//print the array in the form:1->2->3->0
	for(int i=0;i<length;i++)
	{
		if(i<length-1)
			cout<<array[i]<<"->";
		else
			cout<<array[i]<<endl;
	}
}

int main()
{
	int test1[10]={9,7,0,2,5,4,1,6,8,3};
	
	Print(test1,10);
	BucketSort(test1,10);
	Print(test1,10);
	
	return 0;
}