#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
const int MAX = 10000 + 5;
const int inf = 0x3f3f3f3f;

using namespace std;

struct minHeap{
    int a[MAX];
    int num;
    
    int Top()
    {
    	return a[1];
    }

    int getSize()
    {
    	return num;
    }

    void Insert(int x)
    {
        a[++num] = x;
        int i = num;
        while(i > 1 && a[i >> 1] > a[i])
        {
            swap(a[i], a[i >> 1]);
            i >>= 1;
        }
    }

    int Pop()
    {
    	int res = a[1];
    	swap(a[1], a[num]);
    	num --;
    	int i = 1;
    	while (i * 2 <= num)
    	{
    		int left = i << 1;
    		if (left < num && a[left] > a[left + 1])
    			left ++;
    		if (a[i] > a[left])
			{
 				swap(a[left], a[i]);
 				i = left;
    		}
    		else break;
    	}
		return res;
    }
}Min;


struct maxHeap{
    int a[MAX];
    int num;
    
    int Top()
    {
    	return a[1];
    }

    int getSize()
    {
    	return num;
    }

    void Insert(int x)
    {
        a[++num] = x;
        int i = num;
        while(i > 1 && a[i >> 1] < a[i])
        {
            swap(a[i], a[i >> 1]);
            i >>= 1;
        }
    }

    int Pop()
    {
    	int res = a[1];
    	swap(a[1], a[num]);
    	num --;
    	int i = 1;
    	while (i * 2 <= num)
    	{
    		int left = i << 1;
    		if (left < num && a[left] < a[left + 1])
    			left ++;
    		if (a[i] < a[left])
			{
 				swap(a[left], a[i]);
 				i = left;
    		}
    		else break;
    	}
		return res;
    }
}Max;


struct heap{
	int a[MAX];
	int num;
	bool (*op)(int, int);

	int Top()
	{
		return a[1];
	}

	int getSize()
	{
		return num;
	}

	void Insert(int x)
	{
		a[++num] = x;
		int i = num;
		while(i > 1 && op(a[i >> 1], a[i]))
		{
			swap(a[i >> 1], a[i]);
			i >>= 1;
		}
	}

	int Pop()
	{
		int res = a[1];
		swap(a[1], a[num]);
		num --;
		int i = 1;
		while(i << 1 <= num)
		{
			int l = i << 1;
			if (l < num && op(a[l], a[l + 1])) l++;
			if (op(a[i], a[l]))
			{
				swap(a[i], a[l]);
				i = l;
			}
			else break;
		}

		return res;
	}

}iheap,aheap;

bool max(int a, int b)
{
	return a > b;
}

bool min(int a, int b)
{
	return a < b;
}

bool cmp(int a, int b)
{
	max(a, b);
}



int main()
{

	int a[] = {29,23,20,22,17,15,26,51,19,12,35,40};
	
	make_heap(&a[0], &a[12], cmp);   
	for(int i = 0; i < 12; i++)
	{
		cout<<a[i]<<" ";
	}cout<<endl;

	
	a[12] = 8;
	push_heap(&a[0], &a[13], cmp);
	for(int i = 0; i < 13; i++)
	{
		cout<<a[i]<<" ";
	}cout<<endl;

	
	pop_heap(&a[0], &a[13], cmp);

	for(int i = 0; i < 13; i++)   
	{
		cout<<a[i]<<" ";
	}cout<<endl;


	
	for (int i = 12; i >= 0; i--)
	{
		pop_heap(&a[0], &a[i], cmp);
	}
	for(int i = 0; i < 13; i++)   
	{
		cout<<a[i]<<" ";
	}cout<<endl;

	
	make_heap(&a[0], &a[13],cmp);
	sort_heap(&a[0], &a[13], cmp);
	for(int i = 0; i < 13; i++)
	{
		cout<<a[i]<<" ";
	}cout<<endl;

	int k;

	cout<<"case 1：建立小根堆"<<endl;
	for (int i = 1; i <= 10 ; i++)
	{
		cin >> k;
		Min.Insert(k);
	}
	for (int i = 1; i <= 10; i++)
	{
		cout<<Min.Top()<<" ";
		Min.Pop();
	}cout<<endl;


	cout<<"case 2：建立大根堆"<<endl;
	for (int i = 1; i <= 10 ; i++)
	{
		cin >> k;
		Max.Insert(k);
	}
	for (int i = 1; i <= 10; i++)
	{
		cout<<Max.Top()<<" ";
		Max.Pop();
	}cout<<endl;


	cout<<"case 3：同时建立大根堆和小根堆"<<endl;
	iheap.op = max;
	aheap.op = min;
	for (int i = 1; i <= 10; i++)
	{
		cin>>k;
		iheap.Insert(k);
		aheap.Insert(k);
	}
	for (int i = 1; i <= 10; i++)
	{
		cout<<iheap.Top()<<" ";
		iheap.Pop();
	}cout<<endl;

	for (int i = 1; i <= 10; i++)
	{
		cout<<aheap.Top()<<" ";
		aheap.Pop();
	}cout<<endl;
	

    return 0;
}














































































































































































































