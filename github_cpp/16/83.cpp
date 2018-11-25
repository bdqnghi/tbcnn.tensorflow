#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "ShellSort.h"

	void seed();

using namespace std;

    ShellSort::ShellSort()
    {
      
    }
    ShellSort::ShellSort(int x)
    {
    	size = x;
    	range = 3*x;
    	seed();
    	list = new int[size];
    	fill();
    }
    ShellSort::~ShellSort()
    {
		
    }
    void ShellSort::fill()
    {
    	for(int i = 0;i < size;i++)
    	{
    		list[i] = rand()%(2*range+1) - range;
    	}
    }
    void ShellSort::sort(int inc)
    {
    	int i, j, tmp;
		for(i = inc;i<size;i++)
		{
			tmp = list[i];
			for(j = i - inc; j>= 0 && list[j] > tmp; j-=inc)
			{
				list[j+inc] = list[j];
				list[j] = tmp;
			}
		}
    }
    void ShellSort::sortRec(int inc)
    {
    	for(int i = 0;i+inc < size;i++)
    	{
    		compare(inc,i);
    	}
    }
    void ShellSort::compare(int inc,int i)
    {   	
    	
		if(i+inc < size && list[i] > list[i+inc])
		{
			swap(i,i+inc);
			compare(inc,i+inc);
		}
		compareRev(inc,i);
	}
	void ShellSort::compareRev(int inc,int i)
	{
		if(i-inc >= 0 && list[i] < list[i-inc])
		{
			swap(i,i-inc);
			compareRev(inc,i-inc);
		}
	}
    void ShellSort::swap(int x,int y)
    {
    	
    	int tmp = list[x];
    	list[x] = list[y];
    	list[y] = tmp;
    }
    void ShellSort::print()
    {
    	cout << endl;
    	for(int i = 0;i<size;i++)
    	{
    		cout << list[i] << endl;
    	}
    	cout << endl;
    }
    void ShellSort::check()
    {
    	for(int i = 0;i+1<size;i++)
    	{
    		if(list[i]>list[i+1])
    		{
    			cout << "broke" << endl;
    			return;
    		}
    	}
    	cout << "good" << endl;
    }
    void seed()
    {
    	time_t timer;
    	srand(time(&timer));
    }
