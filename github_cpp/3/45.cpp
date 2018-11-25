

#ifndef AVL_H
#define AVL_H

#include "bst.h"

template <typename T, typename K> class AVL : public BST<T,K>
{
  private:
    int bfactor() const;     
    void fix_height() const; 
    void rotate_left();      
    void rotate_right();     
    void balance();          

  public:
    virtual void insert(const T& x, const K&k); 
    virtual void remove(const K& k);            

    typedef typename BT<T,K>::node bt_node;
};

#include "avl.cpp"


#endif 
