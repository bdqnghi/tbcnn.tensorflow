
#include <iostream.h>

void shellsort(int x[], int n)
{
  int span = 1;
  int temp = 0;
  int counter = 0;
  int i,j;

  
  while (span < n)
    span = 3*span + 1;
  
  do
  {
    span = span/3;
    cout << span << endl;
    for (i = span-1; i < n; ++i)
    {
      
      temp = x[i];
      for (j = i; j >= span && x[j-span] > temp; j -= span)
	x[j] = x[j-span];
      x[j] = temp;
    }
  } while(span > 0);
}
