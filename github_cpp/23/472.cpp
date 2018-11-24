/**
 * @file skipList.cpp
 * Doubly Linked Skip List (lab_gdb2), skip list implementation
 *
 * @author Arman Tajback - Created
 * @author Jordi Paris Ferrer & Arman Tajback - Modified
 * @date (created) Fall 2016
 * @date (modified) Spring 2017
 * @date (modified) Fall 2017
 */

#include "skipList.h"


/**
 * Default constructs the SkipList.
 * Uses two sentinel nodes, each initially of height 1
 */
SkipList::SkipList()
{
    head = new SkipNode();
    tail = new SkipNode();

    head->nodePointers[0].next = tail;
    tail->nodePointers[0].prev = head;

    head->key = INT_MIN;
    head->value = HSLAPixel();

    tail->key = INT_MAX;
    tail->value = HSLAPixel();

    listHeight = 1;
    length = 0;

    probability = 50;
    maxLevel = 14;  // log(128 * 128)
}

/**
 * The assignment= operator.
 * @param other The SkipList to copy into ourselves.
 * @return The current object
 * @see copy()
 */
const SkipList& SkipList::operator=(const SkipList & other)
{
    if(this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}



/**
 * Inserts a new node into the sorted order in the list, initialized with the provided values.
 * Will replace the value at key if it already exists
 * @param key The key to associate with the new Node
 * @param value The value to associate with the new Node
 */
void SkipList::insert(int key, HSLAPixel value)
{

    SkipNode *temp = this->find(key);
    if (temp)
    {
        temp->value = value;
	return;
    }   

    length++;

    int newNodeLevel = levelGenerator();

    SkipNode * traverse = head;

    int level=head->nodePointers.size()-1;

    // Set up traverse to point to the node right before where we want to insert
    while (traverse->nodePointers[0].next != tail && (level >= 0))
    {
        int nextKey = traverse->nodePointers[level].next->key;

        if (key < nextKey)
        {
            level--;
            if(level < 0 )
                break;
        }
        else 
        {
            traverse = traverse->nodePointers[level].next;
            level = traverse->nodePointers.size()-1;
        }

    }

    // expand head and tail to encompass the new height of the list, if needed
    for(int i = listHeight; i < max(this->listHeight, newNodeLevel); i++)
    {
        head->nodePointers.push_back(SkipPointer());
        tail->nodePointers.push_back(SkipPointer());
    }
     
    this->listHeight = max(this->listHeight, newNodeLevel);

    SkipNode * prev = traverse;
    SkipNode * forward = traverse->nodePointers[0].next;
    SkipNode * newNode = new SkipNode(key, value, newNodeLevel);

    int forwardLevel = 0;
    int backwardLevel = 0;


    int maxLevel = min(newNodeLevel, this->listHeight);

    while (forwardLevel < maxLevel)
    {
        if(forward == tail)
        {
            forward->nodePointers[forwardLevel].prev = newNode;
            newNode->nodePointers[forwardLevel].next = forward;
            forwardLevel++;

        }
	else if(forward->nodePointers.size() > (size_t)forwardLevel)
        {
            forward->nodePointers[forwardLevel].prev = newNode;
            newNode->nodePointers[forwardLevel].next = forward;
            forwardLevel++;
        }
        else
        {
            forward = forward->nodePointers[0].next;
        }
    }

    while (backwardLevel < maxLevel)
    {
        if(prev == head)
        {
            prev->nodePointers[backwardLevel].next = newNode;
            newNode->nodePointers[backwardLevel].prev = prev;
            backwardLevel++;
        }

	else if(prev->nodePointers.size() > (size_t)backwardLevel)
        {
            prev->nodePointers[backwardLevel].next = newNode;
            newNode->nodePointers[backwardLevel].prev = prev;
            backwardLevel++;
        }
        else
        {
            prev = prev->nodePointers[0].prev;
        }
    }


}
/**
 * A function that searches for the given key and returns the associated HSLAPixel
 * Returns (0, 0, 0, 50) if it's not found
 * @param key The key to search for
 * @return The pixel with the specified key, or (0, 0, 0, 50) if not found
 */
HSLAPixel SkipList::search(int key)
{
    SkipNode * retval;

    retval = find(key);

    if (retval != NULL) 
        return retval->value;

    return HSLAPixel(0,0,0, 50);
}

/**
 * Finds the given key in the list if it exists, and returns a pointer to the node containing it.
 * Randomly calls findR or findI
 * @param key The key to search for in the list
 * @return A pointer to the node containing key, or NULL if not found in the list
 */
SkipNode * SkipList::find(int key)
{
    SkipNode * retval;
    if ((rand() % 2) ==0)
        retval=findR(key);
    else 
        retval=findI(key);

    return retval;
}


/**
 * Finds the given key in the list if it exists, and returns a pointer to the node containing it.
 * @param key The key to search for in the list
 * @return A pointer to the node containing key, or NULL if not found in the list
 */
SkipNode * SkipList::findR(int key)
{
    return findRHelper(key, head->nodePointers.size()-1, head);
}

/**
 * Helper function for findR.
 * @param key The key to search for
 * @param level The level we're searching through
 * @param curr The current node we're searching through
 * @return A pointer to the node with the given key, or NULL if it could not be found
 */
SkipNode * SkipList::findRHelper(int key, int level, SkipNode * curr)
{

    if (curr == tail || level < 0)
        return NULL;

    int nextKey =  curr->nodePointers[level].next->key;
    SkipNode* ret;

    if (nextKey == key)
        return curr->nodePointers[level].next;

    else if (nextKey > key) 
        return findRHelper(key, level-1, curr);

    else
        return findRHelper(key, level, curr->nodePointers[level].next);    


    return NULL;
}

/**
 * An iterative find function
 * @param key The key to search for
 * @return A pointer to the node with the given key, or NULL if it could not be found
 */
SkipNode * SkipList::findI(int key)
{

    SkipNode * traverse = head;
    SkipNode * retNode=NULL;

    int level = head->nodePointers.size()-1;

    while (traverse->nodePointers[0].next != tail && level >= 0)
    {
        int nextKey = traverse->nodePointers[level].next->key;

        if (nextKey == key)
        {
            return traverse->nodePointers[level].next;
        }
        else if (key < nextKey)
        {
            level--;
        }
        else {
            traverse=traverse->nodePointers[level].next;
            //level=traverse->nodePointers.size()-1; // slightly slows down code in our sorted inserts
        }

    }
    return NULL;
}



/**
 * Removes the node with the given key from the list.
 * @param key The key to search for and remove from the list
 * @return A boolean indicating whether a node was successfully removed from the list
 */
bool SkipList::remove(int key)
{
    // don't allow the removal of sentinel nodes
    if(key == INT_MAX || key == INT_MIN)
        return false;


    SkipNode * node = find(key);
    bool ret = true;

    // can't remove a node that doesn't exist
    if(node == NULL)
        return false;

    length--;

    // pass through all the pointers on either side of us
    for(size_t i = 0; i < node->nodePointers.size(); i++)
    {
        SkipNode * next = node->nodePointers[i].next;
        SkipNode * prev = node->nodePointers[i].prev;

        prev->nodePointers[i].next = next;
        next->nodePointers[i].prev = prev;
    }

    delete node;

    return true;
}



/**
 * A function that returns the keys of the list in a vector, using only next pointers.
 * @return a vector containing the keys from head to tail, including the sentinel values
 */
vector<int> SkipList::traverse()
{
    SkipNode * listPrintingTraverser = head;

    vector<int> ret;

    while (listPrintingTraverser != NULL)
    {
        ret.push_back(listPrintingTraverser->key);

        listPrintingTraverser = listPrintingTraverser->nodePointers[0].next;
    }

    return ret;
}
