//////////////////////////////////////////////////////////////////////////////
// Program Name:    stree.h
// Programmer:      Joseph E. Sutton
// Description:     AVL Balanced Binary Tree, Sorted and Searchable
// Start Date:      5/6/2004
// Last Updated:    5/19/2004
// Version:         1.50
//////////////////////////////////////////////////////////////////////////////

#ifndef SORT_TREE_H  
#define SORT_TREE_H

enum { LEFT = false, RIGHT = true};

inline int max(int a, int b)
{
    return (a > b) ? a : b;
}

template<class NDT>
class avlnode
{
protected:
    int depth;

public:
    NDT data;
    avlnode<NDT> *t[2];  // left, right array

    avlnode(NDT d = 0)
    {
        data = d;
        t[LEFT] = t[RIGHT] = NULL;
        depth = 0;
    }

    int Diff(bool dir) const
    {
        return GetDepth(dir) - GetDepth(!dir);
    }

    void UpdateDepth()
    {
        depth = 1 + max(GetDepth(LEFT), GetDepth(RIGHT));
    }

    int GetDepth(int dir=-1) const
    {
        int rval = 0;

        if(dir == LEFT)
            rval = (t[LEFT] == NULL) ? -1 : t[LEFT]->depth;
        else
            if(dir == RIGHT)
                rval = (t[RIGHT] == NULL) ? -1 : t[RIGHT]->depth;
            else
                rval = depth;

        return rval;
    }
};

template<class BTDT>
class sTree
{
protected:
    avlnode<BTDT> *entry;   // entry into tree pointer
    avlnode<BTDT> **next;   // temp pointer to pointer
    int rval;               // return value
    bool toggle;            // when deleting 'toggle' tries to
                            // prevent systematic unbalancing

    void rcopy(avlnode<BTDT>* &pn, const avlnode<BTDT>* const s);
    void rrelease(avlnode<BTDT>* &pn);
    int  radd(avlnode<BTDT>* &pn, BTDT d);
    avlnode<BTDT> ** rfind(const avlnode<BTDT>* const &pn, BTDT d);
	// call rfind first before calling rdel to find node to delete
    int  rdel(avlnode<BTDT>** pn);
    void rshow(const avlnode<BTDT>* const pn) const;

    // checks and balances tree
    void rbalance(avlnode<BTDT>* &pn);
    // checks for AVL
    void check_avl(avlnode<BTDT>* &pn, bool dir);
    // rotates node to balance tree
    void rotate(avlnode<BTDT>* &pn, bool dir);
    // rotates twice to balance tree
    void dbl_rotate(avlnode<BTDT>* &pn, bool dir);


public:
    sTree()
    {
        entry = NULL;
        next = NULL;
        toggle = false;
        rval = 0;
    }

    sTree(const sTree<BTDT> &src);        // copy constructor
    ~sTree();                             // deconstructor
    const sTree<BTDT> &operator =(const sTree<BTDT> &src);
    
    void release();
    int  add(BTDT d);
    int  find(BTDT d);
    int  del(BTDT d);
    void show();
};

// For MS VC++ 6
#ifdef WIN32
	#include "sTree.cpp"
#endif
//

#endif // SORT_TREE_H
