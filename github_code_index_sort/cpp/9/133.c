#include "SelectionSort.h"
#include"Sorter.h"
#include<cmath>
#include<iostream>
#include<time.h>
#include<iomanip>

using namespace std;

SelectionSort::SelectionSort()
{
    elements.clear();
}
SelectionSort::SelectionSort(vector <int> ele)
{
    int len = ele.size();
    for(int i = 0 ; i < len;i++)
      {elements.push_back(ele[i]);}
}

vector<int> SelectionSort::sort()
{
    int index ;
    int len = elements.size();
    for(int i = 0 ; i < len- 1; i++)
    {
        index = i;
        for(int j = i+1 ; j < len; j++)
        {
            if(elements[index]>elements[j])
                index = j;
        }
        swap(elements[i],elements[index]);
    }
 return elements;

}

vector<int> SelectionSort::reverse()
{
    int index ;
    int len = elements.size();
    for(int i = 0 ; i < len- 1; i++)
    {
        index = i;
        for(int j = i+1 ; j < len; j++)
        {
            if(elements[index]<elements[j])
                index = j;
        }
        swap(elements[i],elements[index]);
    }
    return elements;
}
SelectionSort::~SelectionSort()
{
    //dtor
}
