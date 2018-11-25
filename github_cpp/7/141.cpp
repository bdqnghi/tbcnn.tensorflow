

#include "bingmann-lcp_mergesort_kway.hpp"

namespace bingmann {

using namespace stringtools;




static inline void
lcp_mergesort_4way(string* strings, uintptr_t* lcp, size_t n)
{
    lcp_mergesort_kway<4>(strings, lcp, n);
}

static inline void
lcp_mergesort_8way(string* strings, uintptr_t* lcp, size_t n)
{
    lcp_mergesort_kway<8>(strings, lcp, n);
}

static inline void
lcp_mergesort_16way(string* strings, uintptr_t* lcp, size_t n)
{
    lcp_mergesort_kway<16>(strings, lcp, n);
}

static inline void
lcp_mergesort_64way(string* strings, uintptr_t* lcp, size_t n)
{
    lcp_mergesort_kway<64>(strings, lcp, n);
}

PSS_CONTESTANT(lcp_mergesort_4way, "bingmann/lcp_mergesort_4way",
               "4-way LCP-Mergesort by Timo Bingmann and Andreas Eberle")
PSS_CONTESTANT(lcp_mergesort_8way, "bingmann/lcp_mergesort_8way",
               "8-way LCP-Mergesort by Timo Bingmann and Andreas Eberle")
PSS_CONTESTANT(lcp_mergesort_16way, "bingmann/lcp_mergesort_16way",
               "16-way LCP-Mergesort by Timo Bingmann and Andreas Eberle")
PSS_CONTESTANT(lcp_mergesort_64way, "bingmann/lcp_mergesort_64way",
               "64-way LCP-Mergesort by Timo Bingmann and Andreas Eberle")




static inline void
lcp_mergesort_cache_4way(string* strings, lcp_t* lcp, uint8_t* cache, size_t n)
{
    lcp_mergesort_cache_kway<4>(strings, lcp, cache, n);
}

static inline void
lcp_mergesort_cache_8way(string* strings, lcp_t* lcp, uint8_t* cache, size_t n)
{
    lcp_mergesort_cache_kway<8>(strings, lcp, cache, n);
}

static inline void
lcp_mergesort_cache_16way(string* strings, lcp_t* lcp, uint8_t* cache, size_t n)
{
    lcp_mergesort_cache_kway<16>(strings, lcp, cache, n);
}

static inline void
lcp_mergesort_cache_64way(string* strings, lcp_t* lcp, uint8_t* cache, size_t n)
{
    lcp_mergesort_cache_kway<64>(strings, lcp, cache, n);
}

PSS_CONTESTANT(lcp_mergesort_cache_4way, "bingmann/lcp_mergesort_cache_4way",
               "4-way LCP-Mergesort by Timo Bingmann and Andreas Eberle")
PSS_CONTESTANT(lcp_mergesort_cache_8way, "bingmann/lcp_mergesort_cache_8way",
               "8-way LCP-Mergesort by Timo Bingmann and Andreas Eberle")
PSS_CONTESTANT(lcp_mergesort_cache_16way, "bingmann/lcp_mergesort_cache_16way",
               "16-way LCP-Mergesort by Timo Bingmann and Andreas Eberle")
PSS_CONTESTANT(lcp_mergesort_cache_64way, "bingmann/lcp_mergesort_cache_64way",
               "64-way LCP-Mergesort by Timo Bingmann and Andreas Eberle")

} 


