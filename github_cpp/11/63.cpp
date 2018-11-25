

#include "heapsort.h"

using namespace heap;

extern "C"
{
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class HeapSort());
	}

	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class HeapSort*>( x);
	}
}

const char HeapSort::m_sort_name[] = "HeapSort";

HeapSort::HeapSort()
{}

HeapSort::~HeapSort()
{}

enum bench::SortBase::SpeedGrade HeapSort::speedGrade()
{
	return bench::SortBase::FAST;
}

const char* HeapSort::name()
{
	return HeapSort::m_sort_name;
}

void HeapSort::sort()
{
	bench::feld_t::size_type z = feld.size() - 1;
	
	for (bench::feld_t::size_type i = feld.size()/2 - 1; i < feld.size()/2 && i >= 0; i--)
		reheap( i, z);
	
	for (bench::feld_t::size_type i = 0; i < z; i++)
	{
		std::swap( feld[ 0], feld[ z-i]);
		reheap( 0, z-i-1);
	}
}

void HeapSort::post()
{}

void HeapSort::reheap( bench::feld_t::size_type x, const bench::feld_t::size_type len)
{
	unsigned short decision;

	while (2*x+1 <= len)
	{
		decision = 1;
		if ((2*x+2 <= len) && (feld[ 2*x+2] > feld[ 2*x+1]))
			decision = 2;
		
		if (feld[ x] < feld[ 2*x+decision])
		{
			std::swap( feld[ x], feld[ 2*x+decision]);
			x = 2*x+decision;
		}
		else
			break;
	}
}

