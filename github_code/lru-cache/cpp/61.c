/*
 * LRU.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: ryancsmith
 */

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
/*
 * This function implements an LRU cache.
 */
bool Cache::lookup(unsigned int addr, unsigned int time) {
	unsigned int blocksToShift = calcBits(blockSize);
	unsigned int tagNumber = addr >> blocksToShift;

	int LRUIndex = 0;
	int LRUTime = time;
	for (int i = 0; i < cacheSize; i++){
		//if this CacheEntry == tagNumber - report hit
		if (entries[i].tag == tagNumber){
			entries[i].time = time;
			return true;
		}
		//update LRU value if applicable
		if (entries[i].time < LRUTime){
			LRUIndex = i;
			LRUTime = entries[i].time;
		}
	}
	//didn't find a match - evict LRU CacheEntry and replace with new one
	entries[LRUIndex].tag = tagNumber;
	entries[LRUIndex].time = time;
	return false;
}


