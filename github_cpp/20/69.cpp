
#ifndef SPAMO_CISML_H
#define SPAMO_CISML_H

#include "spamo-matches.h"
#include "red-black-tree.h"


void load_spamo_primary(
  const char *file,           
  int margin,                 
  double score_threshold,     
  RBTREE_T *sequences,        
  MOTIF_T *primary_motif      
);


void load_spamo_secondary(
  const char *file,           
  int margin,                 
  double score_threshold,     
  int bin,                    
  double sigthresh,           
  int test_max,               
  int total_tests,            
  BOOLEAN_T output_sequences, 
  char *output_directory,     
  RBTREE_T *sequences,        
  MOTIF_T *primary_motif,     
  RBTREE_T *secondary_motifs, 
  int db_id                   
);

#endif
