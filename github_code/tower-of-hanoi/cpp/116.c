/*
 * File: tower_of_hanoi.cpp
 * ---------------------
 *  Recursive program implementation of the game Tower of Hanoi
 */
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
/* Function prototypes */
void moveDisk(char start, char finish);
void towerOfHanoi(int n, char start, char finish, char temp);

/* Main program */
int main() {
  int n;
  cout << "Enter disks : ";
  cin >> n;
  towerOfHanoi(n, 'A', 'B', 'C');
  
  system("pause");
  return 0;
}

/*
 * Function: moveDisk
 * Usage: moveDisk(start, finish);
 * ----------------------------------
 * Prints out next move.
 */
void moveDisk(char start, char finish){
  cout<< "Moved from " << start << " to " << finish << endl;
}

/*
 * Function: towerOfHanoi
 * Usage: towerOfHanoi(n, start, finish, temp);
 * ----------------------------------
 * Makes recursive call to progress moves with n-1 disks.
 */
void towerOfHanoi(int n, char start, char finish, char temp){
    if(n == 1){
      moveDisk(start, finish);
    } else {
        // start - A, tmp - C, finish - B (moves from A to C)
        towerOfHanoi(n - 1, start, temp, finish);
        //output to console
        moveDisk(start, finish);
        //start - C, Finish B, Tmp - A
        towerOfHanoi(n - 1, temp, finish, start);
    }
}
