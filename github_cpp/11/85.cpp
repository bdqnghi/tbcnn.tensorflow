/*
	heap_sort.h

	(c) 2015 by David 'movatica' Weiß, david+code@movatica.com

	This file is part of cpp-algorithms.

	cpp-algorithms is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-algorithms is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-algorithms. If not, see <http://www.gnu.org/licenses/>
*/

/*
	This file provides a generic STL-based implementation
	of the heapsort algorithm.
	
	Heapsort is comparable in speed to quicksort, but is
	stable and features a better worstcase complexity.
	Like all efficient sorting algorithms, it relies on a
	random accessible datastructure like std::vector.
	As the STL already provides the necessary functionality
	with the algorithms header, the "implementation" is trivial.

	Complexity:
		O( N*log(N) ) comparisions
		O( 1 ) auxiliary space

	Further reading:
		http://en.wikipedia.org/wiki/Heapsort

	STL reference:
		http://en.cppreference.com/w/cpp/concept/RandomAccessIterator
		http://en.cppreference.com/w/cpp/algorithm/make_heap
		http://en.cppreference.com/w/cpp/algorithm/sort_heap
*/

#ifndef MOVATICA_HEAP_SORT_H
#define MOVATICA_HEAP_SORT_H

#include <algorithm> // std::make_heap, std::sort_heap

namespace movatica {

template< class RandomIt >
void heap_sort( RandomIt first, RandomIt last )
{
	std::make_heap( first, last );
	std::sort_heap( first, last );
}

template< class RandomIt, class Compare >
void heap_sort( RandomIt first, RandomIt last, Compare comp )
{
	std::make_heap( first, last, comp );
	std::sort_heap( first, last, comp );
}

} // namespace movatica

#endif // MOVATICA_HEAP_SORT_H
