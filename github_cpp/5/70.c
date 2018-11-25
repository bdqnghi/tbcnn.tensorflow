#ifndef InsertionSort_CPP
#define InsertionSort_CPP

#include <vector>

namespace InsertionSort
{
	template <class T> void insertionSort( std::vector<T> &items )
	{//Main Insertion Sort function. Sorts the vector items in-place.
		for( unsigned int j = 1; j < items.size(); j++ )
		{//Go from the second item to the last.
			T key = items.at(j);
			int i = j-1;
			for( i = j-1; (i >= 0) && (items.at(i) > key); i-- )
			{//While the current item is less than the key and haven't run out of items to check, keep moving the key forward.
				items.at(i+1) = items.at(i);
			}
			items.at(i+1) = key;
		}
	}
}

#endif /* InsertionSort_CPP */
