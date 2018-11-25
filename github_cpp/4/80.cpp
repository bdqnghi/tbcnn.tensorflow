/*
 * File: towerofhanoi.cpp
 * Author: Keith Bush (2013)
 *
 * Purpose: Demonstrates the use of recusion to solve a non trivial puzzle: the "Tower of Hanoi" problem.
 */

#include <iostream>

using namespace std;

//Keep a global "move" counter
static int x=0;

void towerOfHanoi(int n, char A, char B, char C){
	if(n>0){
		towerOfHanoi(n-1,A,C,B);
		x++;
		cout << x << ": Move Disk " << n << " from " << A << " to " << C << endl;
		towerOfHanoi(n-1,B,A,C);
	}
}

void main(){
	towerOfHanoi(20, 'A', 'B', 'C');
	system("PAUSE");
}