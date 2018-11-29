#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;
//Merge-Sort 合并排序
    template <typename T>
void Merge_Sort(T &A, unsigned p, unsigned r)
{
    cout << "merge sort " << p << " " << r << endl;
    //分治
    if (p < r) {
        unsigned q = (p+r)/2;
        cout << "begin left" << endl;
        Merge_Sort(A, p, q);
        cout << "begin right " << endl;
        Merge_Sort(A, q+1, r);
        Merge(A, p, q, r);
    }
}
//Merge 合并，子程序
    template <typename T>
void Merge(T &A, unsigned p, unsigned q, unsigned r)
{
    cout << "merge " << p << " " << q << " " << r << endl;
    typename T::iterator it_ini = A.begin();
    //用迭代器赋值与下标有些不同
    T A_left(it_ini+p, it_ini+q+1), A_right(it_ini+q+1, it_ini+r+1);
    T A_sort_ok;
    typename T::iterator it1 = A_left.begin(), it2 = A_right.begin();
    while (it1 != A_left.end() && it2 != A_right.end()) {
        cout << "compare " << *it1 << " " << *it2 << endl;
        if (*it1 < *it2) A_sort_ok.push_back(*it1++);
        else A_sort_ok.push_back(*it2++);
    }
    while (it1 != A_left.end()) A_sort_ok.push_back(*it1++);
    while (it2 != A_right.end()) A_sort_ok.push_back(*it2++);
    //把排列好的部分替换给A
    it_ini = A.begin()+p;
    it1 = A_sort_ok.begin();
    while (it_ini != A.begin()+r+1) *it_ini++ = *it1++;
}
int main()
{
    //产生一个随机长度，随机数值的无序数组
    srand(time(NULL));
    vector<int> need_sort;
    unsigned sample_len = rand()%30;
    for (unsigned ix = 0; ix != sample_len; ++ix) need_sort.push_back(rand()%100);
    //打印排序前：
    cout << "before Merge-Sort: " << endl;
    for (unsigned ix = 0; ix != need_sort.size(); ++ix) cout << need_sort[ix] << ' ';
    cout << endl;
    //调用Merge-Sort
    Merge_Sort(need_sort, 0, need_sort.size()-1);
    //打印合并排序后结果
    cout << "after Merge-Sort: " << endl;
    for (unsigned ix = 0; ix != need_sort.size(); ++ix) cout << need_sort[ix] << ' ';
    cout << endl;
    return 0;
}
