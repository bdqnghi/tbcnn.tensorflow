



#ifndef MOVATICA_MERGE_SORT_H
#define MOVATICA_MERGE_SORT_H

#include <algorithm> 
#include <iterator> 

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

} 

#endif 
