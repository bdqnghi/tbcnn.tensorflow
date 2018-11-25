
#include <iostream>
#include <algorithm>
#include <vector>

void quicksort(int a[], int head, int end)
{
    int i = head;
    int j = end;
    int mid = a[(i + j) / 2];
    while (i < j)
    {
        while (a[i] < mid)
        {
            ++i;
        }
        while (a[j] > mid)
        {
            --j;
        }
        if (i <= j)
        {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    if (head < j)
        quicksort(a, head, j);
    if (i < end)
        quicksort(a, i, end);
}

int main()
{
    int n;

    std::cout << "Number of value: ";
    std::cin >> n;
    int *a = new int(n);
    for (int i = 0; i < n; i++)
    {
        
        std::cout << "Value: ";
        std::cin >> a[i];
    }

    quicksort(a, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
    }
}