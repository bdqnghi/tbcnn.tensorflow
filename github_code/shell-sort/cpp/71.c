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
    /*
     * Construction function
    */
    ShellSort(vector<T> _list, unsigned _len)
    {
        for (unsigned i = 0; i < _len; ++i) list.push_back(_list[i]);
        this->len = _len;
    }
    /*
     * Shellsort function
    */
    void shellSort()
    {
        int insertNum;
        unsigned gap = len/2; // initial increment
        while(gap) // while gap>=1
        {
            for (unsigned i = gap; i < len; ++i) // Insertsort within subsequence
            {
                insertNum = list[i];//Target number to be inserted into the subsequence
                unsigned j = i;
                while (j >= gap && insertNum < list[j-gap])//Find position
                {
                    list[j] = list[j - gap];
                    j -= gap;
                }
                list[j] = insertNum;
            }//end for
            gap /= 2;
        }//end while(gap)
    }// end shellSort

    /*
    * Display the sorted result
    */
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

//shellSortTest
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