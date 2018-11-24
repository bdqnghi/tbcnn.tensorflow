/* 
 *遵循知识共享（CC By2.5）协议详见
 *http://creativecommons.org/licenses/by/2.5/cn/
 */
/**
 * @file bubble-sort.cpp
 * @Synopsis  冒泡排序
 * @author 罗磊, luoleicn@gmail.com
 * @version 
 * @date 2011-04-18
 */

#include <iostream>
#include <iterator>

using namespace std;

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  bubble_sort 冒泡排序
 *
 * @tparam T 泛型参数
 * @Param T[] 待排序数组
 * @Param size 数组大小
 */
/* ----------------------------------------------------------------------------*/
template<class T> void bubble_sort(T[], int);
int main(int args, char** argv)
{
    int ia[] = {1, 9, 5, 4, 8, 0, 2, 3, 7, 9};
    int size = sizeof(ia)/sizeof(int);

    bubble_sort(ia, size);
    copy(ia, ia+size, ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}

template<class T> 
void bubble_sort(T s[], int size)
{
    for (int i=0; i<size; i++)
    {
        bool change = false;
        int index = 0;
        for (int j=index+1; j<size-i; j++)
        {
            if (s[j] < s[index])
            {
                swap(s[index], s[j]);
                change = true;
            }
            index = j;
        }
        if (!change)
            break;
    }
}
