#ifndef SHELLSORT_H
#define SHELLSORT_H
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

template <typename T>
class ShellSort
{
private:
    unsigned len;
    vector<T> list;
public:
    
    ShellSort(vector<T> _list, unsigned _len)
    {
        for (unsigned i = 0; i < _len; ++i) list.push_back(_list[i]);
        this->len = _len;
    }
    
    void shellSort()
    {
        int insertNum;
        unsigned gap = len/2; 
        while(gap) 
        {
            for (unsigned i = gap; i < len; ++i) 
            {
                insertNum = list[i];
                unsigned j = i;
                while (j >= gap && insertNum < list[j-gap])
                {
                    list[j] = list[j - gap];
                    j -= gap;
                }
                list[j] = insertNum;
            }
            gap /= 2;
        }
    }

    
    void out()
    {
        for (unsigned i = 0; i < len; ++i)
        {
            cout << list[i] << " ";
            if ((i + 1) % 18 == 0) cout << endl;
        }
        cout << endl;
    }
};
#endif


#include "ShellSort.h"
#include <vector>
using namespace std;

const unsigned numEle = 8;
int data[numEle] = {1,5,7,3,8,2,6,4};


int main()
{
    vector<int> testData;
    for (unsigned i = 0; i < numEle; ++i) testData.push_back(data[i]);

    ShellSort<int> test(testData, numEle);
    test.shellSort();
    test.out();
    return 0;
}