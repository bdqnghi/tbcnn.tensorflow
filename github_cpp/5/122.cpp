
 /****************************************************************************
 * File: AVLTree.hh
 * Author: Keith Schwarz (htiek@cs.stanford.edu)
 *
 * An implementation of a sorted dictionary backed by an AVL tree.  AVL trees
 * are a type of self-balancing binary tree and were the first such structure
 * to be described that guaranteed that the tree height was no greater than
 * O(lg n).
 *
 * The idea behind the AVL tree is to ensure that for every node in the tree,
 * the height of the node's left and right subtrees differ by at most one.  To
 * see that this ensures that the tree remains balanced, we can show that the
 * minimum number of nodes n required to create a tree of height h is governed
 * by the relationship n = O(lg h).  Once we have this, we know that any AVL
 * tree containing n nodes must have height no greater than O(lg n), and all
 * the standard BST operations on such a tree will complete in time O(lg n).
 * We can show this inductively.  Let N(h) be the minimum number of nodes that
 * could be present in a tree of height h.  Clearly, N(0) = 0, since the empty
 * tree can't have any nodes in it.  We also have that N(1) = 1, since a tree
 * of height one must have at least one node.  Now, let's suppose that we are
 * considering a tree of height h + 2.  This means that the root of the tree
 * must have some subtree that has height h + 1.  Because we enforce the
 * invariant that the heights of the subtrees of each node differ by at most
 * one, this means that the minimum height of the other subtree of the root is
 * h.  This gives us that the minimum number of nodes in the tree is
 * N(h + 2) = N(h) + N(h + 1) + 1, with the +1 coming from the root element.
 * We claim that N(h) = F(h + 2) - 1, where F(h) is the hth Fibonacci 
 * number.  This proof is by induction:
 *
 *   Base cases: N(0) = 0 = 1 - 1 = F(2) - 1
 *               N(1) = 1 = 2 - 1 = F(3) - 1
 *   Inductive step: N(h + 2)  = N(h) + N(h + 1) + 1
 *                             = F(h + 2) - 1 + F(h + 3) - 1 + 1
 *                             = F(h + 2) + F(h + 3) - 1
 *                             = F(h + 4) - 1
 *                             = F((h + 2) + 2) - 1
 *
 * It's well-known that F(h) = (1 / sqrt(5)) (P^h - p^h), where
 *
 *                             P = (1 + sqrt(5)) / 2 ~= 1.6
 *                             p = (1 - sqrt(5)) / 2 ~= 0.6
 *
 * For h > 1, F(h) >= (P^h / sqrt(5)) - 1, and so we have that
 *
 *                       N(h)      >= P^h / sqrt(5) - 1
 *                       N(h) + 1  >= P^h / sqrt(5)
 *              sqrt(5) (N(h) + 1) >= P^h
 *        lg_P(sqrt(5) (N(h) + 1)) >= h
 *
 * And so we have that h = O(lg N(h)); that is, the height of the tree is
 * O(lg n) as required.
 *
 * Given that a tree with this structure will have O(lg n) height, the
 * question now is how we can maintain this property in the tree as we begin
 * adding and removing nodes.  To do this, we'll have each node keep track of
 * its height in the tree.  Whenever we insert a node, we can propagate the
 * new height information from the newly-inserted node up to the root.  If in
 * the course of doing so we detect that a node has two subtrees whose heights
 * differ by more than 1, we can use a series of tree rotations to fix up the
 * balancing.  In particular, there are two cases to consider, plus two
 * symmetric cases:
 *
 * Case 1: We have two nodes in this configuration:
 *
 *                                  a (+2)
 *                                 / \
 *                     (+0 or +1) b   Z
 *                               / \
 *                              X   Y
 *
 *                           
 *
 * Here, the values in parentheses are the "balance term" for each node, which
 * is defined as the difference between the height of its left and right
 * subtrees.  If we are in this case, then suppose that subtree Z has height
 * h.  Since a has a balance factor of +2, this means that the height of b
 * must be h + 2, so at least one of X or Y has height h + 1, and since the
 * balance term of b is not -1, either X and Y both have height h + 1, or X
 * has height h + 1 and Y has height h.  To fix up the balance terms here, we
 * rotate along the edge from a to b to give this setup:
 *
 *                               b (+0 or -1)
 *                              / \
 *                             X   a  (+0 or +1)
 *                                / \
 *                               Y   Z
 *
 * The values of these balance terms can be seen quite easily.  We know that 
 * Z has height h, and Y either has height h + 1 or h.  This means that node
 * a is either at height h + 1 or h + 2, and its balance term is either +0 or
 * +1.  Tree X has height h + 1 as well, and so the balance term of b is
 * either +0 or -1.  Notice that when we started the root of this tree was at
 * height h + 3, and after this operation the height is still h + 3, and so
 * none of the node heights above this tree are affected.
 *
 * Case 2: We have three nodes in this configuration:
 *
 *                                  a (+2)
 *                                 / \
 *                           (-1) b   Z
 *                               / \
 *                              W   c (?)
 *                                 / \
 *                                X   Y
 *
 * Because the balance terms are the way they are, we know that if tree Z has
 * height h, tree b has height h + 2.  Moreover, since the balance term on the
 * node is -1, we know that tree W has height h and the tree rooted at c has
 * height h + 1.  Consequently, at least one of X and Y have height h, and at
 * most one of them has height h - 1.   In this case, we do two rotations.  
 * First, we rotate c and b to get
 *
 *                               (+2) a
 *                                   / \
 *                       (+1 or +2) c   Z
 *                                 / \
 *                     (+0 or +1) b   Y
 *                               / \
 *                              W   X
 *
 * The balance terms here are as follows.  Since W has height h and X has
 * height either h or h - 1, the balance term on b is either 0 or 1, and the
 * height of the tree rooted at b is h + 1.  Y has height either h or h - 1,
 * and so the balance term on c is either +1 or +2, and it has height h + 2.
 * Finally, the height of Z is defined as h, and so a has balance term +2.  To
 * fix up all of these imbalances, we do one more rotation to pull c above a:
 *
 *                             (+0) c
 *                                /   \
 *                    (+0 or +1) b     a (+0 or -1)
 *                              / \   / \
 *                             W   X Y   Z
 *
 * The term on b is unchanged from the previous step and it is still at height
 * h + 1.  Since Z has height h and Y has height either h - 1 or h, a has
 * balance either +0 or -1, and is at height h + 1.  This means that node c
 * is at height h + 2 and has balance term 0.  However, notice that the height
 * of the root of this tree is now h + 2 instead of h + 3, meaning that the
 * balance terms of nodes above this one may need to be updated in response.
 *
 * The logic for removing a node from an AVL tree is similar.  We use standard
 * techniques to remove the node in question from the BST, then run a fixup
 * step like this one to fix all the imbalances in the tree.  This is tricky,
 * and the approach I've opted
 * to use is based on the discussion from the libavl discussion at
 * http://www.stanford.edu/~blp/avl/libavl.html/Deleting-from-a-BST.html.
 * However, I've opted to ignore their Case 2/Case 3 distinction, since I
 * don't see it as necessary.
 *
 * Case 1: If the node has no left child or no right child, we can just
 *         replace it with the child it does have (if any).
 *
 *                          a                a
 *                         / \              / \
 *                        Z   x     ->     Z   Y
 *                             \
 *                              Y
 *
 *         In this case, we need to begin a fixup pass from a, since the
 *         balance factors may have changed.
 *
 * Case 2: If the node has both children and its left child has a right child,
 *         then replace the node with its successor.  This works by
 *         identifying the node's successor in its left subtree, which is the
 *         leftmost node of the tree.  If it's not a leaf, then it's a node 
 *         missing a left child and we can easily delete it using the logic 
 *         in Case 1.  This raises the successor's subtree (if any) by one
 *         level in the tree.
 *
 * In both cases, there is some point in the tree in which some subtree's
 * height decreases by one, and we need to do apply the rebalance step to fix
 * it up.
 */
#ifndef AVLTree_Included
#define AVLTree_Included

#include <algorithm>   // For lexicographical_compare, equal, max
#include <functional>  // For less
#include <utility>     // For pair
#include <iterator>    // For iterator, reverse_iterator
#include <stdexcept>   // For out_of_range
#include <cassert>

/**
 * A map-like class backed by a AVL tree.
 */
template <typename Key, typename Value, typename Comparator = std::less<Key> >
class AVLTree {
public:
  /**
   * Constructor: AVLTree(Comparator comp = Comparator());
   * Usage: AVLTree<string, int> myAVLTree;
   * Usage: AVLTree<string, int> myAVLTree(MyComparisonFunction);
   * -------------------------------------------------------------------------
   * Constructs a new, empty AVL tree that uses the indicated comparator to
   * compare keys.
   */
  AVLTree(Comparator comp = Comparator());

  /**
   * Destructor: ~AVLTree();
   * Usage: (implicit)
   * -------------------------------------------------------------------------
   * Destroys the AVL tree, deallocating all memory allocated internally.
   */
  ~AVLTree();

  /**
   * Copy functions: AVLTree(const AVLTree& other);
   *                 AVLTree& operator= (const AVLTree& other);
   * Usage: AVLTree<string, int> one = two;
   *        one = two;
   * -------------------------------------------------------------------------
   * Makes this AVL tree equal to a deep-copy of some other AVL tree.
   */
  AVLTree(const AVLTree& other);
  AVLTree& operator= (const AVLTree& other);

  /**
   * Type: iterator
   * Type: const_iterator
   * -------------------------------------------------------------------------
   * A pair of types that can traverse the elements of an AVL tree in 
   * ascending order.
   */
  class iterator;
  class const_iterator;

  /**
   * Type: reverse_iterator
   * Type: const_reverse_iterator
   * -------------------------------------------------------------------------
   * A pair of types that can traverse the elements of an AVL tree in 
   * descending order.
   */
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  /**
   * std::pair<iterator, bool> insert(const Key& key, const Value& value);
   * Usage: myAVLTree.insert("Skiplist", 137);
   * -------------------------------------------------------------------------
   * Inserts the specified key/value pair into the AVL tree.  If an entry with
   * the specified key already existed, this function returns false paired
   * with an iterator to the extant value.  If the entry was inserted
   * successfully, returns true paired with an iterator to the new element.
   */
  std::pair<iterator, bool> insert(const Key& key, const Value& value);

  /**
   * bool erase(const Key& key);
   * Usage: myAVLTree.erase("AVL Tree");
   * -------------------------------------------------------------------------
   * Removes the entry from the AVL tree with the specified key, if it exists.
   * Returns whether or not an element was erased.  All outstanding iterators
   * remain valid, except for those referencing the deleted element.
   */
  bool erase(const Key& key);

  /**
   * iterator erase(iterator where);
   * Usage: myAVLTree.erase(myAVLTree.begin());
   * -------------------------------------------------------------------------
   * Removes the entry referenced by the specified iterator from the tree,
   * returning an iterator to the next element in the sequence.
   */
  iterator erase(iterator where);

  /**
   * iterator find(const Key& key);
   * const_iterator find(const Key& key);
   * Usage: if (myAVLTree.find("Skiplist") != myAVLTree.end()) { ... }
   * -------------------------------------------------------------------------
   * Returns an iterator to the entry in the AVL tree with the specified key,
   * or end() as as sentinel if it does not exist.
   */
  iterator find(const Key& key);
  const_iterator find(const Key& key) const;

  /**
   * Value& operator[] (const Key& key);
   * Usage: myAVLTree["skiplist"] = 137;
   * -------------------------------------------------------------------------
   * Returns a reference to the value associated with the specified key in the
   * AVL tree.  If the key is not contained in the AVL tree, it will be 
   * inserted into the AVL tree with a default-constructed Entry as its value.
   */
  Value& operator[] (const Key& key);

  /**
   * Value& at(const Key& key);
   * const Value& at(const Key& key) const;
   * Usage: myAVLTree.at("skiplist") = 137;
   * -------------------------------------------------------------------------
   * Returns a reference to the value associated with the specified key,
   * throwing a std::out_of_range exception if the key does not exist in the
   * AVL tree.
   */
  Value& at(const Key& key);
  const Value& at(const Key& key) const;

  /**
   * (const_)iterator begin() (const);
   * (const_)iterator end() (const);
   * Usage: for (AVLTree<string, int>::iterator itr = t.begin(); 
   *             itr != t.end(); ++itr) { ... }
   * -------------------------------------------------------------------------
   * Returns iterators delineating the full contents of the AVL tree.  Each
   * iterator acts as a pointer to a std::pair<const Key, Entry>.
   */
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  /**
   * (const_)reverse_iterator rbegin() (const);
   * (const_)reverse_iterator rend() (const);
   * Usage: for (AVLTree<string, int>::reverse_iterator itr = s.rbegin(); 
   *             itr != s.rend(); ++itr) { ... }
   * -------------------------------------------------------------------------
   * Returns iterators delineating the full contents of the AVL tree in 
   * reverse order.
   */
  reverse_iterator rbegin();
  reverse_iterator rend();
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

  /**
   * (const_)iterator lower_bound(const Key& key) (const);
   * (const_)iterator upper_bound(const Key& key) (const);
   * Usage: for (AVLTree<string, int>::iterator itr = t.lower_bound("AVL");
   *             itr != t.upper_bound("skiplist"); ++itr) { ... }
   * -------------------------------------------------------------------------
   * lower_bound returns an iterator to the first element in the AVL tree 
   * whose key is at least as large as key.  upper_bound returns an iterator 
   * to the first element in the AVL tree whose key is strictly greater than 
   * key.
   */
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  const_iterator lower_bound(const Key& key) const;
  const_iterator upper_bound(const Key& key) const;

  /**
   * std::pair<(const_)iterator, (const_)iterator> 
   *    equal_range(const Key& key) (const);
   * Usage: std::pair<AVLTree<int, int>::iterator, AVLTree<int, int>::iterator>
   *          range = t.equal_range("AVL");
   * -------------------------------------------------------------------------
   * Returns a range of iterators spanning the unique copy of the entry whose
   * key is key if it exists, and otherwise a pair of iterators both pointing
   * to the spot in the AVL tree where the element would be if it were.
   */
  std::pair<iterator, iterator> equal_range(const Key& key);
  std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;

  /**
   * size_t size() const;
   * Usage: cout << "AVLTree contains " << s.size() << " entries." << endl;
   * -------------------------------------------------------------------------
   * Returns the number of elements stored in the AVL tree.
   */
  size_t size() const;

  /**
   * bool empty() const;
   * Usage: if (s.empty()) { ... }
   * -------------------------------------------------------------------------
   * Returns whether the AVL tree contains no elements.
   */
  bool empty() const;

  /**
   * void swap(AVLTree& other);
   * Usage: one.swap(two);
   * -------------------------------------------------------------------------
   * Exchanges the contents of this AVL tree and some other AVL tree.  All
   * outstanding iterators are invalidated.
   */
  void swap(AVLTree& other);

private:
  /* A type representing a node in the AVL tree. */
  struct Node {
    std::pair<const Key, Value> mValue; // The actual value stored here

    /* The children are stored in an array to make it easier to implement tree
     * rotations.  The first entry is the left child, the second the right.
     */
    Node* mChildren[2];

    /* Pointer to the parent node. */
    Node* mParent;

    /* Pointer to the next and previous node in the sorted sequence. */
    Node* mNext, *mPrev;

    /* The height of this node, which is stored as an integer to make
     * subtraction easier.
     */
    int mHeight;

    /* Constructor sets up the value to the specified key/value pair with the
     * specified height.
     */
    Node(const Key& key, const Value& value, int height);
  };

  /* A pointer to the first and last elements of the AVL tree. */
  Node* mHead, *mTail;

  /* A pointer to the root of the tree. */
  Node* mRoot;
  
  /* The comparator to use when storing elements. */
  Comparator mComp;

  /* The number of elements in the list. */
  size_t mSize;

  /* A utility base class for iterator and const_iterator which actually
   * supplies all of the logic necessary for the two to work together.  The
   * parameters are the derived type, the type of a pointer being visited, and
   * the type of a reference being visited.  This uses the Curiously-Recurring
   * Template Pattern to work correctly.
   */
  template <typename DerivedType, typename Pointer, typename Reference>
  class IteratorBase;
  template <typename DerivedType, typename Pointer, typename Reference>
  friend class IteratorBase;

  /* Make iterator and const_iterator friends as well so they can use the
   * Node type.
   */
  friend class iterator;
  friend class const_iterator;

  /* A utility function to perform a tree rotation to pull the child above its
   * parent.  This function is semantically const but not bitwise const, since
   * it changes the structure but not the content of the elements being
   * stored.
   */
  void rotateUp(Node* child);

  /* A utility function that, given a node, returns the height of that node.
   * If the node is NULL, 0 is returned.
   */
  static int height(const Node* node);

  /* A utility function that, given a node, returns its balance factor. */
  static int balanceFactor(const Node* node);

  /* A utility function which does a BST search on the tree, looking for the
   * indicated node.  The return result is a pair of pointers, the first of
   * which is the node being searched for, or NULL if that node is not found.
   * The second node is that node's parent, which is either the parent of the
   * found node, or the last node visited in the tree before NULL was found
   * if the node was not found.
   */
  std::pair<Node*, Node*> findNode(const Key& key) const;

  /* A utility function which walks up from the indicated node up to the root,
   * performing the tree rotations necessary to restore the balances in the
   * tree.
   */
  void rebalanceFrom(Node* where);

  /* A utility function which, given a node with at most one child, splices
   * that node out of the tree by replacing it with its one child.  The next
   * and previous pointers of that node are not modified, since this function
   * can be used to structurally remove nodes from the tree while remembering
   * where they are in sorted order.
   */
  void spliceOut(Node* where);

  /* A utility function which, given a node and the node to use as its parent,
   * recursively deep-copies the tree rooted at that node, using the parent
   * node as the new tree's parent.
   */
  static Node* cloneTree(Node* toClone, Node* parent);

  /* A utility function which, given a tree and a pointer to the predecessor
   * of that tree, rewires the linked list in that tree to represent an
   * inorder traversal.  No fields are modified.  The return value is the node
   * with the highest key.
   */
  static Node* rethreadLinkedList(Node* root, Node* predecessor);
};

/* Comparison operators for AVLTrees. */
template <typename Key, typename Value, typename Comparator>
bool operator<  (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs);
template <typename Key, typename Value, typename Comparator>
bool operator<= (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs);
template <typename Key, typename Value, typename Comparator>
bool operator== (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs);
template <typename Key, typename Value, typename Comparator>
bool operator!= (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs);
template <typename Key, typename Value, typename Comparator>
bool operator>= (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs);
template <typename Key, typename Value, typename Comparator>
bool operator>  (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs);

/* * * * * Implementation Below This Point * * * * */

/* Definition of the IteratorBase type, which is used to provide a common
 * implementation for iterator and const_iterator.
 */
template <typename Key, typename Value, typename Comparator>
template <typename DerivedType, typename Pointer, typename Reference>
class AVLTree<Key, Value, Comparator>::IteratorBase {
public:
  /* Utility typedef to talk about nodes. */
  typedef typename AVLTree<Key, Value, Comparator>::Node Node;

  /* Advance operators just construct derived type instances of the proper
   * type, then advance them.
   */
  DerivedType& operator++ () {
    mCurr = mCurr->mNext;

    /* Downcast to our actual type. */
    return static_cast<DerivedType&>(*this);
  }
  const DerivedType operator++ (int) {
    /* Copy our current value by downcasting to our real type. */
    DerivedType result = static_cast<DerivedType&>(*this);

    /* Advance to the next element. */
    ++*this;

    /* Hand back the cached value. */
    return result;
  }

  /* Backup operators work on the same principle. */
  DerivedType& operator-- () {
    /* If the current pointer is NULL, it means that we've walked off the end
     * of the structure and need to back up a step.
     */
    if (mCurr == NULL) {
      mCurr = mOwner->mTail;
    }
    /* Otherwise, just back up a step. */
    else {
      mCurr = mCurr->mPrev;
    }

    /* Downcast to our actual type. */
    return static_cast<DerivedType&>(*this);
  }
  const DerivedType operator-- (int) {
    /* Copy our current value by downcasting to our real type. */
    DerivedType result = static_cast<DerivedType&>(*this);

    /* Back up a step. */
    --*this;

    /* Hand back the cached value. */
    return result;
  }

  /* Equality and disequality operators are parameterized - we'll allow anyone
   * whose type is IteratorBase to compare with us.  This means that we can
   * compare both iterator and const_iterator against one another.
   */
  template <typename DerivedType2, typename Pointer2, typename Reference2>
  bool operator== (const IteratorBase<DerivedType2, Pointer2, Reference2>& rhs) {
    /* Just check the underlying pointers, which (fortunately!) are of the 
     * same type.
     */
    return mOwner == rhs.mOwner && mCurr == rhs.mCurr;
  }
  template <typename DerivedType2, typename Pointer2, typename Reference2>
  bool operator!= (const IteratorBase<DerivedType2, Pointer2, Reference2>& rhs) {
    /* We are disequal if equality returns false. */
    return !(*this == rhs);
  }

  /* Pointer dereference operator hands back a reference. */
  Reference operator* () const {
    return mCurr->mValue;
  }
  
  /* Arrow operator returns a pointer. */
  Pointer operator-> () const {
    /* Use the standard "&**this" trick to dereference this object and return
     * a pointer to the referenced value.
     */
    return &**this;
  }

protected:
  /* Which AVLTree we belong to.  This pointer is const even though we are
   * possibly allowing ourselves to modify the AVL tree elements to avoid having
   * to duplicate this logic once again for const vs. non-const iterators.
   */
  const AVLTree* mOwner;

  /* Where we are in the list. */
  Node* mCurr;

  /* In order for equality comparisons to work correctly, all IteratorBases
   * must be friends of one another.
   */
  template <typename Derived2, typename Pointer2, typename Reference2>
  friend class IteratorBase;

  /* Constructor sets up the AVL tree and node pointers appropriately. */
  IteratorBase(const AVLTree* owner = NULL, Node* curr = NULL) 
  : mOwner(owner), mCurr(curr) {
    // Handled in initializer list
  }
};

/* iterator and const_iterator implementations work by deriving off of
 * IteratorBase, passing in parameters that make all the operators work.
 * Additionally, we inherit from std::iterator to import all the necessary
 * typedefs to qualify as an iterator.
 */
template <typename Key, typename Value, typename Comparator>
class AVLTree<Key, Value, Comparator>::iterator:
  public std::iterator< std::bidirectional_iterator_tag,
                        std::pair<const Key, Value> >,
  public IteratorBase<iterator,                       // Our type
                      std::pair<const Key, Value>*,   // Reference type
                      std::pair<const Key, Value>&> { // Pointer type 
public:
  /* Default constructor forwards NULL to base implicity. */
  iterator() {
    // Nothing to do here.
  }

  /* All major operations inherited from the base type. */

private:
  /* Constructor for creating an iterator out of a raw node just forwards this
   * argument to the base type.  This line is absolutely awful because the
   * type of the base is so complex.
   */
  iterator(const AVLTree* owner,
           typename AVLTree<Key, Value, Comparator>::Node* node) :
    IteratorBase<iterator,
                 std::pair<const Key, Value>*,
                 std::pair<const Key, Value>&>(owner, node) {
    // Handled by initializer list
  }

  /* Make the AVLTree a friend so it can call this constructor. */
  friend class AVLTree;

  /* Make const_iterator a friend so we can do iterator-to-const_iterator
   * conversions.
   */
  friend class const_iterator;
};

/* Same as above, but with const added in. */
template <typename Key, typename Value, typename Comparator>
class AVLTree<Key, Value, Comparator>::const_iterator:
  public std::iterator< std::bidirectional_iterator_tag,
                        const std::pair<const Key, Value> >,
  public IteratorBase<const_iterator,                       // Our type
                      const std::pair<const Key, Value>*,   // Reference type
                      const std::pair<const Key, Value>&> { // Pointer type 
public:
  /* Default constructor forwards NULL to base implicity. */
  const_iterator() {
    // Nothing to do here.
  }

  /* iterator conversion constructor forwards the other iterator's base fields
   * to the base class.
   */
  const_iterator(iterator itr) :
    IteratorBase<const_iterator,
                 const std::pair<const Key, Value>*,
                 const std::pair<const Key, Value>&>(itr.mOwner, itr.mCurr) {
    // Handled in initializer list
  }

  /* All major operations inherited from the base type. */

private:
  /* See iterator implementation for details about what this does. */
  const_iterator(const AVLTree* owner,
                 typename AVLTree<Key, Value, Comparator>::Node* node) :
    IteratorBase<const_iterator,
                 const std::pair<const Key, Value>*,
                 const std::pair<const Key, Value>&>(owner, node) {
    // Handled by initializer list
  }
  
  /* Make the AVLTree a friend so it can call this constructor. */
  friend class AVLTree;
};

/**** AVLTree::Node Implementation. ****/

/* Constructor sets up the key and value, then sets the height to one.  The
 * linked list fields are left uninitialized.
 */
template <typename Key, typename Value, typename Comparator>
AVLTree<Key, Value, Comparator>::Node::Node(const Key& key,
                                            const Value& value,
                                            int height) 
  : mValue(key, value), mHeight(height) {
  // Handled in initializer list.
}

/**** AVLTree Implementation ****/

/* Constructor sets up a new, empty AVLTree. */
template <typename Key, typename Value, typename Comparator>
AVLTree<Key, Value, Comparator>::AVLTree(Comparator comp) : mComp(comp) {
  /* Initially, the list of elements is empty and the tree is NULL. */
  mHead = mTail = mRoot = NULL;

  /* The tree is created empty. */
  mSize = 0;
}

/* Destructor walks the linked list of elements, deleting all nodes it
 * encounters.
 */
template <typename Key, typename Value, typename Comparator>
AVLTree<Key, Value, Comparator>::~AVLTree() {
  /* Start at the head of the list. */
  Node* curr = mHead;
  while (curr != NULL) {
    /* Cache the next value; we're about to blow up our only pointer to it. */
    Node* next = curr->mNext;

    /* Free memory, then go to the next node. */
    delete curr;
    curr = next;
  }
}

/* Inserting a node works by walking down the tree until the insert point is
 * found, adding the value, then fixing up the balance factors on each node.
 */
template <typename Key, typename Value, typename Comparator>
std::pair<typename AVLTree<Key, Value, Comparator>::iterator, bool>
AVLTree<Key, Value, Comparator>::insert(const Key& key, const Value& value) {
  /* Recursively walk down the tree from the root, looking for where the value
   * should go.  In the course of doing so, we'll maintain some extra
   * information about the node's successor and predecessor so that we can
   * wire the new node in in O(1) time.
   *
   * The information that we'll need will be the last nodes at which we
   * visited the left and right child.  This is because if the new node ends
   * up as a left child, then its predecessor is the last ancestor on the path
   * where we followed its right pointer, and vice-versa if the node ends up
   * as a right child.
   */
  Node* lastLeft = NULL, *lastRight = NULL;
  
  /* Also keep track of our current location as a pointer to the pointer in
   * the tree where the node will end up, which allows us to insert the node
   * by simply rewiring this pointer.
   */
  Node** curr   = &mRoot;

  /* Also track the last visited node. */
  Node*  parent = NULL;

  /* Now, do a standard binary tree insert.  If we ever find the node, we can
   * stop early.
   */
  while (*curr != NULL) {
    /* Update the parent to be this node, since it's the last one visited. */
    parent = *curr;

    /* Check whether we belong in the left subtree. */
    if (mComp(key, (*curr)->mValue.first)) {
      lastLeft = *curr;
      curr = &(*curr)->mChildren[0];
    }
    /* ... or perhaps the right subtree. */
    else if (mComp((*curr)->mValue.first, key)) {
      lastRight = *curr; // Last visited node where we went right.
      curr = &(*curr)->mChildren[1];
    }
    /* Otherwise, the key must already exist in the tree.  Return a pointer to
     * it.
     */
    else
      return std::make_pair(iterator(this, *curr), false);
  }

  /* At this point we've found our insertion point and can create the node
   * we're going to wire in.  Initially, it's at height 1.
   */
  Node* toInsert = new Node(key, value, 1);
  
  /* Splice it into the tree. */
  toInsert->mParent = parent;
  *curr = toInsert;

  /* The new node has no children. */
  toInsert->mChildren[0] = toInsert->mChildren[1] = NULL;

  /* Wire this node into the linked list in-between its predecessor and
   * successor in the tree.  The successor is the last node where we went
   * left, and the predecessor is the last node where we went right.
   */
  toInsert->mNext = lastLeft;
  toInsert->mPrev = lastRight;

  /* Update the previous pointer of the next entry, or change the list tail
   * if there is no next entry.
   */
  if (toInsert->mNext)
    toInsert->mNext->mPrev = toInsert;
  else
    mTail = toInsert;

  /* Update the next pointer of the previous entry similarly. */
  if (toInsert->mPrev)
    toInsert->mPrev->mNext = toInsert;
  else
    mHead = toInsert;
  
  /* Rebalance the tree from this node upward. */
  rebalanceFrom(toInsert);

  /* Increase the size of the tree, since we just added a node. */
  ++mSize;

  /* Hand back an iterator to the new element, along with a notification that
   * it was inserted correctly.
   */
  return std::make_pair(iterator(this, toInsert), true);
}

/* To perform a tree rotation, we identify whether we're doing a left or
 * right rotation, then rewrite pointers as follows:
 *
 * In a right rotation, we do the following:
 *
 *      B            A
 *     / \          / \
 *    A   2   -->  0   B
 *   / \              / \
 *  0   1            1   2
 *
 * In a left rotation, this runs backwards.
 *
 * The reason that we've implemented the nodes as an array of pointers rather
 * than using two named pointers is that the logic is symmetric.  If the node
 * is its left child, then its parent becomes its right child, and the node's
 * right child becomes the parent's left child.  If the node is its parent's
 * right child, then the node's parent becomes its left child and the node's
 * left child becomes the parent's right child.  In other words, the general
 * formula is
 *
 * If the node is its parent's SIDE child, then the parent becomes that node's
 * OPPOSITE-SIDE child, and the node's OPPOSITE-SIDE child becomes the
 * parent's SIDE child.
 *
 * This code also updates the root if the tree root gets rotated out.  It also
 * ensures that the heights of the rotated nodes are properly adjusted.
 */
template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::rotateUp(Node* node) {
  /* Determine which side the node is on.  It's on the left (side 0) if the
   * parent's first pointer matches it, and is on the right (side 1) if the
   * node's first pointer doesn't match it.  This is, coincidentally, whether
   * the node is not equal to the first pointer of its root.
   */
  const int side = (node != node->mParent->mChildren[0]);
  
  /* The other side is the logical negation of the side itself. */
  const int otherSide = !side;

  /* Cache the displaced child and parent of the current node. */
  Node* child  = node->mChildren[otherSide];
  Node* parent = node->mParent;
  
  /* Shuffle pointers around to make the node the parent of its parent. */
  node->mParent = parent->mParent;
  node->mChildren[otherSide] = parent;

  /* Shuffle around pointers so that the parent takes on the displaced
   * child.
   */
  parent->mChildren[side] = child;
  if (child)
    child->mParent = parent;

  /* Update the grandparent (if any) so that its child is now the rotated
   * element rather than the parent.  If there is no grandparent, the node is
   * now the root.
   */
  if (parent->mParent) {
    const int parentSide = (parent != parent->mParent->mChildren[0]);
    parent->mParent->mChildren[parentSide] = node;
  } else
    mRoot = node;

  /* In either case, change the parent so that it now treats the node as the
   * parent.
   */
  parent->mParent = node;

  /* Change the heights of the nodes.  Each node is now at a height one 
   * greater than the max height of its children.  We recompute the parent's
   * height first to ensure that any changes to it propagate correctly.
   */
  parent->mHeight = 1 + std::max(height(parent->mChildren[0]), 
                                 height(parent->mChildren[1]));
  node->mHeight = 1 + std::max(height(node->mChildren[0]), 
                               height(node->mChildren[1]));
}

/* To determine the height of a node, we just hand back the node's recorded
 * height, or 0 if the node is NULL.
 */
template <typename Key, typename Value, typename Comparator>
int AVLTree<Key, Value, Comparator>::height(const Node* node) {
  return node? node->mHeight : 0;
}

/* Computing the balance factor just computes the difference in heights
 * between a node's left and right children.
 */
template <typename Key, typename Value, typename Comparator>
int AVLTree<Key, Value, Comparator>::balanceFactor(const Node* node) {
  return height(node->mChildren[0]) - height(node->mChildren[1]);
}

/* Implementation of the logic for rebalancing the AVL tree via a series of
 * rotations.  This code computes the balance factor at each node and makes
 * one of the following two rotations if the balance is either +2 or -2:
 *
 * 1. If the child on the tall side has a balance factor whose sign isn't the
 *    opposite of the real node's balance factor, perform a single rotation
 *    from that child.
 * 2. If the child on the tall side has a balance factor whose sign is the
 *    opposite of the real node's balance factor, rotate its child on its
 *    tall side upward, then rotate it again with the original node.
 */
template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::rebalanceFrom(Node* where) {
  /* Start walking up from the node toward the root, checking for any new
   * imbalances and recomputing heights as appropriate.
   */
  while (where != NULL) {
    /* Recompute the height of this node. */
    where->mHeight = 1 + std::max(height(where->mChildren[0]), 
                                  height(where->mChildren[1]));


    /* Get the balance factor. */
    const int balance = balanceFactor(where);

    /* If the balance factor is +/- 2, we need to do some rotations. */
    if (balance == 2 || balance == -2) {
      /* Determine what child is on the heavy side.  If the balance is +2,
       * this is the left child (child 0), and if it's -2 it's the right child
       * (child 1).  We use the comparison balance == -2 for this, since its
       * values match what we need in this case.
       */
      Node* tallChild = where->mChildren[balance == -2];

      /* Check its balance factor and see what kind of rotation we need. */
      const int childBalance = balanceFactor(tallChild);

      /* We do a single rotation unless the child node is balanced opposite of
       * its parent.
       */
      if (childBalance == 0 || (childBalance < 0) == (balance < 0)) {
        rotateUp(tallChild);

        /* This node is now balanced, but we still need to update heights up
         * elsewhere in the tree.  Set the search to continue from the parent
         * of this node.
         */
        where = tallChild->mParent;
      }
      /* Otherwise, we need to do a double rotation. */
      else {
        /* We need a slightly different test to determine what child is heavy
         * since the balance is going to be +1 or -1 in this case.
         */
        Node* tallGrandchild = tallChild->mChildren[childBalance == -1];

        /* Rotate this node up twice. */
        rotateUp(tallGrandchild);
        rotateUp(tallGrandchild);

        /* Again, pick up the search from this point. */
        where = tallGrandchild->mParent;
      }
    }
    /* If we didn't end up doing any rotations, have the search go up one
     * level.
     */
    else {
      /* Pick up the search from the parent of this node. */
      where = where->mParent;
    }
  }
}

/* const version of find works by doing a standard BST search for the node in
 * question.
 */
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::const_iterator
AVLTree<Key, Value, Comparator>::find(const Key& key) const {
  /* Do a standard BST search and wrap up whataver we found. */
  return const_iterator(this, findNode(key).first);
}

/* Non-const version of find implemented in terms of const find. */
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::iterator
AVLTree<Key, Value, Comparator>::find(const Key& key) {
  /* Get the underlying const_iterator by calling the const version of this
   * function.
   */
  const_iterator itr = static_cast<const AVLTree*>(this)->find(key);

  /* Strip off the constness by wrapping it up as a raw iterator. */
  return iterator(itr.mOwner, itr.mCurr);
}

/* findNode just does a standard BST lookup, recording the last node that was
 * found before the one that was ultimately returned.
 */
template <typename Key, typename Value, typename Comparator>
std::pair<typename AVLTree<Key, Value, Comparator>::Node*,
          typename AVLTree<Key, Value, Comparator>::Node*>
AVLTree<Key, Value, Comparator>::findNode(const Key& key) const {
  /* Start the search at the root and work downwards.  Keep track of the last
   * node we visited.
   */
  Node* curr = mRoot, *prev = NULL;
  while (curr != NULL) {
    /* Update the prev pointer so that it tracks the last node we visited. */
    prev = curr;

    /* If the key is less than this node, go left. */
    if (mComp(key, curr->mValue.first))
      curr = curr->mChildren[0];
    /* Otherwise if the key is greater than the node, go right. */
    else if (mComp(curr->mValue.first, key))
      curr = curr->mChildren[1];
    /* Otherwise, we found the node.  Return that node and its parent as the
     * pair in question.  We explicitly use the parent here instead of prev
     * since the first part of this loop updates prev to be equal to curr.
     */
    else
      return std::make_pair(curr, curr->mParent);
  }

  /* If we ended up here, then we know that we didn't find the node in
   * question.  Handing back the pair of NULL and the most-recently-visited
   * node.  Note that due to the fact that NULL is #defined as zero, we have
   * to explicitly cast it to a Node* so that the template argument deduction
   * will work correctly; omitting this cast yields a pair<int, Node*>, which
   * gives a type error.
   */
  return std::make_pair((Node*)NULL, prev);
}

/* begin and end return iterators wrapping the head of the list or NULL,
 * respectively.
 */
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::iterator
AVLTree<Key, Value, Comparator>::begin() {
  return iterator(this, mHead);
}
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::const_iterator
AVLTree<Key, Value, Comparator>::begin() const {
  return iterator(this, mHead);
}
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::iterator
AVLTree<Key, Value, Comparator>::end() {
  return iterator(this, NULL);
}
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::const_iterator
AVLTree<Key, Value, Comparator>::end() const {
  return iterator(this, NULL);
}

/* rbegin and rend return wrapped versions of end() and begin(),
 * respectively.
 */
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::reverse_iterator
AVLTree<Key, Value, Comparator>::rbegin() {
  return reverse_iterator(end());
}
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::const_reverse_iterator
AVLTree<Key, Value, Comparator>::rbegin() const {
  return const_reverse_iterator(end());
}
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::reverse_iterator
AVLTree<Key, Value, Comparator>::rend() {
  return reverse_iterator(begin());
}
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::const_reverse_iterator
AVLTree<Key, Value, Comparator>::rend() const {
  return const_reverse_iterator(begin());
}

/* size just returns the cached size of the AVL tree. */
template <typename Key, typename Value, typename Comparator>
size_t AVLTree<Key, Value, Comparator>::size() const {
  return mSize;
}

/* empty returns whether the size is zero. */
template <typename Key, typename Value, typename Comparator>
bool AVLTree<Key, Value, Comparator>::empty() const {
  return size() == 0;
}

/* To splice out a node in the tree, we determine where its singleton child is
 * (if there even is one), then replace it with that node.
 */
template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::spliceOut(Node* node) {
  /* Confirm that this node has at most one child. */
  assert (!node->mChildren[0] || !node->mChildren[1]);

  /* For simplicity, cache the node's pointer. */
  Node* parent = node->mParent;

  /* Get a pointer to a child node that exists, if there even is a child
   * node that exists.  This works by seeing if the right child exists and
   * picking it if it does, and otherwise picking the left child.  If there
   * are no children this picks NULL, and otherwise picks the valid child.
   */
  const size_t childIndex = (node->mChildren[1] != NULL);
  Node* child = node->mChildren[childIndex];

  /* Make sure the other is NULL. */
  assert (node->mChildren[!childIndex] == NULL);
  
  /* If there is a child, change its parent to be the parent of the node
   * that's being deleted.
   */
  if (child)
    child->mParent = parent;
  
  /* Change the parent of the node being deleted to use the new child node
   * instead of the node to delete.  However, the node in question might be
   * the root, in which case we need to change the root of the tree.
   */
  if (parent) {
    /* We need to change the correct pointer in the parent.  If the node is
     * a right child, we should change the right pointer, and otherwise we
     * change the left pointer.
     */
    parent->mChildren[node == parent->mChildren[1]] = child;
  }
  /* If there is no parent, then the new node is at the root of the tree. */
  else
    mRoot = child;
}

/* Removing a node from the AVL tree is perhaps the most difficult part of the
 * implementation.  We first need to remove the node from the tree, which
 * requires us to do some special-casing logic to figure out what will replace
 * the node.  Then, we have to do a pass upward from where we did the switch 
 * to fix up the tree structure and confirm that the invariants hold.
 */
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::iterator
AVLTree<Key, Value, Comparator>::erase(iterator where) {
  /* Extract the node pointer from the iterator. */
  Node* node = where.mCurr;

  /* For simplicity, cache the parent pointer. */
  Node* parent = node->mParent;

  /* Drop the number of elements; we're about to remove something. */
  --mSize;

  /* There are two cases to consider here, both of which are outlined in the
   * file comments.  The first case comes up when we're removing a node that
   * does not have both children (easy), and the second when both children
   * are present (hard).
   */
  
  /* Case 1: Missing at least one child. */
  if (!node->mChildren[0] || !node->mChildren[1]) {
    spliceOut(node);
    rebalanceFrom(parent);
  }
  /* Case 2: Both children present.  Replace the node with its successor. */
  else {
    /* The successor node is, fortunately, encoded by the linked list
     * structure.
     */
    Node* successor = node->mNext;

    /* The successor shouldn't have a left child, since otherwise that would
     * be the real successor of this node.
     */
    assert (successor->mChildren[0] == NULL);

    /* Keep track of the parent of this node, since that's where we're going
     * to have to run the cleanup step from.
     */
    Node* successorParent = successor->mParent;

    /* Cut this node out from its parent, possibly splicing its child above
     * it.
     */
    spliceOut(successor);

    /* Now, replace the node to be removed with the successor.  This means
     * that we need to copy over the children and parents of the node to
     * remove into the successor, then fix the incoming pointers into the node
     * as well.
     */
    successor->mParent = parent;
    for (size_t i = 0; i < 2; ++i)
      successor->mChildren[i] = node->mChildren[i];
    
    /* Set the parents of the children to be this node.  We still need to
     * check that these nodes aren't NULL, because it's possible that the
     * successor node was a direct child and somehow got cut.
     */
    for (size_t i = 0; i < 2; ++i)
      if (successor->mChildren[i])
        successor->mChildren[i]->mParent = successor;

    /* Change the parent of this node to point back down at it, again
     * requiring some special-case logic.
     */
    if (parent) {
      /* Check whether the node to delete, NOT the successor, is a left child
       * because the successor node can't possibly be a child.
       */
      parent->mChildren[node == parent->mChildren[1]] = successor;
    }
    else
      mRoot = successor;

    /* Whew!  We've successfully spliced out the node.  Now, run a fixup pass
     * from where we cut the successor.  There are two cases to consider,
     * though.  First, if the successor node was a direct child of the node
     * that we're deleting, we need to run the fixup pass from the successor
     * node, which has been moved.  Second, if the successor was not a direct
     * child of the node to remove, then its parent might be dealing with an
     * imbalanced tree and we need to fix it up.
     */
    rebalanceFrom(node == successorParent? successor : successorParent);
  }

  /* We've now removed the node in question from the tree structure, and now
   * we need to remove it from the doubly-linked list.
   */

  /* If there is a next node, wire its previous pointer around the current
   * node.  Otherwise, the tail just changed.
   */
  if (node->mNext)
    node->mNext->mPrev = node->mPrev;
  else
    mTail = node->mPrev;

  /* If there is a previous node, wite its next pointer around the current
   * node.  Otherwise, the head just changed.
   */
  if (node->mPrev)
    node->mPrev->mNext = node->mNext;
  else
    mHead = node->mNext;

  /* Since we need to return an iterator to the element in the tree after this
   * one, we'll cache the next pointer of the node to delete.  It won't be
   * available after we delete the node.
   */
  iterator result(this, node->mNext);

  /* Free the node's resources. */
  delete node;
  return result;
}

/* Erasing a single value just calls find to locate the element and the
 * iterator version of erase to remove it.
 */
template <typename Key, typename Value, typename Comparator>
bool AVLTree<Key, Value, Comparator>::erase(const Key& key) {
  /* Look up where this node is, then remove it if it exists. */
  iterator where = find(key);
  if (where == end()) return false;

  erase(where);
  return true;
}

/* Square brackets implemented in terms of insert(). */
template <typename Key, typename Value, typename Comparator>
Value& AVLTree<Key, Value, Comparator>::operator[] (const Key& key) {
  /* Call insert to get a pair of an iterator and a bool.  Look at the
   * iterator, then consider its second field.
   */
  return insert(key, Value()).first->second;
}

/* at implemented in terms of find. */
template <typename Key, typename Value, typename Comparator>
const Value& AVLTree<Key, Value, Comparator>::at(const Key& key) const {
  /* Look up the key, failing if we can't find it. */
  const_iterator result = find(key);
  if (result == end())
    throw std::out_of_range("Key not found in AVL tree.");

  /* Otherwise just return the value field. */
  return result->second;
}

/* non-const at implemented in terms of at using the const_cast/static_cast
 * trick.
 */
template <typename Key, typename Value, typename Comparator>
Value& AVLTree<Key, Value, Comparator>::at(const Key& key) {
  return const_cast<Value&>(static_cast<const AVLTree*>(this)->at(key));
}

/* The copy constructor is perhaps the most complex part of this entire
 * implementation.  It works in two passes.  First, the tree structure itself
 * is duplicated, without paying any attention to the next and previous
 * pointers threaded through.  Next, we run a recursive pass over the cloned
 * tree, fixing up all of the next and previous pointers as we go.
 */
template <typename Key, typename Value, typename Comparator>
AVLTree<Key, Value, Comparator>::AVLTree(const AVLTree& other) {
  /* Start off with the simple bits - copy over the size field and 
   * comparator. 
   */
  mSize = other.mSize;
  mComp = other.mComp;

  /* Clone the tree structure. */
  mRoot = cloneTree(other.mRoot, NULL);

  /* Rectify the linked list. */
  rethreadLinkedList(mRoot, NULL);

  /* Finally, fix up the first and last pointers of the list by looking for
   * the smallest and largest elements in the tree.
   */
  mTail = mHead = mRoot;
  while (mHead && mHead->mChildren[0]) mHead = mHead->mChildren[0];
  while (mTail && mTail->mChildren[1]) mTail = mTail->mChildren[1];
}

/* Cloning a tree is a simple structural recursion. */
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::Node*
AVLTree<Key, Value, Comparator>::cloneTree(Node* toClone, Node* parent) {
  /* Base case: the clone of the empty tree is that tree itself. */
  if (toClone == NULL) return NULL;

  /* Create a copy of the node, moving over the height and key/value pair */
  Node* result = new Node(toClone->mValue.first, toClone->mValue.second,
                          toClone->mHeight);

  /* Recursively clone the subtrees. */
  for (int i = 0; i < 2; ++i)
    result->mChildren[i] = cloneTree(toClone->mChildren[i], result);

  /* Set the parent. */
  result->mParent = parent;

  return result;
}

/* Fixing up the doubly-linked list is a bit tricky.  The function acts as an
 * inorder traversal.  We first fix up the left subtree, getting a pointer to
 * the node holding the largest value in that subtree (the predecessor of this
 * node).  We then chain the current node into the linked list, then fix up
 * the nodes to the right (which have the current node as their predecessor).
 */
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::Node*
AVLTree<Key, Value, Comparator>::rethreadLinkedList(Node* root, Node* predecessor) {
  /* Base case: if the root is null, then the largest element visited so far
   * is whatever we were told it was.
   */
  if (root == NULL) return predecessor;

  /* Otherwise, recursively fix up the left subtree using the actual
   * predecessor.  Store the return value as the new predecessor.
   */
  predecessor = rethreadLinkedList(root->mChildren[0], predecessor);

  /* Add ourselves to the linked list. */
  root->mPrev = predecessor;
  if (predecessor)
    predecessor->mNext = root;
  root->mNext = NULL;

  /* Recursively invoke on the right subtree, passing in this node as the
   * predecessor.
   */
  return rethreadLinkedList(root->mChildren[1], root);
}

/* Assignment operator implemented using copy-and-swap. */
template <typename Key, typename Value, typename Comparator>
AVLTree<Key, Value, Comparator>&
AVLTree<Key, Value, Comparator>::operator= (const AVLTree& other) {
  AVLTree clone = other;
  swap(clone);
  return *this;
}

/* swap just does an element-by-element swap. */
template <typename Key, typename Value, typename Comparator>
void AVLTree<Key, Value, Comparator>::swap(AVLTree& other) {
  /* Use std::swap to get the job done. */
  std::swap(mRoot, other.mRoot);
  std::swap(mSize, other.mSize);
  std::swap(mHead, other.mHead);
  std::swap(mTail, other.mTail);
  std::swap(mComp, other.mComp);
}

/* lower_bound works by walking down the tree to where the node belongs.  If
 * it's in the tree, then it's its own lower bound.  Otherwise, we either
 * found the predecessor or successor of the node in question, and correct it
 * to the resulting node.
 */
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::const_iterator
AVLTree<Key, Value, Comparator>::lower_bound(const Key& key) const {
  /* One unusual edge case that complicates the logic here is what to do if
   * the tree is empty.  If this happens, then the lower_bound is end().
   */
  if (empty()) return end();

  /* Locate the node in question. */
  std::pair<Node*, Node*> result = findNode(key);

  /* If we found the node we wanted, we can just wrap it up as an iterator. */
  if (result.first)
    return iterator(this, result.first);

  /* Otherwise, the value isn't here, but we do know the value in the tree
   * that would be its parent.  This value is therefore either the predecessor
   * or the successor of the value in question.  If it's the predecessor, then
   * we need to advance it forward one step to get the smallest value greater
   * than the indicated key.  Note that we can assume that there is some
   * predecessor, since we know that the tree is not empty.
   *
   * To check whether we're looking at the predecessor, we're curious whether
   * the key field of the value of the node of the second Node*.  Phew!
   */
  if (mComp(result.second->mValue.first, key))
    result.second = result.second->mNext;
  
  return iterator(this, result.second);
}

/* Non-const version of this function implemented by calling the const version
 * and stripping constness.
 */
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::iterator
AVLTree<Key, Value, Comparator>::lower_bound(const Key& key) {
  /* Call the const version to get the answer. */
  const_iterator result = static_cast<const AVLTree*>(this)->lower_bound(key);

  /* Rewrap it in a regular iterator to remove constness. */
  return iterator(result.mOwner, result.mCurr);
}

/* equal_range looks up where the node should be.  If it finds it, it hands
 * back iterators spanning it.  If not, it just hands back two iterators to the
 * same spot.
 */
template <typename Key, typename Value, typename Comparator>
std::pair<typename AVLTree<Key, Value, Comparator>::const_iterator,
          typename AVLTree<Key, Value, Comparator>::const_iterator>
AVLTree<Key, Value, Comparator>::equal_range(const Key& key) const {
  /* Call lower_bound to find out where we should start looking. */
  std::pair<const_iterator, const_iterator> result;
  result.first = result.second = lower_bound(key);

  /* If we hit the end, we're done. */
  if (result.first == end()) return result;

  /* Otherwise, check whether the iterator we found matches the value.  If so,
   * bump the second iterator one step.
   */
  if (!mComp(key, result.second->first))
    ++result.second;

  return result;
}

/* Non-const version calls the const version, then strips off constness. */
template <typename Key, typename Value, typename Comparator>
std::pair<typename AVLTree<Key, Value, Comparator>::iterator,
          typename AVLTree<Key, Value, Comparator>::iterator>
AVLTree<Key, Value, Comparator>::equal_range(const Key& key) {
  /* Invoke const version to get the iterators. */
  std::pair<const_iterator, const_iterator> result =
    static_cast<const AVLTree*>(this)->equal_range(key);

  /* Unwrap into regular iterators. */
  return std::make_pair(iterator(result.first.mOwner,  result.first.mCurr),
                        iterator(result.second.mOwner, result.second.mCurr));
}

/* upper_bound just calls equal_range and returns the second value. */
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::iterator
AVLTree<Key, Value, Comparator>::upper_bound(const Key& key) {
  return equal_range(key).second;
}
template <typename Key, typename Value, typename Comparator>
typename AVLTree<Key, Value, Comparator>::const_iterator
AVLTree<Key, Value, Comparator>::upper_bound(const Key& key) const {
  return equal_range(key).second;
}

/* Comparison operators == and < use the standard STL algorithms. */
template <typename Key, typename Value, typename Comparator>
bool operator<  (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(),
                                      rhs.begin(), rhs.end());
}
template <typename Key, typename Value, typename Comparator>
bool operator== (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs) {
  return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), 
                                                rhs.begin());
}

/* Remaining comparisons implemented in terms of the above comparisons. */
template <typename Key, typename Value, typename Comparator>
bool operator<= (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs) {
  /* x <= y   iff !(x > y)   iff !(y < x) */
  return !(rhs < lhs);
}
template <typename Key, typename Value, typename Comparator>
bool operator!= (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs) {
  return !(lhs == rhs);
}
template <typename Key, typename Value, typename Comparator>
bool operator>= (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs) {
  /* x >= y   iff !(x < y) */
  return !(lhs < rhs);
}
template <typename Key, typename Value, typename Comparator>

bool operator>  (const AVLTree<Key, Value, Comparator>& lhs,
                 const AVLTree<Key, Value, Comparator>& rhs) {
  /* x > y iff y < x */
  return rhs < lhs;
}

#endif
