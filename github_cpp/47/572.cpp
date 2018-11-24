#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
int Binary_search(int array[],int left,int right,int key)
{
    int mid;
    while(left<=right)
    {
        mid=(left+right)/2;
        if(array[mid]==key)
            return mid;
        else if(array[mid]>key)
            right=mid-1;
        else
            left=mid+1;
    }
    return -1;
}
int main()
{
    int N,array[100],key;
    cout<<"������N��"<<endl;
    cin>>N;
    cout<<"������N��������"<<endl;
    for(int i=0; i<N; i++)
        cin>>array[i];
    sort(array,array+N);
    cout<<"��С���������"<<endl;
    for(int i=0; i<N-1; i++)
        cout<<array[i]<<" ";
    cout<<array[N-1]<<endl;
    cout<<"������Ҫ���ҵ�����";
    cin>>key;
    int m=Binary_search(array,0,N-1,key);
    if(m!=-1)
        cout<<key<<" �ڵ�"<<m+1<<" ��λ��"<<endl;
    else
        cout<<"û���ҵ�"<<endl;
}

