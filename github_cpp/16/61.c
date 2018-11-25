
#include "sorting.hh"

template void Sortings<int,intintCompare>::shell(int *, unsigned int);
template void Sortings<char*,strstrCompare>::shell(char**, unsigned int);

template <class Elem, class Comp>


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
