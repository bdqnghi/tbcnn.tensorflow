/*
	数组元素不大于1000,使用计数排序进行各位排序

	Author : jefby
	Email  : jef199006@gmail.com

*/
//============================================================================ 
// Name        : base sort 
// Author      : xiaoshuai 
// Version     : 
// Copyright   : Your copyright notice 
// Description : Hello World in C++, Ansi-style 
//============================================================================ 
#include <iostream>
#include<algorithm> 
using namespace std; 
struct Node{ 
    int key; 
    struct Node *next; 
    Node(int _key){ 
        key=_key;next=NULL; 
    } 
}; 
Node *buck[10];//创建一个链表数组 
Node *tail[10];//链表的尾结点  这是典型的以空间换时间的做法 
void base_sort_LSD(int *a,int n){ 
    int k,i,Max,kth,high,low; 
    Node *p; 
 
    for(Max=a[0],i=1;i<n;i++)
    	Max=max(Max,a[i]); 
    memset(buck,0,sizeof(buck)); 
 
    for(low=1,k=0;high=low*10,low<Max;low*=10,k++){//只要没有排好序，就一直排序 
        for(i=0;i<n;i++){//往桶里扔 
            kth=(a[i]%high)/low;//取出序列中的数，根据位数放置到对应的桶中 
            p=new Node(a[i]);//创建新结点 
            //把数放到对应的桶中 这里一定要接到末尾，而不能从头结点插入 
            buck[kth]!=NULL ?tail[kth]->next=p,tail[kth]=p:buck[kth]=p,tail[kth]=p; 
        } 
        for(kth=0,i=0;kth<n;i++){//把桶中的数据放回数组中 
            while(buck[i]!=NULL){ 
                a[kth++]=buck[i]->key; 
                p=buck[i],buck[i]=buck[i]->next,delete p;//收回动态开辟的空间 
            } 
        } 
    } 
} 
int main(){ 
    int n=10; 
    int data[]={1000,50,80000,81000,3,26,467,6987,10953,2354}; 
    base_sort_LSD(data,n); 
    for(int i=0;i<n;i++) 
        printf("%d ",data[i]); 
} 