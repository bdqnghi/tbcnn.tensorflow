#include <iostream>
using namespace std;
int a[] = {1, 255, 8, 6, 25, 47, 14, 35, 58, 75, 96, 158, 657};
const int len = sizeof(a) / sizeof(int);
int b[10][len + 1] = {0}; //将b全部置0
void bucketSort(int a[]);//桶排序函数
void distributeElments(int a[], int b[10][len + 1], int digits);
void collectElments(int a[], int b[10][len + 1]);
int numOfDigits(int a[]);
void zeroBucket(int b[10][len + 1]); //将b数组中的全部元素置0

int main()
{
    cout << "原始数组：";
    for (int i = 0; i < len; i++)
        cout << a[i] << ",";
    cout << endl;
    bucketSort(a);
    cout << "排序后数组：";
    for (int i = 0; i < len; i++)
        cout << a[i] << ",";
    cout << endl;
    return 0;
}
void bucketSort(int a[])
{
    int digits = numOfDigits(a);
    for (int i = 1; i <= digits; i++)
    {
        distributeElments(a, b, i);
        collectElments(a, b);
        if (i != digits)
            zeroBucket(b);
    }
}
int numOfDigits(int a[])
{
    int largest = 0;
    for (int i = 0; i < len; i++) //获取最大值
        if (a[i] > largest)
            largest = a[i];
    int digits = 0; //digits为最大值的位数
    while (largest)
    {
        digits++;
        largest /= 10;
    }
    return digits;
}
void distributeElments(int a[], int b[10][len + 1], int digits)
{
    int divisor = 10; //除数
    for (int i = 1; i < digits; i++)
        divisor *= 10;
    for (int j = 0; j < len; j++)
    {
        int numOfDigist = (a[j] % divisor - a[j] % (divisor / 10)) / (divisor / 10);
        //numOfDigits为相应的(divisor/10)位的值,如当divisor=10时,求的是个位数
        int num = ++b[numOfDigist][0]; //用b中第一列的元素来储存每行中元素的个数
        b[numOfDigist][num] = a[j];
    }
}
void collectElments(int a[], int b[10][len + 1])
{
    int k = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 1; j <= b[i][0]; j++)
            a[k++] = b[i][j];
}
void zeroBucket(int b[][len + 1])
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < len + 1; j++)
            b[i][j] = 0;
}
