


#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include "sort.h"

template <class T>
   class SelectionSort : public Sort<T>   
   {
   public:
      SelectionSort();
      ~SelectionSort();
      void doit (T glob[], int size);
   };

template <class T>
   inline SelectionSort<T>::SelectionSort(){
   }

template <class T>
   inline SelectionSort<T>::~SelectionSort(){
   }

template <class T>
   inline void SelectionSort<T>::doit(T glob[], int size){
      int min;
      for (int i = 0; i < size-1; i++)
      {
         min = i;
         for (int j = i+1; j < size; j++)
         {
            if (glob[j] < glob[min])
               min = j;
         }
         swap(glob[i],glob[min]);
      }
   
   }
	#endif

