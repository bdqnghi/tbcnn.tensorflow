// string_view.h is an independent implementation of the C++17 <string_view> 
// standard library header, which can be compiled by C++14 compliant 
// compilers. The original author of this file is Sterling Orsten, and 
// its permanent home is https://github.com/sgorsten/vocab-types

// This is free and unencumbered software released into the public domain.
// 
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
// 
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// 
// For more information, please refer to <http://unlicense.org/>

#ifndef EARLY17_STRING_VIEW
#define EARLY17_STRING_VIEW

#include <iterator>
#include <algorithm>
#include <stdexcept>

#pragma warning(push)
#pragma warning(disable : 4814) // "in C++14 'constexpr' will not imply 'const'" - We know and are specifying constexpr non-const functions deliberately

namespace std {

///////////////////////////////////////////////////////////////////////////////////
// basic_string_view - http://en.cppreference.com/w/cpp/string/basic_string_view //
///////////////////////////////////////////////////////////////////////////////////

template<class CharT, class Traits = std::char_traits<CharT>> class basic_string_view
{
public:
    using traits_type =	Traits;
    using value_type = CharT;
    using pointer = CharT*;
    using const_pointer = const CharT*;
    using reference = CharT&;
    using const_reference = const CharT&;
    using const_iterator = const_pointer; // Note: implementation-defined RandomAccessIterator;
    using iterator = const_iterator;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator = const_reverse_iterator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
private:
    const_pointer _Data;
    size_type _Size;

    constexpr size_type _IndexOf(const_iterator it) const noexcept { return it == end() ? npos : it - begin(); }
    constexpr size_type _IndexOf(const_reverse_iterator it, size_type s) const noexcept { return it == rend() ? npos : size() - (it - rbegin()) - s; }
public:
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // (constructor) - http://en.cppreference.com/w/cpp/string/basic_string_view/basic_string_view //
    /////////////////////////////////////////////////////////////////////////////////////////////////

    constexpr basic_string_view() noexcept : _Data{nullptr}, _Size{0} {} // (1)
    constexpr basic_string_view(const basic_string_view& other) noexcept = default; // (2)
    constexpr basic_string_view(const CharT* s, size_type count) noexcept : _Data{s}, _Size{count} {} // (3)
    constexpr basic_string_view(const CharT* s) : _Data{s}, _Size{Traits::length(s)} {} // (4)

    ///////////////////////////////////////////////////////////////////////////////////////
    // operator= - http://en.cppreference.com/w/cpp/string/basic_string_view/operator%3D // 
    ///////////////////////////////////////////////////////////////////////////////////////

    basic_string_view& operator= (const basic_string_view & view) noexcept = default;

    /////////////////////////////////////////////////////////////////////////////
    // begin - http://en.cppreference.com/w/cpp/string/basic_string_view/begin //
    /////////////////////////////////////////////////////////////////////////////

    constexpr const_iterator begin() const noexcept { return cbegin(); }
    constexpr const_iterator cbegin() const noexcept { return _Data; }

    /////////////////////////////////////////////////////////////////////////
    // end - http://en.cppreference.com/w/cpp/string/basic_string_view/end //
    /////////////////////////////////////////////////////////////////////////

    constexpr const_iterator end() const noexcept { return cend(); }
    constexpr const_iterator cend() const noexcept { return _Data + _Size; }

    ///////////////////////////////////////////////////////////////////////////////
    // rbegin - http://en.cppreference.com/w/cpp/string/basic_string_view/rbegin //
    /////////////////////////////////////////////////////////////////////////////

    constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator{cend()}; }
    constexpr const_reverse_iterator rcbegin() const noexcept { return const_reverse_iterator{cend()}; }

    ///////////////////////////////////////////////////////////////////////////
    // rend - http://en.cppreference.com/w/cpp/string/basic_string_view/rend //
    ///////////////////////////////////////////////////////////////////////////

    constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator{cbegin()}; }
    constexpr const_reverse_iterator rcend() const noexcept { return const_reverse_iterator{cbegin()}; }

    ////////////////////////////////////////////////////////////////////////////////////////
    // operator[] - http://en.cppreference.com/w/cpp/string/basic_string_view/operator_at //
    ////////////////////////////////////////////////////////////////////////////////////////

    constexpr const_reference operator[](size_type pos) const noexcept { return _Data[pos]; }

    ///////////////////////////////////////////////////////////////////////
    // at - http://en.cppreference.com/w/cpp/string/basic_string_view/at //
    ///////////////////////////////////////////////////////////////////////

    constexpr const_reference at(size_type pos) const { if(pos >= _Size) throw std::out_of_range{"bad pos"}; return _Data[pos]; }

    /////////////////////////////////////////////////////////////////////////////
    // front - http://en.cppreference.com/w/cpp/string/basic_string_view/front //
    /////////////////////////////////////////////////////////////////////////////

    constexpr const_reference front() const noexcept { return _Data[0]; }

    ///////////////////////////////////////////////////////////////////////////
    // back - http://en.cppreference.com/w/cpp/string/basic_string_view/back //
    ///////////////////////////////////////////////////////////////////////////

    constexpr const_reference back() const noexcept { return _Data[_Size-1]; }

    ///////////////////////////////////////////////////////////////////////////
    // data - http://en.cppreference.com/w/cpp/string/basic_string_view/data //
    ///////////////////////////////////////////////////////////////////////////

    constexpr const_pointer data() const noexcept { return _Data; }

    ///////////////////////////////////////////////////////////////////////////
    // size - http://en.cppreference.com/w/cpp/string/basic_string_view/size //
    ///////////////////////////////////////////////////////////////////////////

    constexpr size_type size() const noexcept { return _Size; }
    constexpr size_type length() const noexcept { return _Size; }

    ///////////////////////////////////////////////////////////////////////////////////
    // max_size - http://en.cppreference.com/w/cpp/string/basic_string_view/max_size //
    ///////////////////////////////////////////////////////////////////////////////////

    constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); } // TODO: Is this correct? Do we have to account for what subset of memory is accessible?

    /////////////////////////////////////////////////////////////////////////////
    // empty - http://en.cppreference.com/w/cpp/string/basic_string_view/empty //
    /////////////////////////////////////////////////////////////////////////////

    constexpr bool empty() const noexcept { return _Size == 0; }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // remove_prefix - http://en.cppreference.com/w/cpp/string/basic_string_view/remove_prefix //
    /////////////////////////////////////////////////////////////////////////////////////////////

    constexpr void remove_prefix(size_type n) noexcept { _Data += n; _Size -= n; }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // remove_suffix - http://en.cppreference.com/w/cpp/string/basic_string_view/remove_suffix //
    /////////////////////////////////////////////////////////////////////////////////////////////

    constexpr void remove_suffix(size_type n) noexcept { _Size -= n; }

    ///////////////////////////////////////////////////////////////////////////
    // swap - http://en.cppreference.com/w/cpp/string/basic_string_view/swap //
    ///////////////////////////////////////////////////////////////////////////

    constexpr void swap(basic_string_view& v) noexcept { swap(_Data, v._Data); swap(_Size, v._Size); }

    ///////////////////////////////////////////////////////////////////////////
    // copy - http://en.cppreference.com/w/cpp/string/basic_string_view/copy //
    ///////////////////////////////////////////////////////////////////////////

    size_type copy(CharT* dest, size_type count, size_type pos = 0) const
    { 
        auto sub = substr(pos, count);
        return std::copy(begin(sub), end(sub), dest) - dest;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // substr - http://en.cppreference.com/w/cpp/string/basic_string_view/substr //
    ///////////////////////////////////////////////////////////////////////////////

    constexpr basic_string_view substr(size_type pos = 0, size_type count = npos ) const
    {
        if(pos > size()) throw std::out_of_range{"bad pos"};
        return {data() + pos, std::min(count, size() - pos)};
    }

    /////////////////////////////////////////////////////////////////////////////////
    // compare - http://en.cppreference.com/w/cpp/string/basic_string_view/compare //
    /////////////////////////////////////////////////////////////////////////////////

    constexpr int compare(basic_string_view v) const noexcept // (1)
    {
        return [this,v](int r)
        {
            if(r < 0) return -1;
            if(r > 0) return 1;
            if(size() < v.size()) return -1;
            if(size() > v.size()) return 1;
            return 0;        
        }(Traits::compare(data(), v.data(), min(size(), v.size())));
    }
    constexpr int compare(size_type pos1, size_type count1, basic_string_view v) const noexcept { return substr(pos1, count1).compare(v); } // (2)
    constexpr int compare(size_type pos1, size_type count1, basic_string_view v, size_type pos2, size_type count2) const noexcept { return substr(pos1, count1).compare(v.substr(pos2, count2)); } // (3)
    constexpr int compare(const CharT* s) const noexcept { return compare(basic_string_view(s)); } // (4)
    constexpr int compare(size_type pos1, size_type count1, const CharT* s) const noexcept { return substr(pos1, count1).compare(basic_string_view(s)); } // (5)
    constexpr int compare(size_type pos1, size_type count1, const CharT* s, size_type count2) const noexcept { return substr(pos1, count1).compare(basic_string_view(s, count2)); } // (6)

    ///////////////////////////////////////////////////////////////////////////
    // find - http://en.cppreference.com/w/cpp/string/basic_string_view/find //
    ///////////////////////////////////////////////////////////////////////////

    constexpr size_type find(basic_string_view v, size_type pos = 0) const noexcept { return _IndexOf(std::search(begin() + pos, end(), v.begin(), v.end())); } // (1)
    constexpr size_type find(CharT c, size_type pos = 0) const noexcept { return find(basic_string_view(&c, 1), pos); } // (2)
    constexpr size_type find(const CharT* s, size_type pos, size_type count) const noexcept { return find(basic_string_view(s, count), pos); } // (3)
    constexpr size_type find(const CharT* s, size_type pos = 0) const noexcept { return find(basic_string_view(s), pos); } // (4)

    /////////////////////////////////////////////////////////////////////////////
    // rfind - http://en.cppreference.com/w/cpp/string/basic_string_view/rfind //
    /////////////////////////////////////////////////////////////////////////////

    constexpr size_type rfind(basic_string_view v, size_type pos = npos) const noexcept { return _IndexOf(std::search(rend() - std::min(pos, size()), rend(), v.rbegin(), v.rend()), v.size()); } // (1)
    constexpr size_type rfind(CharT c, size_type pos = npos) const noexcept { return rfind(basic_string_view(&c, 1), pos); } // (2)
    constexpr size_type rfind(const CharT* s, size_type pos, size_type count) const noexcept { return rfind(basic_string_view(s, count), pos); } // (3)
    constexpr size_type rfind(const CharT* s, size_type pos = npos) const noexcept { return rfind(basic_string_view(s), pos); } // (4)

    /////////////////////////////////////////////////////////////////////////////////////////////
    // find_first_of - http://en.cppreference.com/w/cpp/string/basic_string_view/find_first_of //
    /////////////////////////////////////////////////////////////////////////////////////////////
    
    constexpr size_type find_first_of(basic_string_view v, size_type pos = 0) const { return _IndexOf(std::find_first_of(begin() + pos, end(), v.begin(), v.end())); } // (1)
    constexpr size_type find_first_of(CharT c, size_type pos = 0) const { return find_first_of(basic_string_view(&c, 1), pos); } // (2)
    constexpr size_type find_first_of(const CharT* s, size_type pos, size_type count) const { return find_first_of(basic_string_view(s, count), pos); } // (3)
    constexpr size_type find_first_of(const CharT* s, size_type pos = 0) const { return find_first_of(basic_string_view(s), pos); } // (4)

    ///////////////////////////////////////////////////////////////////////////////////////////
    // find_last_of - http://en.cppreference.com/w/cpp/string/basic_string_view/find_last_of //
    ///////////////////////////////////////////////////////////////////////////////////////////

    constexpr size_type find_last_of(basic_string_view v, size_type pos = npos) const { return _IndexOf(std::find_first_of(rend() - std::min(pos, size()), rend(), v.begin(), v.end()), 1); } // (1)
    constexpr size_type find_last_of(CharT c, size_type pos = npos) const { return find_last_of(basic_string_view(&c, 1), pos); } // (2)
    constexpr size_type find_last_of(const CharT* s, size_type pos, size_type count) const { return find_last_of(basic_string_view(s, count), pos); } // (3)
    constexpr size_type find_last_of(const CharT* s, size_type pos = npos) const { return find_last_of(basic_string_view(s), pos); } // (4)

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // find_first_not_of - http://en.cppreference.com/w/cpp/string/basic_string_view/find_first_not_of //
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    constexpr size_type find_first_not_of(basic_string_view v, size_type pos = 0) const { return _IndexOf(std::find_if(begin() + pos, end(), [v](CharT ch) { return v.find(ch) == npos; })); } // (1)
    constexpr size_type find_first_not_of(CharT c, size_type pos = 0) const { return find_first_not_of(basic_string_view(&c, 1), pos); } // (2)
    constexpr size_type find_first_not_of(const CharT* s, size_type pos, size_type count) const { return find_first_not_of(basic_string_view(s, count), pos); } // (3)
    constexpr size_type find_first_not_of(const CharT* s, size_type pos = 0) const { return find_first_not_of(basic_string_view(s), pos); } // (4)

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // find_last_not_of - http://en.cppreference.com/w/cpp/string/basic_string_view/find_last_not_of // 
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    constexpr size_type find_last_not_of(basic_string_view v, size_type pos = npos) const { return _IndexOf(std::find_if(rend() - std::min(pos, size()), rend(), [v](CharT ch) { return v.find(ch) == npos; }), 1); } // (1)
    constexpr size_type find_last_not_of(CharT c, size_type pos = npos) const { return find_last_not_of(basic_string_view(&c, 1), pos); }
    constexpr size_type find_last_not_of(const CharT* s, size_type pos, size_type count) const { return find_last_not_of(basic_string_view(s, count), pos); } // (3)
    constexpr size_type find_last_not_of(const CharT* s, size_type pos = npos) const { return find_last_not_of(basic_string_view(s), pos); } // (4)

    ///////////////////////////////////////////////////////////////////////////
    // npos - http://en.cppreference.com/w/cpp/string/basic_string_view/npos //
    ///////////////////////////////////////////////////////////////////////////

    static constexpr const size_type npos = size_type(-1);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // NOTE: In a standards-compliant implementation, it is the responsibility of basic_string to provide an //
    // implicit conversion to basic_string_view and an explicit constructor from basic_string_view. Since we //
    // cannot modify the definition of basic_string, we are instead providing an implicit constructor from   //
    // basic_string and an explicit conversion to basic_string. In doing so, we lose the ability to pass an  //
    // allocator to basic_string's constructor, but otherwise hopefully maintain reasonable compatibility.   //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Instead of: basic_string<CharT, Traits>::operator basic_string_view<CharT, Traits>() const noexcept;
    basic_string_view(const basic_string<CharT, Traits> & s) noexcept : basic_string_view{s.data(), s.size()} {}

    // Instead of: explicit basic_string::basic_string(basic_string_view<CharT, Traits> sv, const Allocator& alloc = Allocator());
    explicit operator basic_string<CharT, Traits>() const { return {data(), size()}; }
};

template<class CharT, class Traits> const size_t std::basic_string_view<CharT, Traits>::npos;

using string_view =	basic_string_view<char>;
using wstring_view = basic_string_view<wchar_t>;
using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// operator==, !=, <, <=, >, >= - http://en.cppreference.com/w/cpp/string/basic_string_view/operator_cmp //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

template< class CharT, class Traits > constexpr bool operator==( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) == 0; } // (1)
template< class CharT, class Traits > constexpr bool operator!=( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) != 0; } // (2)
template< class CharT, class Traits > constexpr bool operator< ( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) <  0; } // (3)
template< class CharT, class Traits > constexpr bool operator<=( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) <= 0; } // (4)
template< class CharT, class Traits > constexpr bool operator> ( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) >  0; } // (5)
template< class CharT, class Traits > constexpr bool operator>=( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) >= 0; } // (6)

//////////////////////////////////////////////////////////////////////////////////////////
// operator<< - http://en.cppreference.com/w/cpp/string/basic_string_view/operator_ltlt //
//////////////////////////////////////////////////////////////////////////////////////////

template<class CharT, class Traits> std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits>& os, std::basic_string_view<CharT, Traits> v)
{
    for(auto ch : v) os << ch;
    return os;
}

///////////////////////////////////////////////////////////////////////////
// hash - http://en.cppreference.com/w/cpp/string/basic_string_view/hash //
///////////////////////////////////////////////////////////////////////////

namespace _Early17
{
    // NOTE: This is a painfully bad hashing algorithm, but I don't want to risk inadvertantly adding someone else's copyrighted code to this project
    template<class T> size_t hash_string_view(const std::basic_string_view<T> & view) noexcept
    {
        std::hash<T> h;
        size_t r = 0;
        for(auto ch : view) r = (r << 1) ^ h(ch);
        return r;
    }
}

template<> struct hash<std::string_view> { size_t operator() (const std::string_view & key) const noexcept { return _Early17::hash_string_view(key); } };
template<> struct hash<std::wstring_view> { size_t operator() (const std::wstring_view & key) const noexcept { return _Early17::hash_string_view(key); } };
template<> struct hash<std::u16string_view> { size_t operator() (const std::u16string_view & key) const noexcept { return _Early17::hash_string_view(key); } };
template<> struct hash<std::u32string_view> { size_t operator() (const std::u32string_view & key) const noexcept { return _Early17::hash_string_view(key); } };

} // namespace std

#pragma warning(pop) 

#endif
