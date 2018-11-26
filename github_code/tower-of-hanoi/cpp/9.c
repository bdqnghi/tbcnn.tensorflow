//
//  main.cpp
//  Divide_and_Conquer(Tower of Hanoi)
//  https://www.acmicpc.net/problem/11729
//  Created by Sangchul, Song on 4/9/16.
//  Copyright © 2016 HYU. All rights reserved.
//
#include <iostream>
#include <math.h>
#include "hanoi.hpp"

// Hanoi Problem: Move 'N' disks from 'tower_p' to 'tower_r'
void Hanoi(Tower &tower_p, Tower &tower_q, Tower &tower_r, int N);

int main(int argc, const char *argv[])
{
    // Initialization
    Tower tower_A(1), tower_B(2), tower_C(3);
    int N;
    cin >> N;
    for (int disk = N; disk > 0; disk--)
        tower_A.put(disk);
    
    // # of minimum movement required to solve tower of hanoi
    int cnt_movement = (int) (pow(2, N) - 1);
    cout << cnt_movement << "\n";

    Hanoi(tower_A, tower_B, tower_C, N);
    
    return 0;
}

// Recursive Version of Hanoi
inline void
Hanoi(Tower &tower_p, Tower &tower_q, Tower &tower_r, int N)
{
    if (N == 1) // Base Condition
        Tower::move(tower_p, tower_r);
    else
    {
        // Divide and Conquer
        Hanoi(tower_p, tower_r, tower_q, N - 1);
        Tower::move(tower_p, tower_r);
        Hanoi(tower_q, tower_p, tower_r, N - 1);
    }
}
