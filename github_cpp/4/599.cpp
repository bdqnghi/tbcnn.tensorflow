#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "catch.hpp"

using namespace std;

template <typename HashedObj>
class HashTable {
public:
  HashTable(int size);

  bool contains(HashedObj x);
  void makeEmpty();
  bool insert(HashedObj x);
  bool remove(HashedObj x);

private:
  vector<list<HashedObj>> table;
  int currentSize;

  void rehash();
  size_t myHash(HashedObj &x);
};

template <typename Key>
class Hash {
public:
  size_t operator() (const Key &k) const;
};

template <>
class Hash<string> {
public:
  size_t operator() (const string &key) const {
    size_t hashVal = 0;
    for (char ch: key) {
      hashVal = 37 * hashVal + ch;
    }
    return hashVal;
  }
};

template <>
class Hash<int> {
public:
  size_t operator() (const int &key) const {
    return key;
  }
};

template <typename HashedObj>
HashTable<HashedObj>::HashTable(int size) {
  table.resize(size);
}

template <typename HashedObj>
size_t HashTable<HashedObj>::myHash(HashedObj &x) {
  static Hash<HashedObj> hf;
  return hf(x) % table.size();
}

template <typename HashedObj>
bool HashTable<HashedObj>::insert(HashedObj x) {
  auto &whichList = table[myHash(x)];
  if (find(begin(whichList), end(whichList), x) != end(whichList)) {
    return false;
  }
  whichList.push_back(x);
  return true;
}

template <typename HashedObj>
bool HashTable<HashedObj>::contains(HashedObj x) {
  auto &whichList = table[myHash(x)];
  return find(begin(whichList), end(whichList), x) != end(whichList);
}

// tests

TEST_CASE("HashTables") {
  HashTable<int> ht(10);

  SECTION("inserts a node") {
    for (int i = 1; i <= 9; i += 1) {
      ht.insert(i * i);
    }

    REQUIRE(ht.contains(81));
  }
}
