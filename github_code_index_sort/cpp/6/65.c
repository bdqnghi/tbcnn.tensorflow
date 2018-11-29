/*******************************************************************************
 * tlx/sort/strings/radix_sort.hpp
 *
 * Out-of-place and in-place radix sort for strings. This is an internal
 * implementation header, see tlx/sort/strings.hpp for public front-end
 * functions.
 *
 * These are explicit stack-based most-significant-digit radix sort
 * implementations. All implementations were written by Timo Bingmann and are
 * based on work by Juha Kärkkäinen and Tommi Rantala. "Engineering Radix Sort
 * for Strings."  International Symposium on String Processing and Information
 * Retrieval (SPIRE). Springer, 2008.
 *
 * Part of tlx - http://panthema.net/tlx
 *
 * Copyright (C) 2015-2018 Timo Bingmann <tb@panthema.net>
 *
 * All rights reserved. Published under the Boost Software License, Version 1.0
 ******************************************************************************/

#ifndef TLX_SORT_STRINGS_RADIX_SORT_LCP_HEADER
#define TLX_SORT_STRINGS_RADIX_SORT_LCP_HEADER

#include <tlx/container/simple_vector.hpp>
#include <tlx/define/likely.hpp>
#include <tlx/sort/strings/multikey_quicksort.hpp>
#include <tlx/sort/strings/multikey_quicksort_lcp.hpp>
#include <tlx/sort/strings/string_set.hpp>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
#include "radix_sort.hpp"
namespace tlx {
namespace sort_strings_detail {

/******************************************************************************/


/******************************************************************************/
template <typename StringSet, typename LcpIterator>
struct RadixStep_CE0_lcp {
    StringShadowPtr<StringSet> strptr;
    LcpIterator lcp_it;
    size_t idx, pos, bkt_size[256];

    typedef typename StringSet::Iterator Iterator;

    RadixStep_CE0_lcp(const StringShadowPtr<StringSet>& in_strptr, size_t depth, LcpIterator lcp_it)
        : strptr(in_strptr) , lcp_it(lcp_it) {

        const StringSet& ss = strptr.active();

        // count character occurrences
        std::fill(bkt_size, bkt_size + 256, 0);
        for (Iterator i = ss.begin(); i != ss.end(); ++i)
            ++bkt_size[ss.get_uint8(ss[i], depth)];

        // prefix sum
        Iterator bkt_index[256];
        bkt_index[0] = strptr.shadow().begin();
        for (size_t i = 1; i < 256; ++i)
            bkt_index[i] = bkt_index[i - 1] + bkt_size[i - 1];
        size_t j = 0;
        while(!bkt_size[j]) ++j;
        while((bkt_index[j] - bkt_index[0])+ bkt_size[j] < ss.size())
        {
          *(lcp_it + (bkt_index[j] - bkt_index[0]) + bkt_size[j]) = depth;
          ++j;
        }
        // distribute
        for (Iterator i = ss.begin(); i != ss.end(); ++i)
            *(bkt_index[ss.get_uint8(ss[i], depth)]++) = std::move(ss[i]);

        idx = 0; // will increment to 1 on first process
        pos = bkt_size[0];

        // copy back finished strings in zeroth bucket
        strptr.flip(0, pos).copy_back();
        for(size_t i = 1; i < pos; ++i)
          *(lcp_it + i) = depth;
    }
};

/*
 * Out-of-place 8-bit radix-sort WITHOUT character caching.
 */
template <typename StringSet, typename LcpIterator>
static inline void
radixsort_CE0(const StringSet& ss, size_t depth, size_t memory, LcpIterator lcp_it) {

    if (ss.size() < g_inssort_threshold)
        return insertion_sort(ss, depth, memory, lcp_it);

    typedef RadixStep_CE0_lcp<StringSet, LcpIterator> RadixStep;

    // try to estimate the amount of memory used
    size_t memory_use =
        2 * sizeof(size_t) + sizeof(StringSet)
        + ss.size() * sizeof(typename StringSet::String);
    size_t memory_slack = 3 * sizeof(RadixStep);

    if (memory != 0 && memory < memory_use + memory_slack + 1)
        return multikey_quicksort(ss, depth, memory, lcp_it);

    typename StringSet::Container shadow = ss.allocate(ss.size());
    StringShadowPtr<StringSet> strptr(ss, StringSet(shadow));

    std::stack<RadixStep, std::vector<RadixStep> > radixstack;
    std::stack<size_t, std::vector<size_t> > lcp_offset_stack;
    radixstack.emplace(strptr, depth, lcp_it);
    lcp_offset_stack.emplace(0);
    const auto lcp_it_begin = lcp_it;
    while (radixstack.size())
    {
        while (radixstack.top().idx < 255)
        {
            RadixStep& rs = radixstack.top();
            size_t lcp_offset = rs.lcp_it - lcp_it;

            // process the bucket rs.idx
            size_t bkt_size = rs.bkt_size[++rs.idx];
            if (bkt_size == 0) {
              // done
            }
            else if (bkt_size < g_inssort_threshold) {
                insertion_sort(
                    rs.strptr.flip(rs.pos, rs.pos + bkt_size).copy_back(),
                    depth + radixstack.size(),
                    memory - sizeof(RadixStep) * radixstack.size(),
                    lcp_it + lcp_offset + rs.pos);

                rs.pos += bkt_size;
            }
            else if (TLX_UNLIKELY(memory != 0 &&
                                  memory < sizeof(RadixStep) * radixstack.size() + 1))
            {
                multikey_quicksort(
                    rs.strptr.flip(rs.pos, rs.pos + bkt_size).copy_back(),
                    depth + radixstack.size(),
                    memory - sizeof(RadixStep) * radixstack.size(), 
                    lcp_it + rs.pos + lcp_offset);
                
                                rs.pos += bkt_size;
            }
            else
            {
                rs.pos += bkt_size;
                radixstack.emplace(rs.strptr.flip(rs.pos - bkt_size, rs.pos),
                                   depth + radixstack.size(), lcp_it + rs.pos  -bkt_size + lcp_offset);
                // cannot add here, because rs may have invalidated

            }
        }
        radixstack.pop();
    }

    *lcp_it_begin = 0;
    StringSet::deallocate(shadow);
}

/******************************************************************************/
// Out-of-place 8-bit radix-sort with character caching.

template <typename StringSet, typename LcpIterator>
struct RadixStep_CE2_lcp {
    StringShadowPtr<StringSet> strptr;
    LcpIterator lcp_it;
    size_t idx, pos, bkt_size[256];

    typedef typename StringSet::Iterator Iterator;

    RadixStep_CE2_lcp(const StringShadowPtr<StringSet>& in_strptr, size_t depth,
                  uint8_t* charcache, LcpIterator lcp_it) : strptr(in_strptr), lcp_it(lcp_it) {

        const StringSet& ss = strptr.active();
        const size_t n = ss.size();

        // read characters and count character occurrences
        std::fill(bkt_size, bkt_size + 256, 0);
        uint8_t* cc = charcache;
        for (Iterator i = ss.begin(); i != ss.end(); ++i, ++cc)
            *cc = ss.get_uint8(ss[i], depth);
        for (cc = charcache; cc != charcache + n; ++cc)
            ++bkt_size[static_cast<uint8_t>(*cc)];

        // prefix sum
        Iterator bkt_index[256];
        bkt_index[0] = strptr.shadow().begin();
        for (size_t i = 1; i < 256; ++i)
            bkt_index[i] = bkt_index[i - 1] + bkt_size[i - 1];

        size_t j = 0;
        while(!bkt_size[j]) ++j;
        while((bkt_index[j] - bkt_index[0])+ bkt_size[j] < ss.size())
        {
          *(lcp_it + (bkt_index[j] - bkt_index[0]) + bkt_size[j]) = depth;
          ++j;
        }

        // distribute
        cc = charcache;
        for (Iterator i = ss.begin(); i != ss.end(); ++i, ++cc)
            *(bkt_index[static_cast<uint8_t>(*cc)]++) = std::move(ss[i]);

        idx = 0; // will increment to 1 on first process
        pos = bkt_size[0];

        // copy back finished strings in zeroth bucket
        strptr.flip(0, pos).copy_back();
        for(size_t i = 1; i < pos; ++i)
          *(lcp_it + i) = depth;

    }
};

/*
 * Out-of-place 8-bit radix-sort with character caching.
 */
template <typename StringSet, typename LcpIterator>
static inline void
radixsort_CE2(const StringShadowPtr<StringSet>& strptr,
              uint8_t* charcache, size_t depth, size_t memory, LcpIterator lcp_it) {

    typedef RadixStep_CE2_lcp<StringSet, LcpIterator> RadixStep;

    std::stack<RadixStep, std::vector<RadixStep> > radixstack;
    radixstack.emplace(strptr, depth, charcache, lcp_it);

    while (TLX_LIKELY(!radixstack.empty()))
    {
        while (TLX_LIKELY(radixstack.top().idx < 255))
        {
            RadixStep& rs = radixstack.top();
            size_t lcp_offset = rs.lcp_it - lcp_it;

            // process the bucket rs.idx
            size_t bkt_size = rs.bkt_size[++rs.idx];

            if (TLX_UNLIKELY(bkt_size == 0)) {
                // done
            }
            else if (bkt_size < g_inssort_threshold) {
                insertion_sort(
                    rs.strptr.flip(rs.pos, rs.pos + bkt_size).copy_back(),
                    depth + radixstack.size(),
                    memory - sizeof(RadixStep) * radixstack.size(),
                    lcp_it + lcp_offset + rs.pos);
                rs.pos += bkt_size;
            }
            else if (TLX_UNLIKELY(memory != 0 &&
                                  memory < sizeof(RadixStep) * radixstack.size() + 1))
            {
                multikey_quicksort(
                    rs.strptr.flip(rs.pos, rs.pos + bkt_size).copy_back(),
                    depth + radixstack.size(),
                    memory - sizeof(RadixStep) * radixstack.size(),
                    lcp_it + rs.pos + lcp_offset);
                rs.pos += bkt_size;
            }
            else
            {
                // have to increment first, as rs may be invalidated
                rs.pos += bkt_size;
                radixstack.emplace(rs.strptr.flip(rs.pos - bkt_size, rs.pos),
                                   depth + radixstack.size(), charcache, lcp_it + rs.pos - bkt_size + lcp_offset);
            }
        }
        radixstack.pop();
    }
}

template <typename StringSet, typename LcpIterator>
static inline void
radixsort_CI3(const StringSet& ss, size_t depth, size_t memory, LcpIterator lcp_it);

/*
 * Out-of-place 8-bit radix-sort with character caching.
 */
template <typename StringSet, typename LcpIterator>
static inline void
radixsort_CE2(const StringSet& ss, size_t depth, size_t memory, LcpIterator lcp_it) {

    if (ss.size() < g_inssort_threshold)
        return insertion_sort(ss, depth, memory, lcp_it);

    typedef RadixStep_CE2_lcp<StringSet, LcpIterator> RadixStep;

    // try to estimate the amount of memory used
    size_t memory_use =
        2 * sizeof(size_t) + sizeof(StringSet) + ss.size() * sizeof(uint8_t)
        + ss.size() * sizeof(typename StringSet::String);
    size_t memory_slack = 3 * sizeof(RadixStep);

    if (memory != 0 && memory < memory_use + memory_slack + 1)
        return radixsort_CI3(ss, depth, memory, lcp_it);

    typename StringSet::Container shadow = ss.allocate(ss.size());
    StringShadowPtr<StringSet> strptr(ss, StringSet(shadow));

    uint8_t* charcache = new uint8_t[ss.size()];

    radixsort_CE2<StringSet, LcpIterator>(
        strptr, charcache, depth, memory - memory_use, lcp_it);

    delete[] charcache;
    StringSet::deallocate(shadow);
}

template <typename BucketSizesType>
size_t get_next_non_empty_bucket_index(const BucketSizesType& bucket_sizes,  size_t size, size_t start)
{
  if (start >= size)
    return size;
  size_t j = start;
  while(j < size && !bucket_sizes[j]) ++j;
  return j;
}

/******************************************************************************/
// Out-of-place adaptive radix-sort with character caching

template <typename StringSet, typename LcpIterator>
struct RadixStep_CE3_lcp {
    enum { RADIX = 0x10000 };

    StringShadowPtr<StringSet> strptr;
    LcpIterator lcp_it;
    size_t idx, pos, bkt_size[RADIX];

    typedef typename StringSet::Iterator Iterator;

    RadixStep_CE3_lcp(const StringShadowPtr<StringSet>& in_strptr, size_t depth,
                  uint16_t* charcache, LcpIterator lcp_it) : strptr(in_strptr), lcp_it(lcp_it) {

        const StringSet& ss = strptr.active();
        const size_t n = ss.size();

        // read characters and count character occurrences
        std::fill(bkt_size, bkt_size + RADIX, 0);
        uint16_t* cc = charcache;
        for (Iterator i = ss.begin(); i != ss.end(); ++i, ++cc)
            *cc = ss.get_uint16(ss[i], depth);
        for (cc = charcache; cc != charcache + n; ++cc)
            ++bkt_size[static_cast<uint16_t>(*cc)];

        // prefix sum
        simple_vector<Iterator> bkt_index(RADIX);
        bkt_index[0] = strptr.shadow().begin();
        for (size_t i = 1; i < RADIX; ++i)
            bkt_index[i] = bkt_index[i - 1] + bkt_size[i - 1];

        size_t first = get_next_non_empty_bucket_index(bkt_size, RADIX, 0);
        size_t second = get_next_non_empty_bucket_index(bkt_size, RADIX, first + 1);
        
        while(second < RADIX)
        {
          if ((first >> 8) == (second >> 8))
            *(lcp_it + (bkt_index[first] - bkt_index[0]) + bkt_size[first]) = depth + 1; 
          else
            *(lcp_it + (bkt_index[first] - bkt_index[0]) + bkt_size[first]) = depth; 

          first = second;
          second = get_next_non_empty_bucket_index(bkt_size, RADIX, second + 1);
        }
        

        // distribute
        cc = charcache;
        for (Iterator i = ss.begin(); i != ss.end(); ++i, ++cc)
            *(bkt_index[static_cast<uint16_t>(*cc)]++) = std::move(ss[i]);

        idx = 0; // will increment to 1 on first process
        pos = bkt_size[0];

        // copy back finished strings in zeroth bucket
        strptr.flip(0, pos).copy_back();
        for(size_t i = 1; i < pos; ++i)
          *(lcp_it + i) = depth; 

    }
};

/*
 * Out-of-place adaptive radix-sort with character caching which starts with
 * 16-bit radix sort and then switching to 8-bit for smaller string sets.
 */
template <typename StringSet, typename LcpIterator>
static inline void
radixsort_CE3(const StringSet& ss, size_t depth, size_t memory, LcpIterator lcp_it) {
    enum { RADIX = 0x10000 };

    if (ss.size() < g_inssort_threshold)
        return insertion_sort(ss, depth, memory, lcp_it);

    if (ss.size() < RADIX)
        return radixsort_CE2(ss, depth, memory, lcp_it);

    typedef RadixStep_CE3_lcp<StringSet, LcpIterator> RadixStep;

    // try to estimate the amount of memory used
    size_t memory_use =
        2 * sizeof(size_t) + sizeof(StringSet) + ss.size() * sizeof(uint16_t)
        + ss.size() * sizeof(typename StringSet::String);
    size_t memory_slack = 3 * sizeof(RadixStep);

    if (memory != 0 && memory < memory_use + memory_slack + 1)
        return radixsort_CE2(ss, depth, memory, lcp_it);

    typename StringSet::Container shadow = ss.allocate(ss.size());
    StringShadowPtr<StringSet> strptr(ss, StringSet(shadow));

    uint16_t* charcache = new uint16_t[ss.size()];

    typedef std::stack<RadixStep, std::vector<RadixStep> > radixstack_type;
    radixstack_type radixstack;
    radixstack.emplace(strptr, depth, charcache, lcp_it);

    while (TLX_LIKELY(!radixstack.empty()))
    {
        while (TLX_LIKELY(radixstack.top().idx < RADIX - 1))
        {
            RadixStep& rs = radixstack.top(); 
            size_t lcp_offset = rs.lcp_it - lcp_it;

            // process the bucket rs.idx
            size_t bkt_size = rs.bkt_size[++rs.idx];
            if (TLX_UNLIKELY(bkt_size == 0)) {
                // done
            }
            else if (TLX_UNLIKELY((rs.idx & 0xFF) == 0)) { // zero-termination
                rs.strptr.flip(rs.pos, rs.pos + bkt_size).copy_back();
                for(size_t i = rs.pos + 1; i < (rs.pos + bkt_size); ++i)
                  *(lcp_it + lcp_offset + i) = depth + 2 * radixstack.size() - 1; 
                rs.pos += bkt_size;
            }
            else if (TLX_UNLIKELY(bkt_size < g_inssort_threshold))
            {
                insertion_sort(
                    rs.strptr.flip(rs.pos, rs.pos + bkt_size).copy_back(),
                    depth + 2 * radixstack.size(),
                    memory - memory_use - sizeof(RadixStep) * radixstack.size(),
                    lcp_it + lcp_offset + rs.pos);
                rs.pos += bkt_size;
            }
            else if (bkt_size < RADIX)
            {
                radixsort_CE2(
                    rs.strptr.flip(rs.pos, rs.pos + bkt_size),
                    reinterpret_cast<uint8_t*>(charcache),
                    depth + 2 * radixstack.size(),
                    memory - memory_use - sizeof(RadixStep) * radixstack.size(),
                    lcp_it + rs.pos + lcp_offset);
                rs.pos += bkt_size;
            }
            else if (TLX_UNLIKELY(memory != 0 &&
                                  memory < memory_use + sizeof(RadixStep) * radixstack.size() + 1))
            {
                multikey_quicksort(
                    rs.strptr.flip(rs.pos, rs.pos + bkt_size).copy_back(),
                    depth + 2 * radixstack.size(),
                    memory - memory_use - sizeof(RadixStep) * radixstack.size(),
                    lcp_it + rs.pos + lcp_offset);
                rs.pos += bkt_size;
            }
            else
            {
                // have to increment first, as rs may be invalidated
                rs.pos += bkt_size;
                radixstack.emplace(
                    rs.strptr.flip(rs.pos - bkt_size, rs.pos),
                    depth + 2 * radixstack.size(), charcache, lcp_it + rs.pos - bkt_size + lcp_offset);
            }
        }
        radixstack.pop();
    }

    delete[] charcache;
    StringSet::deallocate(shadow);
}

/******************************************************************************/
// In-place 8-bit radix-sort with character caching.

template <typename StringSet, typename LcpIterator>
struct RadixStep_CI2_lcp {

    typedef typename StringSet::Iterator Iterator;
    typedef typename StringSet::String String;
    LcpIterator lcp_it;

    size_t idx;
    Iterator pos;
    size_t bkt_size[256];

    RadixStep_CI2_lcp(const StringSet& ss, size_t depth, uint8_t* charcache, LcpIterator lcp_it) : lcp_it(lcp_it) {
        const size_t n = ss.size();

        // read characters and count character occurrences
        std::fill(bkt_size, bkt_size + 256, 0);
        uint8_t* cc = charcache;
        for (Iterator i = ss.begin(); i != ss.end(); ++i, ++cc)
            *cc = ss.get_uint8(ss[i], depth);
        for (cc = charcache; cc != charcache + n; ++cc)
            ++bkt_size[static_cast<uint8_t>(*cc)];

        // inclusive prefix sum
        size_t bkt[256];
        bkt[0] = bkt_size[0];
        size_t last_bkt_size = bkt_size[0];
        for (size_t i = 1; i < 256; ++i) {
            bkt[i] = bkt[i - 1] + bkt_size[i];
            if (bkt_size[i]) last_bkt_size = bkt_size[i];
        }
        size_t j = 0;
        while(!bkt_size[j]) ++j;
        while(bkt[j] < ss.size())
        {
          *(lcp_it + bkt[j]) = depth;
          ++j;
        }

        // premute in-place
        for (size_t i = 0, j; i < n - last_bkt_size; )
        {
            String perm = std::move(ss[ss.begin() + i]);
            uint8_t permch = charcache[i];
            while ((j = --bkt[permch]) > i)
            {
                std::swap(perm, ss[ss.begin() + j]);
                std::swap(permch, charcache[j]);
            }
            ss[ss.begin() + i] = std::move(perm);
            i += bkt_size[permch];
        }

        pos = ss.begin() + bkt_size[0];
        idx = 0; // will increment to 1 on first process, bkt 0 is not sorted further
        for(size_t i = 1; i < bkt_size[0]; ++i)
          *(lcp_it + i) = depth; 
    }
};

/*
 * In-place 8-bit radix-sort with character caching.
 */
template <typename StringSet, typename LcpIterator>
static inline void
radixsort_CI2(const StringSet& ss, uint8_t* charcache,
              size_t depth, size_t memory, LcpIterator lcp_it) {

    typedef RadixStep_CI2_lcp<StringSet, LcpIterator> RadixStep;

    std::stack<RadixStep, std::vector<RadixStep> > radixstack;
    radixstack.emplace(ss, depth, charcache, lcp_it);

    while (TLX_LIKELY(!radixstack.empty()))
    {
        while (TLX_LIKELY(radixstack.top().idx < 255))
        {
            RadixStep& rs = radixstack.top();
            size_t lcp_offset = rs.lcp_it - lcp_it;

            // process the bucket rs.idx
            size_t bkt_size = rs.bkt_size[++rs.idx];

            if (TLX_UNLIKELY(bkt_size <= 1)) {
                // done
                rs.pos += bkt_size;
            }
            else if (bkt_size < g_inssort_threshold) {
                insertion_sort(
                    ss.sub(rs.pos, rs.pos + bkt_size),
                    depth + radixstack.size(),
                    memory - sizeof(RadixStep) * radixstack.size(),
                    lcp_it  + (rs.pos - ss.begin()));
                rs.pos += bkt_size;
            }
            else if (TLX_UNLIKELY(memory != 0 &&
                                  memory < sizeof(RadixStep) * radixstack.size() + 1))
            {
                multikey_quicksort(
                    ss.sub(rs.pos, rs.pos + bkt_size),
                    depth + radixstack.size(),
                    memory - sizeof(RadixStep) * radixstack.size(),
                    lcp_it + (rs.pos - ss.begin()) );
                rs.pos += bkt_size;
            }
            else
            {
                // have to increment first, as rs may be invalidated
                rs.pos += bkt_size;
                radixstack.emplace(ss.sub(rs.pos - bkt_size, rs.pos),
                                   depth + radixstack.size(), charcache, lcp_it +  (rs.pos - ss.begin()) - bkt_size);
            }
        }
        radixstack.pop();
    }
}
/*
 * In-place 8-bit radix-sort with character caching.
 */
template <typename StringSet, typename LcpIterator>
static inline void
radixsort_CI2(const StringSet& ss, size_t depth, size_t memory, LcpIterator lcp_it) {

    if (ss.size() < g_inssort_threshold)
        return insertion_sort(ss, depth, memory, lcp_it);

    typedef RadixStep_CI2_lcp<StringSet, LcpIterator> RadixStep;

    // try to estimate the amount of memory used
    size_t memory_use =
        2 * sizeof(size_t) + sizeof(StringSet) + ss.size() * sizeof(uint8_t);
    size_t memory_slack = 3 * sizeof(RadixStep);

    if (memory != 0 && memory < memory_use + memory_slack + 1)
        return multikey_quicksort(ss, depth, memory, lcp_it);

    uint8_t* charcache = new uint8_t[ss.size()];

    radixsort_CI2<StringSet>(ss, charcache, depth, memory - memory_use, lcp_it);

    delete[] charcache;
}

/******************************************************************************/
// In-place adaptive radix-sort with character caching

template <typename StringSet, typename LcpIterator>
struct RadixStep_CI3_lcp {
    enum { RADIX = 0x10000 };

    typedef typename StringSet::Iterator Iterator;
    typedef typename StringSet::String String;

    LcpIterator lcp_it;
    size_t idx;
    Iterator pos;
    size_t bkt_size[RADIX];

    RadixStep_CI3_lcp(const StringSet& ss, size_t depth, uint16_t* charcache, LcpIterator lcp_it) : lcp_it(lcp_it) {
        const size_t n = ss.size();

        // read characters and count character occurrences
        std::fill(bkt_size, bkt_size + RADIX, 0);
        uint16_t* cc = charcache;
        for (Iterator i = ss.begin(); i != ss.end(); ++i, ++cc)
            *cc = ss.get_uint16(ss[i], depth);
        for (cc = charcache; cc != charcache + n; ++cc)
            ++bkt_size[static_cast<uint16_t>(*cc)];

        // inclusive prefix sum
        simple_vector<size_t> bkt(RADIX);
        bkt[0] = bkt_size[0];
        size_t last_bkt_size = bkt_size[0];
        for (size_t i = 1; i < RADIX; ++i) {
            bkt[i] = bkt[i - 1] + bkt_size[i];
            if (bkt_size[i]) last_bkt_size = bkt_size[i];
        }
        
        size_t first = get_next_non_empty_bucket_index(bkt_size, RADIX, 0);
        size_t second = get_next_non_empty_bucket_index(bkt_size, RADIX, first + 1);
        
        while(second < RADIX)
        {
          if ((first >> 8) == (second >> 8))
            *(lcp_it + bkt[first]) = depth + 1; 
          else
            *(lcp_it + bkt[first]) = depth; 

          first = second;
          second = get_next_non_empty_bucket_index(bkt_size, RADIX, second + 1);
        }

        // premute in-place
        for (size_t i = 0, j; i < n - last_bkt_size; )
        {
            String perm = std::move(ss[ss.begin() + i]);
            uint16_t permch = charcache[i];
            while ((j = --bkt[permch]) > i)
            {
                std::swap(perm, ss[ss.begin() + j]);
                std::swap(permch, charcache[j]);
            }
            ss[ss.begin() + i] = std::move(perm);
            i += bkt_size[permch];
        }

        // will increment to 1 on first process, bkt 0 is not sorted further
        idx = 0;
        pos = ss.begin() + bkt_size[0];
        for(size_t i = 1; i < bkt_size[0]; ++i)
          *(lcp_it + i) = depth;
    }
};

/*
 * In-place adaptive radix-sort with character caching which starts with 16-bit
 * radix sort and then switching to 8-bit for smaller string sets.
 */
template <typename StringSet, typename LcpIterator>
static inline void
radixsort_CI3(const StringSet& ss, size_t depth, size_t memory, LcpIterator lcp_it) {
    enum { RADIX = 0x10000 };

    if (ss.size() < g_inssort_threshold)
        return insertion_sort(ss, depth, memory, lcp_it);

    if (ss.size() < RADIX)
        return radixsort_CI2(ss, depth, memory, lcp_it);

    typedef RadixStep_CI3_lcp<StringSet, LcpIterator> RadixStep;

    // try to estimate the amount of memory used
    size_t memory_use =
        2 * sizeof(size_t) + sizeof(StringSet) + ss.size() * sizeof(uint16_t);
    size_t memory_slack = 3 * sizeof(RadixStep);

    if (memory != 0 && memory < memory_use + memory_slack + 1)
        return radixsort_CI2(ss, depth, memory, lcp_it);

    uint16_t* charcache = new uint16_t[ss.size()];

    std::stack<RadixStep, std::vector<RadixStep> > radixstack;
    radixstack.emplace(ss, depth, charcache, lcp_it);

    while (TLX_LIKELY(!radixstack.empty()))
    {
        while (TLX_LIKELY(radixstack.top().idx < RADIX - 1))
        {
            RadixStep& rs = radixstack.top();

            // process the bucket rs.idx
            size_t bkt_size = rs.bkt_size[++rs.idx];

            if (TLX_UNLIKELY(bkt_size <= 1)) {
                // done
                rs.pos += bkt_size;
            }
            else if (TLX_UNLIKELY((rs.idx & 0xFF) == 0)) { // zero-termination
              for(size_t i = (rs.pos - ss.begin()) + 1; i < (rs.pos - ss.begin()) + bkt_size; ++i)
                *(lcp_it + i) = depth + 2 * radixstack.size() - 1; 

                rs.pos += bkt_size;
            }
            else if (TLX_UNLIKELY(bkt_size < g_inssort_threshold))
            {
                insertion_sort(
                    ss.sub(rs.pos, rs.pos + bkt_size),
                    depth + 2 * radixstack.size(),
                    memory - memory_use - sizeof(RadixStep) * radixstack.size(),
                    lcp_it + (rs.pos - ss.begin()));
                rs.pos += bkt_size;
            }
            else if (bkt_size < RADIX)
            {
                radixsort_CI2(ss.sub(rs.pos, rs.pos + bkt_size),
                              reinterpret_cast<uint8_t*>(charcache),
                              depth + 2 * radixstack.size(),
                              memory - memory_use - sizeof(RadixStep) * radixstack.size(),
                              lcp_it + (rs.pos - ss.begin()));
                rs.pos += bkt_size;
            }
            else if (TLX_UNLIKELY(memory != 0 &&
                                  memory < memory_use + sizeof(RadixStep) * radixstack.size() + 1))
            {
                multikey_quicksort(
                    ss.sub(rs.pos, rs.pos + bkt_size),
                    depth + 2 * radixstack.size(),
                    memory - memory_use - sizeof(RadixStep) * radixstack.size(), 
                    lcp_it + (rs.pos - ss.begin()));
                rs.pos += bkt_size;
            }
            else
            {
                // have to increment first, as rs may be invalidated
                rs.pos += bkt_size;
                radixstack.emplace(
                    ss.sub(rs.pos - bkt_size, rs.pos),
                    depth + 2 * radixstack.size(), charcache, lcp_it + (rs.pos - ss.begin()) - bkt_size);
            }
        }
        radixstack.pop();
    }

    delete[] charcache;
}

} // namespace sort_strings_detail
} // namespace tlx

#endif // !TLX_SORT_STRINGS_RADIX_SORT_HEADER
