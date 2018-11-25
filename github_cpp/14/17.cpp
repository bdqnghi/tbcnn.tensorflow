

#include <deque>
#include <list>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iterator>

#include <examples.h>

typedef std::deque<int, std::allocator<int> >                     IntDeque;
typedef std::vector<IntDeque, std::allocator<IntDeque> >          DeqVector;
typedef std::list<int, std::allocator<int> >                      IntList;
typedef std::ostream_iterator<int, char, std::char_traits<char> > OstreamIter;


class copyIntoBuckets {
public:
    copyIntoBuckets (int d, DeqVector &b, bool &f)
      : divisor (d), buckets (b), flag (f)
        {}

    void operator () (unsigned int v) {
        const int inx = (v / divisor) % 10;
        
        if (inx)
            flag = true; 
        buckets [inx].push_back (v);
    }

    int        divisor;
    DeqVector &buckets;
    bool      &flag;
};


IntList::iterator
copyList (IntList::iterator c, IntDeque &lst) {
    
    return std::copy (lst.begin (), lst.end (), c);
}


void radixSort (IntList & values) {
    bool flag   = true;
    int divisor = 1;
    
    while (flag)
    {
        DeqVector buckets (10);
        flag = false;

        std::for_each (values.begin (), values.end (), 
            copyIntoBuckets (divisor, buckets, flag));
        std::accumulate (buckets.begin (), buckets.end (), values.begin (), copyList);
        divisor *= 10;
        std::copy (values.begin (), values.end (), OstreamIter (std::cout, " "));
        std::cout << std::endl;
    }
}


int main () {
    
    std::cout << "Radix sort program"  << std::endl;

    const IntList::value_type data[] = { 624, 852, 426, 987, 269,
                                       146, 415, 301, 730, 78, 593 };

    IntList values (data, data + sizeof data / sizeof *data);

    radixSort (values);
    std::copy (values.begin (), values.end (), OstreamIter (std::cout, " "));

    std::cout << std::endl << "End radix sort program" << std::endl;

    return 0;   
}
