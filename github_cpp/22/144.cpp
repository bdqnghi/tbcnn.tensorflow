//Group ID 14114069-14114022    Tejal Singh & Deepanshu Singhal
//Date: 7 Feb 2016
//bucket_sort.cpp         bucket_sort algorithm
#include <iostream>
#include "bucket_sort.h"
using namespace std;
void bucket_array(int* a, int s)
{
	int bucket[1000];
	for(int i=0;i<1000;i++)
	{
		bucket[i]=0;
	}
	for(int i=0;i<s;i++)
	{
		bucket[a[i]]++;
	}
	int index=0;
	for(int i=0;i<1000;i++)
	{
		while(bucket[i]!=0)
		{	
			a[index]=i;
			index++;
			bucket[i]--;
		}
	}
}
void bucket_link(node* root,int s)
{
	int bucket[1000];
	for(int i=0;i<1000;i++)
	{
		bucket[i]=0;
	}
	node* p=root;
	while(p)
	{
		bucket[p->x]++;
		p=p->rptr;
	}
	p=root;
	for(int i=0;i<1000;i++)
	{
		while(bucket[i]!=0)
		{
			p->x=i;
			p=p->rptr;
			bucket[i]--;
		}
	}
}