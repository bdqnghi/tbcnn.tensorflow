#include"bubblesort.h"


void bubble_sort(int list[], int size) 
{

	int index = 0, passes = 0, temp = 0; 

	for(passes = 1; passes < size  ;passes++)
	{
		for(index = 0; index < size - passes; index++)
		{//trying to do ascending order 

			if(list[index] > list[index+1] ) //swap
			{
				temp = list[index] ; 
				list[index] = list[index+1];
				list[index+1] = temp ; 
			}


		}


	}
}


void print_list(int list[], int size) 
{
	int index = 0 ; 
	while( index < size) 
	{
		printf("list[%d]: %d \n", index, list[index]); 
		index++; 
	}
}