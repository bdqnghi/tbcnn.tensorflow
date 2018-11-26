#ifndef STX_ALGO_RADIX_SORT_HPP_
#define STX_ALGO_RADIX_SORT_HPP_

//  Radix sort implementation.
//  
//  TODO: RandomAccessIterator == T*, doesn't work with any RandomAccessIterator, e.g. deque::iterator.
//  
//  template <class Container>
//  inline void radix_sort(Container& c, radix_sort_params *p = 0);
//
//  template <class RandomAccessIterator>
//  inline void radix_sort(RandomAccessIterator first, RandomAccessIterator last, radix_sort_params *p = 0);
//
//  template <class RandomAccessIterator>
//  inline void radix_sort(RandomAccessIterator first, const std::size_t size, radix_sort_params *p = 0);
//
//  template <class Container, class SortFieldGetter>
//  inline void radix_sort(Container& c, SortFieldGetter getter, radix_sort_params *p = 0);
//
//  template <class RandomAccessIterator, class SortFieldGetter>
//  inline void radix_sort(RandomAccessIterator first, RandomAccessIterator last, SortFieldGetter getter, radix_sort_params *p = 0);
//
//  template <class RandomAccessIterator, class SortFieldGetter>
//  inline void radix_sort(RandomAccessIterator first, const std::size_t size, SortFieldGetter getter, radix_sort_params *p = 0);

#include <stx/common.hpp>
#include <stx/bit_cast.hpp>
#include <stx/begin_end.hpp>
#include <stx/type_traits.hpp>
#include <stx/misc/scoped_free.hpp>
#include <stx/ordered_unsigned.hpp>
#include <cstddef>
#include <cstring>
#include <climits>
#include <limits>
#include <iterator>
#include <vector>
#include <stdexcept>
#include <utility>
#include <functional> // std::unary_function

namespace stx {

struct radix_sort_params
{
    std::size_t radix_bits;

    radix_sort_params()
    {
        radix_bits = 8;
    }
};

template <class ElementType, class Enable = void>
struct radix_sort_field_t;

template <class T>
struct radix_sort_field_t<T,
    typename enable_if<
        is_arithmetic<T>::value || is_pointer<T>::value
    >::type> { typedef T type; };

template <class elem_t, class field_t>
struct default_radix_sort_field_getter: std::unary_function<elem_t, field_t>
{
    field_t* operator()(elem_t& x) const { return &x; }
};

template <class T> STX_ALWAYS_INLINE
void radix_sort_nullify(T *p, std::size_t size)
{
    typedef all_zero_bits_represent_null<T> bool_type;
    radix_sort_nullify(p, size, bool_type());
}

template <class T> STX_ALWAYS_INLINE
void radix_sort_nullify(T *p, std::size_t size, false_type)
{
    for (std::size_t i = 0; i < size; ++i) { p[i] = 0; }
}

template <class T> STX_ALWAYS_INLINE
void radix_sort_nullify(T *p, std::size_t size, true_type)
{
    memset(p, 0, sizeof(T)*size);
}

template <class ElementType, class SortFieldGetter> STX_ALWAYS_INLINE
void radix_sort_copy_element_impl(ElementType *dst, ElementType *src, SortFieldGetter getter, true_type)
{
    bit_cast(*dst, *src);
}

//  We can't just copy non-POD types with assignment operator, because
//  elem may contain invalid member variable value (e.g. of type float).
//  This will cause undefined behavior. Therefore we assign correct
//  null value before copying, and then set it back to original value.
template <class ElementType, class SortFieldGetter> STX_ALWAYS_INLINE
void radix_sort_copy_element_impl(ElementType *dst, ElementType *src, SortFieldGetter getter, false_type)
{
    typedef typename SortFieldGetter::result_type field_t;
    field_t null_val = 0, val;
    field_t *src_field = getter(*src), *dst_field = getter(*dst);
    bit_cast(val, *src_field);
    bit_cast(*src_field, null_val);
    *dst = *src;
    bit_cast(*src_field, val);
    bit_cast(*dst_field, val);
}

template <class ElementType, class SortFieldGetter> STX_ALWAYS_INLINE
void radix_sort_copy_element(ElementType *dst, ElementType *src, SortFieldGetter getter)
{
    typedef typename SortFieldGetter::result_type field_t;
    typedef typename is_same<
        SortFieldGetter, default_radix_sort_field_getter<ElementType, field_t>
    >::type is_default_getter;
    radix_sort_copy_element_impl(dst, src, getter, is_default_getter());
}

template <class RadixType, class RandomAccessIterator, class SortFieldGetter>
inline void radix_sort_impl(
    RandomAccessIterator first,
    const std::size_t size,
    SortFieldGetter getter,
    radix_sort_params *params = NULL)
{
    using namespace std;
    radix_sort_params default_params;
    if (!params) { params = &default_params; }
    typedef RandomAccessIterator iter_t;
    typedef typename iterator_traits<iter_t>::value_type elem_t;
    typedef typename SortFieldGetter::result_type field_t;
    typedef typename same_size_uint<field_t>::type value_t;
    typedef RadixType radix_t;

    iter_t last = first + size;
    const size_t radix_bits = params->radix_bits;
    const size_t value_bits = sizeof(value_t)*CHAR_BIT;
    const size_t num_passes = 1 + (value_bits - 1)/radix_bits;
    const value_t mask = (radix_bits < value_bits) ? ((((value_t) 1) << radix_bits) - 1) : ((value_t) -1);
    const size_t bucket_size = ((size_t) 1) << radix_bits;
    const size_t dst_index_table_size = bucket_size + 1;
    const size_t num_buckets = num_passes == 1 ? 1 : 2;

    vector<radix_t> buf_vec(num_buckets*bucket_size + dst_index_table_size);
    radix_t *buf = &buf_vec[0];
    radix_t *bucket = buf;
    radix_t *next_bucket = num_passes == 1 ? bucket : bucket + bucket_size;
    radix_t *dst_index_table = next_bucket + bucket_size;
    
    elem_t *src = &*first, *dst = src, *last_dst = src;
    elem_t *tmp_arr = &*first;
    scoped_free tmp_arr_sf;
    // TODO: we can perform an optimization for a single pass in the future
    //       and change "if" condition to: if (num_passes > 1)
    if (1) {
        tmp_arr = (elem_t*) malloc(sizeof(elem_t)*size);
        tmp_arr_sf.reset(tmp_arr);
        dst = tmp_arr;
    }
    // TODO: src must be of type iter_t, and dst of *elem_t !
    // RandomAccessIterator == T*
    
    size_t i, bucket_index, next_bucket_index;
    iter_t iter;
    elem_t *elem;
    field_t *field;
    value_t value = 0;
    value_t shift = 0, shift_delta = radix_bits;
    
    for (i = 0; i < size; ++i) {
        elem = &src[i];
        field = getter(*elem);
        to_ordered_unsigned(*field, value);
        bit_cast(*field, value);
        bucket_index = mask & (value >> shift);
        ++bucket[bucket_index];
    }
    
    bool last_pass = false;
    for (size_t pass = 0; pass < num_passes; ++pass, shift += shift_delta) {
        if (pass == num_passes - 1) last_pass = true;
        dst_index_table[0] = 0;
        for (i = 0; i < bucket_size; ++i) {
            dst_index_table[i+1] = bucket[i] + dst_index_table[i];
        }
        for (i = 0; i < bucket_size; ++i) {
            bucket[i] += dst_index_table[i];
        }
        if (!last_pass) {
            radix_sort_nullify(next_bucket, bucket_size);
            for (i = 0; i < size; ++i) {
                elem = &src[i];
                field = getter(*elem);
                bit_cast(value, *field);
                bucket_index = mask & (value >> shift);
                radix_sort_copy_element(&dst[dst_index_table[bucket_index]], elem, getter);
                dst_index_table[bucket_index] += 1;
                next_bucket_index = mask & (value >> (shift + shift_delta));
                ++next_bucket[next_bucket_index];
            }
        } else {
            for (i = 0; i < size; ++i) {
                elem = &src[i];
                field = getter(*elem);
                bit_cast(value, *field);
                bucket_index = mask & (value >> shift);
                from_ordered_unsigned(*field, value);
                radix_sort_copy_element(&dst[dst_index_table[bucket_index]], elem, getter);
                dst_index_table[bucket_index] += 1;
            }
        }
        last_dst = dst;
        swap(src, dst);
        swap(bucket, next_bucket);
    }
    src = &*first;
    if (last_dst != src) {
        for (i = 0; i < size; ++i) {
            src[i] = last_dst[i];
        }
    }
}

template <class RandomAccessIterator, class SortFieldGetter> inline
void radix_sort(
    RandomAccessIterator first,
    const std::size_t size,
    SortFieldGetter getter,
    radix_sort_params *params = NULL)
{
    if (size <= 1) return;
#   define _RADIX_SORT_IMPL(RadixType) \
        radix_sort_impl<RadixType, RandomAccessIterator>(first, size, getter, params)
    if      (size <= ((uint8_t)  -1)) { _RADIX_SORT_IMPL(uint8_t);  }
    else if (size <= ((uint16_t) -1)) { _RADIX_SORT_IMPL(uint16_t); }
    else if (size <= ((uint32_t) -1)) { _RADIX_SORT_IMPL(uint32_t); }
    else                              { _RADIX_SORT_IMPL(uint64_t); }
#   undef _RADIX_SORT_IMPL
}

template <class RandomAccessIterator, class SortFieldGetter> inline
void radix_sort(
    RandomAccessIterator first,
    RandomAccessIterator last,
    SortFieldGetter getter,
    radix_sort_params *params = NULL)
{
    radix_sort(first, (std::size_t) (std::distance(first, last)), getter, params);
}

template <class Container, class SortFieldGetter> inline
void radix_sort(
    Container& c,
    SortFieldGetter getter,
    radix_sort_params *params = NULL)
{
    radix_sort(begin(c), end(c), getter, params);
}

template <class RandomAccessIterator> inline
void radix_sort(
    RandomAccessIterator first,
    const std::size_t size,
    radix_sort_params *params = NULL)
{
    typedef RandomAccessIterator iter_t;
    typedef typename std::iterator_traits<iter_t>::value_type elem_t;
    typedef typename radix_sort_field_t<elem_t>::type field_t;
    typedef default_radix_sort_field_getter<elem_t, field_t> getter_t;
    radix_sort(first, size, getter_t(), params);
}

template <class RandomAccessIterator> inline
void radix_sort(
    RandomAccessIterator first,
    RandomAccessIterator last,
    radix_sort_params *params = NULL)
{
    typedef RandomAccessIterator iter_t;
    typedef typename std::iterator_traits<iter_t>::value_type elem_t;
    typedef typename radix_sort_field_t<elem_t>::type field_t;
    typedef default_radix_sort_field_getter<elem_t, field_t> getter_t;
    radix_sort(first, last, getter_t(), params);
}

template <class Container> inline
void radix_sort(
    Container& c,
    radix_sort_params *params = NULL)
{
    typedef typename Container::iterator iter_t;
    typedef typename std::iterator_traits<iter_t>::value_type elem_t;
    typedef typename radix_sort_field_t<elem_t>::type field_t;
    typedef default_radix_sort_field_getter<elem_t, field_t> getter_t;
    radix_sort(c, getter_t(), params);
}

} // namespace stx

#endif // STX_ALGO_RADIX_SORT_HPP_
