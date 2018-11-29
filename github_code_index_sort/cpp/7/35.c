// Temp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

using namespace std;

/** 
 * ֱ�Ӳ��������һ����ʽ 
 * 
 * @param int dk ��С�����������ֱ�Ӳ�������dk=1 
 * 
 */  
 /*
void ShellInsertSort(int a[], int n, int dk)  
{  
    for(int i= dk; i<n; ++i)
	{  
        if(a[i] < a[i-dk])
		{          //���i��Ԫ�ش���i-1Ԫ�أ�ֱ�Ӳ��롣С�ڵĻ����ƶ����������  
            int j = i-dk;     
            int x = a[i];           //����Ϊ�ڱ������洢������Ԫ��  
            a[i] = a[i-dk];         //���Ⱥ���һ��Ԫ��  
            while(x < a[j] && j >=0)
			{     //�����������Ĳ���λ��  
                a[j+dk] = a[j];  
                j -= dk;             //Ԫ�غ���  
            }  
            a[j+dk] = x;            //���뵽��ȷλ��  
        }  
		//cout << "-------" << dk << endl;
        print(a, n,i );  
		
    }  
      
}  */
/***********************************************************************
//
//  Shell Sort
//
***********************************************************************/
void Shell_Short(int a[], int len)
{
	int dk = len / 2;
	int lin = 0;
	int key = 0;
	while (dk >0)
	{
		for (int i = dk; i < len; i++)
		{
			if (a[i] < a[i - dk])
			{
				lin = i - dk;
				key = a[i];
				a[i] = a[i - dk];
				while (a[lin] > key && lin >= 0)
				{
					a[lin + dk] = a[lin];
					lin -= dk;
				}
				a[lin + dk] = key;
			}
		}
		dk /= 2;
	}
}

int main(int argc, char* argv[])
{
	int a[] = { 7,6,3,9,5,1,2,8,4,10 };
	int length = sizeof(a) / sizeof(a[0]);
	int i = 0;
	cout << "����ǰ��" << endl;
	for ( i = 0; i < length; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	
	Shell_Short(a, length );
	
	cout << "�����" << endl;
	for ( i = 0; i < length; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;

	return 0;
}

