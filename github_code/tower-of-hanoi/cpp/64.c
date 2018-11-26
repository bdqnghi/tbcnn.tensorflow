/*
Date : 18/04/2015
		First try
> Visual Studio 2013
@TODO:
- Autocreate first position, with a parameter: NBDISK
- Enhance Visualize :) : with SFML ?
	+ animations ?
	+ initial disk number parameter choice : combobox ?...
- Change data structures ... (sure? to what?)
*/

//#include "stdafx.h" // to use _TCHAR, ... and accelerate compilation on Visual Studio/Windows ...

#include <iostream>
#include <chrono> // @QUEST: what difference with ctime.h ?

using namespace std;

const int MAXDISKS = 10;
const int NBTOWERS = 3;
typedef int disk;

#define NULL -1 // why a redefinition warning ...
#define N sizeof(Hanoi[0].disks) / sizeof(Hanoi[0].disks[0]) // macro to get the max number of possible disks "easily" ...

// definitions
void hanoi(disk, char, char, char);
void moveDisk(char, char);
disk getTopDiskPosition(char);
int getTowerPositionByName(char);
void print_tower(char*, int);

// data structure
typedef struct { char name; disk disks[MAXDISKS]; } tower;
typedef tower HanoiGame[NBTOWERS]; // attention : http://stackoverflow.com/questions/4523497/typedef-fixed-length-array
HanoiGame Hanoi = {
	{ 'A', { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 } },
	{ 'B', { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } },
	{ 'C', { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } }
};


int kkk = 0; // debug...

//int _tmain(int argc, _TCHAR* argv[])
int main()
{
	print_tower("(before) 1st tower : ", 0);
	print_tower("(before) 2nd tower : ", 1);
	print_tower("(before) 3rd tower : ", 2);
	
	clock_t t;
	double duration;
	t = clock();

	hanoi(N, /*From*/ Hanoi[0].name, /*Destination*/ Hanoi[2].name, /*Intermediate*/ Hanoi[1].name);
	
	duration = (clock() - t) / (double) CLOCKS_PER_SEC;
	cout << "----------- finished in " << duration << " seconds." << endl;

	print_tower("(after) 1st tower : ", 0);
	print_tower("(after) 2nd tower : ", 1);
	print_tower("(after) 3rd tower : ", 2);

	cout << endl;
	cout << "number of recursions = " << kkk << endl;
#ifdef WIN32
	system("PAUSE");
#endif
	return EXIT_SUCCESS;
}

void hanoi(disk n, char fromPos, char toPos, char throughPos) {
	if (n > 0) {
		kkk++; // debug
		hanoi(n - 1, fromPos, throughPos, toPos);
		moveDisk(fromPos, toPos);
		hanoi(n - 1, throughPos, toPos, fromPos);
	}
}

void print_tower(char* message, int position) { //@FIX: char* ? sure ?
	for (int i = 0; i < MAXDISKS; i++) {
		cout << Hanoi[position].disks[i] << " ** ";
	}
	cout << endl;
}

/*
 if we have a disk on tower "from", we put it on tower "to"
 @param	char	from
 @param	char	to

 @TODO : check that tower "to" is not full, even if its not possible with 3 disks and 3 towers ...
*/
void moveDisk(char from, char to) {
	
	disk fDiskPos = getTopDiskPosition(from);
	disk tDiskPos = getTopDiskPosition(to);
	
	//cout << from << "(" << fDiskPos << ") -> " << to << "(" << tDiskPos << ")" << endl;

	// if we have a disk to move ...
	if (fDiskPos != NULL) {
		
		int t1 = getTowerPositionByName(from);
		int t2 = getTowerPositionByName(to);
		tDiskPos = tDiskPos == NULL ? 0 : tDiskPos + 1; // first free position in tower (@TODO: simplify usage?)

		//cout << "moveDisk: Hanoi[" << t1 << "].disks[" << fDiskPos << "]  vers  Hanoi[" << t2 << "].disks[" << tDiskPos << "]" << endl;

		// copy to destination
		Hanoi[t2].disks[tDiskPos] = Hanoi[t1].disks[fDiskPos];
		// delete original disk
		Hanoi[t1].disks[fDiskPos] = NULL;
	}
}

/*
@param	char	towerName		example : 'A', 'B' ou 'C'
@return disk					position from 0 of the highest disk in the tower, or NULL if no disk ...
*/
disk getTopDiskPosition(char towerName) {
	int i = getTowerPositionByName(towerName);
	for (int j = 0; j < MAXDISKS; j++) {
		if (Hanoi[i].disks[j] == NULL) { // no more disk above (presumably) ...
			return j - 1 >= 0 ? j - 1 : NULL; // NULL or max disk position in the tower (from 0)
		}
	}
	return MAXDISKS - 1; // max reached, no empty space
}

int getTowerPositionByName(char towerName) {
	for (int i = 0; i < N; i++) {
		if (Hanoi[i].name == towerName)
			return i;
	}
	return NULL; // unavailable tower ...			@TODO: use exceptions ?...
}
