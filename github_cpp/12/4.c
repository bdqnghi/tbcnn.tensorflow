



#ifndef BIALMINIMUMSPANNINGTREE_H
#define BIALMINIMUMSPANNINGTREE_H

#include "Common.hpp"
#include "Feature.hpp"
#include "Vector.hpp"

namespace Bial {
  
  class MinimumSpanningTree {

  public:
    
    template< template< class D > class C, class D >
    static void MST( const Feature< D > &feature, C< D > &distance_map, C< int > &predecessor_map );

  };

}

#include "MinimumSpanningTree.cpp"

#endif
