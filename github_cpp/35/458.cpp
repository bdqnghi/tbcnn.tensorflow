
#include <assert.h>

template <class T>
class LinkedList {
  public:
    T value;
    LinkedList<T> *next;

    LinkedList(T nodeValue) {
      value = nodeValue;
      next = NULL;
    }

    LinkedList(T nodeValue, LinkedList<T> *nodeNext) {
      value = nodeValue;
      next = nodeNext;
    }

    LinkedList<T>* query(const T search) {
      if(value == search) return this;
      if(next == NULL) return NULL;
      return next->query(search);
    }

    bool insertAfter(LinkedList<T> *node, LinkedList<T> *newNode) {
      if(this == node) {
        LinkedList<T> *oldNext = (*node).next;
        (*node).next = newNode;
        (*newNode).next = oldNext;
        return true;
      }
      if(next == NULL) return false;
      return next->insertAfter(node, newNode);
    }

    bool removeAfter(LinkedList<T> *node) {
      if(next == NULL) return false;
      if(this == node) {
        next = next->next;
        return true;
      }
      return next->removeAfter(node);
    }

    void append(LinkedList<T> *list) {
      if(next == NULL) {
        next = list;
      } else {
        next->append(list);
      }
    }

    int size() {
      if(next == NULL) return 1;
      return next->size(1);
    }

  private:
    /*
     * Written this way for tail-call optimization
     */
    int size(int count) {
      ++count;
      if(next == NULL) return count;
      return next->size(count);
    }
};


int main() {
  typedef LinkedList<int> LLI;

  LLI root(12);
  LLI child1(24);

  assert(root.query(0) == NULL);
  assert(root.query(12) == &root);
  assert(root.size() == 1);

  root.append(&child1);

  assert(root.size() == 2);

  LLI* child2 = new LLI(36);

  bool didInsert = root.insertAfter(&child1, child2);

  assert(didInsert);
  assert(root.size() == 3);

  bool didRemove = root.removeAfter(&root);

  assert(didRemove);
  assert(root.size() == 2);

  LLI* list = new LLI(48, new LLI(60, new LLI(72)));

  assert(list->size() == 3);

  root.append(list);

  assert(root.size() == 5);
  assert(root.query(48) == list);

  return 0;
}

