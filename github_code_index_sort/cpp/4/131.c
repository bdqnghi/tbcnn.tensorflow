// Heap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

using namespace std;

struct Heap
{
    Heap(vector<int>& v)
        : data(v)
    {

    }

  /*  void Down()
    {
        int size = data.size();
        for (int i = 0; i < size / 2; i++)
        {
            int r = i * 2 + 2;
            int l = i * 2 + 1;
            if (r < size && data[r] < data[l])
                l = r;
            if (data[i] < data[l])
            {
                swap(data[i], data[l]);
            }
        }
    }*/

    void Down(int i, int n)
    {
        while (i <= n/2-1)
        {
            int r = i * 2 + 2;
            int l = i * 2 + 1;
            if (r < n && data[r] < data[l])
                l = r;
            if (data[i] > data[l])
            {
                swap(data[i], data[l]);
                i = l;
            }
            else
                break;
        }
    }
    void Up()
    {
        int size = data.size();
        for (int i = 1 ; i < size; i++)
        {
            Up(i);
        }
    }

    void Up(int i)
    {
        while (i >= 1)
        {
            int p = (i-1) / 2;
            if (data[i] < data[p])
            {
                swap(data[i], data[p]);
                //i = p;
            }
            i = p;
        }
    }

    void Sort()
    {
        Up();
        int size = data.size()-1;
        while (size>=1)
        {
            swap(data[0], data[size]);
            
            Down(0, size);
            size--;
        }
    }

    void Sort2()
    {
        int size = (data.size() - 1)/2;
        while (size >= 0)
        {
            Down(size, data.size());
            size--;
        }
    }
    vector<int>& data;
};
#include <time.h>
#include <assert.h>
void test() 
{
    
    srand(time(nullptr));

    for (int i = 0; i < 10000; i++)
    {
        int size = rand() % 100 + 2;

        vector<int> v(size);
        for (int j = 0; j < size; j++)
            v[j] = rand()%100000;
        Heap h(v);
       /* h.Up();

        for (int j = 1; j < size; j++)
        {
            assert(v[j] >= v[(j-1)/2]);
        }*/

        h.Sort();

        for (int j = 1; j < size; j++)
        {
            assert(v[j - 1] >= v[j]);
        }
       
    }
}

#include <algorithm>
#include <functional>
#include <queue>
int main()
{
   // test();

    vector<int> v = { 1,3,4,6,9,2,5 };

    std::priority_queue<int, vector<int>, greater<int>> pq(v.begin(), v.end());

    while (!pq.empty())
    {
        printf("%d\t", pq.top());
        pq.pop();
    }

    auto v2 = v;
    Heap h(v);
    h.Up();
    h.Sort();
    std::make_heap(v.begin(), v.end());
    std::sort_heap(v.begin(), v.end());
    

    std::make_heap(v.begin(), v.end(), std::less<int>());
    std::sort_heap(v.begin(), v.end(), std::less<int>());

    std::make_heap(v.begin(), v.end(), std::greater<int>());
    std::sort_heap(v.begin(), v.end(), std::greater<int>());

  
    return 0;
}

