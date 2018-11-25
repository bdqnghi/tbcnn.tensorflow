#include "radixsort.h"
#include <iostream>

short radix_sort_get_MSB(unsigned int n)
{
    
    short bits = sizeof(n) * 8;
    
    unsigned int currentBit = bits - 1;
    
    unsigned int mask = 1 << currentBit;
    while(mask != 1)
    {
        
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
    
    unsigned int mask = 1;
    
    short bits = 1;
    bool firstRun = true;
    for(short i = 0; i <= bits; i++)
    {
        
        for(int n : v)
        {
            
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
        
        v.clear();
        
        for(int n : bucket0)
        {
            v.push_back(n);
        }
        for(int n : bucket1)
        {
            v.push_back(n);
        }
        
        bucket0.clear();
        bucket1.clear();
        
        mask = mask << 1;
        firstRun = false;
    }
}

