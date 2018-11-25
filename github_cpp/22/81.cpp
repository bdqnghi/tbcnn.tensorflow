



#ifndef BIALFASTDECREASINGLIFOBUCKETQUEUE_H
#define BIALFASTDECREASINGLIFOBUCKETQUEUE_H

#include "BucketQueue.hpp"
#include "Common.hpp"
#include "Vector.hpp"

namespace Bial {

  
  class FastDecreasingLifoBucketQueue : public BucketQueue {

  protected:

    ldbl minimum; 
    ldbl maximum; 
    ldbl current; 

  public:

    
    FastDecreasingLifoBucketQueue( size_t size, ldbl minimum_value, size_t n_buckets );

  protected:

    
    size_t Index( ldbl value );

  public:

    
    void Insert( size_t idt, ldbl wgt );

    
    size_t Remove( );

  protected:

    
    void Remove( size_t idt, ldbl wgt );

  public:

    
    void Update( size_t idt, ldbl cur_wgt, ldbl new_wgt );

  };

}

#include "FastDecreasingLifoBucketQueue.cpp"

#endif
