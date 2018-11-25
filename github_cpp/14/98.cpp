

#ifndef DPP_RADIX_SORT_HH_
#define DPP_RADIX_SORT_HH_

#include <algorithm>
#include <limits>

#include <stdint.h>



namespace dpp {

  
  template <typename X, size_t bits>
  struct radix_sort_type
  {
    static unsigned int extract(const X x, size_t pos)
    {
      X::_requires_8bits_radix_width_for_custom_types();
      return 0;
    }
  };

  
  template <typename X>
  struct radix_sort_type<const X &, 8>
  {
    static unsigned int extract(const X x, size_t pos)
    {
      const uint8_t *d = (const uint8_t *)&x;
      return d[pos];
    }
  };

  
#define _DPP_RADIX_SORT_INT(type)					\
  	\
  template <size_t bits>						\
  struct radix_sort_type<unsigned type, bits>				\
  {									\
    static const size_t _bsize = 1 << bits;				\
    static const size_t _passes = sizeof(type) * 8 / bits + (bits % 8 != 0); \
									\
    static unsigned int extract(unsigned type x, size_t pos)		\
    {									\
      return (x >> (bits * pos)) & ((1 << bits) - 1);			\
    }									\
  };									\
									\
  	\
  template <size_t bits>						\
  struct radix_sort_type<signed type, bits>				\
  {									\
    static const size_t _bsize = 1 << bits;				\
    static const size_t _passes = sizeof(type) * 8 / bits + (bits % 8 != 0); \
									\
    static unsigned int extract(signed type x, size_t pos)		\
    {									\
      static const signed type s = std::numeric_limits<signed type>::min(); \
      return ((x - s) >> (bits * pos)) & ((1 << bits) - 1);		\
    }									\
  };

  _DPP_RADIX_SORT_INT(char);
  _DPP_RADIX_SORT_INT(short);
  _DPP_RADIX_SORT_INT(int);
  _DPP_RADIX_SORT_INT(long);
  _DPP_RADIX_SORT_INT(long long);

  
#define _DPP_RADIX_SORT_FLOAT(type)					\
  	\
  template <size_t bits>						\
  struct radix_sort_type<type, bits>					\
  {									\
    static const size_t _bsize = 1 << bits;				\
    static const size_t _passes = sizeof(type) * 8 / bits + (bits % 8 != 0); \
									\
    static unsigned int extract(type x, size_t pos)			\
    {									\
      switch (sizeof(type))						\
	{								\
          case 4: {							\
	    union { int32_t v; float f; };				\
	    f = x;							\
	    return ((((v >> 31) | (1 << 31)) ^ v) >> (bits * pos)) & ((1 << bits) - 1); \
	  }								\
          case 8: {							\
	    union { int64_t v; double f; };				\
	    f = x;							\
	    return ((((v >> 63) | (1ULL << 63)) ^ v) >> (bits * pos)) & ((1 << bits) - 1); \
	  }								\
	default:							\
	  std::abort();							\
	}								\
    }									\
  }

  _DPP_RADIX_SORT_FLOAT(float);
  _DPP_RADIX_SORT_FLOAT(double);

  
  template <typename X, size_t bits>
  struct _radix_sort
  {
    static const size_t _bsize = 1 << bits;
    static const size_t _passes = sizeof(X) * 8 / bits + (bits % 8 != 0);

    
    static void sort(X *in, X *next_in, X *out, size_t len)
    {
      size_t hist[_passes][_bsize];

      
      for (size_t j = 0; j < _passes; j++)
	for (size_t i = 0; i < _bsize; i++)
	  hist[j][i] = 0;

      
      for (size_t i = 0; i < len; i++)
	for (size_t j = 0; j < _passes; j++)
	  hist[j][radix_sort_type<X, bits>::extract(in[i], j)]++;

      
      for (size_t j = 0; j < _passes; j++)
	{
	  uintptr_t offset[_bsize], o;

	  
	  o = offset[0] = 0;
	  for (size_t i = 1; i < _bsize; i++)
	    o = offset[i] = o + hist[j][i - 1];

	  
	  for (size_t i = 0; i < len; i++)
	    {
	      size_t x = radix_sort_type<X, bits>::extract(in[i], j);
	      out[offset[x]++] = in[i];
	    }

	  
	  in = next_in;
	  std::swap(in, out);
	  next_in = in;
	}
    }

    
    static void sort_in(X *in, size_t len)
    {
      X tmp[len];

      sort(in, in, tmp, len);

      if (_passes % 2)
	for (size_t i = 0; i < len; i++)
	  in[i] = tmp[i];
    }
    
    
    static void sort_out(const X *in, X *out, size_t len)
    {
      if (_passes % 2)
	{
	  X tmp[len];

	  for (size_t i = 0; i < len; i++)
	    tmp[i] = in[i];
	  sort(tmp, tmp, out, len);
	}
      else if (_passes > 1)
	{
	  X tmp[len];
	  sort((X*)in, out, tmp, len);
	}
      else
	{
	  sort((X*)in, 0, out, len);
	}
    }
  };

  
  template <typename iterator>
  void radix_sort(const iterator &begin, const iterator &end)
  {
    typedef typename iterator::value_type type;
    size_t len = end - begin;

    _radix_sort<type, 8>::sort_in(&*begin, len);
  }

  
  template <typename iterator, size_t bits>
  void radix_sort(const iterator &begin, const iterator &end)
  {
    typedef typename iterator::value_type type;
    size_t len = end - begin;

    _radix_sort<type, bits>::sort_in(&*begin, len);
  }

  
  template <typename X>
  void radix_sort(X *begin, X *end)
  {
    typedef X type;
    size_t len = end - begin;

    _radix_sort<type, 8>::sort_in(begin, len);
  }

  
  template <typename X, size_t bits>
  void radix_sort(X *begin, X *end)
  {
    typedef X type;
    size_t len = end - begin;

    _radix_sort<type, bits>::sort_in(begin, len);
  }

  
  template <typename X>
  void radix_sort(const X *begin, const X *end, X *out)
  {
    typedef X type;
    size_t len = end - begin;

    _radix_sort<type, 8>::sort_out(begin, out, len);
  }

  
  template <typename X, size_t bits>
  void radix_sort(const X *begin, const X *end, X *out)
  {
    typedef X type;
    size_t len = end - begin;

    _radix_sort<type, bits>::sort_out(begin, out, len);
  }

}

#endif

