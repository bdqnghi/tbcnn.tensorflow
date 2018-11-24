/**
 * @file skipList_given.cpp
 * Doubly Linked Skip List (lab_gdb2), given functions
 *
 * @author Arman Tajback - Created
 * @author Jordi Paris Ferrer & Arman Tajback - Modified
 * @date (created) Fall 2016
 * @date (modified) Spring 2017
 * @date (modified) Fall 2017
 */

// You shouldn't modify this file

#include "skipList.h"

using namespace std;

/**
 * Constructs an empty list with the specified probability and maxlevel.
 * @param probability The probability of increasing the height of a node
 * @param maxlevel The maximum allowable height of the skiplist
 */
SkipList::SkipList(int probability, int maxlevel) : SkipList()
{
    this->probability = probability;
    this->maxLevel = maxlevel;
}

/**
 * Constructs the SkipList with one initial node, which is constructed with the provided values.
 * Also sets probability and maxlevel of the skiplist
 * 
 * @param key The key to associate with the initial node
 * @param value The pixel to associate with the initial node
 * @param probability The probability of increasing the height of a node
 * @param maxlevel The maximum allowable height of the skiplist

*/

SkipList::SkipList(int key, HSLAPixel value, int probability, int maxlevel) : SkipList(probability, maxlevel)
{
    insert(key, value);
}


/**
 * Constructs the SkipList with one initial node, which is constructed with the provided values.
 * 
 * @param key The key to associate with the initial node
 * @param value The pixel to associate with the initial node
 */
SkipList::SkipList(int key, HSLAPixel value) : SkipList()
{
    insert(key, value);      
}

/**
 * Copy constructs the current SkipList.
 * @param other The SkipList to copy
 * @see copy()
 */
SkipList::SkipList(const SkipList & other)
{
    copy(other);
}

/**
 * The copy() helper method - used in the copy constructor and assignment= operator.
 * @param other The SkipList to copy into ourselves
 */
void SkipList::copy(const SkipList & other)
{
    head = NULL;
    tail = NULL;
    listHeight = 1;
    length = other.length;

    std::map<SkipNode*, SkipNode*> pointerMap;
    pointerMap[NULL] = NULL;

    SkipNode* curr = other.head;

    // populate our map of old pointers to new pointers
    while(curr != NULL)
    {
        SkipNode * currCopy = new SkipNode(*curr);
        pointerMap[curr] = currCopy;

        if(head == NULL)
            head = currCopy;

        if(curr->nodePointers[0].next == NULL)
            tail = currCopy;

        curr = curr->nodePointers[0].next;
    }	

    curr = head;

    // change all old pointers to new pointers
    while(curr != NULL)
    {
        for(auto & p : curr->nodePointers)
        {
            p.next = pointerMap[p.next];
            p.prev = pointerMap[p.prev];
        }

        curr = curr->nodePointers[0].next;
    }

    listHeight = other.listHeight;
}


/**
 * The destructor for SkipList.
 * @see clear()
 */
SkipList::~SkipList() 
{
    clear();   
}

/**
 * Clears up all memory associated with this SkipList
 */
void SkipList::clear()
{
    SkipNode * temp = head;
    SkipNode * prev = head;
    while (temp != NULL)
    {
        prev = temp;
        temp = temp->nodePointers[0].next;
        delete prev;
    }
}

/**
 * Returns the height to use for the next node.
 * Is based on the probability and maxLevels global variables
 * @return The height to use for the next node
 */
int SkipList::levelGenerator()
{
    int retLevel = 1;
    while (((rand() % 100) < probability) && (retLevel < maxLevel))
    {
        retLevel++;
    }
    return retLevel;
}
/**
 * Makes and returns an image showing how degenerate the list is.
 * The less degenerate the faster and more efficient the skip list will be.
 * More black pixels in the image == more degenerate
 * @param imgSize How large to make each side of the image
 * @param fg The color of the foreground, or degenerate pixels in this case
 * @param bg The color of the background, or normal pixels in this case
 * @return A pointer to a PNG representing how degenerate the list is
 */
PNG SkipList::makeImage(int imgSize, HSLAPixel fg, HSLAPixel bg)
{
    int absolutelyNotDegenerate = 0;

    // This value represents how many nodes*height we'd have in a perfect skip list
    absolutelyNotDegenerate = imgSize * imgSize * 2 - 1;

    SkipNode *temp = head->nodePointers[0].next;
    int counter = 0;
    while (temp != tail)
    {
        counter += temp->nodePointers.size();
        temp = temp->nodePointers[0].next;
    }

    counter = abs(absolutelyNotDegenerate - counter);

    PNG colors(imgSize, imgSize);
    vector<pair <int,int> > coordinates;

    for (int i = 0; i < imgSize; i++)
    {
        for (int j = 0; j < imgSize; j++)
        {
            *colors.getPixel(i, j) = bg;
            
            coordinates.push_back(make_pair(i,j));
        }
    }

    random_shuffle(coordinates.begin(), coordinates.end());	
    int x=0,y=0;
   	while (counter != -1)
    {
        if((size_t)counter < coordinates.size())
        {
            x = coordinates[counter].first;
            y = coordinates[counter].second;
            *colors.getPixel(x, y) = fg;
        }       
        counter--;
    }

    return colors;
}


/**
 * A function that prints the keys of the list using only next pointers.
 */
void SkipList::printKeys()
{
    SkipNode * listPrintingTraverser = head->nodePointers[0].next;

    cout << "< " ;

    while (listPrintingTraverser != tail)
    {
        SkipNode * t = listPrintingTraverser->nodePointers[0].next;

        cout << listPrintingTraverser->key << (t == tail ? " " : ", ");

        listPrintingTraverser = listPrintingTraverser->nodePointers[0].next;
    }

    cout << ">" << endl;
}

/**
 * A function that prints the keys in the list using only prev pointers
 */
void SkipList::printKeysReverse()
{
    cout << "< ";
    printKeysReverse(tail->nodePointers[0].prev);
    cout << ">" << endl;
}

/**
 * A helper function for printKeysReverse().
 * @param curr The current node we are printing
 * @see printKeysReverse()
 */
void SkipList::printKeysReverse(SkipNode * curr)
{
    if(curr == head) return;

    // print out the rest of the list
    printKeysReverse(curr->nodePointers[0].prev);

    SkipNode * t = curr->nodePointers[0].next;

    // then print us, so that it looks the same as a normal forward print
    cout << curr->key << (t == tail ? " " : ", ");
}



/**
 * A function that returns the keys of the list in a vector, using only prev pointers.
 * @return a vector containing the keys from head to tail, including the sentinel values
 */
vector<int> SkipList::traverseReverse()
{
    vector<int> ret;

    traverseReverse(tail, ret);

    return ret;
}

/**
 * A helper function for traverseReverse()
 * @param curr The current node
 * @param out The vector we are adding to
 */
void SkipList::traverseReverse(SkipNode * curr, vector<int> & out)
{
    if(curr == NULL) return;

    // add the rest of the list first
    traverseReverse(curr->nodePointers[0].prev, out);

    // add us, so that the order is the same as a normal forwards traversal
    out.push_back(curr->key);
}

/**
 * A function that returns a PNG showing the structure of the current list
 * NOTE: This draws the sentinel nodes as well
 * @param maxHeight the height of the PNG; scales heights into the range [0, maxHeight)
 * @param fg The color to draw the nodes
 * @param bg The color of the background
 * @return a new PNG object representing the current list
 */
PNG SkipList::toPNG(int maxHeight, HSLAPixel fg, HSLAPixel bg) const
{
    PNG ret(length + 2, maxHeight);     // the length doesn't include the sentinels

    SkipNode* curr = head;
    size_t x = 0;

    while (curr)
    {
        int height = (double)curr->nodePointers.size() / maxLevel * maxHeight;

        // fill in our height
        for(int y = 0; y < height; y++)
            *ret.getPixel(x, maxHeight - y - 1) = fg;
        for(int y = height; y < maxHeight; y++)
            *ret.getPixel(x, maxHeight - y - 1) = bg;

        curr = curr->nodePointers[0].next;
        x++;
    }

    return ret;
}


/**
 * A function that will return the index-th SkipPointer from node.
 * Used because STL containers don't play well with gdb
 * @param node The node to consider
 * @param index The level of the node to get a SkipPointer for
 * @return A copy of the SkipPointer in node's index-th level
 */
SkipPointer SkipList::gdbGetPointer(SkipNode * node, size_t index) const
{
    return node->nodePointers[index];
}

/**
 * A function that will print out the current node's next and previous node's keys at each level
 * Used because STL containers don't play well with gdb.
 * Note that this doesn't work well if you are using layour src
 * @param node The node to print out
 */
void SkipList::gdbPrintNode(SkipNode * node) const
{
    cout << gdbGetNode(node) << endl;
}

/**
 * A function that will get the current node's next and previous node's keys at each level
 * Used because STL containers don't play well with gdb.
 * @param node The node to get out
 * @return A string representing the node
 */
string SkipList::gdbGetNode(SkipNode * node) const
{
    // first calculate how wide each number needs to be
    int width = 1;
    for(SkipPointer & p : node->nodePointers)
    {
        if(p.next != NULL && to_string(p.next->key).size() > (size_t)width)
            width = to_string(p.next->key).size();

        if(p.prev != NULL && to_string(p.prev->key).size() > (size_t)width)
            width = to_string(p.prev->key).size();
    }
    if(to_string(node->key).size() > (size_t)width)
        width = to_string(node->key).size();

    string ret;
    char* s = new char[(9 + 22)](); // allocate enough memory for 9 chars + 2 11digit large numbers

    for (int i = node->nodePointers.size() - 1; i >= 0; i--)
    {
        string n = node->nodePointers[i].next ? to_string(node->nodePointers[i].next->key) : "NULL";
        string p = node->nodePointers[i].prev ? to_string(node->nodePointers[i].prev->key) : "NULL";
        sprintf(s, "[ %*s | %*s ]\n", width, p.c_str(), width, n.c_str());   // need that formatting
        ret += string(s);
        sprintf(s, "| %*s | %*s |\n", width, "", width, "");   
        ret += string(s);
    }
    sprintf(s, "| %*s %d %*s |\n", (int)(width-to_string(node->key).size()/2), "", node->key, (int)(width-(to_string(node->key).size()-1)/2), "");
    ret += string(s);

    delete [] s ;

    return ret;
}

