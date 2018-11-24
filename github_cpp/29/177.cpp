#include <iostream>
#include <cstdlib>

#include "BloomFilter.h"

using namespace std;

BloomFilter::BloomFilter(unsigned int m, unsigned int k):
    _m(m), _k(k) {
        table.resize(_m);
        for(int i = 0; i < _m; ++i)
            table[i] = false;
}

unsigned int BloomFilter::getSeed(unsigned int hash_index) {
    string seed = "13";
    for(int i = 0; i < hash_index; ++i)
        seed += (i % 2 == 0)? "1" : "3";

    return atoi(seed.c_str());
}

unsigned int BloomFilter::BKDR_Hash(string s, unsigned int hash_index) {
    const char *ps = s.c_str();
    unsigned int seed = getSeed(hash_index);
    unsigned int hash = 0;

    for(int i = 0; i < s.size(); ++i)
        hash += hash * seed + ps[i];

    return hash % _m;
}

void BloomFilter::insertElement(string s) {
    for(int i = 0; i < _k; ++i) {
        unsigned int index = BKDR_Hash(s, i);
        // cout << index << endl;
        table[index] = true;
    }
}

bool BloomFilter::existsElement(string s) {
    for(int i = 0; i < _k; ++i) {
        unsigned int index = BKDR_Hash(s, i);
        if(!table[index])
            return false;
    }
    return true;
}
