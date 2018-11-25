




#ifndef YB_INC_ystdex_string_view_hpp_
#define YB_INC_ystdex_string_view_hpp_ 1

#include "range.hpp" 





#if (YB_IMPL_MSCPP >= 1910 && _MSVC_LANG >= 201603) \
	|| (__cplusplus >= 201703L && __has_include(<string_view>))
#	include <string_view>



#	if (YB_IMPL_MSCPP >= 1910 && _MSVC_LANG >= 201603) \
	|| __cpp_lib_string_view >= 201603L
#		define YB_Has_string_view 1
#	endif
#endif
#if YB_Has_string_view == 1
#	include <libdefect/string.h>
#else
#	include "cstring.h" 

#	include "operators.hpp" 
#	include <limits> 
#	include <stdexcept> 
#	include "hash.hpp" 
#endif



#ifndef __cpp_lib_string_view
#	if (YB_IMPL_MSCPP >= 1910 && _MSVC_LANG >= 201606) || __cplusplus >= 201606L
#		define __cpp_lib_string_view 201606L
#	endif
#endif


namespace ystdex
{


inline namespace cpp2017
{

#if YB_Has_string_view == 1

using std::basic_string_view;
#else


template<typename _tChar, class _tTraits = std::char_traits<_tChar>>
class basic_string_view
	: yimpl(private totally_ordered<basic_string_view<_tChar, _tTraits>>)
{
public:
	using traits_type = _tTraits;
	using value_type = _tChar;
	using pointer = _tChar*;
	using const_pointer = const _tChar*;
	using reference = _tChar&;
	using const_reference = const _tChar&;
	using const_iterator = yimpl(const _tChar*);
	using iterator = const_iterator;
	using const_reverse_iterator = ystdex::reverse_iterator<const_iterator>;
	using reverse_iterator = const_reverse_iterator;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	static yconstexpr size_type npos = size_type(-1);

private:
	const_pointer data_;
	size_type size_;

public:
	yconstfn
	basic_string_view() ynothrow
		: data_(), size_()
	{}
	YB_NONNULL(2) yconstfn
	basic_string_view(const _tChar* str)
		: data_(str), size_(traits_type::length(str))
	{}
	YB_NONNULL(2) yconstfn
	basic_string_view(const _tChar* str, size_type len)
		: data_(str), size_(len)
	{}
	yconstfn
	basic_string_view(const basic_string_view&) ynothrow = default;

	yconstfn_relaxed basic_string_view&
	operator=(const basic_string_view&) ynothrow = default;

	yconstfn const_iterator
	begin() const ynothrow
	{
		return data_;
	}

	yconstfn const_iterator
	end() const ynothrow
	{
		return data_ + size_;
	}

	yconstfn const_iterator
	cbegin() const ynothrow
	{
		return data_;
	}

	yconstfn const_iterator
	cend() const ynothrow
	{
		return data_ + size_;
	}

	yconstfn const_reverse_iterator
	rbegin() const ynothrow
	{
		return const_reverse_iterator(end());
	}

	yconstfn const_reverse_iterator
	rend() const ynothrow
	{
		return const_reverse_iterator(begin());
	}

	yconstfn const_reverse_iterator
	crbegin() const ynothrow
	{
		return const_reverse_iterator(cend());
	}

	yconstfn const_reverse_iterator
	crend() const ynothrow
	{
		return const_reverse_iterator(cbegin());
	}

	yconstfn size_type
	size() const ynothrow
	{
		return size_;
	}

	yconstfn size_type
	length() const ynothrow
	{
		return size_;
	}

	yconstfn size_type
	max_size() const ynothrow
	{
		
		return std::numeric_limits<size_type>::max();
	}

	YB_ATTR_nodiscard yconstfn bool
	empty() const ynothrow
	{
		return size_ == 0;
	}

	yconstfn const_reference
	operator[](size_type pos) const
	{
		return yconstraint(pos < size_), data_[pos];
	}

	yconstfn const_reference
	at(size_type pos) const
	{
		return pos < size_ ? data_[pos]
			: (throw std::out_of_range("string_view::at"), data_[0]);
	}

	yconstfn const_reference
	front() const
	{
		return yconstraint(0 < size_), data_[0];
	}

	yconstfn const_reference
	back() const
	{
		return yconstraint(0 < size_), data_[size_ - 1];
	}

	yconstfn const_pointer
	data() const ynothrow
	{
		return data_;
	}

	yconstfn_relaxed void
	remove_prefix(size_type n) ynothrowv
	{
		yconstraint(n <= size_), yunseq(data_ += n, size_ -= n);
	}

	yconstfn_relaxed void
	remove_suffix(size_type n) ynothrowv
	{
		yconstraint(n <= size_), size_ -= n;
	}

	yconstfn_relaxed void
	swap(basic_string_view& s) ynothrow
	{
		std::swap(data_, s.data_),
		std::swap(size_, s.size_);
	}

	YB_NONNULL(2) size_type
	copy(_tChar* s, size_type n, size_type pos = 0) const
	{
		yconstraint(s);
		if(pos <= size_)
		{
			const auto rlen(std::min<size_type>(n, size_ - pos));

			std::copy_n(data_ + pos, rlen, s);
			return rlen;
		}
		throw std::out_of_range("string_view::copy");
	}

	yconstfn basic_string_view
	substr(size_type pos = 0, size_type n = npos) const
	{
		return pos <= size_ ? basic_string_view(data_ + pos,
			std::min(n, size_type(size_ - pos)))
			: throw std::out_of_range("string_view::substr");
	}

	yconstfn int
	compare(basic_string_view s) const ynothrow
	{
		return compare_remained(s, _tTraits::compare(data(), s.data(),
			std::min<size_type>(size(), s.size())));
	}
	yconstfn int
	compare(size_type pos1, size_type n1, basic_string_view s) const
	{
		return substr(pos1, n1).compare(s);
	}
	yconstfn int
	compare(size_type pos1, size_type n1, basic_string_view s, size_type pos2,
		size_type n2) const
	{
		return substr(pos1, n1).compare(s.substr(pos2, n2));
	}
	YB_NONNULL(2) yconstfn int
	compare(const _tChar* s) const
	{
		return compare(basic_string_view(s));
	}
	YB_NONNULL(4) yconstfn int
	compare(size_type pos1, size_type n1, const _tChar* s) const
	{
		return substr(pos1, n1).compare(basic_string_view(s));
	}
	YB_NONNULL(4) yconstfn int
	compare(size_type pos1, size_type n1, const _tChar* s, size_type n2) const
	{
		return substr(pos1, n1).compare(basic_string_view(s, n2));
	}

private:
	yconstfn int
	compare_remained(basic_string_view s, int ret) const ynothrow
	{
		return ret == 0 ? (size() == s.size() ? 0
			: (size() < s.size() ? -1 : 1)) : ret;
	}

public:
#define YB_Impl_StringView_search_fn_head(_n, _attr, _spec, ...) \
	yconstfn_relaxed _attr size_type \
	_n(__VA_ARGS__) const _spec \
	{
#define YB_Impl_StringView_search1(_n, _arg) \
	YB_Impl_StringView_search_fn_head(_n, , ynothrow, basic_string_view s, \
		size_type pos = _arg) \
		return ystdex::str_##_n<value_type, size_type, traits_type, \
			npos>(data_, size_, s.data_, pos, s.size_); \
	}
#define YB_Impl_StringView_search34(_n, _arg) \
	YB_Impl_StringView_search_fn_head(_n, YB_NONNULL(2), , const _tChar* s, \
		size_type pos, size_type n) \
		return yconstraint(s), _n(basic_string_view(s, n), pos); \
	} \
	YB_Impl_StringView_search_fn_head(_n, YB_NONNULL(2), , const _tChar* s, \
		size_type pos = _arg) \
		return _n(s, pos, traits_type::length(s)); \
	}
#define YB_Impl_StringView_search_mf(_n, _arg) \
	YB_Impl_StringView_search1(_n, _arg) \
	YB_Impl_StringView_search_fn_head(_n, , ynothrow, _tChar c, \
		size_type pos = _arg) \
		return ystdex::str_##_n<value_type, size_type, traits_type, \
			npos>(data_, size_, c, pos); \
	} \
	YB_Impl_StringView_search34(_n, _arg)
#define YB_Impl_StringView_search_mf2(_n, _arg, _n2) \
	YB_Impl_StringView_search1(_n, _arg) \
	YB_Impl_StringView_search_fn_head(_n, , ynothrow, _tChar c, \
		size_type pos = _arg) \
		return _n2(c, pos); \
	} \
	YB_Impl_StringView_search34(_n, _arg)

	YB_Impl_StringView_search_mf(find, 0)

	YB_Impl_StringView_search_mf(rfind, npos)

	YB_Impl_StringView_search_mf2(find_first_of, 0, find)

	YB_Impl_StringView_search_mf2(find_last_of, npos, rfind)

	YB_Impl_StringView_search_mf(find_first_not_of, 0)

	YB_Impl_StringView_search_mf(find_last_not_of, npos)

#undef YB_Impl_StringView_search_mf
#undef YB_Impl_StringView_search_mf2
#undef YB_Impl_StringView_search1
#undef YB_Impl_StringView_search34
#undef YB_Impl_StringView_search_fn_head
};



template<typename _tChar, class _tTraits>
yconstfn bool
operator==(basic_string_view<_tChar, _tTraits> x,
	basic_string_view<_tChar, _tTraits> y) ynothrow
{
	return x.compare(y) == 0;
}
template<typename _tChar, class _tTraits>
yconstfn bool
operator==(basic_string_view<_tChar, _tTraits> x,
	yimpl(decay_t<basic_string_view<_tChar, _tTraits>>) y) ynothrow
{
	return x.compare(y) == 0;
}

template<typename _tChar, class _tTraits>
yconstfn bool
operator==(yimpl(decay_t<basic_string_view<_tChar, _tTraits>>) x,
	basic_string_view<_tChar, _tTraits> y) ynothrow
{
	return x.compare(y) == 0;
}

template<typename _tChar, class _tTraits>
yconstfn bool
operator<(basic_string_view<_tChar, _tTraits> x,
	basic_string_view<_tChar, _tTraits> y) ynothrow
{
	return x.compare(y) < 0;
}

template<typename _tChar, class _tTraits>
yconstfn bool
operator<(basic_string_view<_tChar, _tTraits> x,
	yimpl(decay_t<basic_string_view<_tChar, _tTraits>>) y) ynothrow
{
	return x.compare(y) < 0;
}

template<typename _tChar, class _tTraits>
yconstfn bool
operator<(yimpl(decay_t<basic_string_view<_tChar, _tTraits>>) x,
	basic_string_view<_tChar, _tTraits> y) ynothrow
{
	return x.compare(y) < 0;
}

template<typename _tChar, class _tTraits>
std::basic_ostream<_tChar, _tTraits>&
operator<<(std::basic_ostream<_tChar, _tTraits>& os,
	basic_string_view<_tChar, _tTraits> str)
{
	
	return os << std::basic_string<_tChar, _tTraits>(str.data(), str.size());
}


#endif

using string_view = basic_string_view<char>;
using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;
using wstring_view = basic_string_view<wchar_t>;

} 


template<class _tString>
using string_view_t = basic_string_view<typename _tString::value_type>;

} 


#if YB_Has_string_view != 1
namespace std
{


template<typename _tChar, class _tTraits>
struct hash<ystdex::basic_string_view<_tChar, _tTraits>>
{
	size_t
	operator()(const ystdex::string_view& k) const yimpl(ynothrow)
	{
		return ystdex::hash_range(k.data(), k.data() + k.size());
	}
};

} 
#endif

#endif

