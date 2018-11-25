



#ifndef __IRR_HEAPSORT_H_INCLUDED__
#define __IRR_HEAPSORT_H_INCLUDED__

#include "compileConfig.h"

namespace irrgame
{
	namespace core
	{
		template<class T>
		class SharedHeapsort
		{
			public:
				
				static SharedHeapsort<T>& getInstance();

			private:
				
				SharedHeapsort();

				
				virtual ~SharedHeapsort();

				
				SharedHeapsort(const SharedHeapsort& root);

				
				const SharedHeapsort& operator=(SharedHeapsort&);

			public:

				
				void sink(T* array, s32 element, s32 max);

				
				void sort(T* arr, s32 size);

		};

		
		template<class T>
		inline SharedHeapsort<T>& SharedHeapsort<T>::getInstance()
		{
			static SharedHeapsort instance;
			return instance;
		}

		
		template<class T>
		inline SharedHeapsort<T>::SharedHeapsort()
		{
		}

		
		template<class T>
		inline SharedHeapsort<T>::~SharedHeapsort()
		{
		}

		
		template<class T>
		inline void SharedHeapsort<T>::sink(T* array, s32 element, s32 max)
		{
			while ((element << 1) < max) 
			{
				s32 j = (element << 1);

				if (j + 1 < max && array[j] < array[j + 1])
				{
					j = j + 1; 
				}

				if (array[element] < array[j])
				{
					T t = array[j]; 
					array[j] = array[element];
					array[element] = t;
					element = j;
				}
				else
				{
					break;
				}
			}
		}

		
		template<class T>
		inline void SharedHeapsort<T>::sort(T* arr, s32 size)
		{
			
			
			

			T* virtualArray = arr - 1;
			s32 virtualSize = size + 2;
			s32 i;

			
			for (i = ((size - 1) / 2); i >= 0; --i)
			{
				sink(virtualArray, i + 1, virtualSize - 1);
			}

			
			for (i = size - 1; i >= 0; --i)
			{
				T t = arr[0];
				arr[0] = arr[i];
				arr[i] = t;
				sink(virtualArray, 1, i + 1);
			}
		}
	} 
} 

#endif

