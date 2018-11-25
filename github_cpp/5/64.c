















#ifndef MSCOMP_SORTING
#define MSCOMP_SORTING

#include "internal.h"

#define SORT_SWITCH_TO_INSERT_LIMIT 90




template<typename T> 
void insertion_sort(uint16_t* syms, const T* const conditions, const uint_fast16_t len)
{
	for (uint_fast16_t i = 1; i < len; ++i)
	{
		const uint16_t x = syms[i];
		const T cond = conditions[x];
		uint_fast16_t j = i;
		while (j > 0 && conditions[syms[j-1]] > cond) { syms[j] = syms[j-1]; --j; }
		syms[j] = x;
	}
}



template<typename T> 
void merge_sort(uint16_t* syms, uint16_t* temp, const T* const conditions, const uint_fast16_t len)
{
	if (len < SORT_SWITCH_TO_INSERT_LIMIT)
	{
		
		insertion_sort(syms, conditions, len);
	}
	else
	{
		
		const uint_fast16_t m = len >> 1;
		uint_fast16_t i = 0, j = 0, k = m;
		
		
		merge_sort(syms,   temp,   conditions, m      );
		merge_sort(syms+m, temp+m, conditions, len - m);
		memcpy(temp, syms, len*sizeof(uint16_t));
		
		
		while (j < m && k < len) syms[i++] = (conditions[temp[k]] < conditions[temp[j]]) ? temp[k++] : temp[j++]; 
		if (j < m)        { memcpy(syms+i, temp+j, (m  -j)*sizeof(uint16_t)); }
		else if (k < len) { memcpy(syms+i, temp+k, (len-k)*sizeof(uint16_t)); }
	}
}

#endif
