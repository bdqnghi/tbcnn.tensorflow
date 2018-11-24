#include<iostream>
using namespace std;
int A[] = {1, 4, 5, 7, 8, 9, 10, 12, 15, 22, 23, 27, 32, 35};

int binarySearch(int x)
{
    int low = 0, mid, high = sizeof(A)/sizeof(int) -1;
    int j = 0;
    while(low <= high && j == 0){
        mid = (low + high) / 2;
        if (x == A[mid])
            j = mid;
        else
            if(x < A[mid])
                high = mid - 1;
            else
                low = mid + 1;
    }
    return j;
}

int main()
{
    int x;
    cin>>x;
    if (binarySearch(x))
        cout<<"该数找到"<<endl;
    else
        cout<<"该数不存在！"<<endl;
}
