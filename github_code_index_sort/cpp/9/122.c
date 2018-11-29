#include "SelectionSort.h"

SelectionSort* SelectionSort::_instance = NULL;

SelectionSort::SelectionSort()
{
	;
}

SelectionSort* SelectionSort::Instance()
{
	if (_instance == 0) 
	{ 
		_instance = new SelectionSort(); 
	}
	return _instance;
}

int SelectionSort::Process(int Array[], int ArraySize)
{
	int numOfElements = ArraySize - 1;
	int firstUnsortedElement = 0;
	int currentMinimumVaule = 0;
	int currentMinimumPosition = 0;
	
	while(firstUnsortedElement < numOfElements)
	{
		currentMinimumVaule = Array[firstUnsortedElement];
		currentMinimumPosition = firstUnsortedElement;
		
		for(int i = firstUnsortedElement+1; i <= numOfElements; i++)
		{
			if(Array[i] < currentMinimumVaule)
			{
				currentMinimumVaule = Array[i];
				currentMinimumPosition = i;
			}
		}
		GeneralModule::Instance()->Swap(Array[currentMinimumPosition], Array[firstUnsortedElement]);
		firstUnsortedElement++;
	}
	return 0;
}
