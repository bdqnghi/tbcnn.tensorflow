//! \file tao/algorithm/sorting/selection_sort.hpp
// Tao.Algorithm
//
// Copyright Fernando Pelliccioni 2016-2018
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// C++ Standard used: C++17

#ifndef TAO_ALGORITHM_SORTING_SELECTION_SORT_HPP_
#define TAO_ALGORITHM_SORTING_SELECTION_SORT_HPP_

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/type_attributes.hpp>
#include <tao/algorithm/iterator.hpp>
#include <tao/algorithm/rotate.hpp>

namespace tao { namespace algorithm {

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Mutable<I> && Domain<R, ValueType<I>>)
void selection_sort(I f, I l, R r) {
    //precondition: mutable_bounded_range(f, l)
    using std::swap;
    while (f != l) {
        swap(*f, *tao::algorithm::min_element(f, l, r));
        ++f;
    }
}

template <ForwardIterator I>
    requires(Mutable<I>)
inline
void selection_sort(I f, I l) {
    //precondition: mutable_bounded_range(f, l)
    selection_sort(f, l, std::less<>());
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Mutable<I> && Domain<R, ValueType<I>>)
void selection_sort_n(I f, DistanceType<I> n, R r) {
    //precondition: mutable_counted_range(f, n)
    using std::swap;
    while ( ! zero(n)) {
        auto m = std::get<0>(tao::algorithm::min_element_n(f, n, r));
        swap(*f, *m);
        step_n(f, n);
    }
}

template <ForwardIterator I>
    requires(Mutable<I>)
inline
void selection_sort_n(I f, DistanceType<I> n) {
    //precondition: mutable_counted_range(f, n)
    selection_sort_n(f, n, std::less<>());
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Mutable<I> && Domain<R, ValueType<I>>)
void selection_sort_stable(I f, I l, R r) {
    //precondition: mutable_bounded_range(f, l)
    while (f != l) {
        rotate_right_by_one(f, ++tao::algorithm::min_element(f, l, r));
        ++f;
    }
}

template <ForwardIterator I>
    requires(Mutable<I>)
void selection_sort_stable(I f, I l) {
    //precondition: mutable_bounded_range(f, l)
    selection_sort_stable(f, l, std::less<>());
}

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Mutable<I> && Domain<R, ValueType<I>>)
void selection_sort_stable_n(I f, DistanceType<I> n, R r) {
    //precondition: mutable_counted_range(f, n)
    while ( ! zero(n)) {
        auto m = std::get<0>(tao::algorithm::min_element_n(f, n, r));
        rotate_right_by_one(f, ++m);
        step_n(f, n);
    }
}

template <ForwardIterator I>
    requires(Mutable<I>)
void selection_sort_stable_n(I f, DistanceType<I> n) {
    //precondition: mutable_counted_range(f, n)
    selection_sort_stable_n(f, n, std::less<>());
}

}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SORTING_SELECTION_SORT_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED

#include <tao/benchmark/instrumented.hpp>


TEST_CASE("[selection_sort] testing selection_sort 6 elements random access sorted") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    selection_sort(begin(a), end(a), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[selection_sort] testing selection_sort 6 elements random access reverse") {
    using T = int;
    vector<T> a = {6, 5, 4, 3, 2, 1};
    selection_sort(begin(a), end(a), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[selection_sort] testing selection_sort 6 elements random access random") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5};
    selection_sort(begin(a), end(a), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[selection_sort] testing selection_sort_n 6 elements random access sorted") {
    using T = int;
    vector<T> a = {1, 2, 3, 4, 5, 6};
    selection_sort_n(begin(a), a.size(), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[selection_sort] testing selection_sort_n 6 elements random access reverse") {
    using T = int;
    vector<T> a = {6, 5, 4, 3, 2, 1};
    selection_sort_n(begin(a), a.size(), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("[selection_sort] testing selection_sort_n 6 elements random access random") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5};
    selection_sort_n(begin(a), a.size(), std::less<>());
    CHECK(a == vector<T>{1, 2, 3, 4, 5, 6});
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
