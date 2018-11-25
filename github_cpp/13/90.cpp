#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<time.h>
using namespace std;

double bubblesort(int n)
{
	clock_t start, finish;
	double duration;
	int *nums = new int[n];
	srand((int)time(NULL));
	for (int i=0; i<n; i++)
	{
		nums[i] = rand()%20001;
	}
	int swap = 0;
	start=clock();
	for (int i=0; i<n-1; i++)
	{
		for(int j=0;j<n-1-i;j++)
		{
			if (nums[j]>nums[j+1]) 
				{
			  	swap = nums[j];
			  	nums[j] = nums[j+1];
		      nums[j+1] = swap;
				}
		}
	}
	finish=clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
 	delete[] nums;
 	return duration;
}

void main()
{
	ofstream outfile;
	outfile.open("file.csv");
	if (outfile.is_open()) 
	{
			for (int i=1; i<200; i++)
			{
			int n = i*100;
			outfile<<n<<","<<bubblesort(n)<<endl;
			}
			outfile.close();
	}
	else 
	{
			outfile.close();
	}
		cout<<"�����ϣ�"<<endl; 	
}