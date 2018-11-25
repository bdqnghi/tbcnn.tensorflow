

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

        
        cache.erase(key);

        
        if(tail == NodeToBeRemoved){
            tail = NodeToBeRemoved->prev;
        }

        
        if(NodeToBeRemoved->prev != NULL){
            NodeToBeRemoved->prev->next = NodeToBeRemoved->next;
        }

        if(NodeToBeRemoved->next != NULL){
            NodeToBeRemoved->next->prev = NodeToBeRemoved->prev;
        }

        
        if(head == NodeToBeRemoved){
            head = head->next;
        }

        delete(NodeToBeRemoved);
    }

    
    void AddNodeToCache(int key, int value) {
       Node* newNode = new Node(key,value);

       
       cache[key] = newNode;

       
       if (tail == NULL) {
          tail = newNode;
       }

       
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
            
            return -1;
        }else{
            
           int val = cache[key]->value;
           RemoveNodeFromCache(key);
           AddNodeToCache(key, val);
           return val;
        }
    }

    void set(int key, int value) {
       if (cache.find(key) != cache.end()) {
          
          RemoveNodeFromCache(key);
       }
       else {
          
          if (cache.size() == size) {
             
             
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
