/**
 * Created by Neil on 2018/7/17.
 * 
 */

#include<iostream>
#include<vector>

using namespace std;

void exch(vector<int> &v, int i, int j)
{
    if (i == j)
        return;

    v[i] ^= v[j] ^= v[i] ^= v[j];
}

int partition(vector<int> &v, int lo, int hi)
{
    // 左右扫描指针
    int i = lo, j = hi + 1;
    // 切分元素，即主元
    int pivot = v[lo];

    while (true) {
        while (v[++i] < pivot) if (i == hi) break;
        while (v[--j] > pivot) if (j == lo) break;

        if (i >= j) break;
        exch(v, i, j);
    }

    // 将 pivot = v[j] 放入正确位置
    exch(v, lo, j);

    // v[lo...j-1] <= v[j] <= v[j+1...hi]
    return j;
}

void sort_helper(vector<int> &v, int lo, int hi)
{
    if (hi <= lo) return;

    int j = partition(v, lo, hi);

    sort_helper(v, lo, j - 1);
    sort_helper(v, j + 1, hi);
}

void quick_sort(vector<int> &v)
{
    sort_helper(v, 0, v.size() - 1);
}

int main()
{
    vector<int> v{2, 3, 5, 1, 4, 6, 7};

    quick_sort(v);
    for (auto i : v)
        cout << i << " ";
}