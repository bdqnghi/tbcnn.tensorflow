#include "BubbleSort.h"

BubbleSort* BubbleSort::_instance = NULL;

BubbleSort::BubbleSort()
{
	;
}

BubbleSort* BubbleSort::Instance()
{
	if (_instance == 0) 
	{ 
		_instance = new BubbleSort(); 
	}
	return _instance;
}

int BubbleSort::Floating(int Array[], int ArraySize)
{
	for(int i = 0; i < ArraySize; i++)
	{
		for(int j = i + 1; j < ArraySize; j++)
		{
			if(Array[i] > Array[j])
			{
				GeneralModule::Instance()->Swap(Array[i], Array[j]);
			}
		}
	}
	return 0;
}

int BubbleSort::Diving(int Array[], int ArraySize)
{
	bool swapped = false;
	int indexOfLastUnsortedElement = ArraySize - 1;
	
	while(indexOfLastUnsortedElement >= 0)
	{
		do
		{
			swapped = false;
			for(int i = 0; i < indexOfLastUnsortedElement; i++)
			{
				if(Array[i] > Array[i+1])
				{
					GeneralModule::Instance()->Swap(Array[i], Array[i+1]);
					swapped = true;
				}
			}	
		}while(swapped);
		indexOfLastUnsortedElement--;
	}
	return 0;
}
