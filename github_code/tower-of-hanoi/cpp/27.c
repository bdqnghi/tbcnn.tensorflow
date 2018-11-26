/*
 * TowerOfHanoi.cpp
 *
 *  Created on: Aug 24, 2014
 *      Author: cvora
 */

// Cracking the Coding Interview Solution 3.4
// Understanding tower of hanoi - http://clanguagestuff.blogspot.in/2013/09/tower-of-hanoi.html


/**
 * So, In this way we have decomposed the problem into three parts to solve it.
Now let us say
A-->From
B-->To
C-->Via

So the Tower of hanoid problem is (N,From,To,Via) which can be solved in three steps:

1.) (n-1,From,Via,To) -- first solve the problem of moving n-1 discs From to Via .
2.) (1,From,To,Via) -- Then solve the problem of moving 1 disc From to To.
3.) (n-1,Via,To,From) -- Then Solve the problem of moving n-1 disc from Via to To back.

 *
 */

#include <iostream>
#include <stack>

using namespace std;

class Tower{
private:
	stack<int> disks;
	int index;

public:

	Tower(int i){
		index = i;
	}

	int Index(){
		return index;
	}

	void add(int d){
		if(!disks.empty() && disks.top()<=d){
			cout<<"Error placing disk "<<d<<endl;
		}else{
			disks.push(d);
		}
	}

	void moveTopTo(Tower& t){
		int top = disks.top();
		disks.pop();
		t.add(top);
		cout<<"Move disk "<<top<<" from  "<<Index()<<" to "<<t.Index()<<endl;
	}

	void moveDisks(int n, Tower& dest,Tower& buffer){
		if(n>0)
		{
			moveDisks(n-1,buffer,dest);
			moveTopTo(dest);
			buffer.moveDisks(n-1,dest,*this);
		}
	}
};

int main(){

	int n = 3;
	Tower* towers[n];

	for(int i=0;i<n;i++){
		towers[i] = new Tower(i);
	}

	int noDisks;
	cout<<"Enter the number of disks to add to TOWER 0"<<endl;
	cin>>noDisks;

	for(int i=noDisks-1;i>=0;i--){
		towers[0]->add(i);
	}

	int noDisksMoved;
	cout<<"Enter the number of disks to move from TOWER 0 to TOWER 2 via TOWER 1"<<endl;
	cin>>noDisksMoved;

	if(noDisksMoved>noDisks)
		noDisksMoved = noDisks;
	towers[0]->moveDisks(noDisksMoved,*towers[2],*towers[1]);

	return 0;
}


