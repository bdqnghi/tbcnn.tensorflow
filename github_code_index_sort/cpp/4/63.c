/* vim: set ts=8 sw=8 cindent: **************************************************
*										*
*  Copyright (c) 2007-2013, Alexander Adam					*
*										*
*  All rights reserved.								*
*										*
*  Redistribution and use in source and binary forms, with or without		*
*  modification, are permitted provided that the following conditions are met:	*
*										*
*	-	Redistributions of source code must retain the above copyright	*
*		notice, this list of conditions and the following disclaimer.	*
*	-	Redistributions in binary form must reproduce the above		*
*		copyright notice, this list of conditions and the following	*
*		disclaimer in the documentation and/or other materials provided	*
*		with the distribution.						*
*	-	The names of its contributors may be used to endorse or promote	*
*		products derived from this software without specific prior	*
*		written permission.						*
*										*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS		*
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT		*
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR	*
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER	*
*  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,	*
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,		*
*  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR		*
*  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF	*
*  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING		*
*  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS		*
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.			*
*										*
********************************************************************************/

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
/*
int HeapSort::leafsearch( const int x, const int len)
{
	int j = x;

	while (2*j+1 < len)
	{
		if (feld[ 2*j+1] < feld[ 2*j+2])
			j = 2*j+2;
		else
			j = 2*j+1;
	}
	
	if (2*j+1 == len)
		j = len;

	return j;
}

int HeapSort::bottomupsearch( const int i, int j)
{
	while (feld[ i] < feld[ j])
		j /= 2;

	return j;
}

void HeapSort::interchange( const int i, const int l)
{
	int x = feld[ i];

	for (int k = 0; k < )

	feld[ l] = x;
} */
