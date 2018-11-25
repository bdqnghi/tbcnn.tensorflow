
#ifndef __aspeller_leditdist_hh__
#define __aspeller_leditdist_hh__

#include "weights.hpp"

namespace aspeller {

  
  
  
  
  
  
  
  
  
  

  
  
  
  
  
  
  
  

  
  
  
  

  
  
  

  
  

  struct EditDist {
    int          score;
    const char * stopped_at;
    EditDist() {}
    EditDist(int s, const char * p) 
      : score(s), stopped_at(p) {}
    operator int () const {return score;}
  };

  static const int LARGE_NUM = 0xFFFFF; 
  
  

  int limit_edit_distance(const char * a, const char * b, int limit, 
			  const EditDistanceWeights & w 
			  = EditDistanceWeights());
  
  EditDist limit1_edit_distance(const char * a, const char * b,
				const EditDistanceWeights & w 
				= EditDistanceWeights());

  EditDist limit2_edit_distance(const char * a, const char * b,
				const EditDistanceWeights & w 
				= EditDistanceWeights());
  
}

#endif
