// JASL: For more information see https://github.com/matepek/jasl
//
// Copyright (c) 2018 Mate Pek
//
// This code is licensed under the MIT License (MIT).

/** @file */

#pragma once

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "jasl/jasl_internal/jasl_common.hpp"
#include "jasl/jasl_internal/jasl_feature_test_macro.hpp"

namespace jasl {
namespace nonstd {

template <typename CharT, typename Traits = std::char_traits<CharT>>
class basic_string_view;

typedef basic_string_view<char> string_view;
typedef basic_string_view<wchar_t> wstring_view;
typedef basic_string_view<char16_t> u16string_view;
typedef basic_string_view<char32_t> u32string_view;

}  // namespace nonstd
}  // namespace jasl

#if defined(JASL_USE_JASL_STRING_VIEW_AS_BASE) && \
    defined(JASL_USE_STD_STRING_VIEW_AS_BASE)
#  error "Both defines cannot be used at the same time."
#elif defined(JASL_USE_JASL_STRING_VIEW_AS_BASE)
#  define JASL_INNER_USE_STD_STRING_VIEW_AS_BASE 0
#elif defined(JASL_USE_STD_STRING_VIEW_AS_BASE)
#  define JASL_INNER_USE_STD_STRING_VIEW_AS_BASE 1
#elif !defined(JASL_USE_JASL_STRING_VIEW_AS_BASE) && \
    !defined(JASL_USE_STD_STRING_VIEW_AS_BASE)
/* fallback logic */
#  if defined(JASL_cpp_lib_string_view)
#    define JASL_INNER_USE_STD_STRING_VIEW_AS_BASE 1
#  else
#    define JASL_INNER_USE_STD_STRING_VIEW_AS_BASE 0
#  endif
#else
#  error "Something is really wrong."
#endif

#if JASL_INNER_USE_STD_STRING_VIEW_AS_BASE

#  include <string_view>

namespace jasl {
template <typename CharT, typename Traits = std::char_traits<CharT>>
using basic_string_view = std::basic_string_view<CharT, Traits>;
}  // namespace jasl

#else  // JASL_INNER_USE_STD_STRING_VIEW_AS_BASE

namespace jasl {
/**
 * If JASL_USE_STD_STRING_VIEW_AS_BASE is defined: it is std::basic_string_view
 *
 * If JASL_USE_JASL_STRING_VIEW_AS_BASE is defined it is
 *   jasl::nonstd::basic_string_view.
 *
 * If none if them are defined and there is
 *   std::basic_string_view it is std::basic_string_view else
 *   jasl::nonstd::basic_string_view.
 */
template <typename CharT, typename Traits = std::char_traits<CharT>>
using basic_string_view = nonstd::basic_string_view<CharT, Traits>;
}  // namespace jasl

#endif  // JASL_INNER_USE_STD_STRING_VIEW_AS_BASE

namespace jasl {
typedef basic_string_view<char> string_view;
typedef basic_string_view<wchar_t> wstring_view;
typedef basic_string_view<char16_t> u16string_view;
typedef basic_string_view<char32_t> u32string_view;
}  // namespace jasl

namespace jasl {
namespace nonstd {

/**
 * This class is an optinal substitution of the [std::string_view]
 * for those who have no C++17. To use this as the base class, define
 * JASL_USE_JASL_STRING_VIEW_AS_BASE. The class only has basic
 * functionality. (Please open an issue or endorse an existing if you would like
 * to add some functionality.)
 */

template <typename CharT, typename Traits>
class basic_string_view {
  const CharT* _ptr;
  size_t _size;

 public:
  // types
  typedef Traits traits_type;
  typedef CharT value_type;
  typedef CharT* pointer;
  typedef const CharT* const_pointer;
  typedef CharT& reference;
  typedef const CharT& const_reference;
  typedef const_pointer const_iterator;
  typedef const_iterator iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef const_reverse_iterator reverse_iterator;
  typedef size_t size_type;
  typedef std::ptrdiff_t difference_type;
  static constexpr size_type npos = static_cast<size_type>(-1);

 public:
  constexpr basic_string_view() noexcept : _ptr(nullptr), _size(0) {}

  constexpr basic_string_view(const CharT* ptr, size_type size) noexcept
      : _ptr(ptr), _size(size) {}

  constexpr basic_string_view(const basic_string_view& other) noexcept
      : _ptr(other._ptr), _size(other._size) {}

  JASL_CONSTEXPR_CXX14 basic_string_view& operator=(
      const basic_string_view& other) noexcept {
    _ptr = other._ptr;
    _size = other._size;
    return *this;
  }

  ~basic_string_view() noexcept = default;

#if defined(JASL_SUPPORT_STD_TO_JASL)
#  if defined(JASL_cpp_lib_string_view)
  template <
      typename T,
      typename = typename std::enable_if<
          std::is_convertible<const T&,
                              std::basic_string_view<CharT, Traits>>::value &&
          !std::is_convertible<const T&, const CharT*>::value>::type>
  explicit constexpr basic_string_view(const T& s) noexcept(
      noexcept(s.data()) && noexcept(s.size())) {
    std::basic_string_view<CharT, Traits> sv(s);
    _ptr = sv.data();
    _size = sv.size();
  }

  JASL_CONSTEXPR_CXX14 basic_string_view&
  operator=(const std::basic_string_view<CharT, Traits>& s) noexcept(
      noexcept(s.data()) && noexcept(s.size())) {
    _ptr = s.data();
    _size = s.size();
    return *this;
  }
#  else
  template <typename AllocatorT>
  constexpr basic_string_view(
      const std::basic_string<CharT, Traits, AllocatorT>&
          s) noexcept(noexcept(s.data()) && noexcept(s.size()))
      : _ptr(s.data()), _size(s.size()) {}

  template <typename AllocatorT>
  JASL_CONSTEXPR_CXX14 basic_string_view&
  operator=(const std::basic_string<CharT, Traits, AllocatorT>& s) noexcept(
      noexcept(s.data()) && noexcept(s.size())) {
    _ptr = s.data();
    _size = s.size();
    return *this;
  }
#  endif
#endif

#if defined(JASL_SUPPORT_JASL_TO_STD)
#  if defined(JASL_cpp_lib_string_view)
  operator std::basic_string_view<CharT, Traits>() const noexcept(
      std::is_nothrow_constructible<std::basic_string_view<CharT, Traits>,
                                    const CharT*,
                                    size_t>::value) {
    return std::basic_string_view<CharT, Traits>(_ptr, _size);
  }
#  else
  template <typename AllocatorT>
  operator std::basic_string<CharT, Traits, AllocatorT>() const
      noexcept(std::is_nothrow_constructible<
               std::basic_string<CharT, Traits, AllocatorT>,
               const CharT*,
               size_t>::value) {
    return std::basic_string<CharT, Traits, AllocatorT>(_ptr, _size);
  }
#  endif
#endif

  constexpr const_iterator begin() const noexcept { return cbegin(); }
  constexpr const_iterator end() const noexcept { return cend(); }
  constexpr const_iterator cbegin() const noexcept { return _ptr; }
  constexpr const_iterator cend() const noexcept { return _ptr + _size; }
  constexpr const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(cend());
  }
  constexpr const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(cbegin());
  }
  constexpr const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(cend());
  }
  constexpr const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(cbegin());
  }

  constexpr bool empty() const noexcept { return _size == 0; }
  constexpr const CharT* data() const noexcept { return _ptr; }
  constexpr size_type size() const noexcept { return _size; }
  constexpr size_type length() const noexcept { return _size; }

  constexpr const_reference operator[](size_type pos) const {
    return _ptr[pos];
  }

  JASL_CONSTEXPR_CXX14 const_reference at(size_type pos) const {
    if (pos >= size())
      JASL_THROW(std::out_of_range("string_view::substr"));
    return _ptr[pos];
  }

  constexpr const_reference front() const noexcept {
    JASL_ASSERT(!empty(), "string_view::front(): string is empty");
    return _ptr[0];
  }

  constexpr const_reference back() const noexcept {
    JASL_ASSERT(!empty(), "string_view::back(): string is empty");
    return _ptr[_size - 1];
  }

  JASL_CONSTEXPR_CXX14 void swap(basic_string_view& other) noexcept {
    const value_type* p = _ptr;
    _ptr = other._ptr;
    other._ptr = p;

    size_type s = _size;
    _size = other._size;
    other._size = s;
  }

  size_type copy(CharT* s, size_type n, size_type pos = 0) const {
    if (pos > size())
      JASL_THROW(std::out_of_range("string_view::copy"));
    size_type rlen = std::min(n, size() - pos);
    Traits::copy(s, data() + pos, rlen);
    return rlen;
  }

  JASL_CONSTEXPR_CXX14 basic_string_view substr(size_type pos,
                                                size_type count = npos) const {
    if (pos > size())
      JASL_THROW(std::out_of_range("basic_string_view::substr"));
    size_type rlen = std::min(count, size() - pos);
    return basic_string_view(data() + pos, rlen);
  }

  JASL_CONSTEXPR_CXX14 void remove_prefix(size_type n) noexcept {
    JASL_ASSERT(n <= size(), "remove_prefix() can't remove more than size()");
    _ptr += n;
    _size -= n;
  }

  JASL_CONSTEXPR_CXX14 void remove_suffix(size_type n) noexcept {
    JASL_ASSERT(n <= size(), "remove_suffix() can't remove more than size()");
    _size -= n;
  }

  JASL_CONSTEXPR_CXX14 int compare(const basic_string_view& right) const
      noexcept {
    size_type rlen = std::min(size(), right.size());
    int retval = Traits::compare(data(), right.data(), rlen);
    if (retval == 0)  // first rlen chars matched
      retval = size() == right.size() ? 0 : (size() < right.size() ? -1 : 1);
    return retval;
  }

  JASL_CONSTEXPR_CXX14
  size_type find(const basic_string_view& s) const noexcept {
    JASL_ASSERT(s.size() == 0 || s.data() != nullptr,
                "string_view::find(): received nullptr");
    auto itWhere = cbegin();
    auto itWhat = s.cbegin();
    while (itWhere != cend() && itWhat != s.cend()) {
      if (*itWhere != *itWhat) {
        ++itWhere;
      } else {
        auto match = itWhere++;
        ++itWhat;
        while (itWhere != cend() && itWhat != s.cend() && *itWhere == *itWhat) {
          ++itWhere;
          ++itWhat;
        }
        if (itWhat == s.cend()) {
          return static_cast<size_type>(match - cbegin());
        }
        itWhat = s.cbegin();
      }
    }
    return npos;
  }
};

// http://en.cppreference.com/w/cpp/algorithm/lexicographical_compare

template <typename CharT, typename Traits>
JASL_CONSTEXPR_CXX14 bool operator==(
    const basic_string_view<CharT, Traits>& left,
    const basic_string_view<CharT, Traits>& right) {
  if (left.size() != right.size()) {
    return false;
  }
  return left.compare(right) == 0;
}

template <typename CharT, typename Traits>
JASL_CONSTEXPR_CXX14 bool operator!=(
    const basic_string_view<CharT, Traits>& left,
    const basic_string_view<CharT, Traits>& right) {
  return left.compare(right) != 0;
}

template <typename CharT, typename Traits>
JASL_CONSTEXPR_CXX14 bool operator<(
    const basic_string_view<CharT, Traits>& left,
    const basic_string_view<CharT, Traits>& right) {
  return left.compare(right) < 0;
}

template <typename CharT, typename Traits>
JASL_CONSTEXPR_CXX14 bool operator<=(
    const basic_string_view<CharT, Traits>& left,
    const basic_string_view<CharT, Traits>& right) {
  return left.compare(right) <= 0;
}

template <typename CharT, typename Traits>
JASL_CONSTEXPR_CXX14 bool operator>(
    const basic_string_view<CharT, Traits>& left,
    const basic_string_view<CharT, Traits>& right) {
  return left.compare(right) > 0;
}

template <typename CharT, typename Traits>
JASL_CONSTEXPR_CXX14 bool operator>=(
    const basic_string_view<CharT, Traits>& left,
    const basic_string_view<CharT, Traits>& right) {
  return left.compare(right) >= 0;
}

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,
    basic_string_view<CharT, Traits> v) {
  os.write(v.data(), static_cast<std::make_signed<size_t>::type>(v.size()));
  return os;
}

template <typename CharT, typename Traits>
void swap(
    basic_string_view<CharT, Traits>& lhs,
    basic_string_view<CharT, Traits>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
  lhs.swap(rhs);
}

}  // namespace nonstd
}  // namespace jasl

#if defined(JASL_FORCE_USE_MURMURHASH_HASH) && \
    defined(JASL_DISABLE_JASL_STRING_VIEW_HASH)
#  error "Illegal configration!"
#endif

/*
 * http://en.cppreference.com/w/cpp/utility/hash
 */
#if !defined(JASL_DISABLE_JASL_STRING_VIEW_HASH)
#  if defined(JASL_cpp_lib_string_view) && \
      !defined(JASL_FORCE_USE_MURMURHASH_HASH)
#    include <string_view>
namespace std {
template <typename CharT, typename Traits>
struct hash<jasl::nonstd::basic_string_view<CharT, Traits>> {
  size_t operator()(
      const jasl::nonstd::basic_string_view<CharT, Traits>& x) const noexcept {
    return std::hash<std::basic_string_view<CharT, Traits>>{}(
        std::basic_string_view<CharT, Traits>(x.data(), x.size()));
  }
};
}  // namespace std
#  else
#    include "jasl/jasl_internal/jasl_murmurhash3.hpp"
namespace std {
template <typename CharT, typename Traits>
struct hash<jasl::nonstd::basic_string_view<CharT, Traits>> {
  size_t operator()(
      const jasl::nonstd::basic_string_view<CharT, Traits>& x) const noexcept {
    static_assert(sizeof(size_t) <= 16, "Unexpected platform!");
    size_t res[16 / sizeof(size_t)];
    auto len = static_cast<int>(
        std::min(x.size() * sizeof(CharT),
                 static_cast<size_t>(std::numeric_limits<int>::max())));
    if (sizeof(size_t) >= 8) {
      jasl::murmurhash3::MurmurHash3_x64_128(x.data(), len, 33, &res);
    } else {
      jasl::murmurhash3::MurmurHash3_x86_128(x.data(), len, 33, &res);
    }
    return res[0];
  }
};
}  // namespace std
#  endif  // JASL_cpp_lib_string_view
#endif    // JASL_DISABLE_JASL_STRING_VIEW_HASH
