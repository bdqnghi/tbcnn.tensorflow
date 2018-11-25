


#include <iostream>
#include <iterator>

using namespace std;




template<class T> void quick_sort(T[], int, int);

int main(int args, char** argv)
{
    int ia[] = {1, 9, 5, 4, 8, 0, 2, 3, 7, 9};
    int size = sizeof(ia)/sizeof(int);

    quick_sort(ia, 0, size-1);
    copy(ia, ia+size, ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}

template<class T> 
void quick_sort(T s[], int l, int r)
{
    int i=l, j=r;
    int key = s[(l+r)/2];

    while (i < j)
    {
        for (; s[i] < key; i++);
        for (; s[j] > key; j--);
        
        if (i < j)
        {
            swap(s[i], s[j]);
            i++;
            j--;
        }
    }
    if (i<r)
        quick_sort(s, l, i);
    if (j>l)
        quick_sort(s, j, r);
}

