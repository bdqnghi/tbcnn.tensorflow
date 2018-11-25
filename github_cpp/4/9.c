






#include <iostream>
#include <math.h>
#include "hanoi.hpp"


void Hanoi(Tower &tower_p, Tower &tower_q, Tower &tower_r, int N);

int main(int argc, const char *argv[])
{
    
    Tower tower_A(1), tower_B(2), tower_C(3);
    int N;
    cin >> N;
    for (int disk = N; disk > 0; disk--)
        tower_A.put(disk);
    
    
    int cnt_movement = (int) (pow(2, N) - 1);
    cout << cnt_movement << "\n";

    Hanoi(tower_A, tower_B, tower_C, N);
    
    return 0;
}


inline void
Hanoi(Tower &tower_p, Tower &tower_q, Tower &tower_r, int N)
{
    if (N == 1) 
        Tower::move(tower_p, tower_r);
    else
    {
        
        Hanoi(tower_p, tower_r, tower_q, N - 1);
        Tower::move(tower_p, tower_r);
        Hanoi(tower_q, tower_p, tower_r, N - 1);
    }
}
