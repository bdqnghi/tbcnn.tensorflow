





#include "stdafx.h"

#ifdef STANDARD
#include <stdio.h>
#include <string.h>
#ifdef __WIN__
typedef unsigned __int64 ulonglong;	
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif 
#else
#include <my_global.h>
#include <my_sys.h>
#endif
#include <mysql.h>
#include <m_ctype.h>
#include <m_string.h>		



extern "C" {
my_bool lv_init( UDF_INIT* initid, UDF_ARGS* args, char* message );
void lv_deinit( UDF_INIT* initid );
void lv_reset( UDF_INIT* initid, UDF_ARGS* args, char* is_null, char *error );
void lv_clear( UDF_INIT* initid, char* is_null, char *error );
void lv_add( UDF_INIT* initid, UDF_ARGS* args, char* is_null, char *error );
char *lv(UDF_INIT * initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *  );
}




struct lv_data
{
  
  ulong max_diff;
  ulong diff;
  ulong	length;
  char *concat_string;
  int *workspace;
};



my_bool lv_init( UDF_INIT* initid, UDF_ARGS* args, char* message )
{
  struct lv_data*	data = NULL;
  ulong max_diff;

  if (args->arg_count < 2 || args->arg_count > 3)
  {
    strcpy(
	   message,
     "wrong number of arguments: lv() requires 2 to 3 arguments (field name, compare string, max diffrerence)"
	   );
    return 1;
  }

  if ( args->arg_type[0] != STRING_RESULT )
  {
    strcpy(message, "wrong argument type: lv() requires a STRING as parameter 1");
    return 1;
  }
  if ( args->arg_type[1] != STRING_RESULT )
  {
    strcpy(message, "wrong argument type: lv() requires a STRING as parameter 2");
    return 1;
  }
  if (args->arg_count == 3)
  {
    if ( args->arg_type[2] != INT_RESULT )
    {
      strcpy(message, "wrong argument type: lv() requires an INT as parameter 3");
      return 1;
    }
    max_diff = *((ulong*)args->args[2]);
  } else {
    max_diff = 2;
  }

  data = new struct lv_data;
  
  data->max_diff = max_diff;
  
  
  data->concat_string	= NULL;

  
  data->workspace = new int[(args->lengths[1] + 1) * (args->lengths[1] + max_diff + 1)];


  initid->maybe_null	= 1;		  
  initid->max_length	= 65535;	
  initid->ptr = (char*)data;

  return 0;
}


void lv_deinit( UDF_INIT* initid )
{
  struct lv_data* data = (struct lv_data*)initid->ptr;
  if (data != NULL)
  {
    if (data->concat_string != NULL)
    {
      free(data->concat_string);
      data->concat_string	= NULL;
    }
  if (data->workspace != NULL)
  {
    delete [] data->workspace;
  }
   

    delete data;
    initid->ptr = NULL;
  }
}

void lv_reset( UDF_INIT* initid, UDF_ARGS* args, char* is_null, char* message )
{
  lv_clear(initid, is_null, message);
  lv_add( initid, args, is_null, message );
}

void lv_clear( UDF_INIT* initid, char* is_null, char* message )
{
  struct lv_data* data = (struct lv_data*)initid->ptr;
  if (data->concat_string != NULL)
  {
    free(data->concat_string);
    data->concat_string	= NULL;
  }
  
  
  

  data->diff = data->max_diff+1;
  data->length = 0;
  *is_null = 0;
}

void lv_add( UDF_INIT* initid, UDF_ARGS* args, char* , char*  )
{
  struct lv_data* data	= (struct lv_data*)initid->ptr;

  
  if (data->diff > 0)
  {
    if (args->args[0] && args->args[1])
    {
      unsigned long n = args->lengths[0];
      const char *s = args->args[0];
      unsigned long m = args->lengths[1];
      const char *t = args->args[1];

      if(abs(n - m) < (data->diff))
      {


	
	int *d = (int*) data->workspace;
  	int b,c,f,g,h,i,j,k,min;
  
  
		

		n++;
		m++;

		
    	for (k = 0; k < n; k++)
		{
			d[k] = k;
		}

		
    	for (k = 0; k < m; k++)
		{
      	d[k * n] = k;
		}

		

		
		g = 0;
    	for (i = 1; i < n; i++)
		{
			

			k = i;

			
			f = 0;
      	for (j = 1; j < m; j++)
			{
				

				

				
				h = k;
				
				k += n;

				

				

				min = d[h] + 1;
				b = d[k-1] + 1;
				c = d[h-1] + (s[g] == t[f] ? 0 : 1);

				if (b < min) { min = b; }
				if (c < min) { min = c; }

				d[k] = min;

				
				f = j;
      	}

			
			g = i;
		}

		

    	



        if(d[k] < data->diff) 
        {
          char *lpstrTotal = NULL;
	  lpstrTotal = (char *)malloc(n);


          
          strncpy(lpstrTotal, s,n);

          
          

          
          if (data->concat_string != NULL)
          {
            free(data->concat_string);
          }

          
          data->concat_string = lpstrTotal;
          data->length = n-1;
          data->diff = (ulong) d[k]; 
        } else if(d[k] == data->diff) 
        {
	      ulong intTotal = 0;
	      char *lpstrTotal = NULL;

	     
	      intTotal = n + data->length;

	      lpstrTotal = (char *)malloc(intTotal+1);

	      
	      if (data->concat_string == NULL || data->length == 0)
	      {
	        lpstrTotal[0] = '\0';
	      }
	      else
	      {
	        strncpy(lpstrTotal, data->concat_string, data->length);
	        
	        lpstrTotal[data->length] = '\0';
	        
	        strncat(lpstrTotal, ",", 1);
	      }

	      
	      strncat(lpstrTotal, s ,n-1);

	      
	      lpstrTotal[intTotal] = '\0';

	      
	      if (data->concat_string != NULL)
	      {
	        free(data->concat_string);
	      }

	      
	      data->concat_string = lpstrTotal;
	      data->length = intTotal;
          data->diff = (ulong) d[k]; 
        }
      }
    }

  }

  
 

}


char *lv(UDF_INIT * initid, UDF_ARGS * , char * , unsigned long *length, char *is_null, char *  )
{

  struct lv_data* data = (struct lv_data*)initid->ptr;
  if (!data->concat_string)
  {
    *is_null = 1;
    (*length) = 0;
    return NULL;
  }

  *is_null = 0;
  ulong intResult = data->length;
  initid->max_length	= data->length;

  
  (*length) = intResult;

  return data->concat_string;
}
