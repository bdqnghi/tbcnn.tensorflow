/* This file is part of the Zenipex Library (zenilib).
 * Copyright (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * zenilib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * zenilib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with zenilib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <zeni.h>

#include <cctype>
#include <cstring>
#include <iostream>

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

namespace Zeni {

  String::iterator::iterator() : m_impl(new std::string::iterator) {}
  String::iterator::~iterator() {delete static_cast<std::string::iterator *>(m_impl);}

  String::iterator::iterator(const iterator &rhs) : m_impl(new std::string::iterator(*static_cast<const std::string::iterator * const>(rhs.m_impl))) {}
  String::iterator & String::iterator::operator=(const iterator &rhs) {
    *static_cast<std::string::iterator *>(m_impl) = *static_cast<std::string::iterator *>(rhs.m_impl);
    return *this;
  }
      
  bool String::iterator::operator==(const iterator &rhs) const {return *static_cast<const std::string::iterator * const>(m_impl) == *static_cast<const std::string::iterator *>(rhs.m_impl);}
  bool String::iterator::operator!=(const iterator &rhs) const {return *static_cast<const std::string::iterator * const>(m_impl) != *static_cast<const std::string::iterator *>(rhs.m_impl);}
      
  String::iterator::value_type String::iterator::operator*() const {return static_cast<const std::string::iterator * const>(m_impl)->operator*();}
  String::iterator::value_type & String::iterator::operator*() {return static_cast<const std::string::iterator * const>(m_impl)->operator*();}
  String::iterator::value_type String::iterator::operator->() const {return static_cast<const std::string::iterator * const>(m_impl)->operator*();}
  String::iterator::value_type & String::iterator::operator->() {return static_cast<const std::string::iterator * const>(m_impl)->operator*();}
      
  String::iterator String::iterator::operator++() {
    static_cast<std::string::iterator *>(m_impl)->operator++();
    return *this;
  }
  String::iterator String::iterator::operator--() {
    static_cast<std::string::iterator *>(m_impl)->operator--();
    return *this;
  }
  String::iterator String::iterator::operator++(int) {
    static_cast<std::string::iterator *>(m_impl)->operator++(0);
    return *this;
  }
  String::iterator String::iterator::operator--(int) {
    static_cast<std::string::iterator *>(m_impl)->operator--(0);
    return *this;
  }

  String::iterator String::iterator::operator+(const difference_type &n) const {return static_cast<const std::string::iterator * const>(m_impl)->operator+(n);}
  String::iterator String::iterator::operator-(const difference_type &n) const {return static_cast<const std::string::iterator * const>(m_impl)->operator-(n);}
  String::iterator::difference_type String::iterator::operator-(const iterator &rhs) const {return *static_cast<const std::string::iterator * const>(m_impl) - *static_cast<const std::string::iterator * const>(rhs.m_impl);}

  bool String::iterator::operator<(const iterator &rhs) const {return *static_cast<const std::string::iterator * const>(m_impl) < *static_cast<const std::string::iterator * const>(rhs.m_impl);}
  bool String::iterator::operator>(const iterator &rhs) const {return *static_cast<const std::string::iterator * const>(m_impl) > *static_cast<const std::string::iterator * const>(rhs.m_impl);}
  bool String::iterator::operator<=(const iterator &rhs) const {return *static_cast<const std::string::iterator * const>(m_impl) <= *static_cast<const std::string::iterator * const>(rhs.m_impl);}
  bool String::iterator::operator>=(const iterator &rhs) const {return *static_cast<const std::string::iterator * const>(m_impl) >= *static_cast<const std::string::iterator * const>(rhs.m_impl);}

  String::iterator String::iterator::operator+=(const difference_type &n) {
    static_cast<std::string::iterator *>(m_impl)->operator+=(n);
    return *this;
  }
  String::iterator String::iterator::operator-=(const difference_type &n) {
    static_cast<std::string::iterator *>(m_impl)->operator-=(n);
    return *this;
  }
      
  String::iterator::value_type String::iterator::operator[](const difference_type &n) const {return static_cast<const std::string::iterator * const>(m_impl)->operator[](n);}
  String::iterator::value_type & String::iterator::operator[](const difference_type &n) {return static_cast<std::string::iterator *>(m_impl)->operator[](n);}

  String::iterator::iterator(const std::string::iterator &iter) : m_impl(new std::string::iterator(iter)) {}
  String::iterator & String::iterator::operator=(const std::string::iterator &iter) {
    String::iterator temp(iter);
    std::swap(m_impl, temp.m_impl);
    return *this;
  }

  String::const_iterator::const_iterator() : m_impl(new std::string::const_iterator) {}
  String::const_iterator::~const_iterator() {delete static_cast<std::string::const_iterator *>(m_impl);}

  String::const_iterator::const_iterator(const const_iterator &rhs) : m_impl(new std::string::const_iterator(*static_cast<const std::string::const_iterator * const>(rhs.m_impl))) {}
  String::const_iterator & String::const_iterator::operator=(const const_iterator &rhs) {
    *static_cast<std::string::const_iterator *>(m_impl) = *static_cast<std::string::const_iterator *>(rhs.m_impl);
    return *this;
  }
      
  bool String::const_iterator::operator==(const const_iterator &rhs) const {return *static_cast<const std::string::const_iterator * const>(m_impl) == *static_cast<const std::string::const_iterator *>(rhs.m_impl);}
  bool String::const_iterator::operator!=(const const_iterator &rhs) const {return *static_cast<const std::string::const_iterator * const>(m_impl) != *static_cast<const std::string::const_iterator *>(rhs.m_impl);}
      
  String::const_iterator::value_type String::const_iterator::operator*() const {return static_cast<const std::string::const_iterator * const>(m_impl)->operator*();}
  String::const_iterator::value_type String::const_iterator::operator->() const {return static_cast<const std::string::const_iterator * const>(m_impl)->operator*();}
      
  String::const_iterator String::const_iterator::operator++() {
    static_cast<std::string::const_iterator *>(m_impl)->operator++();
    return *this;
  }
  String::const_iterator String::const_iterator::operator--() {
    static_cast<std::string::const_iterator *>(m_impl)->operator--();
    return *this;
  }
  String::const_iterator String::const_iterator::operator++(int) {
    static_cast<std::string::const_iterator *>(m_impl)->operator++(0);
    return *this;
  }
  String::const_iterator String::const_iterator::operator--(int) {
    static_cast<std::string::const_iterator *>(m_impl)->operator--(0);
    return *this;
  }

  String::const_iterator String::const_iterator::operator+(const difference_type &n) const {return static_cast<const std::string::const_iterator * const>(m_impl)->operator+(n);}
  String::const_iterator String::const_iterator::operator-(const difference_type &n) const {return static_cast<const std::string::const_iterator * const>(m_impl)->operator-(n);}
  String::const_iterator::difference_type String::const_iterator::operator-(const const_iterator &rhs) const {return *static_cast<const std::string::const_iterator * const>(m_impl) - *static_cast<const std::string::const_iterator * const>(rhs.m_impl);}

  bool String::const_iterator::operator<(const const_iterator &rhs) const {return *static_cast<const std::string::const_iterator * const>(m_impl) < *static_cast<const std::string::const_iterator * const>(rhs.m_impl);}
  bool String::const_iterator::operator>(const const_iterator &rhs) const {return *static_cast<const std::string::const_iterator * const>(m_impl) > *static_cast<const std::string::const_iterator * const>(rhs.m_impl);}
  bool String::const_iterator::operator<=(const const_iterator &rhs) const {return *static_cast<const std::string::const_iterator * const>(m_impl) <= *static_cast<const std::string::const_iterator * const>(rhs.m_impl);}
  bool String::const_iterator::operator>=(const const_iterator &rhs) const {return *static_cast<const std::string::const_iterator * const>(m_impl) >= *static_cast<const std::string::const_iterator * const>(rhs.m_impl);}

  String::const_iterator String::const_iterator::operator+=(const difference_type &n) {
    static_cast<std::string::const_iterator *>(m_impl)->operator+=(n);
    return *this;
  }
  String::const_iterator String::const_iterator::operator-=(const difference_type &n) {
    static_cast<std::string::const_iterator *>(m_impl)->operator-=(n);
    return *this;
  }
      
  String::const_iterator::value_type String::const_iterator::operator[](const difference_type &n) const {return static_cast<const std::string::const_iterator * const>(m_impl)->operator[](n);}

  String::const_iterator::const_iterator(const std::string::const_iterator &iter) : m_impl(new std::string::const_iterator(iter)) {}
  String::const_iterator & String::const_iterator::operator=(const std::string::const_iterator &iter) {
    String::const_iterator temp(iter);
    std::swap(m_impl, temp.m_impl);
    return *this;
  }
  
  String::reverse_iterator::reverse_iterator() : m_impl(new std::string::reverse_iterator) {}
  String::reverse_iterator::~reverse_iterator() {delete static_cast<std::string::reverse_iterator *>(m_impl);}

  String::reverse_iterator::reverse_iterator(const reverse_iterator &rhs) : m_impl(new std::string::reverse_iterator(*static_cast<const std::string::reverse_iterator * const>(rhs.m_impl))) {}
  String::reverse_iterator & String::reverse_iterator::operator=(const reverse_iterator &rhs) {
    *static_cast<std::string::reverse_iterator *>(m_impl) = *static_cast<std::string::reverse_iterator *>(rhs.m_impl);
    return *this;
  }
      
  bool String::reverse_iterator::operator==(const reverse_iterator &rhs) const {return *static_cast<const std::string::reverse_iterator * const>(m_impl) == *static_cast<const std::string::reverse_iterator *>(rhs.m_impl);}
  bool String::reverse_iterator::operator!=(const reverse_iterator &rhs) const {return *static_cast<const std::string::reverse_iterator * const>(m_impl) != *static_cast<const std::string::reverse_iterator *>(rhs.m_impl);}
      
  String::reverse_iterator::value_type String::reverse_iterator::operator*() const {return static_cast<const std::string::reverse_iterator * const>(m_impl)->operator*();}
  String::reverse_iterator::value_type & String::reverse_iterator::operator*() {return static_cast<const std::string::reverse_iterator * const>(m_impl)->operator*();}
  String::reverse_iterator::value_type String::reverse_iterator::operator->() const {return static_cast<const std::string::reverse_iterator * const>(m_impl)->operator*();}
  String::reverse_iterator::value_type & String::reverse_iterator::operator->() {return static_cast<const std::string::reverse_iterator * const>(m_impl)->operator*();}
      
  String::reverse_iterator String::reverse_iterator::operator++() {
    static_cast<std::string::reverse_iterator *>(m_impl)->operator++();
    return *this;
  }
  String::reverse_iterator String::reverse_iterator::operator--() {
    static_cast<std::string::reverse_iterator *>(m_impl)->operator--();
    return *this;
  }
  String::reverse_iterator String::reverse_iterator::operator++(int) {
    static_cast<std::string::reverse_iterator *>(m_impl)->operator++(0);
    return *this;
  }
  String::reverse_iterator String::reverse_iterator::operator--(int) {
    static_cast<std::string::reverse_iterator *>(m_impl)->operator--(0);
    return *this;
  }

  String::reverse_iterator String::reverse_iterator::operator+(const difference_type &n) const {return static_cast<const std::string::reverse_iterator * const>(m_impl)->operator+(n);}
  String::reverse_iterator String::reverse_iterator::operator-(const difference_type &n) const {return static_cast<const std::string::reverse_iterator * const>(m_impl)->operator-(n);}
  String::reverse_iterator::difference_type String::reverse_iterator::operator-(const reverse_iterator &rhs) const {return *static_cast<const std::string::reverse_iterator * const>(m_impl) - *static_cast<const std::string::reverse_iterator * const>(rhs.m_impl);}

  bool String::reverse_iterator::operator<(const reverse_iterator &rhs) const {return *static_cast<const std::string::reverse_iterator * const>(m_impl) < *static_cast<const std::string::reverse_iterator * const>(rhs.m_impl);}
  bool String::reverse_iterator::operator>(const reverse_iterator &rhs) const {return *static_cast<const std::string::reverse_iterator * const>(m_impl) > *static_cast<const std::string::reverse_iterator * const>(rhs.m_impl);}
  bool String::reverse_iterator::operator<=(const reverse_iterator &rhs) const {return *static_cast<const std::string::reverse_iterator * const>(m_impl) <= *static_cast<const std::string::reverse_iterator * const>(rhs.m_impl);}
  bool String::reverse_iterator::operator>=(const reverse_iterator &rhs) const {return *static_cast<const std::string::reverse_iterator * const>(m_impl) >= *static_cast<const std::string::reverse_iterator * const>(rhs.m_impl);}

  String::reverse_iterator String::reverse_iterator::operator+=(const difference_type &n) {
    static_cast<std::string::reverse_iterator *>(m_impl)->operator+=(n);
    return *this;
  }
  String::reverse_iterator String::reverse_iterator::operator-=(const difference_type &n) {
    static_cast<std::string::reverse_iterator *>(m_impl)->operator-=(n);
    return *this;
  }
      
  String::reverse_iterator::value_type String::reverse_iterator::operator[](const difference_type &n) const {return static_cast<const std::string::reverse_iterator * const>(m_impl)->operator[](n);}
  String::reverse_iterator::value_type & String::reverse_iterator::operator[](const difference_type &n) {return static_cast<std::string::reverse_iterator *>(m_impl)->operator[](n);}

  String::reverse_iterator::reverse_iterator(const std::string::reverse_iterator &iter) : m_impl(new std::string::reverse_iterator(iter)) {}
  String::reverse_iterator & String::reverse_iterator::operator=(const std::string::reverse_iterator &iter) {
    String::reverse_iterator temp(iter);
    std::swap(m_impl, temp.m_impl);
    return *this;
  }

  String::const_reverse_iterator::const_reverse_iterator() : m_impl(new std::string::const_reverse_iterator) {}
  String::const_reverse_iterator::~const_reverse_iterator() {delete static_cast<std::string::const_reverse_iterator *>(m_impl);}

  String::const_reverse_iterator::const_reverse_iterator(const const_reverse_iterator &rhs) : m_impl(new std::string::const_reverse_iterator(*static_cast<const std::string::const_reverse_iterator * const>(rhs.m_impl))) {}
  String::const_reverse_iterator & String::const_reverse_iterator::operator=(const const_reverse_iterator &rhs) {
    *static_cast<std::string::const_reverse_iterator *>(m_impl) = *static_cast<std::string::const_reverse_iterator *>(rhs.m_impl);
    return *this;
  }
      
  bool String::const_reverse_iterator::operator==(const const_reverse_iterator &rhs) const {return *static_cast<const std::string::const_reverse_iterator * const>(m_impl) == *static_cast<const std::string::const_reverse_iterator *>(rhs.m_impl);}
  bool String::const_reverse_iterator::operator!=(const const_reverse_iterator &rhs) const {return *static_cast<const std::string::const_reverse_iterator * const>(m_impl) != *static_cast<const std::string::const_reverse_iterator *>(rhs.m_impl);}
      
  String::const_reverse_iterator::value_type String::const_reverse_iterator::operator*() const {return static_cast<const std::string::const_reverse_iterator * const>(m_impl)->operator*();}
  String::const_reverse_iterator::value_type String::const_reverse_iterator::operator->() const {return static_cast<const std::string::const_reverse_iterator * const>(m_impl)->operator*();}
      
  String::const_reverse_iterator String::const_reverse_iterator::operator++() {
    static_cast<std::string::const_reverse_iterator *>(m_impl)->operator++();
    return *this;
  }
  String::const_reverse_iterator String::const_reverse_iterator::operator--() {
    static_cast<std::string::const_reverse_iterator *>(m_impl)->operator--();
    return *this;
  }
  String::const_reverse_iterator String::const_reverse_iterator::operator++(int) {
    static_cast<std::string::const_reverse_iterator *>(m_impl)->operator++(0);
    return *this;
  }
  String::const_reverse_iterator String::const_reverse_iterator::operator--(int) {
    static_cast<std::string::const_reverse_iterator *>(m_impl)->operator--(0);
    return *this;
  }

  String::const_reverse_iterator String::const_reverse_iterator::operator+(const difference_type &n) const {return static_cast<const std::string::const_reverse_iterator * const>(m_impl)->operator+(n);}
  String::const_reverse_iterator String::const_reverse_iterator::operator-(const difference_type &n) const {return static_cast<const std::string::const_reverse_iterator * const>(m_impl)->operator-(n);}
  String::const_reverse_iterator::difference_type String::const_reverse_iterator::operator-(const const_reverse_iterator &rhs) const {return *static_cast<const std::string::const_reverse_iterator * const>(m_impl) - *static_cast<const std::string::const_reverse_iterator * const>(rhs.m_impl);}

  bool String::const_reverse_iterator::operator<(const const_reverse_iterator &rhs) const {return *static_cast<const std::string::const_reverse_iterator * const>(m_impl) < *static_cast<const std::string::const_reverse_iterator * const>(rhs.m_impl);}
  bool String::const_reverse_iterator::operator>(const const_reverse_iterator &rhs) const {return *static_cast<const std::string::const_reverse_iterator * const>(m_impl) > *static_cast<const std::string::const_reverse_iterator * const>(rhs.m_impl);}
  bool String::const_reverse_iterator::operator<=(const const_reverse_iterator &rhs) const {return *static_cast<const std::string::const_reverse_iterator * const>(m_impl) <= *static_cast<const std::string::const_reverse_iterator * const>(rhs.m_impl);}
  bool String::const_reverse_iterator::operator>=(const const_reverse_iterator &rhs) const {return *static_cast<const std::string::const_reverse_iterator * const>(m_impl) >= *static_cast<const std::string::const_reverse_iterator * const>(rhs.m_impl);}

  String::const_reverse_iterator String::const_reverse_iterator::operator+=(const difference_type &n) {
    static_cast<std::string::const_reverse_iterator *>(m_impl)->operator+=(n);
    return *this;
  }
  String::const_reverse_iterator String::const_reverse_iterator::operator-=(const difference_type &n) {
    static_cast<std::string::const_reverse_iterator *>(m_impl)->operator-=(n);
    return *this;
  }
      
  String::const_reverse_iterator::value_type String::const_reverse_iterator::operator[](const difference_type &n) const {return static_cast<const std::string::const_reverse_iterator * const>(m_impl)->operator[](n);}

  String::const_reverse_iterator::const_reverse_iterator(const std::string::const_reverse_iterator &iter) : m_impl(new std::string::const_reverse_iterator(iter)) {}
  String::const_reverse_iterator & String::const_reverse_iterator::operator=(const std::string::const_reverse_iterator &iter) {
    String::const_reverse_iterator temp(iter);
    std::swap(m_impl, temp.m_impl);
    return *this;
  }

  String::String() : m_impl(new std::string) {}
  String::String(const String &str) : m_impl(new std::string(*static_cast<std::string *>(str.m_impl))) {}
  String::String(const String &str, size_t pos, size_t n) : m_impl(new std::string(*static_cast<std::string *>(str.m_impl), pos, n)) {}
  String::String(const char * s, size_t n) : m_impl(new std::string(s, n)) {}
  String::String(const char * s) : m_impl(new std::string(s)) {}
  String::String(size_t n, char c) : m_impl(new std::string(n, c)) {}

  String::~String() {delete static_cast<std::string *>(m_impl);}

  String & String::operator=(const String &str) {
    String temp(str);
    swap(temp);
    return *this;
  }
  String & String::operator=(const char *s) {
    String temp(s);
    swap(temp);
    return *this;
  }
  String & String::operator=(char c) {
    String temp(1, c);
    swap(temp);
    return *this;
  }

  String::iterator String::begin() {return static_cast<std::string *>(m_impl)->begin();}
  String::const_iterator String::begin() const {return static_cast<const std::string * const>(m_impl)->begin();}

  String::iterator String::end() {return static_cast<std::string *>(m_impl)->end();}
  String::const_iterator String::end() const {return static_cast<const std::string * const>(m_impl)->end();}

  String::reverse_iterator String::rbegin() {return static_cast<std::string *>(m_impl)->rbegin();}
  String::const_reverse_iterator String::rbegin() const {return static_cast<const std::string * const>(m_impl)->rbegin();}

  String::reverse_iterator String::rend() {return static_cast<std::string *>(m_impl)->rend();}
  String::const_reverse_iterator String::rend() const {return static_cast<const std::string * const>(m_impl)->rend();}

  size_t String::size() const {return static_cast<std::string *>(m_impl)->size();}

  size_t String::length() const {return static_cast<std::string *>(m_impl)->length();}

  size_t String::max_size() const {return static_cast<std::string *>(m_impl)->max_size();}

  void String::resize(size_t n, char c) {static_cast<std::string *>(m_impl)->resize(n, c);}
  void String::resize(size_t n) {static_cast<std::string *>(m_impl)->resize(n);}

  size_t String::capacity() const {return static_cast<std::string *>(m_impl)->capacity();}

  void String::reserve(size_t res_arg) {static_cast<std::string *>(m_impl)->reserve(res_arg);}

  void String::clear() {static_cast<std::string *>(m_impl)->clear();}

  bool String::empty() const {return static_cast<std::string *>(m_impl)->empty();}

  String::value_type String::operator[](const unsigned int &pos) const {return static_cast<const std::string * const>(m_impl)->operator[](pos);}
  String::value_type & String::operator[](const unsigned int &pos) {return static_cast<std::string *>(m_impl)->operator[](pos);}

  String::value_type String::at(size_t pos) const {return static_cast<const std::string * const>(m_impl)->at(pos);}
  String::value_type & String::at(size_t pos) {return static_cast<std::string *>(m_impl)->at(pos);}

  String & String::operator+=(const String & str) {
    *static_cast<std::string *>(m_impl) += *static_cast<std::string *>(str.m_impl);
    return *this;
  }
  String & String::operator+=(const char *s) {
    *static_cast<std::string *>(m_impl) += s;
    return *this;
  }
  String & String::operator+=(char c) {
    *static_cast<std::string *>(m_impl) += c;
    return *this;
  }
    
  String & String::append(const String &str) {
    static_cast<std::string *>(m_impl)->append(*static_cast<std::string *>(str.m_impl));
    return *this;
  }
  String & String::append(const String &str, size_t pos, size_t n) {
    static_cast<std::string *>(m_impl)->append(*static_cast<std::string *>(str.m_impl), pos, n);
    return *this;
  }
  String & String::append(const char *s, size_t n) {
    static_cast<std::string *>(m_impl)->append(s, n);
    return *this;
  }
  String & String::append(const char *s) {
    static_cast<std::string *>(m_impl)->append(s);
    return *this;
  }
  String & String::append(size_t n, char c) {
    static_cast<std::string *>(m_impl)->append(n, c);
    return *this;
  }

  void String::push_back(char c) {static_cast<std::string *>(m_impl)->push_back(c);}
    
  String & String::assign(const String &str) {
    static_cast<std::string *>(m_impl)->assign(*static_cast<std::string *>(str.m_impl));
    return *this;
  }
  String & String::assign(const String &str, size_t pos, size_t n) {
    static_cast<std::string *>(m_impl)->assign(*static_cast<std::string *>(str.m_impl), pos, n);
    return *this;
  }
  String & String::assign(const char *s, size_t n) {
    static_cast<std::string *>(m_impl)->assign(s, n);
    return *this;
  }
  String & String::assign(const char *s) {
    static_cast<std::string *>(m_impl)->assign(s);
    return *this;
  }
  String & String::assign(size_t n, char c) {
    static_cast<std::string *>(m_impl)->assign(n, c);
    return *this;
  }
    
  String & String::insert(size_t pos1, const String &str) {
    static_cast<std::string *>(m_impl)->insert(pos1, *static_cast<std::string *>(str.m_impl));
    return *this;
  }
  String & String::insert(size_t pos1, const String &str, size_t pos2, size_t n) {
    static_cast<std::string *>(m_impl)->insert(pos1, *static_cast<std::string *>(str.m_impl), pos2, n);
    return *this;
  }
  String & String::insert(size_t pos1, const char *s, size_t n) {
    static_cast<std::string *>(m_impl)->insert(pos1, s, n);
    return *this;
  }
  String & String::insert(size_t pos1, const char *s) {
    static_cast<std::string *>(m_impl)->insert(pos1, s);
    return *this;
  }
  String & String::insert(size_t pos1, size_t n, char c) {
    static_cast<std::string *>(m_impl)->insert(pos1, n, c);
    return *this;
  }
  String::iterator String::insert(iterator p, char c) {
    return static_cast<std::string *>(m_impl)->insert(*static_cast<std::string::iterator *>(p.m_impl), c);
  }
  void String::insert(iterator p, size_t n, char c) {
    static_cast<std::string *>(m_impl)->insert(*static_cast<std::string::iterator *>(p.m_impl), n, c);
  }

  String & String::erase(size_t pos, size_t n) {
    static_cast<std::string *>(m_impl)->erase(pos, n);
    return *this;
  }
  String::iterator String::erase(iterator position) {
    return static_cast<std::string *>(m_impl)->erase(*static_cast<std::string::iterator *>(position.m_impl));
  }
  String::iterator String::erase(iterator first, iterator last) {
    return static_cast<std::string *>(m_impl)->erase(*static_cast<std::string::iterator *>(first.m_impl), *static_cast<std::string::iterator *>(last.m_impl));
  }

  String & String::replace(size_t pos1, size_t n1, const String &str) {
    static_cast<std::string *>(m_impl)->replace(pos1, n1, *static_cast<std::string *>(str.m_impl));
    return *this;
  }
  String & String::replace(iterator i1, iterator i2, const String &str) {
    static_cast<std::string *>(m_impl)->replace(*static_cast<std::string::iterator *>(i1.m_impl), *static_cast<std::string::iterator *>(i2.m_impl), *static_cast<const std::string * const>(str.m_impl));
    return *this;
  }
  String & String::replace(size_t pos1, size_t n1, const String &str, size_t pos2, size_t n2) {
    static_cast<std::string *>(m_impl)->replace(pos1, n1, *static_cast<std::string *>(str.m_impl), pos2, n2);
    return *this;
  }
  String & String::replace(size_t pos1, size_t n1, const char *s, size_t n2) {
    static_cast<std::string *>(m_impl)->replace(pos1, n1, s, n2);
    return *this;
  }
  String & String::replace(iterator i1, iterator i2, const char *s, size_t n2) {
    static_cast<std::string *>(m_impl)->replace(*static_cast<std::string::iterator *>(i1.m_impl), *static_cast<std::string::iterator *>(i2.m_impl), s, n2);
    return *this;
  }
  String & String::replace(size_t pos1, size_t n1, const char *s) {
    static_cast<std::string *>(m_impl)->replace(pos1, n1, s);
    return *this;
  }
  String & String::replace(iterator i1, iterator i2, const char *s) {
    static_cast<std::string *>(m_impl)->replace(*static_cast<std::string::iterator *>(i1.m_impl), *static_cast<std::string::iterator *>(i2.m_impl), s);
    return *this;
  }
  String & String::replace(size_t pos1, size_t n1, size_t n2, char c) {
    static_cast<std::string *>(m_impl)->replace(pos1, n1, n2, c);
    return *this;
  }
  String & String::replace(iterator i1, iterator i2, size_t n2, char c) {
    static_cast<std::string *>(m_impl)->replace(*static_cast<std::string::iterator *>(i1.m_impl), *static_cast<std::string::iterator *>(i2.m_impl), n2, c);
    return *this;
  }

  void String::swap(String &str) {std::swap(m_impl, str.m_impl);}

  const char * String::c_str() const {return static_cast<std::string *>(m_impl)->c_str();}

  const char * String::data() const {return static_cast<std::string *>(m_impl)->data();}

#ifdef _WINDOWS
#pragma warning( push )
#pragma warning( disable : 4996 )
#endif
  size_t String::copy(char *s, size_t n, size_t pos) const {return static_cast<std::string *>(m_impl)->copy(s, n, pos);}
#ifdef _WINDOWS
#pragma warning( pop )
#endif

  size_t String::find(const String &str, size_t pos) const {return static_cast<std::string *>(m_impl)->find(*static_cast<std::string *>(str.m_impl), pos);}
  size_t String::find(const char *s, size_t pos, size_t n) const {return static_cast<std::string *>(m_impl)->find(s, pos, n);}
  size_t String::find(const char *s, size_t pos) const {return static_cast<std::string *>(m_impl)->find(s, pos);}
  size_t String::find(char c, size_t pos) const {return static_cast<std::string *>(m_impl)->find(c, pos);}

  size_t String::rfind(const String &str, size_t pos) const {return static_cast<std::string *>(m_impl)->rfind(*static_cast<std::string *>(str.m_impl), pos);}
  size_t String::rfind(const char *s, size_t pos, size_t n) const {return static_cast<std::string *>(m_impl)->rfind(s, pos, n);}
  size_t String::rfind(const char *s, size_t pos) const {return static_cast<std::string *>(m_impl)->rfind(s, pos);}
  size_t String::rfind(char c, size_t pos) const {return static_cast<std::string *>(m_impl)->rfind(c, pos);}

  size_t String::find_first_of(const String &str, size_t pos) const {return static_cast<std::string *>(m_impl)->find_first_of(*static_cast<std::string *>(str.m_impl), pos);}
  size_t String::find_first_of(const char *s, size_t pos, size_t n) const {return static_cast<std::string *>(m_impl)->find_first_of(s, pos, n);}
  size_t String::find_first_of(const char *s, size_t pos) const {return static_cast<std::string *>(m_impl)->find_first_of(s, pos);}
  size_t String::find_first_of(char c, size_t pos) const {return static_cast<std::string *>(m_impl)->find_first_of(c, pos);}

  size_t String::find_last_of(const String &str, size_t pos) const {return static_cast<std::string *>(m_impl)->find_last_of(*static_cast<std::string *>(str.m_impl), pos);}
  size_t String::find_last_of(const char *s, size_t pos, size_t n) const {return static_cast<std::string *>(m_impl)->find_last_of(s, pos, n);}
  size_t String::find_last_of(const char *s, size_t pos) const {return static_cast<std::string *>(m_impl)->find_last_of(s, pos);}
  size_t String::find_last_of(char c, size_t pos) const {return static_cast<std::string *>(m_impl)->find_last_of(c, pos);}

  size_t String::find_first_not_of(const String &str, size_t pos) const {return static_cast<std::string *>(m_impl)->find_first_not_of(*static_cast<std::string *>(str.m_impl), pos);}
  size_t String::find_first_not_of(const char *s, size_t pos, size_t n) const {return static_cast<std::string *>(m_impl)->find_first_not_of(s, pos, n);}
  size_t String::find_first_not_of(const char *s, size_t pos) const {return static_cast<std::string *>(m_impl)->find_first_not_of(s, pos);}
  size_t String::find_first_not_of(char c, size_t pos) const {return static_cast<std::string *>(m_impl)->find_first_not_of(c, pos);}

  size_t String::find_last_not_of(const String &str, size_t pos) const {return static_cast<std::string *>(m_impl)->find_last_not_of(*static_cast<std::string *>(str.m_impl), pos);}
  size_t String::find_last_not_of(const char *s, size_t pos, size_t n) const {return static_cast<std::string *>(m_impl)->find_last_not_of(s, pos, n);}
  size_t String::find_last_not_of(const char *s, size_t pos) const {return static_cast<std::string *>(m_impl)->find_last_not_of(s, pos);}
  size_t String::find_last_not_of(char c, size_t pos) const {return static_cast<std::string *>(m_impl)->find_last_not_of(c, pos);}

  String String::substr(size_t pos, size_t n) const {return String(static_cast<std::string *>(m_impl)->substr(pos, n));}

  int String::compare(const String &str) const {return static_cast<std::string *>(m_impl)->compare(*static_cast<std::string *>(str.m_impl));}
  int String::compare(const char *s) const {return static_cast<std::string *>(m_impl)->compare(s);}
  int String::compare(size_t pos1, size_t n1, const String &str) const {return static_cast<std::string *>(m_impl)->compare(pos1, n1, *static_cast<std::string *>(str.m_impl));}
  int String::compare(size_t pos1, size_t n1, const char *s) const {return static_cast<std::string *>(m_impl)->compare(pos1, n1, s);}
  int String::compare(size_t pos1, size_t n1, const String &str, size_t pos2, size_t n2) const {return static_cast<std::string *>(m_impl)->compare(pos1, n1, *static_cast<std::string *>(str.m_impl), pos2, n2);}
  int String::compare(size_t pos1, size_t n1, const char *s, size_t n2) const {return static_cast<std::string *>(m_impl)->compare(pos1, n1, s, n2);}

  bool String::operator==(const Zeni::String &rhs) const {return *static_cast<const std::string * const>(m_impl) == *static_cast<const std::string * const>(rhs.m_impl);}
  bool String::operator==(const char *rhs) const {return *static_cast<const std::string * const>(m_impl) == rhs;}
  bool String::operator!=(const Zeni::String &rhs) const {return *static_cast<const std::string * const>(m_impl) != *static_cast<const std::string * const>(rhs.m_impl);}
  bool String::operator!=(const char *rhs) const {return *static_cast<const std::string * const>(m_impl) != rhs;}
  bool String::operator<(const Zeni::String &rhs) const {return *static_cast<const std::string * const>(m_impl) < *static_cast<const std::string * const>(rhs.m_impl);}
  bool String::operator<(const char *rhs) const {return *static_cast<const std::string * const>(m_impl) < rhs;}
  bool String::operator>(const Zeni::String &rhs) const {return *static_cast<const std::string * const>(m_impl) > *static_cast<const std::string * const>(rhs.m_impl);}
  bool String::operator>(const char *rhs) const {return *static_cast<const std::string * const>(m_impl) > rhs;}
  bool String::operator<=(const Zeni::String &rhs) const {return *static_cast<const std::string * const>(m_impl) <= *static_cast<const std::string * const>(rhs.m_impl);}
  bool String::operator<=(const char *rhs) const {return *static_cast<const std::string * const>(m_impl) <= rhs;}
  bool String::operator>=(const Zeni::String &rhs) const {return *static_cast<const std::string * const>(m_impl) >= *static_cast<const std::string * const>(rhs.m_impl);}
  bool String::operator>=(const char *rhs) const {return *static_cast<const std::string * const>(m_impl) >= rhs;}

  size_t String::Hash::operator()(const String &str) const {
    size_t val = 42u;
    for(const_iterator it = str.begin(), iend = str.end(); it != iend; ++it)
      val = ((val << 5) | (val >> (8u * sizeof(size_t) - 5))) + static_cast<unsigned int>(*it);
    return val;
  }

  bool String::Hash::operator()(const String &lhs, const String &rhs) const {
    return lhs != rhs;
  }

}

ZENI_DLL Zeni::String::iterator operator+(const Zeni::String::iterator::difference_type &lhs, const Zeni::String::iterator &rhs) {return rhs + lhs;}
ZENI_DLL Zeni::String::const_iterator operator+(const Zeni::String::const_iterator::difference_type &lhs, const Zeni::String::const_iterator &rhs) {return rhs + lhs;}
ZENI_DLL Zeni::String::reverse_iterator operator+(const Zeni::String::reverse_iterator::difference_type &lhs, const Zeni::String::reverse_iterator &rhs) {return rhs + lhs;}
ZENI_DLL Zeni::String::const_reverse_iterator operator+(const Zeni::String::const_reverse_iterator::difference_type &lhs, const Zeni::String::const_reverse_iterator &rhs) {return rhs + lhs;}

ZENI_DLL Zeni::String operator+(const Zeni::String &lhs, const Zeni::String &rhs) {
  Zeni::String rv(lhs);
  return rv += rhs;
}
ZENI_DLL Zeni::String operator+(const Zeni::String &lhs, const char *rhs) {
  Zeni::String rv(lhs);
  return rv += rhs;
}
ZENI_DLL Zeni::String operator+(const Zeni::String &lhs, char rhs) {
  Zeni::String rv(lhs);
  return rv += rhs;
}
ZENI_DLL Zeni::String operator+(const char *lhs, const Zeni::String &rhs) {
  Zeni::String rv(lhs);
  return rv += rhs;
}
ZENI_DLL Zeni::String operator+(char lhs, const Zeni::String &rhs) {
  Zeni::String rv(1, lhs);
  return rv += rhs;
}

ZENI_DLL bool operator==(const char *lhs, const Zeni::String &rhs) {return rhs == lhs;}
ZENI_DLL bool operator!=(const char *lhs, const Zeni::String &rhs) {return rhs != lhs;}
ZENI_DLL bool operator<(const char *lhs, const Zeni::String &rhs) {return rhs >= lhs;}
ZENI_DLL bool operator>(const char *lhs, const Zeni::String &rhs) {return rhs <= lhs;}
ZENI_DLL bool operator<=(const char *lhs, const Zeni::String &rhs) {return rhs > lhs;}
ZENI_DLL bool operator>=(const char *lhs, const Zeni::String &rhs) {return rhs < lhs;}

ZENI_DLL void swap(Zeni::String &lhs, Zeni::String &rhs) {
  lhs.swap(rhs);
}

std::istream & operator>>(std::istream &is, Zeni::String &str) {
  Zeni::String temp;

  if(is >> std::ws)
    while(is && !std::isspace(is.peek()))
      temp += (char)is.get();

  str.swap(temp);

  return is;
}

std::ostream & operator<<(std::ostream &os, const Zeni::String &str) {
  for(Zeni::String::const_iterator it = str.begin(), iend = str.end(); os && it != iend; ++it)
    os.put(*it);

  return os;
}
