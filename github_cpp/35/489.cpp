#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T> struct Node {
    T key;
    Node *prev;
    Node *next;
};

template <class T> class LinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    LinkedList() {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    bool empty_list() {
        return size == 0 ? true : false;
    }

    Node<T> *list_search(T key) {
        Node<T> *node = head;
        while (node != NULL && node->key != key) {
            node = node->next;
        }
        return node;
    }

    void list_insert(T x) {
        Node<T> *node = new Node<T>;
        node->key = x;
        node->next = NULL;
        if (tail == NULL) {
            node->prev = NULL;
    		head = tail = node;
    	} else {
            node->prev = tail;
    		tail->next = node;
    		tail = node;
    	}
        size++;
    }

    void list_delete(Node<T> *node) {
        if (node->prev != NULL) {
            node->prev->next = node->next;
            cout << "1" << endl;
        } else {
            head = node->next;
            cout << "2" << endl;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
            cout << "3" << endl;
        }
        size--;
    }

    void print() {
        Node<T> *node = head;
        int count = 0;
        while (count < size) {
            cout << node->key;
            if (count == 0) {
                cout << "(HEAD)";
            }
            if (count == size - 1) {
                cout << "(TAIL)";
            }
            cout << " -> ";
            node = node->next;
            count++;
        }
        cout << "(null)" << endl;
    }
    
};

int main(int argc, char const *argv[]) {
    LinkedList<float> list;
    list.list_insert(5);
    list.list_insert(10);
    list.list_insert(20);
    list.print();
    Node<float> *node = list.list_search(10);
    list.list_delete(node);
    list.print();
    return 0;
}
