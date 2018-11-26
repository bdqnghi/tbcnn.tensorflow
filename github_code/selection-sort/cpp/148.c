//Name: Alan Cheng
//SID: 861094564
//Date: 5/12/15
//Approach: Make selection sort work for list and vector

//PART 2A:
//Answer: Selection sort is not a stable sort.

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <array>

using namespace std;

#ifndef selectionsort_H
#define selectionsort_H

template<typename L>
void sortDisplay(const L theList)
{
    for(auto i = theList.begin() ; i != theList.end() ; i++)
    {
        cout << *i << " ";
    }
    
    cout << endl;
    
}


template<typename L>
void sortPairDisplay(const L pairList)
{
    for(auto i = pairList.begin() ; i != pairList.end() ; i++)
    {
        cout << "(" << i->first << ", " << i->second << ") ";
    }
    
    cout << endl;
    
}

template<typename L>
void selectionsort(L &l)
{
    int copy = 0;
    int moves = 0;
    
    for(auto i = l.begin() ; i != l.end() ; i++)
    {
        auto min = i;
        for(auto j = i ; j != l.end() ; j++)
        {
            if(*j < *min)
            {
                min = j;
            }
        }
        
        if(i != min)
        {
            swap(*i, *min);
            moves = moves + 3;
        }
    }
    
    cout << copy << " copies and " << moves << " moves" << endl;
}

template<typename L>
void checkStableSort(L &l)
{
    cout << "Select-sort is not a stable sort because of the following example: " << endl;
    cout << endl;
    
    cout << "Original order: " << endl;
    sortPairDisplay(l);
    cout << endl;
    
    for(auto i = l.begin() ; i != l.end() ; i++)
    {
        auto min = i;
        for(auto j = i ; j != l.end() ; j++)
        {
            if((*j).first < (*min).first)
            {
                min = j;
            }
        }
        
        if(i != min)
        {
            swap(*i, *min);
        }
    }
    
    cout << "Order after selection-sort: " << endl;
    sortPairDisplay(l);
    
    cout << endl;
    cout << "As shown in the example, after sorting based on the first component of the element: "<< endl;
    cout << "The elements (2, 2) and (2, 3) do not retain their order (although the first components were equal)." << endl;
    cout << "This proves that selection-sort is not a stable sort" << endl;
    
}

#endif