







#ifndef TowerOfHanoi_hpp
#define TowerOfHanoi_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class TowerOfHanoi {
    private:
    __int64_t numberOfDisk;
    
    public:
    TowerOfHanoi();
    TowerOfHanoi(__int64_t _numberOfDisk);
    ~TowerOfHanoi();
    void moveDisk(__int64_t numberOfDisk, char fromDisk, char toDisk, char supportDisk);
    void setupNumberOfHanoiDisk();
    const __int64_t getNumberOfDisk(void);
    void setNumberOfDisk(__int64_t _numberOfDisk);
};

#endif 
