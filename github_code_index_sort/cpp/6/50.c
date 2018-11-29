

// Radix sort (from Pierre Terdiman)

#include "../bigball.h"
#ifndef BB_RADIXSORT_H
#include "radixsort.h"
#endif

namespace bigball
{

//#define KYLE_HUBERT_VERSION	// Crashes with negative zeros

#define INVALIDATE_RANKS	m_CurrentSize|=0x80000000
#define VALIDATE_RANKS		m_CurrentSize&=0x7fffffff
#define CURRENT_SIZE		(m_CurrentSize&0x7fffffff)
#define INVALID_RANKS		(m_CurrentSize&0x80000000)

#define CHECK_RESIZE(n)																		\
	if(n!=mPreviousSize)																	\
	{																						\
				if(n>m_CurrentSize)	Resize(n);												\
		else						ResetRanks();											\
		mPreviousSize = n;																	\
	}

#if defined(__APPLE__) || defined(_XBOX)
	#define H0_OFFSET	768
	#define H1_OFFSET	512
	#define H2_OFFSET	256
	#define H3_OFFSET	0
	#define BYTES_INC	(3-j)
#else 
	#define H0_OFFSET	0
	#define H1_OFFSET	256
	#define H2_OFFSET	512
	#define H3_OFFSET	768
	#define BYTES_INC	j
#endif

#define CREATE_HISTOGRAMS(type, buffer)														\
	/* Clear counters/histograms */															\
    Memory::Memzero(Histogram, 256*4*sizeof(uint32));											\
																							\
	/* Prepare to count */																	\
	const unsigned char* p = (const unsigned char*)input;													\
	const unsigned char* pe = &p[nb*4];																\
	uint32* h0 = &Histogram[H0_OFFSET];	/* Histogram for first pass (LSB)	*/				\
	uint32* h1 = &Histogram[H1_OFFSET];	/* Histogram for second pass		*/				\
	uint32* h2 = &Histogram[H2_OFFSET];	/* Histogram for third pass			*/				\
	uint32* h3 = &Histogram[H3_OFFSET];	/* Histogram for last pass (MSB)	*/				\
																							\
	bool AlreadySorted = true;	/* Optimism... */											\
																							\
	if(INVALID_RANKS)																		\
	{																						\
		/* Prepare for temporal coherence */												\
		const type* Running = (type*)buffer;												\
		type PrevVal = *Running;															\
																							\
		while(p!=pe)																		\
		{																					\
			/* Read input buffer in previous sorted order */								\
			const type Val = *Running++;													\
			/* Check whether already sorted or not */										\
			if(Val<PrevVal)	{ AlreadySorted = false; break; } /* Early out */				\
			/* Update for next iteration */													\
			PrevVal = Val;																	\
																							\
			/* Create histograms */															\
			h0[*p++]++;	h1[*p++]++;	h2[*p++]++;	h3[*p++]++;									\
		}																					\
																							\
		/* If all input values are already sorted, we just have to return and leave the */	\
		/* previous list unchanged. That way the routine may take advantage of temporal */	\
		/* coherence, for example when used to sort transparent faces.					*/	\
		if(AlreadySorted)																	\
		{																					\
			mNbHits++;																		\
			for(uint32 i=0;i<nb;i++)	m_Ranks[i] = i;										\
			return *this;																	\
		}																					\
	}																						\
	else																					\
	{																						\
		/* Prepare for temporal coherence */												\
		const uint32* Indices = m_Ranks;														\
		type PrevVal = (type)buffer[*Indices];												\
																							\
		while(p!=pe)																		\
		{																					\
			/* Read input buffer in previous sorted order */								\
			const type Val = (type)buffer[*Indices++];										\
			/* Check whether already sorted or not */										\
			if(Val<PrevVal)	{ AlreadySorted = false; break; } /* Early out */				\
			/* Update for next iteration */													\
			PrevVal = Val;																	\
																							\
			/* Create histograms */															\
			h0[*p++]++;	h1[*p++]++;	h2[*p++]++;	h3[*p++]++;									\
		}																					\
																							\
		/* If all input values are already sorted, we just have to return and leave the */	\
		/* previous list unchanged. That way the routine may take advantage of temporal */	\
		/* coherence, for example when used to sort transparent faces.					*/	\
		if(AlreadySorted)	{ mNbHits++; return *this;	}									\
	}																						\
																							\
	/* Else there has been an early out and we must finish computing the histograms */		\
	while(p!=pe)																			\
	{																						\
		/* Create histograms without the previous overhead */								\
		h0[*p++]++;	h1[*p++]++;	h2[*p++]++;	h3[*p++]++;										\
	}

#define CHECK_PASS_VALIDITY(pass)															\
	/* Shortcut to current counters */														\
	const uint32* CurCount = &Histogram[pass<<8];											\
																							\
	/* Reset flag. The sorting pass is supposed to be performed. (default) */				\
	bool PerformPass = true;																\
																							\
	/* Check pass validity */																\
																							\
	/* If all values have the same byte, sorting is useless. */								\
	/* It may happen when sorting bytes or words instead of dwords. */						\
	/* This routine actually sorts words faster than dwords, and bytes */					\
	/* faster than words. Standard running time (O(4*n))is reduced to O(2*n) */				\
	/* for words and O(n) for bytes. Running time for floats depends on actual values... */	\
																							\
	/* Get first byte */																	\
	const unsigned char UniqueVal = *(((unsigned char*)input)+pass);										\
																							\
	/* Check that byte's counter */															\
	if(CurCount[UniqueVal]==nb)	PerformPass=false;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Constructor.
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RadixSort::RadixSort() : m_Ranks(nullptr), m_Ranks2(nullptr), m_CurrentSize(0), mTotalCalls(0), mNbHits(0), m_bDeleteRanks(true)
{
	// Initialize indices
	INVALIDATE_RANKS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Destructor.
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RadixSort::~RadixSort()
{
	// Release everything
	if(m_bDeleteRanks)
	{
		BB_FREE(m_Ranks2);
		BB_FREE(m_Ranks);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Resizes the inner lists.
 *	\param		nb	[in] new size (number of dwords)
 *	\return		true if success
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RadixSort::Resize(uint32 nb)
{
	if(m_bDeleteRanks)
	{
		// Free previously used ram
		BB_FREE(m_Ranks2);
		BB_FREE(m_Ranks);

		// Get some fresh one
		m_Ranks		= (uint32*) Memory::Malloc(sizeof(uint32)*nb);	if(!m_Ranks) return false;
		m_Ranks2	= (uint32*) Memory::Malloc(sizeof(uint32)*nb);	if(!m_Ranks2) return false;
	}
	return true;
}

void RadixSort::CheckResize(uint32 nb)
{
	uint32 CurSize = CURRENT_SIZE;
	if(nb!=CurSize)
	{
		if(nb>CurSize)	Resize(nb);
		m_CurrentSize = nb;
		INVALIDATE_RANKS;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Main sort routine.
 *	This one is for integer values. After the call, mRanks contains a list of indices in sorted order, i.e. in the order you may process your data.
 *	\param		input	[in] a list of integer values to sort
 *	\param		nb		[in] number of values to sort, must be < 2^31
 *	\param		hint	[in] RADIX_SIGNED to handle negative values, RADIX_UNSIGNED if you know your input buffer only contains positive values
 *	\return		Self-Reference
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RadixSort& RadixSort::Sort(const uint32* input, uint32 nb, eRadixHint hint)
{
	// Checkings
	if(!input || !nb || nb&0x80000000)	return *this;

	// Stats
	mTotalCalls++;

	// Resize lists if needed
	CheckResize(nb);

	// Allocate histograms & offsets on the stack
	uint32 Histogram[256*4];
	uint32* Link[256];

	// Create histograms (counters). Counters for all passes are created in one run.
	// Pros:	read input buffer once instead of four times
	// Cons:	mHistogram is 4Kb instead of 1Kb
	// We must take care of signed/unsigned values for temporal coherence.... I just
	// have 2 code paths even if just a single opcode changes. Self-modifying code, someone?
	if(hint==RADIX_UNSIGNED)	{ CREATE_HISTOGRAMS(uint32, input);	}
	else						{ CREATE_HISTOGRAMS(int32, input);	}

	// Radix sort, j is the pass number (0=LSB, 3=MSB)
	for(uint32 j=0;j<4;j++)
	{
		CHECK_PASS_VALIDITY(j);

		// Sometimes the fourth (negative) pass is skipped because all numbers are negative and the MSB is 0xFF (for example). This is
		// not a problem, numbers are correctly sorted anyway.
		if(PerformPass)
		{
			// Should we care about negative values?
			if(j!=3 || hint==RADIX_UNSIGNED)
			{
				// Here we deal with positive values only

				// Create offsets
				Link[0] = m_Ranks2;
				for(uint32 i=1;i<256;i++)		Link[i] = Link[i-1] + CurCount[i-1];
			}
			else
			{
				// This is a special case to correctly handle negative integers. They're sorted in the right order but at the wrong place.

#ifdef KYLE_HUBERT_VERSION
				// From Kyle Hubert:

				Link[128] = m_Ranks2;
				for(uint32 i=129;i<256;i++)	Link[i] = Link[i-1] + CurCount[i-1];

				Link[0] = Link[255] + CurCount[255];
				for(uint32 i=1;i<128;i++)	Link[i] = Link[i-1] + CurCount[i-1];
#else
				// Compute #negative values involved if needed
				uint32 NbNegativeValues = 0;
				if(hint==RADIX_SIGNED)
				{
					// An efficient way to compute the number of negatives values we'll have to deal with is simply to sum the 128
					// last values of the last histogram. Last histogram because that's the one for the Most Significant Byte,
					// responsible for the sign. 128 last values because the 128 first ones are related to positive numbers.
					const uint32* h3 = &Histogram[H3_OFFSET];
					for(uint32 i=128;i<256;i++)	NbNegativeValues += h3[i];	// 768 for last histogram, 128 for negative part
				}

				// Create biased offsets, in order for negative numbers to be sorted as well
				Link[0] = &m_Ranks2[NbNegativeValues];										// First positive number takes place after the negative ones
				for(uint32 i=1;i<128;i++)		Link[i] = Link[i-1] + CurCount[i-1];		// 1 to 128 for positive numbers

				// Fixing the wrong place for negative values
				Link[128] = m_Ranks2;
				for(uint32 i=129;i<256;i++)		Link[i] = Link[i-1] + CurCount[i-1];
#endif
			}

			// Perform Radix Sort
			const unsigned char* InputBytes	= (const unsigned char*)input;
			InputBytes += BYTES_INC;
			if(INVALID_RANKS)
			{
				for(uint32 i=0;i<nb;i++)	*Link[InputBytes[i<<2]]++ = i;
				VALIDATE_RANKS;
			}
			else
			{
				const uint32* Indices		= m_Ranks;
				const uint32* IndicesEnd	= &m_Ranks[nb];
				while(Indices!=IndicesEnd)
				{
					const uint32 id = *Indices++;
					*Link[InputBytes[id<<2]]++ = id;
				}
			}

			// Swap pointers for next pass. Valid indices - the most recent ones - are in mRanks after the swap.
			uint32* Tmp = m_Ranks;
			m_Ranks = m_Ranks2;
			m_Ranks2 = Tmp;
		}
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *	Main sort routine.
 *	This one is for floating-point values. After the call, mRanks contains a list of indices in sorted order, i.e. in the order you may process your data.
 *	\param		input			[in] a list of floating-point values to sort
 *	\param		nb				[in] number of values to sort, must be < 2^31
 *	\return		Self-Reference
 *	\warning	only sorts IEEE floating-point values
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RadixSort& RadixSort::Sort(const float* input2, uint32 nb)
{
	// Checkings
	if(!input2 || !nb || nb&0x80000000)	return *this;

	// Stats
	mTotalCalls++;

	const uint32* input = (const uint32*)input2;

	// Resize lists if needed
	CheckResize(nb);

	// Allocate histograms & offsets on the stack
	uint32 Histogram[256*4];
	uint32* Link[256];

	// Create histograms (counters). Counters for all passes are created in one run.
	// Pros:	read input buffer once instead of four times
	// Cons:	mHistogram is 4Kb instead of 1Kb
	// Floating-point values are always supposed to be signed values, so there's only one code path there.
	// Please note the floating point comparison needed for temporal coherence! Although the resulting asm code
	// is dreadful, this is surprisingly not such a performance hit - well, I suppose that's a big one on first
	// generation Pentiums....We can't make comparison on integer representations because, as Chris said, it just
	// wouldn't work with mixed positive/negative values....
	{ CREATE_HISTOGRAMS(float, input2); }

	// Radix sort, j is the pass number (0=LSB, 3=MSB)
	for(uint32 j=0;j<4;j++)
	{
		// Should we care about negative values?
		if(j!=3)
		{
			// Here we deal with positive values only
			CHECK_PASS_VALIDITY(j);

			if(PerformPass)
			{
				// Create offsets
				Link[0] = m_Ranks2;
				for(uint32 i=1;i<256;i++)		Link[i] = Link[i-1] + CurCount[i-1];

				// Perform Radix Sort
				const unsigned char* InputBytes = (const unsigned char*)input;
				InputBytes += BYTES_INC;
				if(INVALID_RANKS)
				{
					for(uint32 i=0;i<nb;i++)	*Link[InputBytes[i<<2]]++ = i;
					VALIDATE_RANKS;
				}
				else
				{
					const uint32* Indices		= m_Ranks;
					const uint32* IndicesEnd	= &m_Ranks[nb];
					while(Indices!=IndicesEnd)
					{
						const uint32 id = *Indices++;
						*Link[InputBytes[id<<2]]++ = id;
					}
				}

				// Swap pointers for next pass. Valid indices - the most recent ones - are in mRanks after the swap.
				uint32* Tmp = m_Ranks;
				m_Ranks = m_Ranks2;
				m_Ranks2 = Tmp;
			}
		}
		else
		{
			// This is a special case to correctly handle negative values
			CHECK_PASS_VALIDITY(j);

			if(PerformPass)
			{
#ifdef KYLE_HUBERT_VERSION
				// From Kyle Hubert:

				Link[255] = m_Ranks2 + CurCount[255];
				for(uint32 i=254;i>127;i--)	Link[i] = Link[i+1] + CurCount[i];
				Link[0] = Link[128] + CurCount[128];
				for(uint32 i=1;i<128;i++)	Link[i] = Link[i-1] + CurCount[i-1];
#else
				// Compute #negative values involved if needed
				uint32 NbNegativeValues = 0;
				// An efficient way to compute the number of negatives values we'll have to deal with is simply to sum the 128
				// last values of the last histogram. Last histogram because that's the one for the Most Significant Byte,
				// responsible for the sign. 128 last values because the 128 first ones are related to positive numbers.
				// ### is that ok on Apple ?!
				const uint32* h3 = &Histogram[H3_OFFSET];
				for(uint32 i=128;i<256;i++)	NbNegativeValues += h3[i];	// 768 for last histogram, 128 for negative part

				// Create biased offsets, in order for negative numbers to be sorted as well
				Link[0] = &m_Ranks2[NbNegativeValues];										// First positive number takes place after the negative ones
				for(uint32 i=1;i<128;i++)		Link[i] = Link[i-1] + CurCount[i-1];		// 1 to 128 for positive numbers

				// We must reverse the sorting order for negative numbers!
				Link[255] = m_Ranks2;
				for(uint32 i=0;i<127;i++)	Link[254-i] = Link[255-i] + CurCount[255-i];	// Fixing the wrong order for negative values
				for(uint32 i=128;i<256;i++)	Link[i] += CurCount[i];							// Fixing the wrong place for negative values
#endif
				// Perform Radix Sort
				if(INVALID_RANKS)
				{
					for(uint32 i=0;i<nb;i++)
					{
						const uint32 Radix = input[i]>>24;						// Radix byte, same as above. AND is useless here (uint32).
						// ### cmp to be killed. Not good. Later.
						if(Radix<128)		*Link[Radix]++ = i;		// Number is positive, same as above
						else				*(--Link[Radix]) = i;	// Number is negative, flip the sorting order
					}
					VALIDATE_RANKS;
				}
				else
				{
					for(uint32 i=0;i<nb;i++)
					{
						const uint32 Radix = input[m_Ranks[i]]>>24;						// Radix byte, same as above. AND is useless here (uint32).
						// ### cmp to be killed. Not good. Later.
						if(Radix<128)		*Link[Radix]++ = m_Ranks[i];		// Number is positive, same as above
						else				*(--Link[Radix]) = m_Ranks[i];	// Number is negative, flip the sorting order
					}
				}
				// Swap pointers for next pass. Valid indices - the most recent ones - are in mRanks after the swap.
				uint32* Tmp = m_Ranks;
				m_Ranks = m_Ranks2;
				m_Ranks2 = Tmp;
			}
			else
			{
				// The pass is useless, yet we still have to reverse the order of current list if all values are negative.
				if(UniqueVal>=128)
				{
					if(INVALID_RANKS)
					{
						// ###Possible?
						for(uint32 i=0;i<nb;i++)	m_Ranks2[i] = nb-i-1;
						VALIDATE_RANKS;
					}
					else
					{
						for(uint32 i=0;i<nb;i++)	m_Ranks2[i] = m_Ranks[nb-i-1];
					}

					// Swap pointers for next pass. Valid indices - the most recent ones - are in mRanks after the swap.
					uint32* Tmp = m_Ranks;
					m_Ranks = m_Ranks2;
					m_Ranks2 = Tmp;
				}
			}
		}
	}
	return *this;
}

bool RadixSort::SetRankBuffers(uint32* ranks0, uint32* ranks1)
{
	if(!ranks0 || !ranks1)	return false;

	m_Ranks			= ranks0;
	m_Ranks2		= ranks1;
	m_bDeleteRanks	= false;
	return true;
}

} /* namespace bigball */