#include <vector>
#include <iostream>
#include <assert.h>

using std::vector;
using std::cout;
using std::cin;

void selectionsort(vector<double>& array)
{
    // If no elements to sort, RETURN
    if(array.empty())
	return;
    
    double temp = 0.0;
    int minElement = 0;
    for(int i = 0; i < array.size() - 1; ++i)
    {
	minElement = i;
	for(int j = i; j < array.size(); ++j)
	    if(array[j] < array[minElement])
		minElement = j;
	
	// swap the current ith element with the min element
	if(minElement != i)
	{
	    temp = array[minElement];
	    array[minElement] = array[i];
	    array[i] = temp;
	}
    }
}

int main()
{
    int number = 0;
    cout<<"Please Enter number of elements to sort:";
    cin>>number;
    
    if(number <= 0)
    {
	cout<<"No Elements to sort\n";
	return -1;
    }

    vector<double> array(number);
    for(size_t i = 0; i < array.size(); ++i)
    {
	cout<<"Enter number "<<(i + 1)<<" :";
	cin>>array[i];
    }

    cout<<"Calling Selection Sort..\n";
    selectionsort(array);

    cout<<"Sorted array is:";
    for(size_t i = 0; i < array.size(); ++i)
	cout<<array[i]<< " ";
    cout<<"\n";
}
