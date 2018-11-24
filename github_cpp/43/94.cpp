#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "windows.h"
#include "Bucket.cpp"

const int Num = 1000000;
Point array[Num];

int main()
{
	Bucket b(Num);
	string fileName("./dataset/dataset.txt");
	int time0, time1;

	time0 = GetTickCount();
	b.getData(fileName);
	time1 = GetTickCount();
	printf("Got all data!\nCost %.3f seconds.\n",(time1-time0)/1000.0);

	time0 = GetTickCount();
	b.sort(array);
	time1 = GetTickCount();
	printf("Sort array successfully!\nCost %.3f seconds.\n",(time1-time0)/1000.0);

	time0 = GetTickCount();
	freopen("dataout.txt","w",stdout);
	for (int i=0; i<Num; ++i)
	{
		array[i].show();
		printf("\n");
	}
	time1 = GetTickCount();
	printf("Cost %.3f seconds.\n",(time1-time0)/1000.0);

	return 0;
}