



#ifndef BIALSIMPLEBUCKETQUEUE_H
#define BIALSIMPLEBUCKETQUEUE_H

#include "BucketQueueElements.hpp"
#include "Common.hpp"
#include "Vector.hpp"

namespace Bial {

  
  class SimpleBucketQueue {

  protected:

    Vector< IdentityNode > identity; 
    Vector< WeightNode > weight; 
    size_t elements; 
    size_t minimum; 

  public:

    
    SimpleBucketQueue( size_t size, size_t max_dist );

  public:

    
    bool Empty( ) const;

    
    size_t Elements( ) const;

    
    bool Increasing( ) const;
    
    
    BucketState State( size_t idt ) const;

    
    void State( size_t idt, BucketState new_state );

    
    void Finished( size_t idt );

    
    size_t Buckets( ) const;

    
    void ResetMinimum( );

    
    void Reset( );

    
    void Insert( size_t idt, int weight_idx );

    
    size_t Remove( );

  protected:

    
    void Remove( size_t idt, int weight_idx );

  public:

    
    void Update( size_t idt, int cur_wgt, int new_wgt );

  };

}

#include "SimpleBucketQueue.cpp"

#endif
