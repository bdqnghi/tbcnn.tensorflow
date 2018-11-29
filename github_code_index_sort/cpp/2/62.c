#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

//int array[] = {1,3,5,2,4,6,8,9,7,11,10,12};
int result_array[]  = {0,0,1,4,6,8,9,7,2,13,12};
int array[] = {1,2,3,4,5,6};
int elements = 6;


int merge_sort(int inArray[], int total_elements, bool count_inversion)
{
// cout << __FUNCTION__ << "total_elements" << total_elements << endl;
int inversion = 0;


 if (total_elements <= 1 ) {
       return 1;
 }

 merge_sort(&inArray[0], total_elements/2, false);
 merge_sort(&inArray[(total_elements/2)], total_elements - (total_elements/2) , false);

 int *arraya = &inArray[0];
 int *arrayb = &inArray[(total_elements/2)]; 

 int i=0, j=0, k=0;
 
 cout << "Dumping Array A " << total_elements << " :";
 for(int m = 0; m < total_elements/2; m++)
   cout << arraya[m] << " " ;
   cout << endl;

 cout << "Dumping Array B " << total_elements << " :";
 for(int m = 0; m < total_elements - total_elements/2; m++)
   cout << arrayb[m] << " " ;
   cout << endl;

 for( k = 0; k < total_elements; k++)
 {
 if (arraya[i] < arrayb[j])
 {
   if ( i < total_elements/2 )
   {
   result_array[k] = arraya[i];
   i++;
   }
   else
   {
      result_array[k] = arrayb[j];
      j++; 
   }
 }
 else
 {
   if ( j < (total_elements - total_elements/2) )
   {
      result_array[k] = arrayb[j];
      j++; 
   if (count_inversion) 
   {
     inversion += (total_elements/2 - i) ;
   }
   }
   else
   {
      result_array[k] = arraya[i];
      i++;
   }
 }
 }

 for (k =0; k < total_elements; k++)
 {
   inArray[k] = result_array[k];
 }

 cout << "Level Sorted:";
 for(int m = 0; m < total_elements; m++)
   cout << result_array[m] << " " ;
   cout << endl;



 if (count_inversion)
 {
   cout << "Need to count inversion " << inversion << endl;
 }



}



int
 main(int argc, char **argv)
{
    merge_sort (array, elements, true);
}
