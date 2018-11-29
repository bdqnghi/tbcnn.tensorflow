/*************************************************************************
	> File Name: quick.cpp
	> Author: weih
	> Mail: weihcao@163.com 
	> Created Time: Sat 06 Sep 2014 07:32:45 PM CST
 ************************************************************************/

#include <algorithm>
using std::swap;

void sort(int *a, int n)
{
	//0.处理特殊情况
	if(n <= 1) return;
	if(n == 2)
	{
		if(a[0] > a[1]) swap(a[0], a[1]);
		return;
	}

	//1.选择中间的值为key，并移到最左边
	swap(a[0], a[n/2]);
	int key = a[0];

	//2.分组
	int *L = a + 1;
	int *R = a + n -1;
	while(L < R)
	{
		while(L<R && *L < key) ++L;
		while(a<R && *R >= key) --R;
		if(L<R) swap(*L, *R);
	}

	//3.key插入中间，与比key小的最右边的元素交换
	if(*R < key) swap(a[0], *R);

	//4.递归左,右
	sort(a, R-a);
	sort(R+1, n-1-(R-a));
}

