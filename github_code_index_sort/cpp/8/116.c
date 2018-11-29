#include "tensors.h"

// Quick-sort algorithm used in the unstructured parts of the code.  This
// routine uses (in-place?) sorting on ... TODO
//
// Input:
//
//         a  - array to be sorted
//      index - ??? TODO - document this index
//         lo - lower index to sort
//         hi - upper index to sort
//
// Output:
//
//        TODO - document what the output is.  For example, does index AND a get
//        sorted, or just index?  -DS
//
// See also: $DOGPACK/lib/2d/unst/mesh.cpp, for the only other library routine
// that uses this, and for a few applications that use this, see:
//
//           $DOGPACK/apps/2d/Poisson/lib/unst/SetInterpNodes.cpp
//           $DOGPACK/apps/2d/advection/double_periodic_unst/Unstructured_Mesh/MeshPostProcess2.cpp
//
void QuickSort_double(dTensor1& a, iTensor1& index, int lo, int hi)
{

    //  lo is the lower index, hi is the upper index
    //  hi the region of array a that is to be sorted
    int i = lo;
    int j = hi;

    // pivot:
    const double x = a.get( (i+j)/2 );

    //  partition
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

    //  Recursive call:
    if (lo<j) QuickSort_double(a, index, lo, j);
    if (i<hi) QuickSort_double(a, index, i, hi);
}

// Same function as above, but this time sorts an iTensor1.
void QuickSort_int(iTensor1& a, iTensor1& index, int lo, int hi)
{

    //  lo is the lower index, hi is the upper index
    //  hi the region of array a that is to be sorted

    int i = lo;
    int j = hi;

    // Pivot element:
    const int x = a.get( (i+j)/2 );

    //  partition
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

    //  Recursive call:
    if (lo<j) QuickSort_int(a, index, lo, j);
    if (i<hi) QuickSort_int(a, index, i, hi);

}
