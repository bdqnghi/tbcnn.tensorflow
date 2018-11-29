/*
	merge_sort.h

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
	of the merge sort algorithm.
	
	Merge sort is a fast stable sort with optimal worst-case complexity.
	This implementation uses the inplace merge routine provided by the STL.
	It is implemented iterative in a bottom-up approach.
	While the comparision complexities hold for all bidirectional iterators,
	logarithmic element access requires random access.

	Note that std::stable_sort normally implements some variant of merge sort.
	
	Complexity:
		O( N*log(N) ) comparisions
		O( 1 ) auxiliary space

	Further reading:
		http://en.wikipedia.org/wiki/Merge_sort

	STL reference:
		http://en.cppreference.com/w/cpp/concept/BidirectionalIterator
		http://en.cppreference.com/w/cpp/algorithm/inplace_merge
		http://en.cppreference.com/w/cpp/algorithm/min
		http://en.cppreference.com/w/cpp/iterator/distance
		http://en.cppreference.com/w/cpp/iterator/iterator_traits
		http://en.cppreference.com/w/cpp/iterator/next
*/

#ifndef MOVATICA_MERGE_SORT_H
#define MOVATICA_MERGE_SORT_H

#include <algorithm> // std::inplace_merge, std::min
#include <iterator> // std::distance, std::iterator_traits, std::next

namespace movatica {

template< class BidirIt >
void merge_sort( BidirIt first, BidirIt last )
{
	using difference_type = typename std::iterator_traits<BidirIt>::difference_type;
	
	difference_type const max_width = std::distance( first, last );
	
	for( difference_type width = 1; width < max_width; width *= 2 )
	{
		BidirIt partial_first = first;
		difference_type const max_middle = max_width - width;
		
		for( difference_type i = 0; i < max_middle; i += 2*width )
		{
			BidirIt partial_middle = std::next( partial_first, width );
			BidirIt partial_back = std::next( partial_middle, std::min( width, max_middle - i ));
			
			std::inplace_merge( partial_first, partial_middle, partial_back );
			
			partial_first = partial_back;
		}
	}
}

template< class BidirIt, class Compare >
void merge_sort( BidirIt first, BidirIt last, Compare comp )
{
	using difference_type = typename std::iterator_traits<BidirIt>::difference_type;
	
	difference_type const max_width = std::distance( first, last );
	
	for( difference_type width = 1; width < max_width; width *= 2 )
	{
		BidirIt partial_first = first;
		difference_type const max_middle = max_width - width;
		
		for( difference_type i = 0; i < max_middle; i += 2*width )
		{
			BidirIt partial_middle = std::next( partial_first, width );
			BidirIt partial_back = std::next( partial_middle, std::min( width, max_middle - i ));
			
			std::inplace_merge( partial_first, partial_middle, partial_back, comp );
			
			partial_first = partial_back;
		}
	}
}

} // namespace movatica

#endif // MOVATICA_MERGE_SORT_H
