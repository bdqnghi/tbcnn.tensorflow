//	DDCPP/standard/bits/DD_quick_sort.hpp
#ifndef DD_QUICK_SORT_HPP_INCLUDED_
#	define DD_QUICK_SORT_HPP_INCLUDED_ 1



#	include "DD_IsFreeAccessIterator.hpp"
#	include "DD_next.hpp"
#	include "DD_pivot_partition.hpp"



DD_DETAIL_BEGIN_
template <ValidityType is_free_access_iterator_c_>
struct QuickSort_ {
	template <typename BidirectionalIteratorT__>
	static ProcessType quick_sort(
		BidirectionalIteratorT__ begin___,
		BidirectionalIteratorT__ end___
	) {
		while (begin___ != end___) {
			BidirectionalIteratorT__ pivot___(::DD::unguarded_pivot_partition(begin___, end___));
			if (pivot___ != end___) {
				quick_sort(::DD::next(pivot___), end___);
			}
			end___ = pivot___;
		}
	}

	template <typename BidirectionalIteratorT__, typename BinaryPredicateT_>
	static ProcessType quick_sort(
		BidirectionalIteratorT__ begin___,
		BidirectionalIteratorT__ end___,
		BinaryPredicateT_ less___
	) {
		while (begin___ != end___) {
			BidirectionalIteratorT__ pivot___(::DD::unguarded_pivot_partition(begin___, end___, less___));
			if (pivot___ != end___) {
				quick_sort(::DD::next(pivot___), end___, less___);
			}
			end___ = pivot___;
		}
	}


};



template <>
struct QuickSort_<true> {
	template <typename FreeAccessIteratorT__>
	static ProcessType quick_sort(
		FreeAccessIteratorT__ begin___,
		FreeAccessIteratorT__ end___
	) {
		while (begin___ < end___) {
			FreeAccessIteratorT__ pivot___(::DD::unguarded_pivot_partition(begin___, end___));
			quick_sort(::DD::next(pivot___), end___);
			end___ = pivot___;
		}
	}

	template <typename FreeAccessIteratorT__, typename BinaryPredicateT__>
	static ProcessType quick_sort(
		FreeAccessIteratorT__ begin___,
		FreeAccessIteratorT__ end___,
		BinaryPredicateT__ less___
	) {
		while (begin___ < end___) {
			FreeAccessIteratorT__ pivot___(::DD::unguarded_pivot_partition(begin___, end___, less___));
			quick_sort(::DD::next(pivot___), end___, less___);
			end___ = pivot___;
		}
	}


};



template <typename BidirectionalIteratorT_>
inline ProcessType quick_sort(
	BidirectionalIteratorT_ begin__,
	BidirectionalIteratorT_ end__
) DD_NOEXCEPT_AS(QuickSort_<IsFreeAccessIterator<BidirectionalIteratorT_>::value>::quick_sort(begin__, end__)) {
	QuickSort_<IsFreeAccessIterator<BidirectionalIteratorT_>::value>::quick_sort(begin__, end__);
}

template <typename BidirectionalIteratorT_, typename BinaryPredicateT_>
inline ProcessType quick_sort(
	BidirectionalIteratorT_ begin__,
	BidirectionalIteratorT_ end__,
	BinaryPredicateT_ less__
) DD_NOEXCEPT_AS(QuickSort_<IsFreeAccessIterator<BidirectionalIteratorT_>::value>::quick_sort(begin__ DD_COMMA end__ DD_COMMA less__)) {
	QuickSort_<IsFreeAccessIterator<BidirectionalIteratorT_>::value>::quick_sort(begin__, end__, less__);
}

template <typename BidirectionalRangeT_>
inline ProcessType quick_sort(
	BidirectionalRangeT_& range__
) DD_NOEXCEPT_AS(::DD::detail_::quick_sort(DD_SPLIT_RANGE(range__))) {
	::DD::detail_::quick_sort(DD_SPLIT_RANGE(range__));
}

template <typename BidirectionalRangeT_, typename BinaryPredicateT_>
inline ProcessType quick_sort(
	BidirectionalRangeT_& range__,
	BinaryPredicateT_ less__
) DD_NOEXCEPT_AS(::DD::detail_::quick_sort(DD_SPLIT_RANGE(range__) DD_COMMA less__)) {
	::DD::detail_::quick_sort(DD_SPLIT_RANGE(range__), less__);
}



DD_DETAIL_END_



DD_BEGIN_
using detail_::quick_sort;



DD_END_



#endif
