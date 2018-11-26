/* Biomedical Image Analysis Library 
 * See README file in the root instalation directory for more information. 
 */

/**
 * @file MinimumSpanningTree.hpp
 * @author Fábio Augusto Menocci Cappabianco 
 * @date 2012/Sep/26 
 * @version 1.0.00
 * @brief
 * Content: Minimum spanning tree class 
 * <br> Description: Minimum spanning three algorithm. 
 * <br> Future add-on's: Instead of fixed bucket size, use adaptive bucket
 * size, according to the minimum distance in the
 * feature space. 
 */

#ifndef BIALMINIMUMSPANNINGTREE_H
#define BIALMINIMUMSPANNINGTREE_H

#include "Common.hpp"
#include "Feature.hpp"
#include "Vector.hpp"

namespace Bial {
  /**
   * @brief  Minimum spanning three algorithm. 
   */
  class MinimumSpanningTree {

  public:
    /**
     * @date 2013/Sep/04 
     * @param feature: A feature vector whose space will be used to compute the MST. 
     * @param distance_map: Resulting distance map. 
     * @param predecessor_map: Resulting predecessor_map. 
     * @return none. 
     * @brief Computes the minimum spanning tree for the vectors
     * in the given feature space. It returns the
     * predecessors and arc lengths in predecessor_map
     * and distance_map, respectively. 
     * @warning Working for T1 images. 
     */
    template< template< class D > class C, class D >
    static void MST( const Feature< D > &feature, C< D > &distance_map, C< int > &predecessor_map );

  };

}

#include "MinimumSpanningTree.cpp"

#endif
