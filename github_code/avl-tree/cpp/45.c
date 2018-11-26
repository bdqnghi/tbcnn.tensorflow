/*
 * avl.h
 */

#ifndef AVL_H
#define AVL_H

#include "bst.h"

template <typename T, typename K> class AVL : public BST<T,K>
{
  private:
    int bfactor() const;     // TODO: find the balance factor of tree
    void fix_height() const; // TODO: rectify the height of each node in tree
    void rotate_left();      // TODO: single left or anti-clockwise rotation
    void rotate_right();     // TODO: single right or clockwise rotation
    void balance();          // TODO: AVL tree balancing

  public:
    virtual void insert(const T& x, const K&k); // TODO: insert an item in sorted order
    virtual void remove(const K& k);            // TODO: remove an item

    typedef typename BT<T,K>::node bt_node;
};

#include "avl.cpp"


#endif /* AVL_H */
