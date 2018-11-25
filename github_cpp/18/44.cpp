#include <stdio.h>
#include <algorithm>

int g_Price[11] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };


int RodCutting_Recursion(int n)
{
    if (n < 1)
        return 0;

    int result = -1;
    for (int i = 1; i <= n; ++i)
    {
        result = std::max(result, g_Price[i] + RodCutting_Recursion(n - i));
    }
    return result;
}

int RodCutting_TopDown(int n, int* arr)
{
    if (arr[n] != -1)
        return arr[n];
    if (n < 1)
        return 0;

    int result = -1;
    for (int i = 1; i <= n; ++i)
    {
        result = std::max(result, g_Price[i] + RodCutting_TopDown(n - i, arr));
    }
    arr[n] = result;
    return result;
}

int RodCutting_BottomUp(int n)
{
    if (n < 1)
        return 0;

    int* arr = new int[n + 1];
    arr[0] = 0;
    
    for (int len = 1; len <= n; ++len)
    {
        int subMaxValue = -1;
        for (int subLen = 1; subLen <= len; ++subLen)
        {
            subMaxValue = std::max(subMaxValue, g_Price[subLen] + arr[len - subLen]);
        }
        arr[len] = subMaxValue;
    }
    int ret = arr[n];
    delete[] arr;
    return ret;
}

int RodCutting_BottomUp_Extend(int n)
{
    if (n < 1)
        return 0;

    int* arr = new int[n + 1];
    int* cutArr = new int[n + 1];
    arr[0] = 0;
    cutArr[0] = 0;

    for (int len = 1; len <= n; ++len)
    {
        int subMaxValue = -1;
        for (int subLen = 1; subLen <= len; ++subLen)
        {
            int value = g_Price[subLen] + arr[len - subLen];
            if (value > subMaxValue)
            {
                subMaxValue = value;
                cutArr[len] = subLen;
            }
        }
        arr[len] = subMaxValue;
    }
    int ret = arr[n];

    puts("");
    while (n > 0)
    {
        printf("[%d]", cutArr[n]);
        n -= cutArr[n];
    }
    puts("");

    delete[] arr;
    delete[] cutArr;
    return ret;
}


int main()
{
    int n = 10;
    int* arr = new int[n + 1];
    for (int i = 0; i < n + 1; ++i)
        arr[i] = -1;

    printf("1. %d\n", RodCutting_Recursion(n));
    printf("2. %d\n", RodCutting_TopDown(n, arr));
    printf("3. %d\n", RodCutting_BottomUp(n));
    printf("4. %d\n", RodCutting_BottomUp_Extend(n));

    delete[] arr;
    getchar();
}