/* 
 *遵循知识共享（CC By2.5）协议详见
 *http://creativecommons.org/licenses/by/2.5/cn/
 */
/**
 * @file shell-sort.cpp
 * @Synopsis shell sort
 * @author 罗磊, luoleicn@gmail.com
 * @version 
 * @date 2011-04-18
 */

#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  shell sort 
 *      shell排序是对插入排序的一个改装，它每次排序把序列的元素按照某个增量
 * 分成几个子序列，对这几个子序列进行插入排序，然后不断的缩小增量扩大每个子
 * 序列的元素数量，直到增量为一的时候子序列就和原先的待排列序列一样了，此时
 * 只需要做少量的比较和移动就可以完成对序列的排序了
 *
 * @tparam T 泛型变量T要求其实现中重载操作符小于号
 * @Param T[] 待排序数组
 * @Param size 数组大小
 */
/* ----------------------------------------------------------------------------*/
template<class T> void shell_sort(T[], int);

int main(int args, char** argv)
{
    int ia[] = {1, 9, 5, 4, 8, 0, 2, 3, 7, 9};
    int size = sizeof(ia)/sizeof(int);

    shell_sort(ia, size);
    copy(ia, ia+size, ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}


template<class T>
void shell_sort(T s[], int size)
{
    for (int increment=size/2; increment>0; increment/=2)
    {
        for (int i=0; i<size; i++)
        {
            int index = i;
            for (int j=i-increment; j>=0; j-=increment)
            {
                if (s[index] < s[j])
                {
                    swap(s[index], s[j]);
                    index = j;
                }
                else
                {
                    break;
                }
            }
        }
    }
}
