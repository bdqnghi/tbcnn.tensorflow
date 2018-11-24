/*******************************************************************************

Tower of Hanoi
==============

Ref - http://quiz.geeksforgeeks.org/c-program-for-tower-of-hanoi/
    - ADS 2.9

--------------------------------------------------------------------------------

Problem
=======
Tower of Hanoi is a mathematical puzzle where we have three rods and n disks.
The objective of the puzzle is to move the entire stack to another rod, obeying
the following simple rules:
1) Only one disk can be moved at a time.
2) Each move consists of taking the upper disk from one of the stacks and placing
   it on top of another stack i.e. a disk can only be moved if it is the uppermost
   disk on a stack.
3) No disk may be placed on top of a smaller disk.

--------------------------------------------------------------------------------

Algorithm
=========
1) Move the top (n - 1) disks from Source to Aux tower.
2) Move the nth disk from Source to Destination.
3) Move the (n - 1) disks from Aux tower to Destination.
4) Solve recursively.

--------------------------------------------------------------------------------

Time Complexity
===============
O(2^n)
For n disks, total (2^n – 1) moves are required.

--------------------------------------------------------------------------------

Output
======
Move Disk 1 from A to C
Move Disk 2 from A to B
Move Disk 1 from C to B
Move Disk 3 from A to C
Move Disk 1 from B to A
Move Disk 2 from B to C
Move Disk 1 from A to C

*******************************************************************************/

#include <stdio.h>

void towerOfHanoi(int n, char from, char to, char aux)  {
    if (n == 1) {
        printf("Move Disk 1 from %c to %c\n", from, to);
        return;
    }

    towerOfHanoi(n - 1, from, aux, to);
    printf("Move Disk %d from %c to %c\n", n, from, to);
    towerOfHanoi(n - 1, aux, to, from);
}

int main()  {
    towerOfHanoi(3, 'A', 'C', 'B');
    return 0;
}
