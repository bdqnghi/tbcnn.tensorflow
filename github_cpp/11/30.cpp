#include<iostream>
using namespace std;

int parent(int i)
{
    return (i-1)/2;
}

int left(int i)
{
    return (2*i)+1;
}

int right(int i)
{
    return (2*i)+2;
}

void heapify(int *A, int n, int i)
{
    int ind_max=i;
    int l=left(i), r=right(i);
    if(l<n && A[l]>A[i])
        ind_max=l;
    if(r<n && A[r]>A[ind_max])
        ind_max=r;
    if(ind_max!=i)
    {
        swap(A[i], A[ind_max]);
        heapify(A, n, ind_max);
    }
}

void buildHeap(int *A, int n)
{
    for(int i=parent(n-1); i>=0; i--)
        heapify(A, n, i);
}

void heapsort(int *A, int n)
{
    buildHeap(A, n);
    for(int i=n-1; i>0; i--)
    {
        swap(A[0], A[i]);
        heapify(A, i, 0);
    }
}
int main()
{
    int n;
    cout<<"enter the size on an array"<<endl;
    cin>>n;
    int *A=new int[n];

    cout<<endl<<"enter the elements of an array"<<endl;
    for(int i=0; i<n; i++)
        cin>>A[i];

    heapsort(A, n);

    cout<<endl<<"this is the result of using heapsort:"<<endl<<endl;
    for(int i=0; i<n; i++)
        cout<<A[i]<<" ";

    cout<<endl;

    return 0;
}
