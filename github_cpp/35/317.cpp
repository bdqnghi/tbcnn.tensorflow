/**
 * @author Nhat M. Nguyen
 * @update 03-08-18
**/


/*
 * This is the updated version of linked-list
 */


#include <cassert>
#include <cstdio>


template <typename T>
struct LinkedListNode {
    T key;
    LinkedListNode* next;

    LinkedListNode(T key) {
        this->key = key;
        this->next = NULL;
    }
};


template <typename T>
struct LinkedList {
    int size;
    LinkedListNode<T>* head;

    LinkedList() {
        this->head = NULL;
        this->size = 0;
    }

    void pushBack(T key) {
        if (this->head == NULL) {
            this->head = new LinkedListNode<T>(key);
        }
        else {
            LinkedListNode<T>* node = this->head;
            while (node->next != NULL) {
                node = node->next;
            }
            node->next = new LinkedListNode<T>(key);
        }
        this->size++;
    }

    void pushFront(T key) {
        if (this->head == NULL) {
            this->head = new LinkedListNode<T>(key);
        }
        else {
            LinkedListNode<T>* old_head = this->head;
            this->head = new LinkedListNode<T>(key);
            this->head->next = old_head;
        }
        this->size++;
    }

    void popBack() {
        assert(this->head != NULL);
        LinkedListNode<T>* prev_node = NULL;
        LinkedListNode<T>* curr_node = this->head;
        while (curr_node->next != NULL) {
            prev_node = curr_node;
            curr_node = curr_node->next;
        }
        delete curr_node;
        prev_node->next = NULL;
        this->size--;
    }

    void popFront() {
        assert(this->head != NULL);
        LinkedListNode<T>* old_head = this->head;
        this->head = this->head->next;
        delete old_head;
        this->size--;
    }

    LinkedListNode<T>* search(T key) {
        LinkedListNode<T>* node = this->head;
        while (node != NULL && node->key != key) {
            node = node->next;
        }
        return node;
    }

    void remove(LinkedListNode<T>* removed_node) {
        assert(this->head != NULL);
        if (removed_node == this->head) {
            delete this->head;
            this->head = NULL;
            this->size--;
            return;
        }

        LinkedListNode<T>* prev_node = NULL;
        LinkedListNode<T>* curr_node = this->head;
        while (curr_node != removed_node) {
            prev_node = curr_node;
            curr_node = curr_node->next;
        }
        prev_node->next = curr_node->next;
        delete curr_node;
        this->size--;
    }

    T& operator [] (int index) {
        assert(index < this->size);
        LinkedListNode<T>* node = this->head;
        for (int i = 1; i < index; i++) {
            node = node->next;
        }
        return node->key;
    }

    void easyPrint() {
        LinkedListNode<T>* node = this->head;

        while (node != NULL) {
            cout << node << ' ';
            node = node->next;
        }
        cout << '\n';
    }

    void hardPrint() {
        if (this->head == NULL) {
            printf("[]\n");
            return;
        }

        printf("[");
        LinkedListNode<T>* node = this->head;
        while (node->next != NULL) {
            printf("%d, ", node->key);
            node = node->next;
        }
        printf("%d]\n", node->key);
    }

    ~LinkedList() {
        LinkedListNode<T>* curr_node = this->head;
        LinkedListNode<T>* next_node = NULL;
        while (curr_node != NULL) {
            next_node = curr_node->next;
            delete curr_node;
            curr_node = next_node;
        }
    }
};


int main() {
    LinkedList<int> linked_list;
    int a[] = {0, 1, 2, 3, 4, 5};
    int n = 6;

    for (int i = 0; i < n; i++) {
        linked_list.pushBack(a[i]);
    }

    linked_list.hardPrint();

    LinkedListNode<int>* node = linked_list.search(4);
    linked_list.remove(node);

    printf("%d\n", node->key);

    linked_list.hardPrint();

    return 0;
}
