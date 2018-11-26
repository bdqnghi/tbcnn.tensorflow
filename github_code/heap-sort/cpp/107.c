// heaps... using array..
#include<iostream>
#define MAXSIZE 10  // way to define constant.. ( maxsize=10)
using namespace std;

int heap[MAXSIZE]={0}; // initilize heap with all zeros..
int N=0;  // for numbber of elements ..initially zero..

void insert(int item)
{
	int par;	
	N=N+1;
	int ptr=N;
	
	while(ptr>1)
	{
		par=ptr/2;
		if(item>heap[par])
		{
			heap[ptr]=item;
		//cout<<heap[ptr];
			return ;			
		}
			
		heap[ptr]=heap[par];
			//cout<<heap[ptr];
		ptr=par;
		
	}
heap[1]=item;
}

int deleteheap()
{
	int item =heap[1];
	int last=heap[N];
	N--;
	int ptr=1;
	int left=2;
	int right=3;
	
	while(right<=N)
	{
		if(last<heap[left] && last<heap[right])
		{
			heap[ptr]=last;
			return item;	
		}		
		if(heap[left]<heap[right])
		{
			heap[ptr]=heap[left];
			ptr=left;
		}
		else{
			heap[ptr]=heap[right];
			ptr=right;
		}
		left=2*ptr;
		right=left+1;
	}
		
	if(left==N && heap[left]<last)
	{
		heap[ptr]=heap[left];
		ptr=left;
	}
	heap[ptr]=last;
	return item;

}

void heapsort()
{
	for(int i=N;i>=1;i--)
	{
		heap[i]=deleteheap();
	}	
}


int main()
{
	insert(54);
	insert(28);
	insert(34);
	insert(17);
	insert(10);
	insert(24);
	insert(12);
	insert(70);
		
	for (int i=1;i<=N;i++)
	{
		cout<<i<<" : "<<heap[i]<<" "<<endl;
	}
	cout<<" now deletion start: "<<endl;
	cout<<deleteheap()<<endl;
	
	
	for (int i=1;i<=N;i++)
	{
		cout<<i<<" : "<<heap[i]<<" "<<endl;
	}
	
	cout<<" after heap-sort :" <<endl; 
	//  after heap-sort N becomes zero..
	int temp=N;
	heapsort();
	
	for (int i=1;i<=temp;i++)
	{
		cout<<i<<" : "<<heap[i]<<" "<<endl;
	}
	
}

