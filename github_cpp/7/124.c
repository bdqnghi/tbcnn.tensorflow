
#ifndef CPPSORT_SORTERS_MERGE_INSERTION_SORTER_H_
#define CPPSORT_SORTERS_MERGE_INSERTION_SORTER_H_




#include <functional>
#include <iterator>
#include <type_traits>
#include <cpp-sort/sorter_facade.h>
#include <cpp-sort/sorter_traits.h>
#include <cpp-sort/utility/functional.h>
#include <cpp-sort/utility/static_const.h>
#include "../detail/iterator_traits.h"
#include "../detail/merge_insertion_sort.h"

namespace cppsort
{
    
    

    namespace detail
    {
        struct merge_insertion_sorter_impl
        {
            template<
                typename RandomAccessIterator,
                typename Compare = std::less<>,
                typename Projection = utility::identity,
                typename = std::enable_if_t<is_projection_iterator_v<
                    Projection, RandomAccessIterator, Compare
                >>
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
                    "merge_insertion_sorter requires at least random-access iterators"
                );

                merge_insertion_sort(first, last, compare, projection);
            }

            
            

            using iterator_category = std::random_access_iterator_tag;
            using is_always_stable = std::false_type;
        };
    }

    struct merge_insertion_sorter:
        sorter_facade<detail::merge_insertion_sorter_impl>
    {};

    
    

    namespace
    {
        constexpr auto&& merge_insertion_sort
            = utility::static_const<merge_insertion_sorter>::value;
    }
}

#endif 
