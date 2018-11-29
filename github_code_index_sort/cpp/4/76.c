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
/*STL标准库的使用*/


int main()
{

	int a[] = {29,23,20,22,17,15,26,51,19,12,35,40};
	//建堆
	make_heap(&a[0], &a[12], cmp);   //或者默认
	for(int i = 0; i < 12; i++)
	{
		cout<<a[i]<<" ";
	}cout<<endl;

	//插入堆，会自动调整
	a[12] = 8;
	push_heap(&a[0], &a[13], cmp);
	for(int i = 0; i < 13; i++)
	{
		cout<<a[i]<<" ";
	}cout<<endl;

	//弹出堆顶元素
	pop_heap(&a[0], &a[13], cmp);

	for(int i = 0; i < 13; i++)   //弹出放到尾？试试看
	{
		cout<<a[i]<<" ";
	}cout<<endl;


	//全部弹出后得到有序序列	
	for (int i = 12; i >= 0; i--)
	{
		pop_heap(&a[0], &a[i], cmp);
	}
	for(int i = 0; i < 13; i++)   //弹出放到尾？试试看
	{
		cout<<a[i]<<" ";
	}cout<<endl;

	//再变回来试试sort直接得到有序序列，排完序就不是堆了。。
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




// #include <iostream>
// #include <cstdio>
// #include <cstring>

// using namespace std;

// /*keep max heapify, 
// *调整堆A的第k个位置，堆的大小是size(调整堆不改变大小)，A并不是全部元素都是堆
// *调用时，从底往上调，调整的是子树的最大堆性质*/
// void maxHeapify(int *a, int k, int size)
// {
// 	int l = 2 * k;
// 	int r = 2 * k + 1;
// 	int large = k;
// 	if (k <= size / 2)
// 	{
// 		if (l <= size && a[large] < a[l])
// 		{
// 			large = l;
// 		}
// 		if (r <= size && a[large] < a[r])
// 		{
// 			large = r;
// 		}
// 		if(large != k)
// 		{
// 			swap(a[k], a[large]);
// 			maxHeapify(a, large, size); //递归调用子树的
// 		}
// 	}
// }

// /*build max heap*/
// void buildMaxHeap(int a[], int size)
// {
// 	for (int i = size / 2; i >= 1; i--)
// 	{
// 		maxHeapify(a, i, size);
// 	}
// }

// /*heapsort*/
// void heapSort(int *a, int size)
// {
// 	buildMaxHeap(a, size);
// 	for (int i = size; i >= 1; i--)
// 	{
// 		swap(a[i], a[1]);    //将堆顶（当前最大值）和堆最后一个元素交换，慢慢生成有序序列
// 		maxHeapify(a, 1, i - 1);
// 	}
// }

// 堆策略

// /*在堆尾插入新元素，up调整*/
// void insertHeap(int *a, int size, int value)
// {
// 	size ++;
// 	a[size] = value;
// 	int i = size;

// 	while(a[i/2] <= value && i != 1)
// 	{
// 		a[i] = a[i/2];
// 		i /= 2;
// 	}
// 	a[i] = value;
// }

// void deleteHeap(int a[], int size)
// {

// }

// void deleteHeapTop(int a[], int size)
// {
// 	a[1] = a[size];
// 	maxHeapify(a, 1, size - 1);
// }

// /*priority queue*/

// /*main*/
// int main()
// {
// 	//int a[] = {1, 2, 3, 5,7,4,2};
// 	//int size = sizeof(a)/sizeof(a[0]);
// 	int a[100];
// 	a[1] = 1;
// 	a[2] = 2;
// 	a[3] = 3;
// 	a[4] = 5;
// 	a[5] = 7;
// 	a[6] = 4;
// 	a[7] = 2;
// 	int size = 7;

// 	//基本的排序操作，从每一个叶子结点开始建堆，将堆顶元素弹出，调整
// 	heapSort(a, size);
// 	for (int i = 1; i <= size; i++)
// 	{
// 		cout<<a[i]<<" ";
// 	}cout<<endl;


// 	//堆的插入删除操作
// 	//size++;
// 	insertHeap(a, size, 3);
// 	heapSort(a, size + 1);
// 	for (int i = 1; i <= size + 1; i++)
// 	{
// 		cout<<a[i]<<" ";
// 	}cout<<endl;


// 	return 0;
// }



// #include <cstring>
// #include <cstdio>
// #include <iostream>
// const int MAX = 10000 + 5;

// using namespace std;

// void insertMaxHeap(int *a, int size, int value)
// {
// 	a[size] = value;
// 	int i = size;
// 	while(a[i/2] < value && i != 1)
// 	{
// 		a[i] = a[i/2];
// 		i /= 2;
// 	}
// 	a[i] = value;
// }

// void insertMinHeap(int *a, int size, int value)
// {
// 	a[size] = value;
// 	int i = size;
// 	int j = (size - 1) / 2;

// 	while(j <= 0 && i != 0)
// 	{
// 		a[i] = a[i/2];
// 		i /= 2;
// 	}
// 	a[i] = value;
// }

// int mian()
// {
// 	int Tcase;
// 	cin>>Tcase;
// 	while(Tcase --)
// 	{
// 		int k, tcase, n;
// 		int MaxHeap[MAX], MinHeap[MAX], b[MAX];
// 		cin>>tcase>>n;
// 		for (int i = 1; i <= n; i++)
// 		{
// 			cin>>b[i];
// 		}
// 		cout<<tcase<<" "<<(n + 1)/2<<endl;

// 		int cnt = 0;
// 		for (int i = 1; i <= n; ++ i)
// 		{
// 			if (i == 1)
// 			{
// 				insertMaxHeap(MaxHeap, i, b[i]);
// 			}
// 			else
// 			{
// 				if (MaxHeap[1] >= b[i])
// 				{
// 					insertMaxHeap(MaxHeap, i, b[i]);
// 				}
// 				else
// 				{
// 					insertMinHeap(MinHeap, i, b[i]);
// 				}
// 			}`

// 			if (i % 2 == 1)
// 			{
// 				cnt ++;
// 				cout<<MaxHeap[1];
// 				if (cnt / 10 == 1)
// 				{
// 					cnt = 0;
// 					cout<<endl;
// 				}
// 				else
// 					cout<<" ";
// 			}
// 		}
// 	}
// 	return 0;
// }