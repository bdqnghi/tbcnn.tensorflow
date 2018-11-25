#include <iostream>

using namespace std;

template <class T>
void heapify(T array[],int size)
{
    for(int parent=size/2;parent>=1;parent--)
    sink(array,parent,size);
}

template <class T>
void sink(T array[],int parent,int size)
{

    while(parent*2<=size)
    {
        int child=parent*2;
        if(child+1<=size)
        {
            if(array[child]<array[child+1])
            child++;
        }
        if(array[parent]<array[child])
        swap(array[parent],array[child]);
        parent=child;
    }
}

template <class T>
void heapsort(T array[], int size)
{
    int index=size;
    while(index>=1)
    {
        swap(array[1],array[index]);
        sink(array,1,index-1);
        index--;
    }
}

int main()
{
    int size;
    cin>>size;
    int array[size+1];
    for(int i=1;i<=size;i++)
    cin>>array[i];
    heapify<int>(array,size);
    heapsort<int>(array,size);
    cout<<"The sorted array is :"<<endl;
    for(int i=1;i<=size;i++)
    cout<<array[i]<<" ";
    cout<<endl;
    return 0;

}
