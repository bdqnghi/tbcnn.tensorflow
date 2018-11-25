
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

bool search(int[], int, int);

int main()
{
	srand(time(0));
	int nums[10];
	for(int i = 0;i<10;i++)
	{
		nums[i] = rand()%100 + 1;
	}
	cout<<"Array before sort"<<endl;
		for(int i = 0; i<10;i++)
			cout<<nums[i]<<" ";
		cout<<endl;

	
	for(int j=0; j<10; j++)
	{
		int index = j;
		for(int k=j; k<10; k++)
		{
			if(nums[index]>nums[k])
			{
				index = k;
			}
		}
		int temp = nums[j];
		nums[j] = nums[index];
		nums[index] = temp;
	}
	cout<<"Array after sort"<<endl;
	for(int i = 0; i<10;i++)
		cout<<nums[i]<<" ";
	cout<<endl;

	int value;
		cout<<"Enter a number between 1 and 100: "<<endl;
		cin>>value;

	if(search(nums, 10, value)== true)
	{
		cout<<"Value "<<value<<" was found\n";
	}
	else
	{
		cout<<"Value "<<value<<" was not found\n";
	}
}
bool search(int numbers[], int size, int value)
{
	
	
	bool found = false;
	int low = 0;
	int high = size - 1;
	int pos = 0;
	while(low <= high && !found)
	{
		pos = (low + high)/2;
		if(numbers[pos] == value)
		{
			found = true;
		}
		else if(numbers[pos] < value)
			{
				low = pos+1;
			}
			else
			{
				high = pos - 1;
			}
	}
	return found;
}

