#include <iostream>
#include <iterator>
#include <algorithm>
#include <array>

template<class RandomIt>
RandomIt partition(RandomIt first, RandomIt last) {
	if (std::distance(first,last) <= 1) {
		return first;
	}
	
	auto pivot = std::prev(last);
	auto mid = first;
	std::advance(mid, std::distance(first,last)/2);
	
	if (*pivot > *first && *pivot > *mid) {
		if (*first > *mid)
			pivot = first;
		else
			pivot = mid;
	}
	else if (*pivot < *first && *pivot < *mid) {
		if (*first < *mid)
			pivot = first;
		else
			pivot = mid;
	}
	
	std::swap(*first, *pivot);
	
	auto i=std::next(first), j = std::prev(last);
	while ( i <= j ) {
		while(i < last && *i <= *first) ++i;
		while(*j > *first) --j;
		if( i < j )
			std::swap( *(i++), *(j--) );
	}
	std::swap( *j, *first );
	return j;
}

template<class RandomIt>
void quickSort(RandomIt first, RandomIt last) {
	auto part = partition(first, last);
	if (part > first) quickSort(first, part);
	if (part != last) quickSort(std::next(part), last);
}

int main() {
	std::array<int, 7> a = {0, 3, -2, -5, 1, 10, 4};
	
	quickSort(a.begin(), a.end());
	
	std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
	
	return 0;
}