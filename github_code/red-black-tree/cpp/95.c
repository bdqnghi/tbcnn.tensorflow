#ifndef SPAMO_SCAN_H
#define SPAMO_SCAN_H

#include "matrix.h"
#include "array.h"
#include "motif.h"
#include "red-black-tree.h"

/**************************************************************************
 * Scan all the sequences with the primary motif and store the best match
 * for each in the sequence data structure.
 **************************************************************************/
void scan_spamo_primary(
  int margin, 
  double score_threshold, 
  ARRAY_T *background, 
  MOTIF_T *motif, 
  RBTREE_T *sequences,
  BOOLEAN_T trimmed
);

/**************************************************************************
 * Scan all the sequences with the secondary motif and store the best match
 * for each in matches list.
 **************************************************************************/
void scan_spamo_secondary(
  int margin, 
  double score_threshold,
  BOOLEAN_T use_best_secondary,
  ARRAY_T *background, 
  MOTIF_T *motif,
  RBTREE_T *sequences, 
  //int *matches,
  ARRAY_T **matches,
  int *hits,
  int hits_size
);

#endif
