
#ifndef SPAMO_CISML_H
#define SPAMO_CISML_H

#include "spamo-matches.h"
#include "red-black-tree.h"


void load_spamo_primary(
  int margin,                 
  double score_threshold,     
  ARRAY_T *background,         
  MOTIF_T *motif,             
  RBTREE_T *sequences,        
  const char *cisml          
);


void load_spamo_secondary(
  const char *cisml,          
  int margin,                 
  double score_threshold,     
  double motif_evalue_cutoff, 
  double sigthresh,           
  int bin,                    
  BOOLEAN_T dump_sig_only,    
  int test_max,               
  int n_secondary_motifs,     
  BOOLEAN_T output_sequences, 
  char *output_directory,     
  RBTREE_T *sequences,        
  MOTIF_T *primary_motif,     
  RBTREE_T *secondary_motifs, 
  ARRAY_T *background,        
  int db_id                   
);

#endif
