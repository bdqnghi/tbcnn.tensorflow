/* Biomedical Image Analysis Library 
 * See README file in the root instalation directory for more information. 
 */

/**
 * @date 2012/Sep/06 
 * @brief
 * Content: Bucket-sort queue class 
 * <br> Description: A bucket-sort queue. It is useful to sort a large set
 * of elements whose weight domain is not very large,
 * e.g. IFT and OPF algorithms over MR images. 
 * <br> Future add-on's: Deal with negative values. 
 *                  Add fast operation functions in which queue does not grow. 
 * Warning: In Boost library, there is a class named circular_buffer
 * that may do exactly the same as Vector< WeightNode >. 
 */

#ifndef BIALSIMPLEBUCKETQUEUE_H
#define BIALSIMPLEBUCKETQUEUE_H

#include "BucketQueueElements.hpp"
#include "Common.hpp"
#include "Vector.hpp"

namespace Bial {

  /** @brief Standard bucket queue class, that may work with both integer or real values. */
  class SimpleBucketQueue {

  protected:

    Vector< IdentityNode > identity; /** @brief vector containing each element data ( state, previous, next ). */
    Vector< WeightNode > weight; /** @brief vector containing pointers to elements that fall into each bucket weight. */
    size_t elements; /** @brief Number of elements currently in the queue. Not required, but worth it for debugging. */
    size_t minimum; /** @brief minimum element currently inserted in the queue. */

  public:

    /**
     * @date 2012/Sep/06 
     * @param size: Total number of elements to be inserted in the queue. 
     * @param max_dist: Maximum simple between elements that simultaneously present in the queue.
     * @return none. 
     * @brief Basic Constructor. 
     * @warning none. 
     */
    SimpleBucketQueue( size_t size, size_t max_dist );

  public:

    /**
     * @date 2012/Sep/06 
     * @param none. 
     * @return Whether bucket queue is empty or not. 
     * @brief Returns true if bucket queue is empty. 
     * @warning none. 
     */
    bool Empty( ) const;

    /**
     * @date 2013/Oct/14 
     * @param none. 
     * @return Number of elements in queue. 
     * @brief Returns the number of elements in queue. 
     * @warning none. 
     */
    size_t Elements( ) const;

    /**
     * @date 2012/Sep/06 
     * @param none. 
     * @return Increasing attribute value. 
     * @brief Returns increasing attribute value. 
     * @warning none. 
     */
    bool Increasing( ) const;
    
    /**
     * @date 2012/Sep/19 
     * @param idt: identity of the element. 
     * @return Element state in queue. 
     * @brief Returns element state in queue. 
     * @warning none. 
     */
    BucketState State( size_t idt ) const;

    /**
     * @date 2012/Sep/25 
     * @param idt: Identity of the element. 
     * @param new_state: New state. 
     * @return none. 
     * @brief Sets new state to element of index idt. 
     * @warning none. 
     */
    void State( size_t idt, BucketState new_state );

    /**
     * @date 2012/Sep/25 
     * @param idt: Identity of the element. 
     * @return none. 
     * @brief Sets finished state to element of index idt. 
     * @warning none. 
     */
    void Finished( size_t idt );

    /**
     * @date 2012/Sep/21 
     * @param none. 
     * @return The current number of buckets. 
     * @brief Returns the current number of buckets. 
     * @warning none. 
     */
    size_t Buckets( ) const;

    /**
     * @date 2017/Oct/20 
     * @param none.
     * @return none. 
     * @brief Restarts minimum.
     * @warning none.
     */
    void ResetMinimum( );

    /**
     * @date 2016/Jan/27 
     * @param none.
     * @return none. 
     * @brief Sets all element states to NOT_VISITED and restarts minimum.
     * @warning none. 
     */
    void Reset( );

    /**
     * @date 2012/Sep/06 
     * @param idt: identity of the element. 
     * @param weight_idx: weight of the element.
     * @return none.
     * @brief Inserts element of identity idt and weight wgt into the bucket queue.
     * @warning none. 
     */
    void Insert( size_t idt, int weight_idx );

    /**
     * @date 2012/Sep/06 
     * @param none. 
     * @return The next element in the bucket queue. 
     * @brief Removes the next element in the bucket queue. 
     * @warning none. 
     */
    size_t Remove( );

  protected:

    /**
     * @date 2012/Sep/06 
     * @param idt: identity of the element. 
     * @param weight_idx: weight of the element. 
     * @return none. 
     * @brief Removes element of identity idt and weight wgt of the bucket queue. 
     * @warning none. 
     */
    void Remove( size_t idt, int weight_idx );

  public:

    /**
     * @date 2012/Sep/06 
     * @param idt: identity of the element. 
     * @param cur_wgt: current weight of the element. 
     * @param new_wgt: the new weight assigned to the element. 
     * @return none. 
     * @brief Updates current weight of element of identity idt. 
     * @warning none. 
     */
    void Update( size_t idt, int cur_wgt, int new_wgt );

  };

}

#include "SimpleBucketQueue.cpp"

#endif
