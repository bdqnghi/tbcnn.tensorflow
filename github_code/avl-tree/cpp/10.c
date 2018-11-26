// avl_tree
//------------------------------------------
// synopsis:
// classes for balanced (AVL) trees
//
// description:
// See comments below.  This code is adapted (by removal of exception
// handling) from the Foundations-1 Class Library.
//------------------------------------------
// Restrictions:
// ...
//------------------------------------------


// avl_tree.hpp, 900531, WMM: balanced tree class declarations

/* Copyright (c) 1990, Software Development Technologies, Inc., Sudbury, MA.
 * All rights reserved.
 */

#ifndef _AVL_TREE_DECLS
#define _AVL_TREE_DECLS

/* Modification history:
 *
 * 900531, WMM: Initial release.
 */

/***************************
 * REQUIRED INCLUDE FILES: *
 *                         *
 *  #include <stddef.h>    *
 *  #include <setjmp.h>    *
 *                         *
 ***************************/

/***************
 * DESCRIPTION *
 ***************/

/* This file contains declarations for classes used in creating, maintaining,
 * and using balanced (AVL) trees as described in Knuth, v.3, pp. 451-471.
 * The following classes are declared:
 *
 * avl_tree:      May be used directly (i.e., is not abstract) to represent
 *                an AVL tree.  It provides member functions which can be
 *                used to find or delete nodes in the tree based on a given
 *                key.
 *
 * avl_iterator:  May be used directly to traverse the nodes of a given tree
 *                in ascending key order.
 *
 * avl_node:      ABSTRACT (i.e., may not be used directly but must be derived
 *                from).  Represents a node in an avl_tree.  Creating a node
 *                inserts it into the tree at the correct point (avl_node
 *                objects must be heap objects and not static or automatic).
 *                Removal of nodes from trees MUST be done via the appropriate
 *                member function of avl_tree, however, not by applying delete
 *                to a node pointer.
 *
 * avl_key:       ABSTRACT class which represents a key value.  Keys are used
 *                to order nodes in the tree.
 *
 * The classes are used as follows:  First, an avl_tree object is instantiated.
 * It may be of any storage class.  The tree is built by creating new nodes;
 * nodes are inserted at the correct point in the tree when they are created.
 * Attempting to create a node with a key which compares equal to an existing
 * node in the tree is not an error; the new node will not be inserted into
 * the tree, however, and it is the responsibility of the creator of the node
 * to interrogate the dup() member function to see if the node was successfully
 * inserted into the tree and, if not, to delete it.  The nodes of the tree
 * can be accessed in two fashions: the avl_tree::find() member function
 * locates a single node identified by a specified key, or an object of the
 * avl_iterator() class may be instantiated to access all the nodes of a
 * tree in ascending key order.
 */

// Forward definitions and typedefs

class avl_key;
class avl_node;
class avl_tree;
typedef avl_node* avl_nodeptr;
typedef avl_nodeptr* avl_linkptr;
typedef avl_tree* avl_treeptr;

/****************************
 * CLASS avl_key (ABSTRACT) *
 ****************************/

/* Class avl_key is used as a base class for the keys which order the nodes
 * of the tree.  The base class provides no data members or member functions
 * but is here primarily to serve as a type for parameters to the member
 * functions of other classes.
 */

class avl_key { };

/*****************************
 * CLASS avl_node (ABSTRACT) *
 *****************************/

/* Objects of class avl_node must be created in the heap and cannot be
 * static or automatic.  When deriving from avl_node, the derived class
 * should include as data (or have a pointer to) an object of the class
 * derived from avl_key which is used for this tree, as well as the
 * associated data, if any.  In circumstances where many duplicate
 * insertions are expected, the derived class can avoid a great deal of
 * allocation overhead by providing operator new()/operator delete() to
 * manage a free list instead of relying on the default heap management
 * routines.
 */

class avl_node {
   friend class avl_tree;
   friend class avl_iterator;

public:

   avl_node(avl_treeptr, const avl_key&);
   /* The constructor inserts the newly created node into the referenced
    * tree at the pointer identified by the key.  Note that it is the
    * responsibility of the derived constructor to insert the key value
    * or pointer thereto into the node.
    */

   virtual ~avl_node();
   /* The default destructor deletes both of its subtrees.  NOTE: nodes
    * MUST be removed from the tree by avl_tree::remove(), NOT by using
    * delete!  Deleting a node in the tree will damage the tree (because
    * there are no backpointers in the nodes to allow rebalancing of
    * parents).
    */

   avl_nodeptr dup() const;
   /* dup() should be called after allocation to find out if the new node
    * duplicates one already in the tree.  If so, the result is a pointer to
    * the existing node (which was *not* replaced by this); the allocator
    * should take whatever cleanup measures are necessary, including deletion
    * of this node.  If no duplicate was found, the result of dup() is NULL.
    * dup() can be called anytime after the constructor has run, including in
    * the derived class constructor.
    */

   virtual int compare(const avl_key& other) const = 0;
   /* compare() is called to compare the key value for this node against
    * the supplied key value.  The result is as follows:
    *        1 => this < other
    *        0 => this == other
    *       -1 => this > other
    * This member function is pure and MUST BE provided by the derived class.
    */

private:
   avl_nodeptr left;
   avl_nodeptr right;
   int balance;

   static void restore_trace(avl_nodeptr from, avl_nodeptr upto,
         int initial_direction);
   };

/******************
 * CLASS avl_tree *
 ******************/

class avl_tree {
   friend class avl_node;
   friend class avl_iterator;

public:

   avl_tree();

   virtual ~avl_tree();
   // Deletes all nodes in the tree.

   avl_nodeptr find(const avl_key&) const;
   /* find() returns the node located by the parameter key or NULL if there
    * is no such node.  It uses avl_node::compare() to locate the appropriate
    * node.
    */

   void remove(const avl_key&);
   /* remove() excises the node (if any) which compares equal to the
    * parameter key and deletes its storage.
    */

   size_t count() { return cnt; }
   /* count() returns the total number of items currently in the tree. */

private:
   avl_nodeptr root;
   size_t cnt;

   int excise_from(avl_nodeptr&, const avl_key&);
   static int rebalance(avl_nodeptr&);
   static int rotate_left(avl_nodeptr&);
   static int rotate_right(avl_nodeptr&);
   };

/**********************
 * CLASS avl_iterator *
 **********************/

class avl_iterator {
public:

   avl_iterator(const avl_tree*);
   // The constructor takes a pointer to the tree which is to be traversed.

   virtual ~avl_iterator();

   avl_nodeptr next();
   /* Each invocation of next() returns a pointer to the next node in the
    * traversal sequence.  It returns NULL if there are no more nodes left
    * in the tree.
    */

   void reset();
   // Start traversal from the beginning again.

private:
   void traverse(avl_node*);
   const avl_tree* treep;
   struct avl_traversal* stackp;
   };

#endif
