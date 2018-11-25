
#include <iostream>
#include <algorithm>

void bubbleSort(int A[],int lo,int hi)
{
    if(lo == hi)
        return;
    int last = lo; 

    for(int i = 0;i < hi -1;i++) 
    {
        if(A[i+1] < A[i])
        {
            swap(A[i+1],A[i]);
            last = i+1; 
        }

    }


    bubbleSort(A,lo,last);
}



void bubbleSort1(int A[],int lo,int hi)
{
    int last = hi;
    while(lo < last)        
    {
        int n = last;
        last = lo;
        for(int i = 0;i < n -1;i++)
        {
            if(A[i] > A[i+1])
            {
                swap(A[i],A[i+1]);
                last = i+1;
            }
        }
    }
}

int main()
{
    int data[] = {0,8,4,3,5,9,4,19};
    vector<int> vi(begin(data),end(data));
    cout << "数组未排序前: \n";
    for_each(vi.begin(),vi.end(),[](const int& val){cout << val << " ";});
    cout << endl << endl;


    bubbleSort1(data,0,vi.size());
    cout << "数组排序后: " << endl;
    for(int i = 0;i < (int)vi.size();i++)
        cout << data[i] << " ";
    cout << endl;

    bubbleSort(data,0,vi.size());

    for(int i = 0;i < (int)vi.size();i++)
        cout << data[i] << " ";

    cout << endl;

}
