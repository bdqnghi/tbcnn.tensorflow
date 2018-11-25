#include "quicksort.h"
#include <cstdlib>
#include "../student.h"

using namespace std;

quicksort::quicksort()
{
  
}

quicksort::~quicksort()
{
  
}






void quicksort::sorter(vector<Student*>& list, int left, int right)
{

  int min = left;
  int max = right;
  int pivot = atoi(list[(min+max)/2]->getId().c_str());

  
  while( min <= max )
  {
    
    while( atoi(list[min]->getId().c_str()) < pivot )
    {
      min++;
    }
    
    while( atoi(list[max]->getId().c_str()) > pivot )
    {
      max--;
    }
    
    if( min <= max )
    {
      
      Student* temp;
      temp = list[min];
      list[min] = list[max];
      list[max] = temp;
      min++;
      max--;
      
    }

  }

  
  if(left < max)
  {
    sorter(list, left, max);
  }
  if(min < right)
  {
    sorter(list, min, right);
  }

}
