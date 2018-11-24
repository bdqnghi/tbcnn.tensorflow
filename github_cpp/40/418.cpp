/* 
 *遵循知识共享（CC By2.5）协议详见
 *http://creativecommons.org/licenses/by/2.5/cn/
 */
/**
 * @file quick-sort.cpp
 * @Synopsis  快排
 * @author 罗磊, luoleicn@gmail.com
 * @version 
 * @date 2011-04-18
 */

#include <iostream>
#include <iterator>

using namespace std;

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  quick_sort 
 *
 * @tparam T
 * @Param T[]
 * @Param int left 
 * @Param int right
 */
/* ----------------------------------------------------------------------------*/
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

