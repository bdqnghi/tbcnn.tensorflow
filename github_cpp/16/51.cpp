#ifndef __OOMTKSYS_SHELLSORT_H__
#define __OOMTKSYS_SHELLSORT_H__



#include <cstddef>


template <typename T>
void shellsort(T * array, size_t length)
{
  int i, j, inc;
  T v;
  
  inc = 1;
  do
  {
    inc *= 3;
    inc ++;
  } while (inc <= length);
  
  do
  {
    inc /= 3;
    for (i = inc; i < length; i++)
    {
      v = array[i];
      j = i;
      while (array[j-inc] > v)
      {
	array[j] = array[j-inc];
	j -= inc;
	if (j < inc)
	  break;
      }
      array[j] = v;
    }
  } while (inc > 1);
}

#endif 
