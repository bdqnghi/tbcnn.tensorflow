// 30-TowerOfHanoi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
 
static int count = 0;

void towerOfHanoi(int n, char* source, char* dest, char* aux){
	if(n == 1){
		printf("%d Move Disk 1 from %s to %s\n",++count,source, dest);
		return;
	}
	towerOfHanoi(n-1, source, aux, dest);
	printf("%d Move Disk %d from %s to %s\n",++count, n, source, dest);
	towerOfHanoi(n-1, aux, dest, source);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nD;
	printf("Enter Number of Disks\n");
	scanf("%d",&nD);
	towerOfHanoi(nD, "Source", "Destination", "Auxillary");
	return 0;
}

