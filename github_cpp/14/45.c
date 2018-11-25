




#pragma once

#include "kernel_utils.h"
#include "vector_types.h"
#include "radixsort_key_conversion.h"

namespace thrust  {
namespace system  {
namespace cuda    {
namespace detail  {
namespace detail  {
namespace b40c_thrust   {





#define B40C_RADIXSORT_LOG_THREADS						7								
#define B40C_RADIXSORT_THREADS							(1 << B40C_RADIXSORT_LOG_THREADS)	


#define B40C_SM20_REDUCE_CTA_OCCUPANCY()					(8)			
#define B40C_SM12_REDUCE_CTA_OCCUPANCY()					(5)			
#define B40C_SM10_REDUCE_CTA_OCCUPANCY()					(3)			
#define B40C_RADIXSORT_REDUCE_CTA_OCCUPANCY(version)		((version >= 200) ? B40C_SM20_REDUCE_CTA_OCCUPANCY() : 	\
			        										 (version >= 120) ? B40C_SM12_REDUCE_CTA_OCCUPANCY() : 	\
					        													B40C_SM10_REDUCE_CTA_OCCUPANCY())		
													                    

#define B40C_SM20_SCAN_SCATTER_CTA_OCCUPANCY()				(7)			
#define B40C_SM12_SCAN_SCATTER_CTA_OCCUPANCY()				(5)			
#define B40C_SM10_SCAN_SCATTER_CTA_OCCUPANCY()				(2)			
#define B40C_RADIXSORT_SCAN_SCATTER_CTA_OCCUPANCY(version)	((version >= 200) ? B40C_SM20_SCAN_SCATTER_CTA_OCCUPANCY() : 	\
			    											 (version >= 120) ? B40C_SM12_SCAN_SCATTER_CTA_OCCUPANCY() : 	\
				    															B40C_SM10_SCAN_SCATTER_CTA_OCCUPANCY())		


#define B40C_SM20_LOG_SETS_PER_PASS()					(1)			
#define B40C_SM12_LOG_SETS_PER_PASS()					(0)			
#define B40C_SM10_LOG_SETS_PER_PASS()					(1)			
#define B40C_RADIXSORT_LOG_SETS_PER_PASS(version)		((version >= 200) ? B40C_SM20_LOG_SETS_PER_PASS() : 	\
			     										 (version >= 120) ? B40C_SM12_LOG_SETS_PER_PASS() : 	\
				    														B40C_SM10_LOG_SETS_PER_PASS())		


#define B40C_SM20_LOG_PASSES_PER_CYCLE(K, V)					(((B40C_MAX(sizeof(K), sizeof(V)) > 4) || _B40C_LP64_) ? 0 : 1)	
#define B40C_SM12_LOG_PASSES_PER_CYCLE(K, V)					(B40C_MAX(sizeof(K), sizeof(V)) > 4 ? 0 : 1)					
#define B40C_SM10_LOG_PASSES_PER_CYCLE(K, V)					(0)																
#define B40C_RADIXSORT_LOG_PASSES_PER_CYCLE(version, K, V)	((version >= 200) ? B40C_SM20_LOG_PASSES_PER_CYCLE(K, V) : 	\
				    										 (version >= 120) ? B40C_SM12_LOG_PASSES_PER_CYCLE(K, V) : 	\
					    														B40C_SM10_LOG_PASSES_PER_CYCLE(K, V))		



#define B40C_SM20_LOG_RAKING_THREADS_PER_PASS()				(B40C_LOG_WARP_THREADS + 1)		
#define B40C_SM12_LOG_RAKING_THREADS_PER_PASS()				(B40C_LOG_WARP_THREADS)			
#define B40C_SM10_LOG_RAKING_THREADS_PER_PASS()				(B40C_LOG_WARP_THREADS + 2)		
#define B40C_RADIXSORT_LOG_RAKING_THREADS_PER_PASS(version)	((version >= 200) ? B40C_SM20_LOG_RAKING_THREADS_PER_PASS() : 	\
				    										 (version >= 120) ? B40C_SM12_LOG_RAKING_THREADS_PER_PASS() : 	\
					    														B40C_SM10_LOG_RAKING_THREADS_PER_PASS())		



#define B40C_RADIXSORT_LOG_CYCLE_ELEMENTS(version, K, V)		(B40C_RADIXSORT_LOG_SETS_PER_PASS(version) + B40C_RADIXSORT_LOG_PASSES_PER_CYCLE(version, K, V) + B40C_RADIXSORT_LOG_THREADS + 1)
#define B40C_RADIXSORT_CYCLE_ELEMENTS(version, K, V)			(1 << B40C_RADIXSORT_LOG_CYCLE_ELEMENTS(version, K, V))


#define B40C_RADIXSORT_LOG_WARPS								(B40C_RADIXSORT_LOG_THREADS - B40C_LOG_WARP_THREADS)
#define B40C_RADIXSORT_WARPS									(1 << B40C_RADIXSORT_LOG_WARPS)


#define B40C_RADIXSORT_LOG_SPINE_THREADS						7		
#define B40C_RADIXSORT_SPINE_THREADS							(1 << B40C_RADIXSORT_LOG_SPINE_THREADS)	


#define B40C_RADIXSORT_LOG_SPINE_CYCLE_ELEMENTS  				9		
#define B40C_RADIXSORT_SPINE_CYCLE_ELEMENTS		    			(1 << B40C_RADIXSORT_LOG_SPINE_CYCLE_ELEMENTS)







struct KeysOnlyType {};


template <typename V>
inline __host__ __device__ bool IsKeysOnly() {return false;}



template <>
inline __host__ __device__ bool IsKeysOnly<KeysOnlyType>() {return true;}



struct CtaDecomposition {
	unsigned int num_big_blocks;
	unsigned int big_block_elements;
	unsigned int normal_block_elements;
	unsigned int extra_elements_last_block;
	unsigned int num_elements;
};


} 
} 
} 
} 
} 
} 

