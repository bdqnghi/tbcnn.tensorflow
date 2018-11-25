#ifndef SPAMO_SCAN_H
#define SPAMO_SCAN_H

#include "matrix.h"
#include "array.h"
#include "motif.h"
#include "red-black-tree.h"


void scan_spamo_primary(
  int margin, 
  double score_threshold, 
  ARRAY_T *background, 
  MOTIF_T *motif, 
  RBTREE_T *sequences,
  BOOLEAN_T trimmed
);


void scan_spamo_secondary(
  int margin, 
  double score_threshold,
  BOOLEAN_T use_best_secondary,
  ARRAY_T *background, 
  MOTIF_T *motif,
  RBTREE_T *sequences, 
  
  ARRAY_T **matches,
  int *hits,
  int hits_size
);

#endif
