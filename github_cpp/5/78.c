#ifndef __SYSTEM_SORT_H__
#define __SYSTEM_SORT_H__
namespace Sys { namespace Collections {

	
	
	
	template<typename T>
	__device__ inline void __SwapValues(T &a, T &b)
	{
		T c = a;
		a = b;
		b = c;
	}

	
	
	
	template<typename T>
	class Sorter
	{
	public:
		__device__ virtual ~Sorter() { }
		__device__ virtual void Sort(T *base, unsigned int num) const = 0;
	};

	
	
	
	template<typename T, typename TDerived>
	class Sort_Quick : public Sorter<T>
	{
	public:
		__device__ virtual void Sort(T *base, unsigned int num) const
		{
			if (num <= 0)
				return;
			const int64 MAX_LEVELS = 128;
			int64 los[MAX_LEVELS], his[MAX_LEVELS];
			
			los[0] = 0;
			his[0] = num - 1;
			for (int64 level = 0; level >= 0;)
			{
				int64 lo = los[level];
				int64 hi = his[level];
				
				if ((hi - lo) >= 4 && level < (MAX_LEVELS - 1))
				{
					
					int64 pi = (lo + hi) / 2;
					
					__SwapValues(base[hi], base[pi]);
					
					T &pivot = base[hi--];
					
					do
					{
						while (static_cast<const TDerived *>(this)->Compare(base[lo], pivot) < 0) { if (++lo >= hi) break; }
						while (static_cast<const TDerived *>(this)->Compare(base[hi], pivot) > 0) { if (--hi <= lo) break; }
						if (lo >= hi) break;
						__SwapValues(base[lo], base[hi]);
					}
					while(++lo < --hi);
					
					
					while (static_cast<const TDerived *>(this)->Compare(base[lo], pivot) <= 0 && lo < his[level]) { lo++; }
					while (static_cast<const TDerived *>(this)->Compare(base[hi], pivot) >= 0 && los[level] < hi) { hi--; }
					
					__SwapValues(pivot, base[lo]);
					assert(level < MAX_LEVELS - 1);
					los[level + 1] = lo;
					his[level + 1] = his[level];
					his[level] = hi;
					level++;
				}
				else
				{
					
					for (; lo < hi; hi--)
					{
						int64 max = lo;
						for (int64 i = lo + 1; i <= hi; i++)
							if (static_cast<const TDerived *>(this)->Compare(base[i], base[max]) > 0) max = i;
						__SwapValues(base[max], base[hi]);
					}
					level--;
				}
			}
		}
	};

	
	
	
	template<typename T>
	class Sort_QuickDefault : public Sort_Quick<T, Sort_QuickDefault<T>>
	{
	public:
		__device__ int Compare(const T &a, const T &b) const { return a - b; }
	};

	
	
	
	template<>
	class Sort_QuickDefault<float> : public Sort_Quick<float, Sort_QuickDefault<float>>
	{
	public:
		__device__ int Compare(const float &a, const float &b) const { return (a < b ? - 1 : (a > b ? 1 : 0)); }
	};

	
	
	
	template<typename T, typename TDerived>
	class Sort_Heap : public Sorter<T>
	{
	public:
		__device__ virtual void Sort(T *base, unsigned int num) const
		{
			
#if 1
			
			for (unsigned int i = num / 2; i > 0; i--)
			{
				
				unsigned int parent = i - 1;
				for (unsigned int child = parent * 2 + 1; child < num; child = parent * 2 + 1)
				{
					if (child + 1 < num && static_cast<const TDerived *>(this)->Compare(base[child + 1], base[child]) > 0) child++;
					if (static_cast<const TDerived *>(this)->Compare(base[child], base[parent]) <= 0) break;
					__SwapValues(base[parent], base[child]);
					parent = child;
				}
			}
#else
			
			for (unsigned int i = 1; i < num; i++)
			{
				
				for (unsigned int child = i; child > 0;)
				{
					unsigned int parent = (child - 1) / 2;
					if (static_cast<const TDerived *>(this)->Compare(base[parent], base[child]) > 0) break;
					SwapValues(base[child], base[parent]);
					child = parent;
				}
			}
#endif
			
			for (unsigned int i = num - 1; i > 0; i--)
			{
				__SwapValues(base[0], base[i]);
				
				unsigned int parent = 0;
				for (unsigned int child = parent * 2 + 1; child < i; child = parent * 2 + 1)
				{
					if (child + 1 < i && static_cast<const TDerived *>( this )->Compare(base[child + 1], base[child]) > 0 ) child++;
					if (static_cast<const TDerived *>(this)->Compare(base[child], base[parent]) <= 0) break;
					__SwapValues( base[parent], base[child] );
					parent = child;
				}
			}
		}
	};

	
	
	
	template<typename T>
	class Sort_HeapDefault : public Sort_Heap<T, Sort_HeapDefault<T>>
	{
	public:
		__device__ int Compare(const T &a, const T &b) const { return a - b; }
	};

	
	
	
	template<typename T, typename TDerived>
	class Sort_Insertion : public Sorter<T>
	{
	public:
		__device__ virtual void Sort(T *base, unsigned int num) const
		{
			T *lo = base;
			T *hi = base + (num - 1);
			while (hi > lo)
			{
				T *max = lo;
				for (T *i = lo + 1; i <= hi; i++)
					if (static_cast<const TDerived *>(this)->Compare(*i, *max) > 0) max = i;
				__SwapValues(*max, *hi);
				hi--;
			}
		}
	};

	
	
	
	template<typename T>
	class Sort_InsertionDefault : public Sort_Insertion<T, Sort_InsertionDefault<T>>
	{
	public:
		__device__ int Compare(const T &a, const T &b) const { return a - b; }
	};

}}
#endif 
