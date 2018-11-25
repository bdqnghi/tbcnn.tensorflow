#include <string>
#include "insertion_sort.h"

using namespace std;

InsertionSort::~InsertionSort()
{
    printf("~InsertionSort %s %p\n", Name().c_str(), this);
}

string InsertionSort::Name()
{
    return "InsertionSort";
}

void InsertionSort::Sort(int a[], int n)
{
    for (int i = 1; i < n; i++) {

        
        int b = a[i];

        
        int j = i - 1;

        
        while (b < a[j] && j >= 0) {
            a[j + 1] = a[j];
            j--;
        }

        
        a[j + 1] = b;
    }
}
