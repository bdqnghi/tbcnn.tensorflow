//
// Created by lizgao on 7/24/18.
//
#include <string>
#include <algorithm>
#include <unordered_map>
#include <list>
namespace {

class LRUCache {
 public:
  LRUCache(int capacity) : capacity_(capacity) {

  }

  int get(int key) {
    auto it = data_map_.find(key);
    if(it == data_map_.end()) {
      return -1;
    }
    key_list_.erase(it->second.second);
    int value = it->second.first;
    key_list_.push_back(key);
  }

  void put(int key, int value) {
    if(key_list_.size() == capacity_) {
      auto k = key_list_.front();
      key_list_.pop_front();
      data_map_.erase(k);
    }
    key_list_.push_back(key);
    data_map_[key] = {value, std::next(key_list_.end(), -1)};
  }
 private:
  int capacity_;
  std::list<int> key_list_;
  std::unordered_map<int, std::pair<int, std::list<int>::iterator>> data_map_;
};

}