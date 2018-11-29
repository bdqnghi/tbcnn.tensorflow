//ѡ������ O(n^2)  ���ȶ����������ͬԪ�ص����飩
//���ȴ�����A���ҳ���С��������Ԫ�����һ��������Ȼ����A���ҳ�
//��С��Ԫ����ڶ���Ԫ�ؽ������Դ����ơ�

#include <iostream>

using namespace std;

void selectionSort(int a[], int n)
{
	int minID;
	for (int i = 0; i < n; i++)
	{
		minID = i;
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[minID])
			{
				minID = j;
			}
		}
		int temp = a[i];
		a[i] = a[minID];
		a[minID] = temp;
	}
}

int main()
{
	const size_t arraySize = 10;
	int arr[arraySize];
	int inputData;        
	cout << "����������" << arraySize << "�����ݣ�" << endl;
	for (int i = 0; i < arraySize; i++)
	{
		cin >> inputData;
		arr[i] = inputData;
	}

	selectionSort(arr, arraySize);

	cout << "�����������������˳����:" << endl;
	for (size_t i = 0; i < arraySize; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}