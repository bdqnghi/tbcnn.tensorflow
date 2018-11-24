/** \link
 * \comments 建堆时间复杂度O(n)，之后每次点整时间复杂度O(logn)。堆排序通常比快速排序稍微慢，但是最坏情况的运行时间总是O(n log n)
 */
 
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template<class T>
void heapAdjust(vector<T> &a, int begin, int end, bool (*cmp)(const T &, const T &))
{
    stack<int> myStack;
    myStack.push(begin);
    while (!myStack.empty()){
        begin = myStack.top();
        myStack.pop();
        if (begin <= (end - 2) / 2){
            int l = begin * 2 + 1, r = l + 1;
            int temp = begin;
            if (l < end && cmp(a[l], a[temp])){
                temp = l;
            }
            if (r < end && cmp(a[r], a[temp])){
                temp = r;
            }
            if(begin != temp){
                swap(a[begin], a[temp]);
                myStack.push(temp);
            }
        }
    }
/*
    //递归
    if (begin <= (end - 2) / 2){
        int l = begin * 2 + 1, r = l + 1;
        int temp = begin;
        if (l < end && cmp(a[l], a[temp])){
            temp = l;
        }
        if (r < end && cmp(a[r], a[temp])){
            temp = r;
        }
        if(begin != temp){
            swap(a[begin], a[temp]);
            heapAdjust(a, temp, end, cmp);
        }
    }
*/
}

template<class T>
void heapBuild(vector<T> &a, bool (*cmp)(const T &, const T &))
{
    for (int i = (a.size() - 2) / 2; i>=0; i--){
        heapAdjust(a, i, a.size(), cmp);
    }
}

template<class T>
void heapSort(vector<T> &a, bool (*cmp)(const T &, const T &))
{
    if (a.size() < 2)
        return ;
    heapBuild(a, cmp);
    for (int i = a.size() - 1; i >= 0; i--){
        swap(a[0], a[i]);
        heapAdjust(a, 0, i, cmp);
    }
}

bool cmp(const int &a, const int &b)
{
    return a > b;
}


int main()
{
    vector<int> a;
    int n, c;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> c;
        a.push_back(c);
    }
    heapSort(a, cmp);
    for (int i = 0; i < n; i++){
        cout << a[i] << ' ';
    };
    return 0;
}
