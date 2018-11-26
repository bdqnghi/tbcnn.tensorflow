// Bubble.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;
void Swap(int &x, int &y) {
	int temp = x;
	x = y;
	y = temp;
}

void Bubble(int list[], int length) {
	for (int i = 0; i < length - 1; i++) {
		if (list[i] > list[i + 1])
			Swap(list[i], list[i + 1]);
	}
}
void BubbleSort(int list[], int length) {
	for (int i = length; i > 1; i--) {
		Bubble(list, i);
	}
}
int main()
{
	int a[] = { 2,5,8,4,6,3,1,9,7 };
	BubbleSort(a, 9);
	for (int i = 0; i < 9; i++) {
		cout << a[i];
	}
	int b;
	cin >> b;
    return 0;
}

