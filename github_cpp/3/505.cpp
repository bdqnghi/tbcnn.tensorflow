#include "util.h"

struct Node {
  int key, value;
  Node *prev, *next;
};

class LRUCache {
public:
  unordered_map<int, Node *> m;
  Node *head, *tail;
  int capacity_, size_;

  LRUCache(int capacity) {
    capacity_ = capacity;
    size_ = 0;
    head = nullptr;
    tail = nullptr;
  }

  void print() {
    Node *t = head;
    int c = 0;
    cout << "[";
    while (t != nullptr) {
      if (t == head)
        cout << "(H)";
      if (t == tail)
        cout << "(T)";
      cout << t->key;
      if (t->next != nullptr)
        cout << " -> ";
      t = t->next;
      c++;
      if (c > 10)
        break;
    }
    cout << "]" << endl;
  }

  void update(Node *n) {
    if (size_ == 1) {
      head = n;
      tail = n;
      return;
    }
    // Only need to update for non-head nodes.
    if (n != head) {
      Node *prev = n->prev, *next = n->next;
      if (prev != nullptr)
        prev->next = next;
      if (next != nullptr)
        next->prev = prev;
      if (next == nullptr)
        tail = prev;
      n->prev = nullptr;
      n->next = head;
      head->prev = n;
      head = n;
    }
  }

  int get(int key) {
    auto it = m.find(key);
    if (it == m.end())
      return -1;

    Node *n = it->second;
    update(n);
    // print();
    return n->value;
  }

  void set(int key, int value) {
    auto it = m.find(key);
    Node *n;
    if (it == m.end()) {
      size_++;
      if (size_ > capacity_) {
        Node *t = tail;
        tail = t->prev;
        m.erase(t->key);
        delete t;
        size_--;
      }

      n = new Node();
      n->key = key;
      n->value = value;
      n->next = nullptr;
      n->prev = tail;
      if (tail != nullptr)
        tail->next = n;
      tail = n;
      m[key] = n;
    } else {
      n = it->second;
      n->value = value;
    }
    update(n);
    // print();
  }
};

int main() {
  LRUCache c(3);
  EXPECT_EQ(-1, c.get(1));
  c.set(1, 2);
  EXPECT_EQ(2, c.get(1));
  c.set(2, 3);

  EXPECT_EQ(3, c.get(2));
  c.set(3, 4);

  EXPECT_EQ(4, c.get(3));

  // c.get(1);
  EXPECT_EQ(2, c.get(1));
  c.set(4, 5);

  c.set(4, 5);

  EXPECT_EQ(5, c.get(4));
  EXPECT_EQ(-1, c.get(2));
  EXPECT_EQ(5, c.get(4));
  return 0;
}
