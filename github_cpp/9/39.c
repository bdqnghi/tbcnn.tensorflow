





























#ifndef EARLY17_STRING_VIEW
#define EARLY17_STRING_VIEW

#include <iterator>
#include <algorithm>
#include <stdexcept>

#pragma warning(push)
#pragma warning(disable : 4814) 

namespace std {





template<class CharT, class Traits = std::char_traits<CharT>> class basic_string_view
{
public:
    using traits_type =	Traits;
    using value_type = CharT;
    using pointer = CharT*;
    using const_pointer = const CharT*;
    using reference = CharT&;
    using const_reference = const CharT&;
    using const_iterator = const_pointer; 
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
    
    
    

    constexpr basic_string_view() noexcept : _Data{nullptr}, _Size{0} {} 
    constexpr basic_string_view(const basic_string_view& other) noexcept = default; 
    constexpr basic_string_view(const CharT* s, size_type count) noexcept : _Data{s}, _Size{count} {} 
    constexpr basic_string_view(const CharT* s) : _Data{s}, _Size{Traits::length(s)} {} 

    
    
    

    basic_string_view& operator= (const basic_string_view & view) noexcept = default;

    
    
    

    constexpr const_iterator begin() const noexcept { return cbegin(); }
    constexpr const_iterator cbegin() const noexcept { return _Data; }

    
    
    

    constexpr const_iterator end() const noexcept { return cend(); }
    constexpr const_iterator cend() const noexcept { return _Data + _Size; }

    
    
    

    constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator{cend()}; }
    constexpr const_reverse_iterator rcbegin() const noexcept { return const_reverse_iterator{cend()}; }

    
    
    

    constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator{cbegin()}; }
    constexpr const_reverse_iterator rcend() const noexcept { return const_reverse_iterator{cbegin()}; }

    
    
    

    constexpr const_reference operator[](size_type pos) const noexcept { return _Data[pos]; }

    
    
    

    constexpr const_reference at(size_type pos) const { if(pos >= _Size) throw std::out_of_range{"bad pos"}; return _Data[pos]; }

    
    
    

    constexpr const_reference front() const noexcept { return _Data[0]; }

    
    
    

    constexpr const_reference back() const noexcept { return _Data[_Size-1]; }

    
    
    

    constexpr const_pointer data() const noexcept { return _Data; }

    
    
    

    constexpr size_type size() const noexcept { return _Size; }
    constexpr size_type length() const noexcept { return _Size; }

    
    
    

    constexpr size_type max_size() const noexcept { return std::numeric_limits<size_type>::max(); } 

    
    
    

    constexpr bool empty() const noexcept { return _Size == 0; }

    
    
    

    constexpr void remove_prefix(size_type n) noexcept { _Data += n; _Size -= n; }

    
    
    

    constexpr void remove_suffix(size_type n) noexcept { _Size -= n; }

    
    
    

    constexpr void swap(basic_string_view& v) noexcept { swap(_Data, v._Data); swap(_Size, v._Size); }

    
    
    

    size_type copy(CharT* dest, size_type count, size_type pos = 0) const
    { 
        auto sub = substr(pos, count);
        return std::copy(begin(sub), end(sub), dest) - dest;
    }

    
    
    

    constexpr basic_string_view substr(size_type pos = 0, size_type count = npos ) const
    {
        if(pos > size()) throw std::out_of_range{"bad pos"};
        return {data() + pos, std::min(count, size() - pos)};
    }

    
    
    

    constexpr int compare(basic_string_view v) const noexcept 
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
    constexpr int compare(size_type pos1, size_type count1, basic_string_view v) const noexcept { return substr(pos1, count1).compare(v); } 
    constexpr int compare(size_type pos1, size_type count1, basic_string_view v, size_type pos2, size_type count2) const noexcept { return substr(pos1, count1).compare(v.substr(pos2, count2)); } 
    constexpr int compare(const CharT* s) const noexcept { return compare(basic_string_view(s)); } 
    constexpr int compare(size_type pos1, size_type count1, const CharT* s) const noexcept { return substr(pos1, count1).compare(basic_string_view(s)); } 
    constexpr int compare(size_type pos1, size_type count1, const CharT* s, size_type count2) const noexcept { return substr(pos1, count1).compare(basic_string_view(s, count2)); } 

    
    
    

    constexpr size_type find(basic_string_view v, size_type pos = 0) const noexcept { return _IndexOf(std::search(begin() + pos, end(), v.begin(), v.end())); } 
    constexpr size_type find(CharT c, size_type pos = 0) const noexcept { return find(basic_string_view(&c, 1), pos); } 
    constexpr size_type find(const CharT* s, size_type pos, size_type count) const noexcept { return find(basic_string_view(s, count), pos); } 
    constexpr size_type find(const CharT* s, size_type pos = 0) const noexcept { return find(basic_string_view(s), pos); } 

    
    
    

    constexpr size_type rfind(basic_string_view v, size_type pos = npos) const noexcept { return _IndexOf(std::search(rend() - std::min(pos, size()), rend(), v.rbegin(), v.rend()), v.size()); } 
    constexpr size_type rfind(CharT c, size_type pos = npos) const noexcept { return rfind(basic_string_view(&c, 1), pos); } 
    constexpr size_type rfind(const CharT* s, size_type pos, size_type count) const noexcept { return rfind(basic_string_view(s, count), pos); } 
    constexpr size_type rfind(const CharT* s, size_type pos = npos) const noexcept { return rfind(basic_string_view(s), pos); } 

    
    
    
    
    constexpr size_type find_first_of(basic_string_view v, size_type pos = 0) const { return _IndexOf(std::find_first_of(begin() + pos, end(), v.begin(), v.end())); } 
    constexpr size_type find_first_of(CharT c, size_type pos = 0) const { return find_first_of(basic_string_view(&c, 1), pos); } 
    constexpr size_type find_first_of(const CharT* s, size_type pos, size_type count) const { return find_first_of(basic_string_view(s, count), pos); } 
    constexpr size_type find_first_of(const CharT* s, size_type pos = 0) const { return find_first_of(basic_string_view(s), pos); } 

    
    
    

    constexpr size_type find_last_of(basic_string_view v, size_type pos = npos) const { return _IndexOf(std::find_first_of(rend() - std::min(pos, size()), rend(), v.begin(), v.end()), 1); } 
    constexpr size_type find_last_of(CharT c, size_type pos = npos) const { return find_last_of(basic_string_view(&c, 1), pos); } 
    constexpr size_type find_last_of(const CharT* s, size_type pos, size_type count) const { return find_last_of(basic_string_view(s, count), pos); } 
    constexpr size_type find_last_of(const CharT* s, size_type pos = npos) const { return find_last_of(basic_string_view(s), pos); } 

    
    
    

    constexpr size_type find_first_not_of(basic_string_view v, size_type pos = 0) const { return _IndexOf(std::find_if(begin() + pos, end(), [v](CharT ch) { return v.find(ch) == npos; })); } 
    constexpr size_type find_first_not_of(CharT c, size_type pos = 0) const { return find_first_not_of(basic_string_view(&c, 1), pos); } 
    constexpr size_type find_first_not_of(const CharT* s, size_type pos, size_type count) const { return find_first_not_of(basic_string_view(s, count), pos); } 
    constexpr size_type find_first_not_of(const CharT* s, size_type pos = 0) const { return find_first_not_of(basic_string_view(s), pos); } 

    
    
    

    constexpr size_type find_last_not_of(basic_string_view v, size_type pos = npos) const { return _IndexOf(std::find_if(rend() - std::min(pos, size()), rend(), [v](CharT ch) { return v.find(ch) == npos; }), 1); } 
    constexpr size_type find_last_not_of(CharT c, size_type pos = npos) const { return find_last_not_of(basic_string_view(&c, 1), pos); }
    constexpr size_type find_last_not_of(const CharT* s, size_type pos, size_type count) const { return find_last_not_of(basic_string_view(s, count), pos); } 
    constexpr size_type find_last_not_of(const CharT* s, size_type pos = npos) const { return find_last_not_of(basic_string_view(s), pos); } 

    
    
    

    static constexpr const size_type npos = size_type(-1);

    
    
    
    
    
    
    

    
    basic_string_view(const basic_string<CharT, Traits> & s) noexcept : basic_string_view{s.data(), s.size()} {}

    
    explicit operator basic_string<CharT, Traits>() const { return {data(), size()}; }
};

template<class CharT, class Traits> const size_t std::basic_string_view<CharT, Traits>::npos;

using string_view =	basic_string_view<char>;
using wstring_view = basic_string_view<wchar_t>;
using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;





template< class CharT, class Traits > constexpr bool operator==( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) == 0; } 
template< class CharT, class Traits > constexpr bool operator!=( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) != 0; } 
template< class CharT, class Traits > constexpr bool operator< ( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) <  0; } 
template< class CharT, class Traits > constexpr bool operator<=( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) <= 0; } 
template< class CharT, class Traits > constexpr bool operator> ( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) >  0; } 
template< class CharT, class Traits > constexpr bool operator>=( basic_string_view <CharT,Traits> lhs, basic_string_view <CharT,Traits> rhs ) noexcept { return lhs.compare(rhs) >= 0; } 





template<class CharT, class Traits> std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits>& os, std::basic_string_view<CharT, Traits> v)
{
    for(auto ch : v) os << ch;
    return os;
}





namespace _Early17
{
    
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

} 

#pragma warning(pop) 

#endif
