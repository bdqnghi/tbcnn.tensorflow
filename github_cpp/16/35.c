


#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

using namespace std;

  
 

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

