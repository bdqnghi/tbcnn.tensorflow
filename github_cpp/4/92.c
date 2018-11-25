//Pranav Sharma//
//“You don't have to be great to start, but you have to start to be great.”
//The Tower of Hanoi is a mathematical game or puzzle. It consists of three rods and a number of disks of different sizes, which can slide onto any rod. The puzzle starts with the disks in a neat stack in ascending order of size on one rod, the smallest at the top, thus making a conical shape.
// The objective of the puzzle is to move the entire stack to another rod, obeying the following simple rules:
// Only one disk can be moved at a time.
// Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack or on an empty rod.
// No disk may be placed on top of a smaller disk.
#include <iostream>
#include <conio.h>
using namespace std;

void TowerOfHanoi(int n, char src,char help, char dest){
	if(n==0){
		return;
	}
	TowerOfHanoi(n-1, src,dest,help);
	cout<<"Move disk "<<n<<" from "<<src<<" to "<<dest<<endl;
	TowerOfHanoi(n-1,help,src,dest);
}

int steps(int n){
	if(n==0){
		return 0;
	}
	return 2*steps(n-1)+1;
}
int main(){
	int n;
	cin>>n;
	TowerOfHanoi(3, 'A' , 'B' , 'C');
	cout<<steps(n)<<endl;
//Your code comes here.
	getch();
	return 0;
}