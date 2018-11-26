// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

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
				//! Singleton realization
				static SharedHeapsort<T>& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedHeapsort();

				//! Destructor. Should use only one time.
				virtual ~SharedHeapsort();

				//! Copy constructor. Do not implement.
				SharedHeapsort(const SharedHeapsort& root);

				//! Override equal operator. Do not implement.
				const SharedHeapsort& operator=(SharedHeapsort&);

			public:

				//! Sinks an element into the heap.
				void sink(T* array, s32 element, s32 max);

				//! Sorts an array with size 'size' using heapsort.
				void sort(T* arr, s32 size);

		};

		//! Singleton realization
		template<class T>
		inline SharedHeapsort<T>& SharedHeapsort<T>::getInstance()
		{
			static SharedHeapsort instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		template<class T>
		inline SharedHeapsort<T>::SharedHeapsort()
		{
		}

		//! Destructor. Should use only one time.
		template<class T>
		inline SharedHeapsort<T>::~SharedHeapsort()
		{
		}

		//! Sinks an element into the heap.
		template<class T>
		inline void SharedHeapsort<T>::sink(T* array, s32 element, s32 max)
		{
			while ((element << 1) < max) // there is a left child
			{
				s32 j = (element << 1);

				if (j + 1 < max && array[j] < array[j + 1])
				{
					j = j + 1; // take right child
				}

				if (array[element] < array[j])
				{
					T t = array[j]; // swap elements
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

		//! Sorts an array with size 'size' using heapsort.
		template<class T>
		inline void SharedHeapsort<T>::sort(T* arr, s32 size)
		{
			// for heapsink we pretent this is not c++, where
			// arrays start with index 0. So we decrease the array pointer,
			// the maximum always +2 and the element always +1

			T* virtualArray = arr - 1;
			s32 virtualSize = size + 2;
			s32 i;

			// build heap
			for (i = ((size - 1) / 2); i >= 0; --i)
			{
				sink(virtualArray, i + 1, virtualSize - 1);
			}

			// sort array
			for (i = size - 1; i >= 0; --i)
			{
				T t = arr[0];
				arr[0] = arr[i];
				arr[i] = t;
				sink(virtualArray, 1, i + 1);
			}
		}
	} // end namespace core
} // end namespace irrgame

#endif

