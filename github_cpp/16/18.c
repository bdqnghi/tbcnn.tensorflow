





#ifdef AAC_PLUS


#include "shellsort.h"

















void shellsort(Int32 in[], Int32 n)
{

    Int32     i;
    Int32     j;
    Int32     v;
    Int32     inc = 1;

    do
    {
        inc = 3 * inc + 1;
    }
    while (inc <= n);

    do
    {
        inc = inc / 3;
        for (i = inc + 1; i <= n; i++)
        {
            v = in[i-1];
            j = i;
            while (in[j-inc-1] > v)
            {
                in[j-1] = in[j-inc-1];
                j -= inc;
                if (j <= inc)
                {
                    break;
                }
            }
            in[j-1] = v;
        }
    }
    while (inc > 1);

}

#endif

