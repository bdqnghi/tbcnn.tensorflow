/*
	selection_sort.h

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
	of the selection sort algorithm.

	Selection sort is probably the most simple comparision-based
	sorting algorithm. Beeing even slower than the otherwise
	comparable insertion sort algorithm, it is of mostly academic use.

	Complexity:
		O( N^2 ) comparisions
		O( 1 ) auxiliary space

	Further reading:
		http://en.wikipedia.org/wiki/Selection_sort

	STL reference:
		http://en.cppreference.com/w/cpp/concept/ForwardIterator
		http://en.cppreference.com/w/cpp/algorithm/iter_swap
		http://en.cppreference.com/w/cpp/algorithm/min_element
*/

#ifndef MOVATICA_SELECTION_SORT_H
#define MOVATICA_SELECTION_SORT_H

#include <algorithm> // std::iter_swap, std::min_element

namespace movatica {

template< class ForwardIt >
void selection_sort( ForwardIt first, ForwardIt last )
{
	while( first != last )
	{
		std::iter_swap( first, std::min_element( first, last ));
		++first;
	}
}

template< class ForwardIt, class Compare >
void selection_sort( ForwardIt first, ForwardIt last, Compare comp )
{
	while( first != last )
	{
		std::iter_swap( first, std::min_element( first, last, comp ));
		++first;
	}
}

} // namespace movatica

#endif // MOVATICA_SELECTION_SORT_H
