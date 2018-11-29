#ifndef _TBT_RADIX_SORT_H
#define _TBT_RADIX_SORT_H


#include <tbt/Module.h>
#include <tbt/DeviceArray.h>


namespace tbt
{

	//! Radix-sort module.
	/**
	 * \ingroup algorithm
	 */
	class RadixSort : public Module
	{
		static cl::Kernel  m_kernelCounting;
		static cl::Kernel  m_kernelPermute;

		static cl::Kernel  m_kernelPrescanSum;
		static cl::Kernel  m_kernelPrescan;
		static cl::Kernel  m_kernelPrescanWithOffset;

		static cl::Kernel m_kernelPrescanUpSweep;
		static cl::Kernel m_kernelPrescanDownSweep;

		static cl::Kernel m_kernelPrescanReduce;
		static cl::Kernel m_kernelPrescanLocal;
		static cl::Kernel m_kernelPrescanLocal64;
		static cl::Kernel m_kernelPrescanBottom;
		static cl::Kernel m_kernelTester;

		cl_uint m_nElements;
		cl_uint m_numGroups;
		cl_uint m_numPrescanGroups;
		cl_uint m_prescanInterval;

		DeviceController *m_devCon;
		DeviceArray<cl_uint> *m_array_gcount;
		DeviceArray<cl_uint> *m_array_psum;

		double m_tKernelCounting;
		double m_tKernelPrescanSum;
		double m_tKernelPrescan;
		double m_tKernelPrescanWithOffset;
		double m_tKernelPermute;

		double m_totalTime;

	public:
		//! Constructs a radix-sort module.
		RadixSort() {
			m_array_gcount = m_array_psum = 0;
			m_devCon = 0;
		}

		//! Runs radix-sort for array \a a with \a n elements.
		void run(DeviceArray<cl_uint> &devArray);

		void run(DeviceArray<cl_uint>::iterator first, DeviceArray<cl_uint>::iterator last);

		//! Returns total running time of counting kernels (in milliseconds).
		double totalTimeKernelCounting         () const { return m_tKernelCounting; }

		//! Returns total running time of prescanSum kernels (in milliseconds).
		double totalTimeKernelPrescanSum       () const { return m_tKernelPrescanSum;  }

		//! Returns total running time of prescan kernels (in milliseconds).
		double totalTimeKernelPrescan          () const { return m_tKernelPrescan;  }

		//! Returns total running time of prescanWithOffset kernels (in milliseconds).
		double totalTimeKernelPrescanWithOffset() const { return m_tKernelPrescanWithOffset;  }

		//! Returns total running time of permute kernels (in milliseconds).
		double totalTimeKernelPermute          () const { return m_tKernelPermute;  }

		//! Returns total running time of all kernels (in milliseconds).
		double totalTimeKernels() const {
			return m_tKernelCounting + m_tKernelPrescanSum + m_tKernelPrescan + m_tKernelPrescanWithOffset + m_tKernelPermute;
		}

		//! Returns total running time (in milliseconds (including data transfer and kernel launch times).
		double totalTime() const { return m_totalTime; }


		static double testKernelPrescanReduce(DeviceArray<cl_uint> &a, DeviceArray<cl_uint> &sum, cl_uint n, cl_uint C);
		static double testKernelPrescanLocal(DeviceArray<cl_uint> &sum, cl_uint C);
		static double testKernelPrescanBottom(DeviceArray<cl_uint> &a, DeviceArray<cl_uint> &sum, cl_uint n, cl_uint C);
		static double testKernelTester(DeviceArray<cl_uint> &a, DeviceArray<cl_uint> &sum, cl_uint n, cl_uint C);

	private:
		void runSingle(DeviceArray<cl_uint> &bufferSrc, DeviceArray<cl_uint> &bufferTgt, cl_uint shift);

		static void assureKernelsLoaded();
	};

}

#endif
