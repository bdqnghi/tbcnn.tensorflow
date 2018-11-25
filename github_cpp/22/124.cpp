#include <time.h>
#include <iostream>
#include <iomanip>
using namespace  std;













void InitialArr(double *arr,int n)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i<n;i++)
    {
        arr[i] = rand()/double(RAND_MAX+1);   
    }
}














void PrintArr(double *arr,int n)
{
    for (int i = 0;i < n; i++)
    {
        cout<<setw(15)<<arr[i];




    }
    cout << endl;
}

void BucketSort(double * arr,int n)     
{
    double **bucket = new double*[10];
    for (int i = 0;i<10;i++)
    {
        bucket[i] = new double[n];
    }
    int count[10] = {0};
    for (int i = 0 ; i < n ; i++)
    {
        double temp = arr[i];
        int flag = (int)(arr[i]*10); 
        bucket[flag][count[flag]] = temp; 
        int j = count[flag]++;

        
        for(;j > 0 && temp < bucket[flag][j - 1]; --j)
        {
            bucket[flag][j] = bucket[flag][j-1];
        }
        bucket[flag][j] =temp;
    }

    
    int k=0;
    for (int i = 0 ; i < 10 ; i++)
    {
        for (int j = 0 ; j< count[i];j++)
        {
            arr[k] = bucket[i][j];
            k++;
        }
    }
    for (int i = 0 ; i<10 ;i++)
    {
        delete bucket[i];
        bucket[i] =NULL;
    }
    delete []bucket;
    bucket = NULL;
}

int main()
{
    double *arr=new double[10];
    InitialArr(arr, 10);
    PrintArr(arr,10);
    BucketSort(arr, 10);
    PrintArr(arr,10);
    delete [] arr;
    getchar();
    return 0;
}
