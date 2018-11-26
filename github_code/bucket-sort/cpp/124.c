#include <time.h>
#include <iostream>
#include <iomanip>
using namespace  std;

// BUCKET-SORT(A)
// let B[0..n - 1] be a new array
// n = A.length
// for i = 0 to n - 1
//     make B[i] an empty list
// for i = 1 to n
//     insert A[i] into list B[|_nA[i]_|]
// for i = 0 to n - 1
//     sort list B[i] with insertion sort
// concatenate the lists B[0], B[1],....B[n - 1] together in order

/*initial arr*/
void InitialArr(double *arr,int n)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i<n;i++)
    {
        arr[i] = rand()/double(RAND_MAX+1);   //(0.1)
    }
}

/* print arr*/
// void PrintArr(double *arr,int n)
// {
//     for (int i = 0;i < n; i++)
//     {
//         cout<<setw(15)<<arr[i];
//         if ((i+1)%5 == 0 || i ==  n-1)
//         {
//             cout<<endl;
//         }
//     }
// }

void PrintArr(double *arr,int n)
{
    for (int i = 0;i < n; i++)
    {
        cout<<setw(15)<<arr[i];
//         if ((i+1)%5 == 0 || i ==  n-1)
//         {
//             cout<<endl;
//         }
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
        int flag = (int)(arr[i]*10); //flag��ʶС���ĵ�һλ 
        bucket[flag][count[flag]] = temp; //�ö�ά�����ÿ�����������С����һλ��ͬ������
        int j = count[flag]++;

        /* ���ò��������ÿһ�н������� */
        for(;j > 0 && temp < bucket[flag][j - 1]; --j)
        {
            bucket[flag][j] = bucket[flag][j-1];
        }
        bucket[flag][j] =temp;
    }

    /* ���������������� */
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
