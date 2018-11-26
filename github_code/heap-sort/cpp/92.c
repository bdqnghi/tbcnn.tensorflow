/* FILE: heapSort.cpp
 * CIS 279 Assignment 5 Heap Sort
 * Date:  12/5/16
 * Development Env: Code::Blocks
 * Solution File:   heapSort.cpp
 * DESCRIPTION:  An ascending order heap sort
 *               algorithm.
 */
#include <iostream>

using namespace std;

typedef string ItemType;

void heapSort(ItemType data[], int n);
void heapify(ItemType data[], int n, int i);

int main()
{
   string a[6] = {"D", "B", "A", "C", "F", "E"};
   heapSort(a, 6);
   for (int i = 0; i < 6; i++)
      cout << a[i] << " ";
   cout << " Sorted array" << endl;
   string b[6] = {"25", "30", "20", "80", "40", "60"};
   heapSort(b, 6);
   for (int i = 0; i < 6; i++)
      cout << b[i] << " ";
   cout << " Sorted array" << endl;
}






void heapSort(ItemType data[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(data, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(data[0], data[i]);
        heapify(data, i, 0);
    }
}






void heapify(ItemType data[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && data[l] > data[largest])
        largest = l;

    if (r < n && data[r] > data[largest])
        largest = r;

    if (largest != i)
    {
        swap(data[i], data[largest]);
        heapify(data, n, largest);
    }
}


/*
A B C D E F  Sorted array
20 25 30 40 60 80  Sorted array


*/
