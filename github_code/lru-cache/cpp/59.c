//
// Created by Sergey Ivanychev on 08/05/2017.
//

#ifndef CPP_LRU_CACHE_LRU_CACHE_H
#define CPP_LRU_CACHE_LRU_CACHE_H

#include <iostream>
#include <map>
#include <forward_list>

namespace lru_cache {

class LruCache {
  // This class implements Least recently used (LRU) cache that is capable of
  // caching function calls (only pure functions are allowed).
  //
  // At the moment, std::string(std::string) is the only supported signature.
  //
  // Usage:
  //
  // string foo(string bar) {
  //   static LruCache cache;
  //
  //   if ((auto pair = cache.find(bar)).second) {
  //     return pair.first;
  //   }
  //   ...
  //   cache.insert(baz);
  //   return baz
  // }
 public:
  using arg_type = std::string;
  using return_type = std::string;

  // Don't need the assignment operator to be defined for cache.
  LruCache& operator=(const LruCache&) = delete;

 private:
  // The list stores (argument, return value) pairs. LRU values are contained
  // at the head of the list. Since it's size doesn't exceed the capacity of the
  // list, too old values are expelled.
  std::forward_list<std::pair<arg_type, return_type>> priority_list_;

  // Current mapping maps arg_type values to nodes where related
  // (argument, return value) is contained (or there's no such key in the
  // mapping).
  std::map<arg_type, decltype(priority_list_)> argument_map_;

  // Capacity of the cache.
  int32_t capacity_;
 public:
  // Default constructor. User can or cannot specify the capacity.
  LruCache(int32_t capacity = 64);

  // Don't need to do anything specific here, yet we need the default destructor
  // to be invoked.
  ~LruCache() = default;

  // Find method returns a pair (::return_type, bool). The second member denotes
  // if the passed key was found or not. If it's true, the first member denotes
  // the corresponding return value. Note: find *updates* the data structure
  // by reordering the priority_list_. Thus, the method is not const.
  std::pair<const return_type&, bool> find(const arg_type& argument);

  // At the end of function's body we always call insert, so the priority_list_
  // updates after every invocation.
  LruCache& insert(std::pair<arg_type, return_type>);
};

} // namespace lru_cache

#endif //CPP_LRU_CACHE_LRU_CACHE_H
