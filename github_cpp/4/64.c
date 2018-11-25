



#include <iostream>
#include <chrono> 

using namespace std;

const int MAXDISKS = 10;
const int NBTOWERS = 3;
typedef int disk;

#define NULL -1 
#define N sizeof(Hanoi[0].disks) / sizeof(Hanoi[0].disks[0]) 


void hanoi(disk, char, char, char);
void moveDisk(char, char);
disk getTopDiskPosition(char);
int getTowerPositionByName(char);
void print_tower(char*, int);


typedef struct { char name; disk disks[MAXDISKS]; } tower;
typedef tower HanoiGame[NBTOWERS]; 
HanoiGame Hanoi = {
	{ 'A', { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 } },
	{ 'B', { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } },
	{ 'C', { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } }
};


int kkk = 0; 


int main()
{
	print_tower("(before) 1st tower : ", 0);
	print_tower("(before) 2nd tower : ", 1);
	print_tower("(before) 3rd tower : ", 2);
	
	clock_t t;
	double duration;
	t = clock();

	hanoi(N,  Hanoi[0].name,  Hanoi[2].name,  Hanoi[1].name);
	
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
		kkk++; 
		hanoi(n - 1, fromPos, throughPos, toPos);
		moveDisk(fromPos, toPos);
		hanoi(n - 1, throughPos, toPos, fromPos);
	}
}

void print_tower(char* message, int position) { 
	for (int i = 0; i < MAXDISKS; i++) {
		cout << Hanoi[position].disks[i] << " ** ";
	}
	cout << endl;
}


void moveDisk(char from, char to) {
	
	disk fDiskPos = getTopDiskPosition(from);
	disk tDiskPos = getTopDiskPosition(to);
	
	

	
	if (fDiskPos != NULL) {
		
		int t1 = getTowerPositionByName(from);
		int t2 = getTowerPositionByName(to);
		tDiskPos = tDiskPos == NULL ? 0 : tDiskPos + 1; 

		

		
		Hanoi[t2].disks[tDiskPos] = Hanoi[t1].disks[fDiskPos];
		
		Hanoi[t1].disks[fDiskPos] = NULL;
	}
}


disk getTopDiskPosition(char towerName) {
	int i = getTowerPositionByName(towerName);
	for (int j = 0; j < MAXDISKS; j++) {
		if (Hanoi[i].disks[j] == NULL) { 
			return j - 1 >= 0 ? j - 1 : NULL; 
		}
	}
	return MAXDISKS - 1; 
}

int getTowerPositionByName(char towerName) {
	for (int i = 0; i < N; i++) {
		if (Hanoi[i].name == towerName)
			return i;
	}
	return NULL; 
}
