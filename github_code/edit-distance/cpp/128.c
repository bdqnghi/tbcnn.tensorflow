/* Copyright (C) 2007 Arne Hullmann */
/* Levenshtein GROUP function implemented by Arne Hullmann 2007-11-29.
   Based on Levenshtein Distance Algorithm implementation as MySQL UDF
	by Joshua Drew for SpinWeb Net Designs, Inc. on 2003-12-28.

   Please leave this information intact.
	The levenshtein function is derived from the C implementation
	by Lorenzo Seidenari. More information about the Levenshtein
	Distance Algorithm can be found at http://www.merriampark.com/ld.htm
*/

/*
** The functions name, type and shared library is saved in the new system
** table 'func'.  To be able to create new functions one must have write
** privilege for the database 'mysql'.	If one starts MySQL with
** --skip-grant, then UDF initialization will also be skipped.
**
** Syntax for the new commands are:
** create function <function_name> returns {string|real|integer}
**		  soname <name_of_shared_library>
** drop function <function_name>
**
** Each defined function may have a xxxx_init function and a xxxx_deinit
** function.  The init function should alloc memory for the function
** and tell the main function about the max length of the result
** (for string functions), number of decimals (for double functions) and
** if the result may be a null value.
**
** If a function sets the 'error' argument to 1 the function will not be
** called anymore and mysqld will return NULL for all calls to this copy
** of the function.
**
** All strings arguments to functions are given as string pointer + length
** to allow handling of binary data.
** Remember that all functions must be thread safe. This means that one is not
** allowed to alloc any global or static variables that changes!
** If one needs memory one should alloc this in the init function and free
** this on the __deinit function.
**
** Note that the init and __deinit functions are only called once per
** SQL statement while the value function may be called many times
**
** Function 'lv' returns the string with the smalles levenshtein-distance in a SELECT query with "GROUP BY" clause (AGGREGATION). 
**
** A dynamicly loadable file should be compiled shared.
** (something like: gcc -shared -o my_func.so myfunc.cc).
** You can easily get all switches right by doing:
** cd sql ; make udf_example.o
** Take the compile line that make writes, remove the '-c' near the end of
** the line and add -shared -o udf_example.so to the end of the compile line.
** The resulting library (udf_example.so) should be copied to some dir
** searched by ld. (/usr/lib ?)
** If you are using gcc, then you should be able to create the udf_example.so
** by simply doing 'make udf_example.so'.
**
** After the library is made one must notify mysqld about the new
** functions with the commands:
**
** CREATE AGGREGATE FUNCTION lv RETURNS STRING SONAME "lv.so"
**
** After this the functions will work exactly like native MySQL functions.
** Functions should be created only once.
**
** The functions can be deleted by:
**
** DROP FUNCTION lv;
**
** The CREATE FUNCTION and DROP FUNCTION update the func@mysql table. All
** Active function will be reloaded on every restart of server
** (if --skip-grant-tables is not given)
**
** If you ge problems with undefined symbols when loading the shared
** library, you should verify that mysqld is compiled with the -rdynamic
** option.
**
** If you can't get AGGREGATES to work, check that you have the column
** 'type' in the mysql.func table.  If not, run 'mysql_fix_privilege_tables'.
**
*/


#include "stdafx.h"

#ifdef STANDARD
#include <stdio.h>
#include <string.h>
#ifdef __WIN__
typedef unsigned __int64 ulonglong;	/* Microsofts 64 bit types */
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif /*__WIN__*/
#else
#include <my_global.h>
#include <my_sys.h>
#endif
#include <mysql.h>
#include <m_ctype.h>
#include <m_string.h>		// To get strmov()


/* These must be right or mysqld will not find the symbol! */
extern "C" {
my_bool lv_init( UDF_INIT* initid, UDF_ARGS* args, char* message );
void lv_deinit( UDF_INIT* initid );
void lv_reset( UDF_INIT* initid, UDF_ARGS* args, char* is_null, char *error );
void lv_clear( UDF_INIT* initid, char* is_null, char *error );
void lv_add( UDF_INIT* initid, UDF_ARGS* args, char* is_null, char *error );
char *lv(UDF_INIT * initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char * /*error*/ );
}

/*
** Syntax for the new aggregate commands are:
** create aggregate function <function_name> returns {string|real|integer}
**		  soname <name_of_shared_library>
**
*/


struct lv_data
{
  //ulong	count;
  ulong max_diff;
  ulong diff;
  ulong	length;
  char *concat_string;
  int *workspace;
};


/*************************************************************************
** init function for lv
** Arguments:
** initid	Points to a structure that the init function should fill.
**		This argument is given to all other functions.
**	my_bool maybe_null	1 if function can return NULL
**				Default value is 1 if any of the arguments
**				is declared maybe_null.
**	unsigned int decimals	Number of decimals.
**				Default value is max decimals in any of the
**				arguments.
**	unsigned int max_length  Length of string result.
**				The default value for integer functions is 21
**				The default value for real functions is 13+
**				default number of decimals.
**				The default value for string functions is
**				the longest string argument.
**	char *ptr;		A pointer that the function can use.
**
** args		Points to a structure which contains:
**	unsigned int arg_count		Number of arguments
**	enum Item_result *arg_type	Types for each argument.
**					Types are STRING_RESULT, REAL_RESULT
**					and INT_RESULT.
**	char **args			Pointer to constant arguments.
**					Contains 0 for not constant argument.
**	unsigned long *lengths;		max string length for each argument
**	char *maybe_null		Information of which arguments
**					may be NULL
**
** message	Error message that should be passed to the user on fail.
**		The message buffer is MYSQL_ERRMSG_SIZE big, but one should
**		try to keep the error message less than 80 bytes long!
**
** This function should return 1 if something goes wrong. In this case
** message should contain something usefull!
**************************************************************************/
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
  //data->count = 0;
  data->max_diff = max_diff;
  //data->end_count = 0;
  //data->length = 0;
  data->concat_string	= NULL;

  /* attempt to allocate memory in which to calculate levenshtein distance */
  data->workspace = new int[(args->lengths[1] + 1) * (args->lengths[1] + max_diff + 1)];


  initid->maybe_null	= 1;		  // The result may be null
  initid->max_length	= 65535;	// 65535 characters maximum (Maximum size of a MySQL "TEXT" field)
  initid->ptr = (char*)data;

  return 0;
}

/****************************************************************************
** Deinit function. This should free all resources allocated by
** this function.
** Arguments:
** initid	Return value from xxxx_init
****************************************************************************/
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
   //data->count = 0;
/*     data->end_count = 0; // Unlimited
    data->length = 0;*/
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
  //data->count = 0;
  //data->start_count = intStartCount-1;
  //data->end_count = intEndCount;

  data->diff = data->max_diff+1;//set start-difference to max+1 => without +1, nothing will be found
  data->length = 0;
  *is_null = 0;
}

void lv_add( UDF_INIT* initid, UDF_ARGS* args, char* /*is_null*/, char* /*message*/ )
{
  struct lv_data* data	= (struct lv_data*)initid->ptr;

  // Check if result already found
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

/* L E V E N S H T E I N */
	/* get a pointer to the memory allocated in lv_init() */
	int *d = (int*) data->workspace;
  	int b,c,f,g,h,i,j,k,min;
  //	if(n != 0 && m != 0) //this (args->args[0] && args->args[1]) helps to prevent the case of n=0 or m=0
  //	{
		/************************************************************************
    	** levenshtein step two
		************************************************************************/

		n++;
		m++;

		/* initialize first row to 0..n */
    	for (k = 0; k < n; k++)
		{
			d[k] = k;
		}

		/* initialize first column to 0..m */
    	for (k = 0; k < m; k++)
		{
      	d[k * n] = k;
		}

		/************************************************************************
    	** levenshtein step three
		************************************************************************/

		/* throughout these loops, g will be equal to i minus one */
		g = 0;
    	for (i = 1; i < n; i++)
		{
			/*********************************************************************
    		** levenshtein step four
			*********************************************************************/

			k = i;

			/* throughout the for j loop, f will equal j minus one */
			f = 0;
      	for (j = 1; j < m; j++)
			{
				/******************************************************************
				** levenshtein step five, six, seven
				******************************************************************/

				/* Seidenari's original was more like:
        		** d[j*n+i] = min(d[(j-1)*n+i]+1,
				**                min(d[j*n+i-1]+1,
				**                    d[(j-1)*n+i-1]+((s[i-1]==t[j-1]) ? 0 : 1)));
				**
				** thanks to algebra, (most or) all of the redundant calculations
				** have been removed; hopefully the variables aren't too confusing
				** :)
				**
				** NOTE: after I did this, I realized I could have just had the
				** compiler optimize the calculations for me... dang
				*/

				/* h = (j * n + i - n)  = ((j - 1) * n + i) */
				h = k;
				/* k = (j * n + i) */
				k += n;

				/* find the minimum among (the cell immediately above plus one),
				** (the cell immediately to the left plus one), and (the cell
				** diagonally above and to the left plus the cost [cost equals
				** zero if argument one's character at index g equals argument
				** two's character at index f; otherwise, cost is one]) 
        		** d[k] = min(d[h] + 1,
				**           min(d[k-1] + 1,
				**               d[h-1] + ((s[g] == t[f]) ? 0 : 1)));
				*/

				/* computing the minimum inline is much quicker than making
				** two function calls (or even one, as Seidenari used)
				**
				** NOTE: after I did this, I realized I could have just had the
				** compiler inline the functions
				*/

				min = d[h] + 1;
				b = d[k-1] + 1;
				c = d[h-1] + (s[g] == t[f] ? 0 : 1);

				if (b < min) { min = b; }
				if (c < min) { min = c; }

				d[k] = min;

				/* f will be equal to j minus one on the 
				** next iteration of this loop */
				f = j;
      	}

			/* g will equal i minus one for the next iteration */
			g = i;
		}

		/* Seidenari's original was:
    	** return (longlong) d[n*m-1]; */

    	//d[k] this is the calculated difference
/*  	}
	else if (n == 0)
	{
		diff = m;
	}
	else
	{
		diff = n;
	}*/
/* E N D */

        if(d[k] < data->diff) //Only if levenshtein-distance is smaller than the one before => save it
        {
          char *lpstrTotal = NULL;
	  lpstrTotal = (char *)malloc(n);//originally n+1


          // Append new string
          strncpy(lpstrTotal, s,n);

          // Force end of string (we never know)
          //lpstrTotal[n] = '\0';//originally active

          // Free previous string, if allocated
          if (data->concat_string != NULL)
          {
            free(data->concat_string);
          }

          // Store results in data structure
          data->concat_string = lpstrTotal;
          data->length = n-1;//originally n
          data->diff = (ulong) d[k]; //save new levenshtein-distance
        } else if(d[k] == data->diff) //Only if levenshtein-distance is equal to the one before => add it
        {
	      ulong intTotal = 0;
	      char *lpstrTotal = NULL;

	     // Compute total string size after concatenation
	      intTotal = n + data->length;

	      lpstrTotal = (char *)malloc(intTotal+1);

	      // Copy previous string
	      if (data->concat_string == NULL || data->length == 0)
	      {
	        lpstrTotal[0] = '\0';
	      }
	      else
	      {
	        strncpy(lpstrTotal, data->concat_string, data->length);
	        // Add a termination character in order to do a strncat (concatenation)
	        lpstrTotal[data->length] = '\0';
	        // Copy separator (if any, and if previous string is not empty/null)
	        strncat(lpstrTotal, ",", 1);
	      }

	      // Append new string
	      strncat(lpstrTotal, s ,n-1);

	      // Force end of string (we never know)
	      lpstrTotal[intTotal] = '\0';

	      // Free previous string, if allocated
	      if (data->concat_string != NULL)
	      {
	        free(data->concat_string);
	      }

	      // Store results in data structure
	      data->concat_string = lpstrTotal;
	      data->length = intTotal;
          data->diff = (ulong) d[k]; //save new levenshtein-distance
        }
      }
    }

  }

  // Count number of concatenated strings
 // data->count++;

}

/***************************************************************************
** UDF string function.
** Arguments:
** initid	Structure filled by xxx_init
** args		The same structure as to xxx_init. This structure
**		contains values for all parameters.
**		Note that the functions MUST check and convert all
**		to the type it wants!  Null values are represented by
**		a NULL pointer
** result	Possible buffer to save result. At least 255 byte long.
** length	Pointer to length of the above buffer.	In this the function
**		should save the result length
** is_null	If the result is null, one should store 1 here.
** error	If something goes fatally wrong one should store 1 here.
**
** This function should return a pointer to the result string.
** Normally this is 'result' but may also be an alloced string.
***************************************************************************/
char *lv(UDF_INIT * initid, UDF_ARGS * /*args*/, char * /*result*/, unsigned long *length, char *is_null, char * /*error*/ )
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

  // Set length of the ouput string
  (*length) = intResult;

  return data->concat_string;
}
