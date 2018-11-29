#include "radixsort.h"
#include <iostream>

short radix_sort_get_MSB(unsigned int n)
{
    // get the size in bits
    short bits = sizeof(n) * 8;
    // var to hold the bit we're checking
    unsigned int currentBit = bits - 1;
    // create the mask
    unsigned int mask = 1 << currentBit;
    while(mask != 1)
    {
        // check if there is a 1
        if(n & mask)
        {
            return currentBit;     
        }
        mask = 1 << --currentBit;
    }
    return 1;
}

void radix_sort(std::vector<unsigned int> &v)
{
    std::vector<unsigned int> bucket0;
    std::vector<unsigned int> bucket1;   
    //bool done = false;
    unsigned int mask = 1;
    // begin by assuming we'll do it all
    short bits = 1;
    bool firstRun = true;
    for(short i = 0; i <= bits; i++)
    {
        // bucket sort based on bit
        for(int n : v)
        {
            // get the # of bits we should sort
            if(firstRun)
            {
                short tmp = radix_sort_get_MSB(n);
                if(tmp > bits)
                    bits = tmp;
            }
            if(n & mask)
            {
                bucket1.push_back(n);
            }
            else
            {
                bucket0.push_back(n);
            }
        }
        // all numbers have been moved so clear it
        v.clear();
        // add numbers back sorted by current bit
        for(int n : bucket0)
        {
            v.push_back(n);
        }
        for(int n : bucket1)
        {
            v.push_back(n);
        }
        // clear the buckets
        bucket0.clear();
        bucket1.clear();
        // move to next bit
        mask = mask << 1;
        firstRun = false;
    }
}

