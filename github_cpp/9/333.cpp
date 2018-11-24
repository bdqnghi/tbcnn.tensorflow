/*---------------------------------------------------------------------------*\
 *  insertion-sort.cpp                                                       *
 *  Written By:  Colin B Hamilton, Tufts University                          *
 *  Last Modified: 2014-9-11                                                 *
 *  Description:                                                             *
 *    The insertion sort algorithm takes a vector of ints and returns the    *
 *    sorted permutation of that vector.  It runs by:                        *
 *    1) Beginning with a sorted sub-array of size 1 (the first element).    *
 *    2) Expanding the size of the sub-array by one.                         *
 *    3) Re-sorting the sub-array by moving the new element to its correct   *
 *       position.                                                           *
 *    4) Repeating until the sorted sub-array's size is that of the full     *
 *       array.                                                              *
 *  The name "insertion sort" comes from the fact that, we are taking one    *
 *  element at a time and inserting it into place in the sorted array.       *
\*---------------------------------------------------------------------------*/

#include "sort.h"

void swap(std::vector<int> &array, int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

void insert(std::vector<int> &array, int index)
{
    int elem = array[index];
    /* Shifts all elements > elem up by one, leaves i pointing at elem's position. */
    int i;
    for (i = index; i > 0 && array[i - 1] > elem; --i) {
        array[i] = array[i - 1];
    }
    array[i] = elem;
}

std::vector<int> sort(std::vector<int> list)
{
    int last = list.size() - 1;
    for (int i = 1; i <= last; ++i) {
        insert(list, i);
    }
    return list;
}

/* STATS:
Tests run on Sat Sep 13 11:38:02 2014
 Timing input file data/random-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.3360s        0.3400s        0.3090s        0.3080s        0.3070s      0.3200s
User:     0.3170s        0.3380s        0.3070s        0.3070s        0.3050s      0.3148s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/random-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:    31.7210s       33.7920s       30.3500s       30.4090s       30.5860s     31.3716s
User:    31.6410s       33.6180s       30.3400s       30.4010s       30.5730s     31.3146s
System:   0.0230s        0.0390s        0.0090s        0.0080s        0.0110s      0.0180s

 Timing input file data/random-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0060s        0.0080s        0.0050s        0.0050s        0.0050s      0.0058s
User:     0.0040s        0.0050s        0.0040s        0.0040s        0.0040s      0.0042s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/random-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0060s        0.0060s        0.0060s        0.0050s        0.0060s      0.0058s
User:     0.0040s        0.0050s        0.0040s        0.0040s        0.0040s      0.0042s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/random-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0050s        0.0060s        0.0050s        0.0050s        0.0050s      0.0052s
User:     0.0040s        0.0050s        0.0040s        0.0040s        0.0040s      0.0042s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.6660s        0.6190s        0.6090s        0.6080s        0.6140s      0.6232s
User:     0.6430s        0.6180s        0.6080s        0.6060s        0.6120s      0.6174s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:    63.3860s       62.6280s       61.1810s       62.5540s       61.2590s     62.2016s
User:    63.3250s       62.5520s       61.1530s       62.4060s       61.2280s     62.1328s
System:   0.0450s        0.0380s        0.0190s        0.0450s        0.0250s      0.0344s

 Timing input file data/reverse-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0080s        0.0110s        0.0090s        0.0080s        0.0080s      0.0088s
User:     0.0070s        0.0090s        0.0070s        0.0070s        0.0070s      0.0074s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0080s        0.0080s        0.0080s        0.0090s        0.0090s      0.0084s
User:     0.0070s        0.0070s        0.0070s        0.0070s        0.0070s      0.0070s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0090s        0.0080s        0.0080s        0.0080s        0.0080s      0.0082s
User:     0.0070s        0.0070s        0.0070s        0.0070s        0.0070s      0.0070s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0070s        0.0070s        0.0070s        0.0060s        0.0070s      0.0068s
User:     0.0050s        0.0050s        0.0050s        0.0050s        0.0050s      0.0050s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0580s        0.0590s        0.0560s        0.0560s        0.0560s      0.0570s
User:     0.0560s        0.0570s        0.0540s        0.0540s        0.0540s      0.0550s
System:   0.0020s        0.0020s        0.0020s        0.0020s        0.0020s      0.0020s

 Timing input file data/sorted-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0030s        0.0020s        0.0020s        0.0020s        0.0020s      0.0022s
User:     0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0020s        0.0020s        0.0020s        0.0020s        0.0020s      0.0020s
User:     0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0020s        0.0020s        0.0020s        0.0020s        0.0020s      0.0020s
User:     0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s


*/
