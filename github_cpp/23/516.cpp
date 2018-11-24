// Struct Skip_node member implementations
// constructor 
#include <iostream>
#include <limits>
#include "skipList.h"

Skip_Node::Skip_Node (int k, const std::string& v, int level)
    :  key(k), value(v)
{
    for (int i = 0; i < level; ++i) forward.emplace_back(nullptr);
} 

//==============================================================================
// Class Skip_list member implementations
// constructor
Skip_list::Skip_list()
    : probability(0.5), maxLevel(16)
{
     // Initialize the head of the skip list

     // smallest possible key
     int headKey = std::numeric_limits<int>::min();
     head = new Skip_Node(headKey, "head", maxLevel);

     // Initialize the last element of the list

     // largest possible key
     int nilKey = std::numeric_limits<int>::max();
     NIL = new Skip_Node(nilKey, "NIL", maxLevel);

     // Connect start to end
     // connect all the levels/forward pointers of the header to NIL
     for (size_t i = 0; i < head->forward.size(); ++i) {
         head->forward[i] = NIL;
     }
}

// destructor
Skip_list::~Skip_list () {
    delete head;
    delete NIL;
}

// Helper functions
/*
    Function: randomLevel()
    Use: implicit in class Skip_list
    It generates node levels in the range
    [1, maxLevel). 

    It uses rand() scaled by its maximum 
    value: RAND_MAX, so that the randomly 
    generated numbers are within [0,1).
*/
int Skip_list::randomLevel () {
    int v = 1;

    while ((((double)std::rand() / RAND_MAX)) < probability && 
           std::abs(v) < maxLevel) {

        v += 1;
    }
    return abs(v);
}

/*
    Function: nodeLevel()
    Use: Implicitly in most of the member functions.

    It returns the number of non-null pointers
    corresponding to the level of the current node.
    (the node that contains the checked vector of 
    forward pointers)

    If list empty returns 1.
*/
int Skip_list::nodeLevel (const std::vector<Skip_Node*>& v) {
    int currentLevel = 1;
    // last element's key is the largest
    int nilKey = std::numeric_limits<int>::max();

    if (v[0]->key == nilKey) {
        return currentLevel;
    }

    for (size_t i = 0; i < v.size(); ++i) {

        if (v[i] != nullptr && v[i]->key != nilKey) {
            ++currentLevel;
        } else { 
            break;
        }
    }
    return currentLevel;
}

// Non-modifying member functions
/*
    Function: print()
    Use: skip_list_obj.print();

    It prints the key, value, level
    of each node of the skip list.

    Prints two nodes per line.
*/
void Skip_list::print () {
    Skip_Node* list = head;
    int lineLenght = 1;

    std::cout <<"{";

    while (list->forward[0] != nullptr) {
        std::cout <<"value: "<< list->forward[0]->value
                  <<", key: "<< list->forward[0]->key
                  <<", level: "<< nodeLevel(list->forward); 

        list = list->forward[0];

        if (list->forward[0] != nullptr) std::cout <<" : ";

        if (++lineLenght % 2 == 0) std::cout <<"\n";
    }
    std::cout <<"}\n";
}

/*
    Function: find()
    Use: Skip_Node* found = skip_list_obj.find(searchKey);

    It searches the skip list and
    returns the element corresponding 
    to the searchKey; otherwise it returns
    failure, in the form of null pointer.
*/
Skip_Node* Skip_list::find(int searchKey) {
    Skip_Node* x = head;
    unsigned int currentMaximum = nodeLevel(head->forward);

    for (unsigned int i = currentMaximum; i-- > 0;) {
        while (x->forward[i] != nullptr && x->forward[i]->key < searchKey) {
            x = x->forward[i];
        }   
    }
    x = x->forward[0];

    if (x->key == searchKey) {
        return x;
    } else {
        return nullptr;
    }
} 

// Modifying member functions
/*
    Function: makeNode ()
    Use: Implicitly in member function insert().

    It wraps the Skip_Node constructor which creates
    a node on the heap and returns a pointer to it. 
*/
Skip_Node* Skip_list::makeNode (int key, std::string val, int level) {
    return new Skip_Node(key, val, level);
}

/*
    Function: insert();
    Use: void insert(searchKey, newValue);

    It searches the skip list for elements
    with seachKey, if there is an element
    with that key its value is reassigned to the 
    newValue, otherwise it creates and splices
    a new node, of random level.
*/
void Skip_list::insert(int searchKey, std::string newValue) {
    // reassign if node exists 
    Skip_Node* x = nullptr;
    x = find(searchKey);
    if (x) {
        x->value = newValue;
        return;
    }

    // vector of pointers that needs to be updated to account for the new node
    std::vector<Skip_Node*> update(head->forward);
    unsigned int currentMaximum = nodeLevel(head->forward);
    x = head;

    // search the list 
    for (unsigned int i = currentMaximum; i-- > 0;) {

        while (x->forward[i] != nullptr && x->forward[i]->key < searchKey) {

            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];

    // create new node
    int newNodeLevel = 1;
    if (x->key != searchKey) {

        newNodeLevel = randomLevel();
        int currentLevel = nodeLevel(update);

        if (newNodeLevel > currentLevel) {

            for (int i = currentLevel + 1; i < newNodeLevel; ++i) {

                update[i] = head;
            }   
        }
        x = makeNode(searchKey, newValue, newNodeLevel);
    }

    // connect pointers of predecessors and new node to successors
    for (int i = 0; i < newNodeLevel; ++i) {

        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x;
    }
}

/*
    Function: delete_node()
    Use: skip_list_obj.erase(searchKey)

    It deletes the element containing 
   searchKey, if it exists.
*/
void Skip_list::erase (int searchKey) {
    // vector of pointers that needs to be updated to account for the deleted node
    std::vector<Skip_Node*> update(head->forward);
    Skip_Node* x = head;
    unsigned int currentMaximum = nodeLevel(head->forward);

    // search and update pointers
    for (unsigned int i = currentMaximum; i-- > 0;) {

        while (x->forward[i] != nullptr && x->forward[i]->key < searchKey) {

            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];

    // update pointers and delete node 
    if (x->key == searchKey) {
        for (size_t i = 0; i < update.size(); ++i) {

            if (update[i]->forward[i] != x) {

                break;
            }
            update[i]->forward[i] = x->forward[i];
        }
        delete x;        
    }    
}