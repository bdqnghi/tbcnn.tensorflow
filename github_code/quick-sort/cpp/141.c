#include "QuickSort.h"
#include"Sorter.h"
#include<cmath>
#include<iostream>
#include<time.h>
#include<vector>

int tim;
QuickSort::QuickSort()
{
   elements.clear();
}

QuickSort::QuickSort(vector <int> ele)
{
    int len = ele.size();
    for(int i = 0 ; i < len;i++)
      {elements.push_back(ele[i]);}
}

vector<int> QuickSort::sort()
{
    quickSort(elements, 0 , elements.size() - 1 );
    return elements;

}

void QuickSort::quickSort(vector <int >&v , int start , int fin)
  {
      tim = clock();
        if(start>= fin)
           {
            return ;
           }
        int pivote = part(v,start,fin);
        quickSort(v,start , pivote - 1);
        quickSort(v , pivote + 1 , fin );

  }

int QuickSort::part(vector < int >&v , int start , int fin)
  {
    int pivote= v[fin];
    int index =start;
    for ( int i = start ; i <fin ; i++ )
    {
        if(v[i] <= pivote )
        {
          swap(v[i],v[index]);
          index++;
        }
    }
    swap (v[index] , v[fin]);
    return index;
  }

QuickSort::~QuickSort()
{
    //dtor
}
