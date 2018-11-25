





#ifndef NV_CORE_RADIXSORT_H
#define NV_CORE_RADIXSORT_H

#include <nvcore/nvcore.h>


#define RADIX_LOCAL_RAM


class NVCORE_API RadixSort {
	NV_FORBID_COPY(RadixSort);
public:
	
	RadixSort();
	~RadixSort();

	
	RadixSort & sort(const uint32* input, uint32 nb, bool signedvalues=true);
	RadixSort & sort(const float* input, uint32 nb);

	
	inline uint32 * indices() const { return mIndices; }

	
	inline uint32 * recyclable() const { return mIndices2; }

	
	uint32 usedRam() const;

	
	inline uint32 totalCalls()	const { return mTotalCalls;	}

	
	inline uint32 hits() const { return mNbHits; }


	private:
#ifndef RADIX_LOCAL_RAM
	uint32*			mHistogram;					
	uint32*			mOffset;					
#endif
	uint32			mCurrentSize;				
	uint32			mPreviousSize;				
	uint32*			mIndices;					
	uint32*			mIndices2;

	
	uint32			mTotalCalls;
	uint32			mNbHits;

	
	bool			resize(uint32 nb);
	void			resetIndices();

};


#endif 
