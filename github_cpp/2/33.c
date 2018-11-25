







#include "LRU.h"

LRU::LRU(int cacheSize){
    this->cacheSize = cacheSize;
    numHits = 0;
    numRequests = 0;
    size = 0;
}

LRU::~LRU(){
    
}

void LRU::setCacheSize(int cacheSize){
    this->cacheSize = cacheSize;
}

void LRU::add(int page){
    numRequests++;
    
    if(contains(page))
        moveToBack(page);
    else{
        if(cache.size() < cacheSize){
            itLocs[page] = cache.insert(cache.end(),page);
            currPages[page] = true;
            size++;
        }
        else
            replacePage(page);
    }
}

bool LRU::contains(int page){
    if(currPages[page]){
        numHits++;
        return true;
    }
    
    return false;
}

float LRU::getHitRatio(){
    calculateHitRatio();
        
    return hitRatio;
}

void LRU::calculateHitRatio(){
    hitRatio = (float)numHits/(float)numRequests * 100;
}

void LRU::moveToBack(int page){
    cache.erase(itLocs[page]);
    itLocs[page] = cache.insert(cache.end(),page);
}

void LRU::replacePage(int page){
    int oldPage = cache.front();
    
    
    
    
    
    removePage(oldPage);
    
    
    currPages[page] = true;
    
    cache.pop_front();

    itLocs[page] = cache.insert(cache.end(), page);
}

void LRU::removePage(int page){
    currPages[page] = false;
    size--;
}
