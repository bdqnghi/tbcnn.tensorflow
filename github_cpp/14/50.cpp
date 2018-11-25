



#include "../bigball.h"
#ifndef BB_RADIXSORT_H
#include "radixsort.h"
#endif

namespace bigball
{



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
																\
    Memory::Memzero(Histogram, 256*4*sizeof(uint32));											\
																							\
																		\
	const unsigned char* p = (const unsigned char*)input;													\
	const unsigned char* pe = &p[nb*4];																\
	uint32* h0 = &Histogram[H0_OFFSET];					\
	uint32* h1 = &Histogram[H1_OFFSET];					\
	uint32* h2 = &Histogram[H2_OFFSET];					\
	uint32* h3 = &Histogram[H3_OFFSET];					\
																							\
	bool AlreadySorted = true;												\
																							\
	if(INVALID_RANKS)																		\
	{																						\
														\
		const type* Running = (type*)buffer;												\
		type PrevVal = *Running;															\
																							\
		while(p!=pe)																		\
		{																					\
											\
			const type Val = *Running++;													\
													\
			if(Val<PrevVal)	{ AlreadySorted = false; break; } 				\
																\
			PrevVal = Val;																	\
																							\
																		\
			h0[*p++]++;	h1[*p++]++;	h2[*p++]++;	h3[*p++]++;									\
		}																					\
																							\
			\
			\
			\
		if(AlreadySorted)																	\
		{																					\
			mNbHits++;																		\
			for(uint32 i=0;i<nb;i++)	m_Ranks[i] = i;										\
			return *this;																	\
		}																					\
	}																						\
	else																					\
	{																						\
														\
		const uint32* Indices = m_Ranks;														\
		type PrevVal = (type)buffer[*Indices];												\
																							\
		while(p!=pe)																		\
		{																					\
											\
			const type Val = (type)buffer[*Indices++];										\
													\
			if(Val<PrevVal)	{ AlreadySorted = false; break; } 				\
																\
			PrevVal = Val;																	\
																							\
																		\
			h0[*p++]++;	h1[*p++]++;	h2[*p++]++;	h3[*p++]++;									\
		}																					\
																							\
			\
			\
			\
		if(AlreadySorted)	{ mNbHits++; return *this;	}									\
	}																						\
																							\
			\
	while(p!=pe)																			\
	{																						\
										\
		h0[*p++]++;	h1[*p++]++;	h2[*p++]++;	h3[*p++]++;										\
	}

#define CHECK_PASS_VALIDITY(pass)															\
															\
	const uint32* CurCount = &Histogram[pass<<8];											\
																							\
					\
	bool PerformPass = true;																\
																							\
																	\
																							\
									\
							\
						\
					\
		\
																							\
																		\
	const unsigned char UniqueVal = *(((unsigned char*)input)+pass);										\
																							\
																\
	if(CurCount[UniqueVal]==nb)	PerformPass=false;




RadixSort::RadixSort() : m_Ranks(nullptr), m_Ranks2(nullptr), m_CurrentSize(0), mTotalCalls(0), mNbHits(0), m_bDeleteRanks(true)
{
	
	INVALIDATE_RANKS;
}




RadixSort::~RadixSort()
{
	
	if(m_bDeleteRanks)
	{
		BB_FREE(m_Ranks2);
		BB_FREE(m_Ranks);
	}
}




bool RadixSort::Resize(uint32 nb)
{
	if(m_bDeleteRanks)
	{
		
		BB_FREE(m_Ranks2);
		BB_FREE(m_Ranks);

		
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




RadixSort& RadixSort::Sort(const uint32* input, uint32 nb, eRadixHint hint)
{
	
	if(!input || !nb || nb&0x80000000)	return *this;

	
	mTotalCalls++;

	
	CheckResize(nb);

	
	uint32 Histogram[256*4];
	uint32* Link[256];

	
	
	
	
	
	if(hint==RADIX_UNSIGNED)	{ CREATE_HISTOGRAMS(uint32, input);	}
	else						{ CREATE_HISTOGRAMS(int32, input);	}

	
	for(uint32 j=0;j<4;j++)
	{
		CHECK_PASS_VALIDITY(j);

		
		
		if(PerformPass)
		{
			
			if(j!=3 || hint==RADIX_UNSIGNED)
			{
				

				
				Link[0] = m_Ranks2;
				for(uint32 i=1;i<256;i++)		Link[i] = Link[i-1] + CurCount[i-1];
			}
			else
			{
				

#ifdef KYLE_HUBERT_VERSION
				

				Link[128] = m_Ranks2;
				for(uint32 i=129;i<256;i++)	Link[i] = Link[i-1] + CurCount[i-1];

				Link[0] = Link[255] + CurCount[255];
				for(uint32 i=1;i<128;i++)	Link[i] = Link[i-1] + CurCount[i-1];
#else
				
				uint32 NbNegativeValues = 0;
				if(hint==RADIX_SIGNED)
				{
					
					
					
					const uint32* h3 = &Histogram[H3_OFFSET];
					for(uint32 i=128;i<256;i++)	NbNegativeValues += h3[i];	
				}

				
				Link[0] = &m_Ranks2[NbNegativeValues];										
				for(uint32 i=1;i<128;i++)		Link[i] = Link[i-1] + CurCount[i-1];		

				
				Link[128] = m_Ranks2;
				for(uint32 i=129;i<256;i++)		Link[i] = Link[i-1] + CurCount[i-1];
#endif
			}

			
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

			
			uint32* Tmp = m_Ranks;
			m_Ranks = m_Ranks2;
			m_Ranks2 = Tmp;
		}
	}
	return *this;
}




RadixSort& RadixSort::Sort(const float* input2, uint32 nb)
{
	
	if(!input2 || !nb || nb&0x80000000)	return *this;

	
	mTotalCalls++;

	const uint32* input = (const uint32*)input2;

	
	CheckResize(nb);

	
	uint32 Histogram[256*4];
	uint32* Link[256];

	
	
	
	
	
	
	
	
	{ CREATE_HISTOGRAMS(float, input2); }

	
	for(uint32 j=0;j<4;j++)
	{
		
		if(j!=3)
		{
			
			CHECK_PASS_VALIDITY(j);

			if(PerformPass)
			{
				
				Link[0] = m_Ranks2;
				for(uint32 i=1;i<256;i++)		Link[i] = Link[i-1] + CurCount[i-1];

				
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

				
				uint32* Tmp = m_Ranks;
				m_Ranks = m_Ranks2;
				m_Ranks2 = Tmp;
			}
		}
		else
		{
			
			CHECK_PASS_VALIDITY(j);

			if(PerformPass)
			{
#ifdef KYLE_HUBERT_VERSION
				

				Link[255] = m_Ranks2 + CurCount[255];
				for(uint32 i=254;i>127;i--)	Link[i] = Link[i+1] + CurCount[i];
				Link[0] = Link[128] + CurCount[128];
				for(uint32 i=1;i<128;i++)	Link[i] = Link[i-1] + CurCount[i-1];
#else
				
				uint32 NbNegativeValues = 0;
				
				
				
				
				const uint32* h3 = &Histogram[H3_OFFSET];
				for(uint32 i=128;i<256;i++)	NbNegativeValues += h3[i];	

				
				Link[0] = &m_Ranks2[NbNegativeValues];										
				for(uint32 i=1;i<128;i++)		Link[i] = Link[i-1] + CurCount[i-1];		

				
				Link[255] = m_Ranks2;
				for(uint32 i=0;i<127;i++)	Link[254-i] = Link[255-i] + CurCount[255-i];	
				for(uint32 i=128;i<256;i++)	Link[i] += CurCount[i];							
#endif
				
				if(INVALID_RANKS)
				{
					for(uint32 i=0;i<nb;i++)
					{
						const uint32 Radix = input[i]>>24;						
						
						if(Radix<128)		*Link[Radix]++ = i;		
						else				*(--Link[Radix]) = i;	
					}
					VALIDATE_RANKS;
				}
				else
				{
					for(uint32 i=0;i<nb;i++)
					{
						const uint32 Radix = input[m_Ranks[i]]>>24;						
						
						if(Radix<128)		*Link[Radix]++ = m_Ranks[i];		
						else				*(--Link[Radix]) = m_Ranks[i];	
					}
				}
				
				uint32* Tmp = m_Ranks;
				m_Ranks = m_Ranks2;
				m_Ranks2 = Tmp;
			}
			else
			{
				
				if(UniqueVal>=128)
				{
					if(INVALID_RANKS)
					{
						
						for(uint32 i=0;i<nb;i++)	m_Ranks2[i] = nb-i-1;
						VALIDATE_RANKS;
					}
					else
					{
						for(uint32 i=0;i<nb;i++)	m_Ranks2[i] = m_Ranks[nb-i-1];
					}

					
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

} 