



#ifndef CPP_LRU_CACHE_LRU_CACHE_H
#define CPP_LRU_CACHE_LRU_CACHE_H

#include <iostream>
#include <map>
#include <forward_list>

namespace lru_cache {

class LruCache {
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
 public:
  using arg_type = std::string;
  using return_type = std::string;

  
  LruCache& operator=(const LruCache&) = delete;

 private:
  
  
  
  std::forward_list<std::pair<arg_type, return_type>> priority_list_;

  
  
  
  std::map<arg_type, decltype(priority_list_)> argument_map_;

  
  int32_t capacity_;
 public:
  
  LruCache(int32_t capacity = 64);

  
  
  ~LruCache() = default;

  
  
  
  
  std::pair<const return_type&, bool> find(const arg_type& argument);

  
  
  LruCache& insert(std::pair<arg_type, return_type>);
};

} 

#endif 
