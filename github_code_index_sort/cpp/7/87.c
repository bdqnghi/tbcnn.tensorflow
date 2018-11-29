/* vim: set ts=8 sw=8 cindent: **************************************************
*										*
*  Copyright (c) 2012-2013, Alexander Adam					*
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

//#define SHELLSORT_DEBUG_OUT

#ifdef SHELLSORT_DEBUG_OUT
	#include <iostream>
#endif

#include <cmath>
#include <stdint.h>

#include "shellsort.h"

using namespace shellsort;

extern "C"
{
	EXPORT_API class bench::SortBase* create()
	{
		return dynamic_cast< class bench::SortBase*>(new class ShellSort());
	}

	EXPORT_API void destroy( class bench::SortBase* x)
	{
		delete dynamic_cast< class ShellSort*>( x);
	}
}

namespace {
	inline uint64_t int_pow( uint64_t x, int p)
	{
		switch (p)
		{
			case 0: return 1;
			case 1: return x;
			default: break;
		}

		int cp = 2;
		uint64_t res = x*x;

		while (cp << 1 < p )
		{
			cp <<= 1;
			res *= res;
		}

		return res * int_pow( x, p - cp);
	}
}

const char ShellSort::m_sort_name[] = "ShellSort";

ShellSort::ShellSort()
{}

ShellSort::~ShellSort()
{}

enum bench::SortBase::SpeedGrade ShellSort::speedGrade()
{
	return bench::SortBase::SLOW;
}

const char* ShellSort::name()
{
	return ShellSort::m_sort_name;
}

void ShellSort::pre( const bench::feld_t &x)
{
	bench::SortBase::pre( x);
	generate_sub_indices( x.size());
}

void ShellSort::sort()
{
	for (sub_ind_t k = this->sub_indices.size()-1; k >= 0 && k < this->sub_indices.size(); --k)
	{
		for (bench::feld_t::size_type i = 1; i < feld.size(); ++i)
		{
			insert( feld[ i], i, this->sub_indices[k]);
		}
	}
}

void ShellSort::insert( const bench::ele_t e, const bench::feld_t::size_type r, size_t period)
{
	bench::feld_t::size_type insert_pos = 0;
	// Einfuegeposition finden, mit binaerer Suche
	bench::feld_t::size_type gl = 0,
				 gr = r / period, // Index in der Subfolge
				 ai = r % period; // Index der Subfolge

	while ( gr-gl > 1 )
	{
		if (feld[ ai + (gr+gl)/2*period ] < e)
			gl = (gr+gl)/2 + 1;
		else
			gr = (gr+gl)/2;
	}

	if ( feld[ ai + gl * period] <= e )
		insert_pos = gr;
	else
		insert_pos = gl;

	// Elemente um eines nach rechts verschieben, ab Einfuegeposition
	for (bench::feld_t::size_type i = insert_pos; i < r/period; ++i)
	{
		feld[ ai +(i+1)*period] = feld[ ai + i*period];
	}

	feld[ ai + insert_pos * period] = e;
}

void ShellSort::generate_sub_indices( bench::feld_t::size_type s)
{
	bench::feld_t::size_type i = 1;

	while (1)
	{
		uint64_t next =	std::ceil((int_pow( 9, i) - int_pow( 4, i)) /
				(double)(5 * int_pow( 4, i-1) ));
		if ( next > s/2)
			break;

		this->sub_indices.push_back( next);
		++i;
	}

#ifdef SHELLSORT_DEBUG_OUT
	for (sub_ind_t i = 0; i < this->sub_indices.size(); ++i)
		std::cout << i << ": " << this->sub_indices[ i] << std::endl;
#endif
}
