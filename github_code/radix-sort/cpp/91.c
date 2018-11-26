#if !defined (RADIXSORT_H)
#define RADIXSORT_H

#include "QueueLinked.h"

template < class T >
class RadixSort
{
   private:
      static void binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* item, int index));
      static void radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 1
      static void radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* item, int index));  //algorithm 2
 
   public:
      static T** radixSort(T** sort, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index));
};

template < class T >
T** RadixSort<T>::radixSort(T** unsorted, int num_to_sort, int num_chars, bool asc, char (*getRadixChar) (T* item, int index))
{
   T** array = T*[num_to_sort];

   for(int i = 0; i < num_to_sort; i++)
   {
      array[i] = unsorted[i];
   }

   if(asc)
   {
      radixSortAsc(array, num_to_sort, num_chars, getRadixChar);
   }

   else
   {
      radixSortDesc(array, num_to_sort, num_chars, getRadixChar);
   }

   return array;
}

template < class T >
void RadixSort<T>::radixSortAsc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS






}

template < class T >
void RadixSort<T>::binSort(QueueLinked<T>* bin, int curr_char, int num_chars, char (*getRadixChar) (T* st, int index))
{
   //DO THIS
   int num_queues = 37;
   QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];

   for(int i = 0; i < num_queues; i++ )
   {
      bins[i] = new QueueLinked<T>();
   }



}

template < class T >
void RadixSort<T>::radixSortDesc(T** sort, int n, int num_chars, char (*getRadixChar) (T* st, int index))
{
   int num_queues = 37;  //covers letters and digits
   QueueLinked<T>** bins = new QueueLinked<T>*[num_queues];  

   //must instantiate each of the queues
   for (int i = 0; i < num_queues; i++)
   {
      //DO THIS
      bins[i] = new QueueLinked<T>();
   }

   for (int i = num_chars; i > 0; i--)  //number of times to bin stuff
   {
      //DO THIS







   }

   for (int i = 0; i < num_queues; i++) 
   {
      delete bins[i];
   }

   delete[] bins;
}

#endif
