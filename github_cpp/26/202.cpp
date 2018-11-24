/*---------------------------------------------------------------------------*\
 *  bubble-sort.cpp                                                          *
 *  Written By:  Colin B Hamilton, Tufts University                          *
 *  Last Modified: 2014-9-11                                                 *
 *  Description:                                                             *
 *    The bubble sort algorithm takes a vector of ints and returns the       *
 *    sorted permutation of that vector.  It runs by:                        *
 *    1) Stepping through the array, looking for adjacent elements in the    *
 *       wrong order.                                                        *
 *    2) Swapping those elements, when found.                                *
 *    3) Repeating until it steps through the array without finding any      *
 *       out-of-order elements.                                              *
 *    Note that this implementation also keeps track of the last swap made   *
 *      on each scan.  Subsequent scans need not pass that point, because    *
 *      if no swaps were made beyond it, that sub-array is already sorted.   *
 *  The name "bubble sort" comes from the idea that the algorithm moves      *
 *  elements slightly closer to the right positions each time, like          *
 *  they are "bubbling" into the correct positions, like bubbles rising to   *
 *  the surface.  Note, however, that large elements move fast; elements get *
 *  pushed very quickly to the end of the array, but it takes quite some     *
 *  time to move small elements to the front if they started toward the      *
 *  end.  The former elements are known as "rabbits," for their speed, while *
 *  the latter are known as "turtles."                                       *
\*---------------------------------------------------------------------------*/

#include "sort.h"

void swap(std::vector<int> &array, int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

int bubble(std::vector<int> &list, int size_unsorted)
{
    int last_element_swapped = 1;
    for (int i = 1; i < size_unsorted; ++i) {
        if (list[i - 1] > list[i]) {
            swap(list, i - 1, i);
            last_element_swapped = i;
        }
    }
    return last_element_swapped;
}

std::vector<int> sort(std::vector<int> list)
{
    int len = list.size();
    while (len > 1) {
        len = bubble(list, len);
    }
    return list;
}

/* STATS:
Tests run on Sat Sep 13 12:02:53 2014
 Timing input file data/random-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     1.0610s        1.0160s        1.0160s        1.0640s        1.1680s      1.0650s
User:     1.0190s        1.0140s        1.0140s        1.0620s        1.1640s      1.0546s
System:   0.0020s        0.0010s        0.0010s        0.0020s        0.0020s      0.0016s

 Timing input file data/random-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:   101.4260s      101.8550s      101.7590s      102.1570s      107.9850s    103.0364s
User:   101.3800s      101.7860s      101.7080s      102.0990s      107.8010s    102.9548s
System:   0.0300s        0.0400s        0.0450s        0.0480s        0.0620s      0.0450s

 Timing input file data/random-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0130s        0.0130s        0.0120s        0.0130s        0.0130s      0.0128s
User:     0.0110s        0.0110s        0.0110s        0.0110s        0.0110s      0.0110s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/random-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0120s        0.0120s        0.0130s        0.0120s        0.0120s      0.0122s
User:     0.0110s        0.0110s        0.0110s        0.0110s        0.0110s      0.0110s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/random-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0120s        0.0160s        0.0130s        0.0120s        0.0130s      0.0132s
User:     0.0110s        0.0140s        0.0110s        0.0110s        0.0110s      0.0116s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     1.2500s        1.5780s        1.2680s        1.2910s        1.2440s      1.3262s
User:     1.2480s        1.5530s        1.2640s        1.2880s        1.2420s      1.3190s
System:   0.0010s        0.0030s        0.0020s        0.0020s        0.0010s      0.0018s

 Timing input file data/reverse-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:   124.1470s      126.3500s      127.1890s      130.2290s      124.7260s    126.5282s
User:   124.1080s      126.2370s      127.0280s      129.9930s      124.6740s    126.4080s
System:   0.0330s        0.0890s        0.1010s        0.0870s        0.0430s      0.0706s

 Timing input file data/reverse-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0150s        0.0150s        0.0150s        0.0190s        0.0190s      0.0166s
User:     0.0130s        0.0140s        0.0140s        0.0170s        0.0170s      0.0150s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-1000-neg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0150s        0.0150s        0.0160s        0.0160s        0.0200s      0.0164s
User:     0.0130s        0.0130s        0.0140s        0.0140s        0.0180s      0.0144s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/reverse-1000-nonneg.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0150s        0.0150s        0.0150s        0.0170s        0.0220s      0.0168s
User:     0.0130s        0.0130s        0.0130s        0.0160s        0.0200s      0.0150s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-10-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0070s        0.0070s        0.0070s        0.0080s        0.0110s      0.0080s
User:     0.0050s        0.0050s        0.0050s        0.0070s        0.0080s      0.0060s
System:   0.0010s        0.0010s        0.0010s        0.0010s        0.0010s      0.0010s

 Timing input file data/sorted-100-000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0560s        0.0580s        0.0570s        0.0670s        0.0830s      0.0642s
User:     0.0530s        0.0550s        0.0550s        0.0650s        0.0770s      0.0610s
System:   0.0010s        0.0020s        0.0020s        0.0020s        0.0020s      0.0018s

 Timing input file data/sorted-1000-all.data:
        TRIAL 0        TRIAL 1        TRIAL 2        TRIAL 3        TRIAL 4       AVG
Real:     0.0020s        0.0030s        0.0020s        0.0020s        0.0030s      0.0024s
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
