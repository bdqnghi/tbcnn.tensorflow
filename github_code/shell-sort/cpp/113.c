/*
* Sample code implementing the shell-sort procedure for
* the object array, using MKL and compiler vectorisation, 
* 
* author: Matthew Dixon and Xin Zhang, based on previous code 
* written by Rainer Storn
*
* Date: Nove. 30 2016
*/

#include "de.h"


/*               
*                                                                   
*  Description:   Shell-sort procedure which sorts array ta_ary[] according
*                 to ta_ary[].fa_cost[0] in ascending order.                 
*                                                                                                                                  
*                                                                  
*  Parameters:    ta_ary[]       population array 
*                 i_len          length of array to be sorteds   
*                    
*                                                                  
*  Postconditions: ta_ary[] will be sorted in ascending order (according to fa_cost[0])
*/

void sort (t_pop ta_ary[], int i_len)
{
  int   done;
  int   step, bound, i, j;
  t_pop temp;

  step = i_len;      //array length
  while (step > 1) 
  {
    step /= 2;	     //halve the step size
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
	       done = FALSE; //if a swap has been made we are not finished yet
	    }  
      }  
    } while (done == FALSE);  
  } 
}

