#ifndef _TBT_ALGORITHM_H
#define _TBT_ALGORITHM_H


#include <tbt/DeviceArray.h>


namespace tbt
{

	//! Sorts a device array with radix-sort.
	/**
	 * @tparam T         is the data type to be sorted. Allowed types are (at the moment) only cl_uint.
	 * @param  devArray  is the device array to be sorted. Radix-sort will be run on the device
	 *                   associated with \a devArray.
	 * \ingroup algorithm
	 */
	template<class T>
	void radixSort(DeviceArray<T> &devArray) {
		throw Error("radixSort: data type of device array not supported", Error::ecDataTypeNotSupported);
	}

	//! Sorts a subinterval of a device array from \a first to just before \a last with radix-sort.
	/**
	 * Radix-sort will be run on the device associated with the device array to which \a first and \a last point.
	 *
	 * \pre The iterators \a first and \a last must both be valid and point to the same device array.
	 *
	 * @tparam T      is the data type to be sorted. Allowed types are (at the moment) only cl_uint.
	 * @param  first  is an iterator pointing to the first position in the device array to be sorted. 
	 * @param  last   is an iterator pointing to one past the last position in the device array to be sorted. 
	 * \ingroup algorithm
	 */
	template<class T>
	void radixSort(typename DeviceArray<T>::iterator first, typename DeviceArray<T>::iterator last) {
		throw Error("radixSort: data type of device array not supported", Error::ecDataTypeNotSupported);
	}


	// specializations

	template<>
	void radixSort<cl_uint>(DeviceArray<cl_uint> &devArray);

	template<>
	void radixSort<cl_uint>(typename DeviceArray<cl_uint>::iterator first, typename DeviceArray<cl_uint>::iterator last);

}


#endif
