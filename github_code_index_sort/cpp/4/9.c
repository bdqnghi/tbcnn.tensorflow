#include <stdio.h>
#include <stdlib.h>
int heap[100];
int sort[100];
int heapsize=0;
void max_heapify(int heap[],int i) // heapify down
{
	int largest,temp;
	int left = 2*i;
	int right = 2*i+1;
	if(left <= heapsize && heap[left] > heap[i])
		largest = left;
	else
		largest = i;
	if(right <= heapsize && heap[right] > heap[largest])
		largest = right;
	if(largest != i)
	{
		temp = heap[i];
		heap[i] = heap[largest];
		heap[largest] = temp;

		max_heapify(heap,largest);
	}
}
void heapify_up(int heap[],int heapsize)
{
	int parent = heapsize/2;
	int child = heapsize;
	int temp;
	while(child > 1 && heap[parent] < heap[child])
	{
		//heap[child] = heap[parent];
		temp = heap[child];
		heap[child] = heap[parent];
		heap[parent] = temp;
		child = parent;
		parent = child/2;
	}
}
void insert(int heap[],int x)
{
	heapsize++;
	heap[heapsize] = x;
	heapify_up(heap,heapsize);
}
int heapsort(int sort[],int heapsize)
{
	int temp,i;
	printf("lol\n");
	int n = heapsize;
	for(int i=n;i>0;i--)
	{
		printf("%d %d %d %d\n",sort[i],sort[1],heapsize,insert);
		temp = sort[i];
		sort[i] = sort[1];
		sort[1] = temp;

		heapsize--;
		max_heapify(sort,1);
	}
	return n;
}
int main()
{
	heap[0] = 9999;
	int x,n,i;
	while(1)
	{
		scanf("%d",&n);
		if(n == 1)
		{
			scanf("%d",&x);
			insert(heap,x);
		}
		if(n == 2)
		{
			for(i=1;i<=heapsize;i++)
				printf("%d ",heap[i]);
			printf("\n");
		}
		if(n == 3)
		{
			sort[0] = 9999;
			for(i=1;i<=heapsize;i++)
				sort[i] = heap[i];
			int n = heapsort(sort,heapsize);
			for(int i=0;i<=n;i++)
				printf("%d ",sort[i]);
		}
	}
}