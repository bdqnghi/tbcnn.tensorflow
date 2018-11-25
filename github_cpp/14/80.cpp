





#ifndef RADIXSORT_H
#define RADIXSORT_H


#include "mytypes.h"






    enum RadixHint
    {
        RADIX_SIGNED,       
        RADIX_UNSIGNED      
    };






    class RadixSort
    {
        public:
                                        RadixSort();
                                        ~RadixSort();

        
                RadixSort&              Sort(const uint* input, uint nb, RadixHint hint=RADIX_SIGNED); 
                RadixSort&              Sort(const float* input, uint nb);

        
        inline uint*                    GetRanks()      const   { return ranks_;      }

        
        inline uint                     GetCallCount()  const   { return totalCalls_; }
        
        inline uint                     GetSize()       const   { return currentSize_; }

        private:



                uint                    currentSize_;           
                uint*                   ranks_;                 
                uint*                   ranks2_;

                uint                    totalCalls_;            
        
         inline void                    CheckResize(uint nb);
         inline bool                    Resize(uint nb);
    };

#endif 
