//
//  TowerOfHanoi.cpp
//  JSAlgorithmVisualizer
//
//  Created by Seoksoon Jang on 2016. 10. 12..
//  Copyright © 2016년 Seoksoon Jang. All rights reserved.
//

#include "TowerOfHanoi.hpp"

void TowerOfHanoi::moveDisk(__int64_t numberOfDisk, char fromDisk, char toDisk, char supportDisk) {
    
    if (numberOfDisk == 1){
        cout << "Move disk 1 from Disk "<< fromDisk <<" to Disk "<< toDisk << "\n";
        return;
    }
    this->moveDisk(numberOfDisk - 1, fromDisk, supportDisk, toDisk);
    cout << "Move disk " << numberOfDisk <<" from Disk " << fromDisk <<" to Disk " << toDisk << "\n";
    this->moveDisk(numberOfDisk - 1, supportDisk, toDisk, fromDisk);
}

void TowerOfHanoi::setupNumberOfHanoiDisk() {
    cout << "Enter the number of disks : \n";
    cin >> numberOfDisk;
    cout << "The sequence of moves involved in the Tower of Hanoi are : %lld" << numberOfDisk << "\n";
}

const __int64_t TowerOfHanoi::getNumberOfDisk(void) {
    return numberOfDisk;
};

void TowerOfHanoi::setNumberOfDisk(__int64_t _numberOfDisk) {
    numberOfDisk = _numberOfDisk;
};

TowerOfHanoi::TowerOfHanoi() {
    numberOfDisk = 0;
}

TowerOfHanoi::TowerOfHanoi(__int64_t _numberOfDisk) {
    numberOfDisk = _numberOfDisk;
}

TowerOfHanoi::~TowerOfHanoi() {
    printf("tower of hanoi destructor!");
}
