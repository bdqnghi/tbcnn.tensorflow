//--------------------------------------------------------------------------//
/// Copyright (c) 2018 by Milos Tosic. All Rights Reserved.                ///
/// License: http://www.opensource.org/licenses/BSD-2-Clause               ///
//--------------------------------------------------------------------------//

#include <rbase_pch.h>

#include <string.h> // memset

namespace rtm {

#define RTM_RADIXSORT_BITS				11
#define RTM_RADIXSORT_HISTOGRAM_SIZE	(1 << RTM_RADIXSORT_BITS)
#define RTM_RADIXSORT_BIT_MASK			(RTM_RADIXSORT_HISTOGRAM_SIZE - 1)

void sortRadix(uint32_t* _keys, uint32_t* _tempKeys, uint32_t _size)
{
	uint16_t histogram[RTM_RADIXSORT_HISTOGRAM_SIZE];
	uint16_t shift = 0;
	for (uint32_t pass=0; pass<3; ++pass)
	{
		memset(histogram, 0, sizeof(uint16_t)*RTM_RADIXSORT_HISTOGRAM_SIZE);
		for (uint32_t i=0; i<_size; ++i)
		{
			uint32_t key = _keys[i];
			uint16_t index = (key>>shift)&RTM_RADIXSORT_BIT_MASK;
			++histogram[index];
		}

		uint16_t offset = 0;
		for (uint32_t i=0; i<RTM_RADIXSORT_HISTOGRAM_SIZE; ++i)
		{
			uint16_t count = histogram[i];
			histogram[i] = offset;
			offset += count;
		}

		for (uint32_t i=0; i<_size; ++i)
		{
			uint32_t key = _keys[i];
			uint16_t index = (key >> shift) & RTM_RADIXSORT_BIT_MASK;
			uint16_t dest = histogram[index]++;
			_tempKeys[dest] = key;
		}

		uint32_t* swapKeys = _tempKeys;
		_tempKeys = _keys;
		_keys = swapKeys;

		shift += RTM_RADIXSORT_BITS;
	}
}

void sortRadix64(uint64_t* _keys, uint64_t* _tempKeys, uint32_t _size)
{
	uint16_t histogram[RTM_RADIXSORT_HISTOGRAM_SIZE];
	uint16_t shift = 0;
	for (uint32_t pass=0; pass<6; ++pass)
	{
		memset(histogram, 0, sizeof(uint16_t)*RTM_RADIXSORT_HISTOGRAM_SIZE);
		for (uint32_t i=0; i<_size; ++i)
		{
			uint64_t key = _keys[i];
			uint16_t index = (key>>shift)&RTM_RADIXSORT_BIT_MASK;
			++histogram[index];
		}

		uint16_t offset = 0;
		for (uint32_t i=0; i<RTM_RADIXSORT_HISTOGRAM_SIZE; ++i)
		{
			uint16_t count = histogram[i];
			histogram[i] = offset;
			offset += count;
		}

		for (uint32_t i=0; i<_size; ++i)
		{
			uint64_t key = _keys[i];
			uint16_t index = (key >> shift) & RTM_RADIXSORT_BIT_MASK;
			uint16_t dest = histogram[index]++;
			_tempKeys[dest] = key;
		}

		uint64_t* swapKeys = _tempKeys;
		_tempKeys = _keys;
		_keys = swapKeys;

		shift += RTM_RADIXSORT_BITS;
	}
}

#undef RTM_RADIXSORT_BITS
#undef RTM_RADIXSORT_HISTOGRAM_SIZE
#undef RTM_RADIXSORT_BIT_MASK

} // namespace rtm
