



#ifndef BIALBUCKETQUEUEELEMENTS_H
#define BIALBUCKETQUEUEELEMENTS_H

#include "Common.hpp"

namespace Bial {

  enum class BucketState : char {
    NOT_VISITED = 0,
      INSERTED = 1,
      UPDATED = 2,
      REMOVED = 3
      };

  class IdentityNode {
  public:
    
    int next;
    
    int prev;
    BucketState state;
    IdentityNode( ) {
      next = -1;
      prev = -1;
      state = BucketState::NOT_VISITED;
    }
  };

  class WeightNode {
  public:
    int first; 
    int last; 
    WeightNode( ) {
      first = -1;
      last = -1;
    }
  };

}

#endif
