


















#ifndef KALDI_UTIL_EDIT_DISTANCE_H_
#define KALDI_UTIL_EDIT_DISTANCE_H_
#include <vector>
#include <set>
#include <algorithm>
#include <limits>
#include <cassert>
#include "base/kaldi-types.h"

namespace kaldi {


template <class T>
int32 LevenshteinEditDistance(const std::vector<T> &a, const std::vector<T> &b);





template <class T>
int32 LevenshteinEditDistance(const std::vector<T> &ref,
                              const std::vector<T> &hyp, int32 *ins, int32 *del,
                              int32 *sub);








template <class T>
int32 LevenshteinAlignment(const std::vector<T> &a, const std::vector<T> &b,
                           T eps_symbol, std::vector<std::pair<T, T> > *output);

}  

#include "edit-distance-inl.h"

#endif
