
#ifndef CPPSORT_SORTERS_HEAP_SORTER_H_
#define CPPSORT_SORTERS_HEAP_SORTER_H_




#include <functional>
#include <iterator>
#include <type_traits>
#include <cpp-sort/sorter_facade.h>
#include <cpp-sort/sorter_traits.h>
#include <cpp-sort/utility/functional.h>
#include <cpp-sort/utility/static_const.h>
#include "../detail/heapsort.h"
#include "../detail/iterator_traits.h"

namespace cppsort
{
    
    

    namespace detail
    {
        struct heap_sorter_impl
        {
            template<
                typename RandomAccessIterator,
                typename Compare = std::less<>,
                typename Projection = utility::identity,
                typename = std::enable_if_t<
                    is_projection_iterator_v<Projection, RandomAccessIterator, Compare>
                >
            >
            auto operator()(RandomAccessIterator first, RandomAccessIterator last,
                            Compare compare={}, Projection projection={}) const
                -> void
            {
                static_assert(
                    std::is_base_of<
                        std::random_access_iterator_tag,
                        iterator_category_t<RandomAccessIterator>
                    >::value,
                    "heap_sorter requires at least random-access iterators"
                );

                heapsort(first, last, compare, projection);
            }

            
            

            using iterator_category = std::random_access_iterator_tag;
            using is_always_stable = std::false_type;
        };
    }

    struct heap_sorter:
        sorter_facade<detail::heap_sorter_impl>
    {};

    
    

    namespace
    {
        constexpr auto&& heap_sort
            = utility::static_const<heap_sorter>::value;
    }
}

#endif 
