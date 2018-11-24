#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "SkipList.h"

using namespace std;

SkipList::SkipList(int max_level) {
    MAX_LEVEL = max_level > 0? max_level : 1;
    head = new SkipListNode;
    tail = new SkipListNode;

    head->next_nodes = new SkipListNode *[MAX_LEVEL];
    for(int i = 0; i < MAX_LEVEL; ++i)
        head->next_nodes[i] = tail;
}

SkipList::~SkipList(void) {
    SkipListNode *curr = nullptr;
    while(head->next_nodes[0] != tail) {
        curr = head->next_nodes[0];
        head->next_nodes[0] = curr->next_nodes[0];
        delete curr->next_nodes;
        delete curr;
    }
    delete head->next_nodes;
    delete head;
    delete tail;
}

int SkipList::RandomLevel(void) {
    int level = 0;
	
    // Geometric distribution satisfying p = 1/2
    while(rand() % 2 && level < MAX_LEVEL - 1)
        ++level;
    return level;
}

void SkipList::insertNode(int key, void *data) {
    SkipListNode *update[MAX_LEVEL]; // Store new node's precursors
    SkipListNode *curr = head;

    // Find new node's precursor in each level.
    for(int i = MAX_LEVEL - 1; i >= 0; --i) {
        if(curr->next_nodes[i] == tail || curr->next_nodes[i]->key > key)
            update[i] = curr;
        else {
            while(curr->next_nodes[i] != tail && curr->next_nodes[i]->key < key)
                curr = curr->next_nodes[i];
            
            // Ensure the key is unique.
            if(curr->next_nodes[i] != tail && curr->next_nodes[i]->key == key) {
                curr->next_nodes[i]->data = data;
                return;
            }
            update[i] = curr;
        }
    }

    // Create the new node to be inserted.
    int level = RandomLevel();
    SkipListNode *temp = new SkipListNode;
    temp->key = key;
    temp->data = data;
    temp->level = level;
    temp->next_nodes = new SkipListNode *[level + 1];

    // Inserted the new node into lists indexing from 0 to level.
    for(int i = 0; i <= level; ++i) {
        temp->next_nodes[i] = update[i]->next_nodes[i];
        update[i]->next_nodes[i] = temp;
    }
}

void SkipList::deleteNode(int key) {
    SkipListNode *update[MAX_LEVEL];
    SkipListNode *curr = head;

    // Find the node's precursors in each level.
    for(int i = MAX_LEVEL - 1; i >= 0; --i) {
        if(curr->next_nodes[i] == tail || curr->next_nodes[i]->key > key)
            update[i] = nullptr;
        else {
            while(curr->next_nodes[i] != tail && curr->next_nodes[i]->key < key)
                curr = curr->next_nodes[i];
            if(curr->next_nodes[i] != tail && curr->next_nodes[i]->key == key)
                update[i] = curr;
            else
                update[i] = nullptr;
        }
    }

    SkipListNode *temp = nullptr;

    // Delete the node from all lists it appears in.
    for(int i = 0; i < MAX_LEVEL; ++i) {
        if(update[i]) {
            temp = update[i]->next_nodes[i];
            update[i]->next_nodes[i] = temp->next_nodes[i];
        }
    }

    // Free the node.
    if(temp) {
        delete temp->next_nodes;
        delete temp;
    }
}

void *SkipList::getData(int key) {
    SkipListNode* curr =  head;
    for(int i = MAX_LEVEL - 1; i >= 0; --i) {
        if(curr->next_nodes[i] == tail || curr->next_nodes[i]->key > key)
            continue;
        else {
            while(curr->next_nodes[i] != tail && curr->next_nodes[i]->key < key)
                curr = curr->next_nodes[i];
            if(curr->next_nodes[i] != tail && curr->next_nodes[i]->key == key)
                return curr->next_nodes[i]->data;
        }
    }
    return nullptr;
}

void SkipList::displayList(void) {
    for(int i = MAX_LEVEL - 1; i >= 0; --i) {
        SkipListNode *curr = head->next_nodes[i];
        SkipListNode *base = head->next_nodes[0];
        cout << "layer " << i << ": ";

        while(base != tail) {
            if(curr == base) {
                cout << setw(4) << curr->key;
                curr = curr->next_nodes[i];
            }
            else
                cout << setw(4) << " ";
            base = base->next_nodes[0];
        }
        cout << endl;
    }
}
