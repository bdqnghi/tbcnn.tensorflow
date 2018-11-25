class LRUCache {
public:
  LRUCache(int capacity) : list_(capacity) {}

  int get(int key) {
    auto it = table_.find(key);
    if (it == table_.end()) return -1;
    return trans(it->second)->second;
  }

  void set(int key, int value) {
    auto node = list_.begin();
    auto it = table_.find(key);
    if (it != table_.end())
      node = it->second;
    else
      table_.erase((table_[key] = node)->first);
    *trans(node) = { key, value };
  }

private:
  typedef list<pair<int, int>> List;

  List::iterator trans(List::iterator node) {
    list_.splice(list_.end(), list_, node);
    return node;
  }

  unordered_map<int, List::iterator> table_;
  List list_;
};
