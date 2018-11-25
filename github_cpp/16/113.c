

#include "de.h"




void sort (t_pop ta_ary[], int i_len)
{
  int   done;
  int   step, bound, i, j;
  t_pop temp;

  step = i_len;      
  while (step > 1) 
  {
    step /= 2;	     
    do 
    {
      done   = TRUE;
      bound  = i_len - step;
      for (j = 0; j < bound; j++) 
      {
	    i = j + step + 1;
	    if (ta_ary[j].fa_cost[0] > ta_ary[i-1].fa_cost[0]) 	
	    {
	       temp     = ta_ary[i-1];
	       ta_ary[i-1] = ta_ary[j];
	       ta_ary[j]   = temp;
	       done = FALSE; 
	    }  
      }  
    } while (done == FALSE);  
  } 
}

