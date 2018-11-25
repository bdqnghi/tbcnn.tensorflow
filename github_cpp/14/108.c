







#include <iostream>
using namespace std;

void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void printArray(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
int getMax(int arr[],int size)
{
    int max = arr[0];
    for(int i=0;i<size;i++)
    {
        if(max<arr[i])
            max = arr[i];
    }
    return max;
}

void countSort(int arr[], int n, int exp)
{
    int output[n]; 
    int i, count[10] = {0};
    
    
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;
    
    
    
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    
    
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
    
    
    
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
void newCountSort(int arr[],int n,int exp){
    
    int range[10] = {0};
    int newArr[n];
    
    for(int i=0;i<n;i++)
    {
        range[((arr[i]/exp)%10)]++;
    }
    for(int i=1;i<10;i++)
    {
        range[i] += range[i-1];
    }
    
    for(int i=n-1;i>=0;i--)
    {
        newArr[range[((arr[i]/exp)%10)]-1] = arr[i];
        range[((arr[i]/exp)%10)]--;
    }
    for(int i=0;i<n;i++)
    {
        arr[i] = newArr[i];
    }
}


void radixsort(int arr[], int n)
{
    
    int m = getMax(arr, n);
    
    
    
    
    for (int exp = 1; m/exp > 0; exp *= 10)
        newCountSort(arr, n, exp);
}





int main(int argc, const char * argv[]) {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int size = (sizeof(arr)/sizeof(arr[0]));
    radixsort(arr, size);
    printArray(arr, size);
    
    return 0;
}
