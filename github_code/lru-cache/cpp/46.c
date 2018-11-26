/*

https://leetcode.com/problems/lru-cache/

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) -   Set or insert the value if the key is not already present.
                    When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
*/

#include <iostream>
#include <map>

using namespace std;

class Node{
public:
    int key;
    int value;
    Node* next;
    Node* prev;

    Node( int key, int val ){
        this->next = NULL;
        this->prev = NULL;
        this->value = val;
        this->key = key;
    }
};

class LRUCache{

private:
    int size;
    map<int,Node*> cache;
    Node* head;
    Node* tail;

    void RemoveNodeFromCache(int key){
        if(cache.find(key) == cache.end()){
            return;
        }

        Node* NodeToBeRemoved = cache[key];

        //Remove the key from cache
        cache.erase(key);

        //update tail
        if(tail == NodeToBeRemoved){
            tail = NodeToBeRemoved->prev;
        }

        //udpate neighbors
        if(NodeToBeRemoved->prev != NULL){
            NodeToBeRemoved->prev->next = NodeToBeRemoved->next;
        }

        if(NodeToBeRemoved->next != NULL){
            NodeToBeRemoved->next->prev = NodeToBeRemoved->prev;
        }

        //update head
        if(head == NodeToBeRemoved){
            head = head->next;
        }

        delete(NodeToBeRemoved);
    }

    //Any node added, is always added to the head
    void AddNodeToCache(int key, int value) {
       Node* newNode = new Node(key,value);

       //update cache
       cache[key] = newNode;

       //update tail
       if (tail == NULL) {
          tail = newNode;
       }

       //update the head
       if (head != NULL) {
          head->prev = newNode;
       }
       newNode->next = head;
       head = newNode;

    }

public:
    LRUCache(int capacity) {
        this->size = capacity;
        this->head = NULL;
        this->tail = NULL;
    }

    int get(int key) {
        if(cache.find(key)==cache.end()){
            //key is not present
            return -1;
        }else{
            //key is present
           int val = cache[key]->value;
           RemoveNodeFromCache(key);
           AddNodeToCache(key, val);
           return val;
        }
    }

    void set(int key, int value) {
       if (cache.find(key) != cache.end()) {
          //key present in Cache
          RemoveNodeFromCache(key);
       }
       else {
          //Key not present in Cache
          if (cache.size() == size) {
             //Cache full
             //Remove the last used Node
             RemoveNodeFromCache(tail->key);
          }
       }
       AddNodeToCache(key, value);
    }

    void cachePrint() {
       cout << "====================" << endl;
       cout << "Table Print" << endl;
       map<int, Node*>::iterator it;
       for (it = cache.begin(); it != cache.end(); it++) {
          Node* temp = it->second;
          cout << it->first << " " << temp->value <<endl;
       }


       cout << "linkedlist front" << endl;
       Node* temphead = head;
       while (temphead != NULL) {
          cout << "k=" << temphead->key << " val=" << temphead->value << endl;
          temphead = temphead->next;
       }

       cout << "LinkedList Back" << endl;
       Node* tempTail = tail;
       while (tempTail != NULL) {
          cout << "k=" << tempTail->key << " val=" << tempTail->value << endl;
          tempTail = tempTail->prev;
       }
       cout << "====================" << endl;
    }
};

int main(){
   LRUCache cache(2);

   cout << cache.get(2) <<endl;
   cache.set(2, 6);
   cout << cache.get(1) << endl;
   cache.set(1, 5);
   cache.cachePrint();
   cache.set(1, 2);
   cache.cachePrint();
   cout << cache.get(1) << endl;
   cout << cache.get(2) << endl;

    return 1;
}
