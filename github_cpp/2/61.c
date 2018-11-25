

#include "Cache.h"
#include <iostream>
#include <stdlib.h>
#include <tgmath.h>

unsigned int Cache::calcBits(unsigned int num){
	if (num <= 2)
		return 1;
	else
		return 1 + Cache::calcBits(num / 2);
}

bool Cache::lookup(unsigned int addr, unsigned int time) {
	unsigned int blocksToShift = calcBits(blockSize);
	unsigned int tagNumber = addr >> blocksToShift;

	int LRUIndex = 0;
	int LRUTime = time;
	for (int i = 0; i < cacheSize; i++){
		
		if (entries[i].tag == tagNumber){
			entries[i].time = time;
			return true;
		}
		
		if (entries[i].time < LRUTime){
			LRUIndex = i;
			LRUTime = entries[i].time;
		}
	}
	
	entries[LRUIndex].tag = tagNumber;
	entries[LRUIndex].time = time;
	return false;
}


