#ifndef LRU_HPP
#define LRU_HPP

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

#include "item.hpp"
#include "common.hpp"
#include "cache_algorithm_base.hpp"
#include "statistics_algorithm_base.hpp"

// TODO: support string keys
// Update the PDF and print it in the end

using namespace std;

class lru : public cache_algorithm_base {
public:
  using cache_algorithm_base::cache_algorithm_base;
  item *get(int key);
  void set(int key, int val);
  item *find(int key);
  void update_lru_head(item *it);
  void unlink(item *it);
  void evict();
  void printCacheContents(); 
  // This method needs to be overwritten to make sense
  // This method is overwritten in lru_avl.cpp and lru_mattson.cpp
  int get_stackdistance(item *findme, int dist=-1) {
    return -1;
  }
};

#endif // LRU_HPP
