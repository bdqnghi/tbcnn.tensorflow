/*
 * shell.cpp
 * Contains the method that performs shell sort
 * Method calls the external method insert2()
 */
#include "sorting.hh"

template void Sortings<int,intintCompare>::shell(int *, unsigned int);
template void Sortings<char*,strstrCompare>::shell(char**, unsigned int);

template <class Elem, class Comp>

/*
 * Method to perform shell sort
 * Precondition: arr is not null, n is less than the length of arr
 * Postcondition: n elements in arr are sorted
 */
void Sortings<Elem, Comp>::shell(Elem *arr, unsigned int n)
{
	if(arr != NULL)
	{
		unsigned int incr, s;

		for(incr = n / 2; incr > THRESHOLD; incr = (incr / 2) + 1)
			for(s = 0; s < incr; s++)
				Sortings::insert2(arr, incr, n, s);

		Sortings::insert2(arr, 1, n, 0);
	}
}
