#include "tensors.h"






















void QuickSort_double(dTensor1& a, iTensor1& index, int lo, int hi)
{

    
    
    int i = lo;
    int j = hi;

    
    const double x = a.get( (i+j)/2 );

    
    while(i<=j) 
    {           
        while (a.get(i)<x) 
        {i++;} 

        while (a.get(j)>x) 
        {j--;}

        if (i<=j)
        {
            double h = a.get(i);
            a.set(i, a.get(j));
            a.set(j, h);

            int itmp = index.get(i);
            index.set(i, index.get(j) );
            index.set(j, itmp );

            i++; j--;
        }
    }

    
    if (lo<j) QuickSort_double(a, index, lo, j);
    if (i<hi) QuickSort_double(a, index, i, hi);
}


void QuickSort_int(iTensor1& a, iTensor1& index, int lo, int hi)
{

    
    

    int i = lo;
    int j = hi;

    
    const int x = a.get( (i+j)/2 );

    
    while(i<=j) 
    {           
        while (a.get(i)<x) 
        {i++;} 

        while (a.get(j)>x) 
        {j--;}

        if (i<=j)
        {
            int h = a.get(i);
            a.set(i,a.get(j));
            a.set(j,h);

            int itmp = index.get(i);
            index.set(i, index.get(j) );
            index.set(j, itmp );

            i++; j--;
        }
    }

    
    if (lo<j) QuickSort_int(a, index, lo, j);
    if (i<hi) QuickSort_int(a, index, i, hi);

}
