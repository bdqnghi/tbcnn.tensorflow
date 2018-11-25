#include <iostream>
#include <vector>
#include "../util/show.cpp"
using namespace std;

class QuickSort
{
    bool less (vector<int>& v, int i, int j)
    {
        return v[i] < v[j];
    }
    void exch (vector<int>& v, int i, int j)
    {
        int t = v[i];
        v[i] = v[j];
        v[j] = t;
    }
    int partition (vector<int>& v, int lo, int hi)
    {
        int i = lo;
        int j = hi+1;
        while(true)
        {
            while(less(v, ++i, lo))
                if(i == hi) break;
            
            while(less(v, lo, --j))
                if(j==lo) break;

            if (i >= j) break;

            exch (v, i, j);
        }
        exch (v, lo, j);
        return j;
    }

    void sort(vector<int>& a, int lo, int hi)
    {
        if(hi <= lo) return;
        int p = partition(a, lo, hi);
        sort(a, lo, p-1);
        sort(a, p+1, hi);
    }

public:
    QuickSort(vector<int>& v)
    {
        sort(v, 0, v.size()-1);
        showVector(v);
    }
};

int main ()
{
    vector<int> v({4, 5, 2, 0, 1});
    QuickSort q(v);
    
}