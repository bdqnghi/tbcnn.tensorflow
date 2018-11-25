

#ifndef TLX_SORT_STRINGS_RADIX_SORT_LCP_UNIFIED_HEADER
#define TLX_SORT_STRINGS_RADIX_SORT_LCP_UNIFIED_HEADER

#include <tlx/container/simple_vector.hpp>
#include <tlx/define/likely.hpp>
#include "sorter/local/strings/insertion_sort_unified.hpp"
#include "sorter/local/strings/multikey_quicksort_unified.hpp"
#include "strings/stringptr.hpp"

#include <iostream>
#include <stack>
#include <utility>
#include <vector>
namespace dss_schimek {


static const size_t g_inssort_threshold = 32;


template <typename StringShadowPtr>
struct RadixStep_CE0 {
    StringShadowPtr strptr;
    size_t idx, pos, bkt_size[256];

    typedef typename StringShadowPtr::StringSet StringSet;
    typedef typename StringSet::Iterator Iterator;

    RadixStep_CE0(const StringShadowPtr& in_strptr, size_t depth)
        : strptr(in_strptr) {

        const StringSet& ss = strptr.active();

        
        std::fill(bkt_size, bkt_size + 256, 0);
        for (Iterator i = ss.begin(); i != ss.end(); ++i)
            ++bkt_size[ss.get_uint8(ss[i], depth)];

        
        Iterator bkt_index[256];
        bkt_index[0] = strptr.shadow().begin();
        for (size_t i = 1; i < 256; ++i)
            bkt_index[i] = bkt_index[i - 1] + bkt_size[i - 1];
        size_t j = 0;
        while(!bkt_size[j]) ++j;
        while((bkt_index[j] - bkt_index[0])+ bkt_size[j] < ss.size())
        {
          strptr.set_lcp((bkt_index[j] - bkt_index[0]) + bkt_size[j], depth);
          ++j;
        }
        
        for (Iterator i = ss.begin(); i != ss.end(); ++i)
            *(bkt_index[ss.get_uint8(ss[i], depth)]++) = std::move(ss[i]);

        idx = 0; 
        pos = bkt_size[0];
        
        
        strptr.flip(0, pos).copy_back();
        for(size_t i = 1; i < pos; ++i)
          strptr.set_lcp(i, depth);
    }
};

template<typename StringShadowPtr>
static inline void
radixsort_CE0(const StringShadowPtr& str_shadow_ptr, size_t depth, size_t memory) {

    typedef RadixStep_CE0<StringShadowPtr> RadixStep;

    std::stack<RadixStep, std::vector<RadixStep> > radixstack;
    radixstack.emplace(str_shadow_ptr, depth);
    while (radixstack.size())
    {
        while (radixstack.top().idx < 255)
        {
            RadixStep& rs = radixstack.top();

            
            size_t bkt_size = rs.bkt_size[++rs.idx];
            if (bkt_size == 0) {
              
            }
            else if (bkt_size < g_inssort_threshold) {
              
              
              dss_schimek::insertion_sort(
                    rs.strptr.flip(rs.pos, bkt_size).copy_back(),
                    depth + radixstack.size(),
                    memory - sizeof(RadixStep) * radixstack.size());

                rs.pos += bkt_size;
            }
            else if (TLX_UNLIKELY(memory != 0 &&
                                  memory < sizeof(RadixStep) * radixstack.size() + 1))
            {
              dss_schimek::multikey_quicksort(
                    rs.strptr.flip(rs.pos, bkt_size).copy_back(),
                    depth + radixstack.size(),
                    memory - sizeof(RadixStep) * radixstack.size());
                
                                rs.pos += bkt_size;
            }
            else
            {
                rs.pos += bkt_size;
                radixstack.emplace(rs.strptr.flip(rs.pos - bkt_size, bkt_size),
                                   depth + radixstack.size());
                

            }
        }
        radixstack.pop();
    }
}

template <typename StringSet>
static inline void
radixsort_CE0(const dss_schimek::StringLcpPtr<StringSet>& strptr, size_t depth, size_t memory) {

    const StringSet& ss = strptr.active();
    if (ss.size() < g_inssort_threshold)
        return dss_schimek::insertion_sort(strptr, depth, memory);

    typedef RadixStep_CE0<dss_schimek::StringShadowLcpPtr<StringSet>> RadixStep;

    
    size_t memory_use =
        2 * sizeof(size_t) + sizeof(StringSet)
        + ss.size() * sizeof(typename StringSet::String);
    size_t memory_slack = 3 * sizeof(RadixStep);

    if (memory != 0 && memory < memory_use + memory_slack + 1)
        return dss_schimek::multikey_quicksort(strptr, depth, memory);

    typename StringSet::Container shadow = ss.allocate(ss.size());
    dss_schimek::StringShadowLcpPtr<StringSet> str_shadow_lcp_ptr(ss, StringSet(shadow), strptr.lcp_array());
    dss_schimek::radixsort_CE0(str_shadow_lcp_ptr, depth, memory);

    StringSet::deallocate(shadow);
}



template <typename StringShadowPtr>
struct RadixStep_CE2 {
  StringShadowPtr strptr;
  size_t idx, pos, bkt_size[256];

  typedef typename StringShadowPtr::StringSet StringSet;
  typedef typename StringSet::Iterator Iterator;

    RadixStep_CE2(const StringShadowPtr& in_strptr, size_t depth,
                  uint8_t* charcache) : strptr(in_strptr) {

        const StringSet& ss = strptr.active();
        const size_t n = ss.size();

        
        std::fill(bkt_size, bkt_size + 256, 0);
        uint8_t* cc = charcache;
        for (Iterator i = ss.begin(); i != ss.end(); ++i, ++cc)
            *cc = ss.get_uint8(ss[i], depth);
        for (cc = charcache; cc != charcache + n; ++cc)
            ++bkt_size[static_cast<uint8_t>(*cc)];

        
        Iterator bkt_index[256];
        bkt_index[0] = strptr.shadow().begin();
        for (size_t i = 1; i < 256; ++i)
            bkt_index[i] = bkt_index[i - 1] + bkt_size[i - 1];

        size_t j = 0;
        while(!bkt_size[j]) ++j;
        while((bkt_index[j] - bkt_index[0])+ bkt_size[j] < ss.size())
        {
          strptr.set_lcp((bkt_index[j] - bkt_index[0]) + bkt_size[j], depth);
          ++j;
        }

        
        cc = charcache;
        for (Iterator i = ss.begin(); i != ss.end(); ++i, ++cc)
            *(bkt_index[static_cast<uint8_t>(*cc)]++) = std::move(ss[i]);

        idx = 0; 
        pos = bkt_size[0];

        
        strptr.flip(0, pos).copy_back();
        for(size_t i = 1; i < pos; ++i)
          strptr.set_lcp(i, depth);

    }
};


template <typename StringSet>
static inline void
radixsort_CI3(const StringSet& ss, size_t depth, size_t memory);



template <typename StringSet, template<typename> typename StringShadowPtr>
static inline void
radixsort_CE2(const StringShadowPtr<StringSet>& strptr,
              uint8_t* charcache, size_t depth, size_t memory) {

    typedef RadixStep_CE2<StringShadowPtr<StringSet>> RadixStep;

    std::stack<RadixStep, std::vector<RadixStep> > radixstack;
    radixstack.emplace(strptr, depth, charcache);

    while (TLX_LIKELY(!radixstack.empty()))
    {
        while (TLX_LIKELY(radixstack.top().idx < 255))
        {
            RadixStep& rs = radixstack.top();

            
            size_t bkt_size = rs.bkt_size[++rs.idx];

            if (TLX_UNLIKELY(bkt_size == 0)) {
                
            }
            else if (bkt_size < g_inssort_threshold) {
              dss_schimek::insertion_sort(
                    rs.strptr.flip(rs.pos, bkt_size).copy_back(),
                    depth + radixstack.size(),
                    memory - sizeof(RadixStep) * radixstack.size());
                rs.pos += bkt_size;
            }
            else if (TLX_UNLIKELY(memory != 0 &&
                                  memory < sizeof(RadixStep) * radixstack.size() + 1))
            {
              dss_schimek::multikey_quicksort(
                    rs.strptr.flip(rs.pos, bkt_size).copy_back(),
                    depth + radixstack.size(),
                    memory - sizeof(RadixStep) * radixstack.size());
                rs.pos += bkt_size;
            }
            else
            {
                
                rs.pos += bkt_size;
                radixstack.emplace(rs.strptr.flip(rs.pos - bkt_size, bkt_size),
                                   depth + radixstack.size(), charcache);
            }
        }
        radixstack.pop();
    }
}

template <typename StringSet>
static inline void
radixsort_CE2(const dss_schimek::StringLcpPtr<StringSet>& strptr, size_t depth, size_t memory) {

    const StringSet& ss = strptr.active();
    if (ss.size() < g_inssort_threshold)
        return dss_schimek::insertion_sort(strptr, depth, memory);

    typedef RadixStep_CE2<dss_schimek::StringShadowLcpPtr<StringSet>> RadixStep;

    
    size_t memory_use =
        2 * sizeof(size_t) + sizeof(StringSet) + ss.size() * sizeof(uint8_t)
        + ss.size() * sizeof(typename StringSet::String);
    size_t memory_slack = 3 * sizeof(RadixStep);

    
    

    typename StringSet::Container shadow = ss.allocate(ss.size());
    dss_schimek::StringShadowLcpPtr<StringSet> str_shadow_lcp_ptr(ss, StringSet(shadow), strptr.lcp_array());

    uint8_t* charcache = new uint8_t[ss.size()];

    dss_schimek::radixsort_CE2<StringSet>(
        str_shadow_lcp_ptr, charcache, depth, memory - memory_use);

    delete[] charcache;
    StringSet::deallocate(shadow);
}





























































































































































































































































































































































































































































































} 

#endif 
