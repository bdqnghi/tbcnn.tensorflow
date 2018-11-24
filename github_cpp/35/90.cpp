#include<iostream>

using namespace std;

template<typename T>
struct Node {
    Node(T _val, Node *_next) : val(_val), next(_next) {

    }

    T val;
    Node *next;
};

template<typename T>
class Iterator;

template<typename T>
class LinkedList {
private:
    Node<T> *front;
    Node<T> *back;

public:

    LinkedList() {
        front = nullptr;
        back = nullptr;
    }

    ~LinkedList() {
        while (!empty()) {
            Node<T> *tmp = front->next;
            delete front;
            front = tmp;
        }
    }

    bool empty() {
        return front == nullptr;
    }

    bool append(T val) {
        return insertAfter(val, end());
    }

    bool insertAfter(T val, Iterator<T> it) {
        Node<T> *newNode = new Node<T>(val, nullptr);
        if (it == end()) {
            if (empty()) {
                front = newNode;
                back = front;
            }

            back->next = newNode;
            back = back->next;


        } else {
            if (!it.valid()) {
                return false;
            }

            Node<T> *tmp = it.next().ptr;
            newNode->next = tmp;
            it.ptr->next = newNode;

        }

        return true;
    }

    Iterator<T> begin() {
        return Iterator<T>(front);
    }

    Iterator<T> end() {
        return Iterator<T>(back);
    }


};


template<typename T>
class Iterator {
private:
    Node<T> *ptr;
public:

    friend class LinkedList<T>;

    Iterator(Node<T> *_ptr) {
        ptr = _ptr;
    }

    Iterator<T> next() {
        return Iterator(ptr->next);
    }

    bool valid() {
        return ptr != nullptr;
    }

    bool operator==(const Iterator &other) {
        return ptr == other.ptr;
    }

    bool operator!=(const Iterator &other) {
        return !(*this == other);
    }

    T &get() const {
        return ptr->val;
    }

    T const &getConst() const;
};


int main() {

    LinkedList<int> ll;

    for (int i = 0; i < 10; i++) {
        ll.append(i);
    }

    bool test_passed = true;
    int counter = 0;
    for (Iterator<int> it = ll.begin(); it != ll.end(); it = it.next()) {
        if (it.get() != counter++) {
            test_passed = false;
        }
    }

    ll.insertAfter(-1, ll.begin());

    Iterator<int> it = ll.begin();
    it = it.next();

    if (it.get() != -1) {
        test_passed = false;
    }

    cout << "Test is " << (test_passed ? "passed" : "failed") << endl;

}