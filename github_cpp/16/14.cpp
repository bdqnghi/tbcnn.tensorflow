#ifndef SORTER_HPP
#define SORTER_HPP

#include <sorter/sequential_sorter.hpp>
#include <sorter/parallel_sorter.hpp>

namespace mysorter {

    
    
    

    struct insertion_tag{};
    struct quick_tag{};
    struct quick2_tag{};
    struct heap_tag{};
    struct shell_tag{};
    struct shell_tbb_tag{};
    struct shell_openmp_tag{};

    struct insertion{ using sort_tag = insertion_tag; }; 
    struct quick{ using sort_tag = quick_tag; };
    struct quick2{ using sort_tag = quick2_tag; };
    struct heap{ using sort_tag = heap_tag; };
    struct shell{ using sort_tag = shell_tag; };
    struct shell_tbb{ using sort_tag = shell_tbb_tag; };
    struct shell_openmp{ using sort_tag = shell_openmp_tag; };

    template <typename T> struct sort_traits { using sort_tag = T; };
    template <> struct sort_traits<insertion> { using sort_tag = insertion::sort_tag; };
    template <> struct sort_traits<quick> { using sort_tag = quick::sort_tag; };
    template <> struct sort_traits<quick2> { using sort_tag = quick2::sort_tag; };
    template <> struct sort_traits<heap> { using sort_tag = heap::sort_tag; };
    template <> struct sort_traits<shell> { using sort_tag = shell::sort_tag; };
    template <> struct sort_traits<shell_openmp> { using sort_tag = shell_openmp::sort_tag; };

    namespace detail {
        template <typename RandomAccessIterator, typename Predicate>
        void sort_(const insertion_tag, RandomAccessIterator first, RandomAccessIterator last, const Predicate pred) {
            insertion_sort(first, last, pred);
        };

        template <typename RandomAccessIterator, typename Predicate>
        void sort_(const quick_tag, RandomAccessIterator first, RandomAccessIterator last, const Predicate pred) {
            quick_sort(first, last, pred);
        };

        template <typename RandomAccessIterator, typename Predicate>
        void sort_(const quick2_tag, RandomAccessIterator first, RandomAccessIterator last, const Predicate pred) {
            quick_sort2(first, last, pred);
        };

        template <typename RandomAccessIterator, typename Predicate>
        void sort_(const heap_tag, RandomAccessIterator first, RandomAccessIterator last, const Predicate pred) {
            heap_sort(first, last, pred);
        };
        template <typename RandomAccessIterator, typename Predicate>
        void sort_(const shell_tag, RandomAccessIterator first, RandomAccessIterator last, const Predicate pred) {
            shell_sort(first, last, pred);
        };
        template <typename RandomAccessIterator, typename Predicate>
        void sort_(const shell_tbb_tag, RandomAccessIterator first, RandomAccessIterator last, const Predicate pred) {
            shell_sort_tbb(first, last, pred);
        };
        template <typename RandomAccessIterator, typename Predicate>
        void sort_(const shell_openmp_tag, RandomAccessIterator first, RandomAccessIterator last, const Predicate pred) {
            shell_sort_openmp(first, last, pred);
        };
        template <typename T, typename RandomAccessIterator, typename Predicate>
        void sort_(const T, RandomAccessIterator first, RandomAccessIterator last, const Predicate pred) {
            quick_sort2(first, last, pred);
        };
    }

    template <typename Tag = quick2, typename RandomAccessIterator, typename Predicate = LessPred<RandomAccessIterator>>
    void sort(const Tag, RandomAccessIterator first, RandomAccessIterator last, const Predicate pred = LessPred<RandomAccessIterator>()) {
        using sort_tag = typename sort_traits<Tag>::sort_tag;
        detail::sort_(sort_tag(), first, last, pred);
    }
}

#endif 
