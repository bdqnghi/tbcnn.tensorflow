//Randall Phillips
//COP4531
//Extra Credit Assignment 5

#include<iostream>
#include<vector>
#include<time.h>
#include<stdlib.h>

using namespace std;


void bubbleSort(int num, int array[]);
void biDirectionalBubbleSort(int num, int array[]);
void bitonicSort(int m, int n);
void sortdown(int m, int n);
void mergeup(int m, int n);
void mergedown(int m, int n);

//global for bitonic array
int *bitonic;

int main()
{

	int *array = new int[10];
	int time;

	for(int i = 0; i < 10; i++)
	{
		array[i] = rand() % 10;
	}
	time = clock();	
	bubbleSort(10, array);
	cout << "Time for bubble sort on 10: " << clock() - time << endl; 
	delete [] array;

	array = new int[50];
	for(int i = 0; i < 50; i++)
	{
		array[i] = rand() % 50;
	}
	time = clock();	
	bubbleSort(50, array);
	cout << "Time for bubble sort on 50: " << clock() - time << endl; 
	delete [] array;

	array = new int[100];
	for(int i = 0; i < 10; i++)
	{
		array[i] = rand() % 100;
	}
	time = clock();	
	bubbleSort(100, array);
	cout << "Time for bubble sort on 100: " << clock() - time << endl; 
	delete [] array;

	array = new int[500];
	for(int i = 0; i < 500; i++)
	{
		array[i] = rand() % 500;
	}
	time = clock();	
	bubbleSort(500, array);
	cout << "Time for bubble sort on 500: " << clock() - time << endl; 
	delete [] array;
	
	array = new int[1000];
	for(int i = 0; i < 1000; i++)
	{
		array[i] = rand() % 1000;
	}
	time = clock();	
	bubbleSort(1000, array);
	cout << "Time for bubble sort on 1000: " << clock() - time << endl; 
	delete [] array;

	array = new int[5000];
	for(int i = 0; i < 5000; i++)
	{
		array[i] = rand() % 5000;
	}
	time = clock();	
	bubbleSort(5000, array);
	cout << "Time for bubble sort on 5000: " << clock() - time << endl; 
	delete [] array;

	array = new int[10000];
	for(int i = 0; i < 10000; i++)
	{
		array[i] = rand() % 10000;
	}
	time = clock();	
	bubbleSort(10000, array);
	cout << "Time for bubble sort on 10000: " << clock() - time << endl; 
	delete [] array;

	array = new int[50000];
	for(int i = 0; i < 50000; i++)
	{
		array[i] = rand() % 50000;
	}
	time = clock();	
	bubbleSort(50000, array);
	cout << "Time for bubble sort on 50000: " << clock() - time << endl; 
	delete [] array;

	array = new int[100000];
	for(int i = 0; i < 10; i++)
	{
		array[i] = rand() % 100000;
	}
	time = clock();	
	bubbleSort(100000, array);
	cout << "Time for bubble sort on 100000: " << clock() - time << endl; 
	delete [] array;

	array = new int[500000];
	for(int i = 0; i < 500000; i++)
	{
		array[i] = rand() % 500000;
	}
	time = clock();	
	bubbleSort(500000, array);
	cout << "Time for bubble sort on 500000: " << clock() - time << endl; 
	delete [] array;

	array = new int[1000000];
	for(int i = 0; i < 1000000; i++)
	{
		array[i] = rand() % 1000000;
	}
	time = clock();	
	bubbleSort(1000000, array);
	cout << "Time for bubble sort on 1000000: " << clock() - time << endl; 
	delete [] array;


	array = new int[10];
	for(int i = 0; i < 10; i++)
	{
		array[i] = rand() % 10;
	}
	time = clock();	
	biDirectionalBubbleSort(10, array);
	cout << "Time for bi directional bubble sort on 10: " << clock() - time << endl; 
	delete [] array;

	array = new int[50];
	for(int i = 0; i < 50; i++)
	{
		array[i] = rand() % 50;
	}
	time = clock();	
	biDirectionalBubbleSort(50, array);
	cout << "Time for bi directional bubble sort on 50: " << clock() - time << endl; 
	delete [] array;

	array = new int[100];
	for(int i = 0; i < 100; i++)
	{
		array[i] = rand() % 100;
	}
	time = clock();	
	biDirectionalBubbleSort(100, array);
	cout << "Time for bi directional bubble sort on 100: " << clock() - time << endl; 
	delete [] array;

	array = new int[500];
	for(int i = 0; i < 500; i++)
	{
		array[i] = rand() % 500;
	}
	time = clock();	
	biDirectionalBubbleSort(500, array);
	cout << "Time for bi directional bubble sort on 500: " << clock() - time << endl; 
	delete [] array;

	array = new int[1000];
	for(int i = 0; i < 1000; i++)
	{
		array[i] = rand() % 1000;
	}
	time = clock();	
	biDirectionalBubbleSort(1000, array);
	cout << "Time for bi directional bubble sort on 1000: " << clock() - time << endl; 
	delete [] array;

	array = new int[5000];
	for(int i = 0; i < 5000; i++)
	{
		array[i] = rand() % 5000;
	}
	time = clock();	
	biDirectionalBubbleSort(5000, array);
	cout << "Time for bi directional bubble sort on 5000: " << clock() - time << endl; 
	delete [] array;

	array = new int[10000];
	for(int i = 0; i < 10000; i++)
	{
		array[i] = rand() % 10000;
	}
	time = clock();	
	biDirectionalBubbleSort(10000, array);
	cout << "Time for bi directional bubble sort on 10000: " << clock() - time << endl; 
	delete [] array;

	array = new int[50000];
	for(int i = 0; i < 50000; i++)
	{
		array[i] = rand() % 50000;
	}
	time = clock();	
	biDirectionalBubbleSort(50000, array);
	cout << "Time for bi directional bubble sort on 50000: " << clock() - time << endl; 
	delete [] array;

	array = new int[100000];
	for(int i = 0; i < 100000; i++)
	{
		array[i] = rand() % 100000;
	}
	time = clock();	
	biDirectionalBubbleSort(100000, array);
	cout << "Time for bi directional bubble sort on 100000: " << clock() - time << endl; 
	delete [] array;

	array = new int[500000];
	for(int i = 0; i < 500000; i++)
	{
		array[i] = rand() % 500000;
	}
	time = clock();	
	biDirectionalBubbleSort(500000, array);
	cout << "Time for bi directional bubble sort on 500000: " << clock() - time << endl; 
	delete [] array;

	array = new int[1000000];
	for(int i = 0; i < 1000000; i++)
	{
		array[i] = rand() % 1000000;
	}
	time = clock();	
	biDirectionalBubbleSort(1000000, array);
	cout << "Time for bi directional bubble sort on 1000000: " << clock() - time << endl; 
	delete [] array;

	bitonic = new int[16];
	for(int i = 0; i < 16; i++)
	{
		bitonic[i] = rand() % 16;
	}
	time = clock();	
	bitonicSort(0, 16);
	cout << "Time for bitonic bubble sort on 16: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[32];
	for(int i = 0; i < 32; i++)
	{
		bitonic[i] = rand() % 32;
	}
	time = clock();	
	bitonicSort(0, 32);
	cout << "Time for bitonic bubble sort on 32: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[64];
	for(int i = 0; i < 64; i++)
	{
		bitonic[i] = rand() % 64;
	}
	time = clock();	
	bitonicSort(0, 64);
	cout << "Time for bitonic bubble sort on 64: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[128];
	for(int i = 0; i < 128; i++)
	{
		bitonic[i] = rand() % 128;
	}
	time = clock();	
	bitonicSort(0, 128);
	cout << "Time for bitonic bubble sort on 128: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[256];
	for(int i = 0; i < 256; i++)
	{
		bitonic[i] = rand() % 256;
	}
	time = clock();	
	bitonicSort(0, 256);
	cout << "Time for bitonic bubble sort on 256: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[512];
	for(int i = 0; i < 512; i++)
	{
		bitonic[i] = rand() % 512;
	}
	time = clock();	
	bitonicSort(0, 512);
	cout << "Time for bitonic bubble sort on 512: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[1024];
	for(int i = 0; i < 1024; i++)
	{
		bitonic[i] = rand() % 1024;
	}
	time = clock();	
	bitonicSort(0, 1024);
	cout << "Time for bitonic bubble sort on 1024: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[2048];
	for(int i = 0; i < 2048; i++)
	{
		bitonic[i] = rand() % 2048;
	}
	time = clock();	
	bitonicSort(0, 2048);
	cout << "Time for bitonic bubble sort on 2048: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[4096];
	for(int i = 0; i < 4096; i++)
	{
		bitonic[i] = rand() % 4096;
	}
	time = clock();	
	bitonicSort(0, 4096);
	cout << "Time for bitonic bubble sort on 4096: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[8192];
	for(int i = 0; i < 8192; i++)
	{
		bitonic[i] = rand() % 8192;
	}
	time = clock();	
	bitonicSort(0, 8192);
	cout << "Time for bitonic bubble sort on 8192: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[16384];
	for(int i = 0; i < 16384; i++)
	{
		bitonic[i] = rand() % 16384;
	}
	time = clock();	
	bitonicSort(0, 16384);
	cout << "Time for bitonic bubble sort on 16384: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[32768];
	for(int i = 0; i < 32768; i++)
	{
		bitonic[i] = rand() % 32768;
	}
	time = clock();	
	bitonicSort(0, 32768);
	cout << "Time for bitonic bubble sort on 32768: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[65536];
	for(int i = 0; i < 65536; i++)
	{
		bitonic[i] = rand() % 65536;
	}
	time = clock();	
	bitonicSort(0, 65536);
	cout << "Time for bitonic bubble sort on 65536: " << clock() - time << endl; 
	delete [] bitonic;

	bitonic = new int[131072];
	for(int i = 0; i < 131072; i++)
	{
		bitonic[i] = rand() % 131072;
	}
	time = clock();	
	bitonicSort(0, 131072);
	cout << "Time for bitonic bubble sort on 131072: " << clock() - time << endl; 
	delete [] bitonic;



return 0;
}


void bubbleSort(int num, int array[])
{

	for(int i = num; i > 0; i--)
	{
		for(int j = 0; j < i; j++)
		{
			if(array[j] > array[j + 1])
			{
				int temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
		}
	}


}



void biDirectionalBubbleSort(int num, int array[])
{

	bool flag = false;
	int begin = -1;
	int end = num - 1;

	if(array[0] > array[num - 1])
	{
		int temp = array[0];
		array[0] = array[num - 1];
		array[num - 1] = temp;
	}
	



	do
	{
		flag = false;
		begin++;
		for(int i = begin; i < end; i++)
		{
			if(array[i] > array[i + 1])
			{
				int temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				flag = true;
			}
		}
		
		if(!flag)
		{
			break;
		}
	
		flag = false;
		
		end = end - 1;

		for(int i = end; i > begin; i--)
		{
			if(array[i] > array[i + 1])
			{
				int temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				flag = true;
			}
		}
	}while(flag);

}


void bitonicSort(int m, int n)
{
	if(n == 1)
	{
		return;
	}

	bitonicSort(m, (n / 2));
	sortdown(m + (n / 2),(n / 2));
	mergeup(m, (n / 2));
  
}


void sortdown(int m, int n)
{
	if(n == 1)
	{
		return;
	}

	bitonicSort(m, (n / 2));
	sortdown(m + (n / 2), (n / 2));
	mergedown(m, (n / 2));
}

void mergeup(int m, int n)
{
	if(n == 0)
	{
		return;
	}
	
	int i;
	for(i = 0; i < n; i++)
	{
		if(bitonic[m + i] > bitonic[m + i + n])
		{
			int temp;
			temp = bitonic[m + i];
			bitonic[m + i] = bitonic[m + i + n];
			bitonic[m + i + n] = temp;
		}
	}

	mergeup(m, (n / 2));
	mergeup(m + n, (n / 2));
}

void mergedown(int m, int n)
{
	if(n == 0)
		return;
	
	int i;
	for(i = 0; i < n; i++)
	{
		if(bitonic[m + i] < bitonic[m + i + n])
		{
			int temp;
			temp = bitonic[m + i];
			bitonic[m + i] = bitonic[m + i + n];
			bitonic[m + i + n] = temp;
		}
	}

	mergedown(m, (n / 2));
	mergedown(m + n, (n / 2));
}

 
