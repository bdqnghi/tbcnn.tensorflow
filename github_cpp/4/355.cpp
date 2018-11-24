#include <string>
#include "gtest/gtest.h"


// Fixed size
static int TABLE_SIZE = 256;

// string-int key value pair
struct Node {
  Node() = delete;
  Node(std::string k, int v): key(k), value(v) {}

  std::string key;
  int value;
};



class HashTable {
public:
  HashTable() {
    // initialize by ()
    table = new Node*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; ++i) {
      table[i] = nullptr;
    }
  }

  ~HashTable() {
    // free pointers and table
    for (int i = 0; i < TABLE_SIZE; ++i) {
      if (table[i]) {
        delete table[i];
      }
    }
    delete []table;
  }

  void set(std::string key, int value) {
    auto __hash = hash(key);

    // in case collision
    while (table[__hash] && table[__hash]->key != key) {
      __hash = hash(__hash + 1);
    }

    table[__hash] = new Node(key, value);
  }

  int search(std::string key) {
    auto __hash = hash(key);

    // in case collision
    while (table[__hash] && table[__hash]->key != key) {
      __hash = hash(__hash + 1);
    }

    if (!table[__hash]) {return -1;}
    return table[__hash]->value;
  }

  bool remove(std::string key) {
    auto __hash = hash(key);

    while (table[__hash]) {
      if (table[__hash]->key == key) {break;}
      __hash = hash(__hash + 1);
    }

    if (!table[__hash]) {return false;}

    // mark as deleted
    delete table[__hash];
    table[__hash] = nullptr;
    return true;
  }

private:


  Node **table;

  // hash function: compute an index into buckets
  int hash(std::string k) {
    int value = 0;
    int len = k.length();
    for (int i = 0; i < len; ++i) {
      value += k[i];
    }
    return value % TABLE_SIZE;
  }

  int hash(int k) {
    return k % TABLE_SIZE;
  }


};

TEST(HashTableTest, SomeTest) {
  auto a = HashTable();

  // set
  a.set("java", 1);
  a.set("yayyyy", 2);
  a.set("yay", 2);

  // search
  EXPECT_EQ(a.search("yay"), 2);
  EXPECT_EQ(a.search("yayyyy"), 2);
  EXPECT_EQ(a.search("java"), 1);
  EXPECT_EQ(a.search("javascript"), -1);

  // remove
  EXPECT_EQ(a.remove("javascript"), false);
  EXPECT_EQ(a.remove("java"), true);
  EXPECT_EQ(a.remove("yayyyy"), true);
  EXPECT_EQ(a.search("yayyyy"), -1);

}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
