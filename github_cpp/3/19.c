








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
    avlnode<NDT> *t[2];  

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
    avlnode<BTDT> *entry;   
    avlnode<BTDT> **next;   
    int rval;               
    bool toggle;            
                            

    void rcopy(avlnode<BTDT>* &pn, const avlnode<BTDT>* const s);
    void rrelease(avlnode<BTDT>* &pn);
    int  radd(avlnode<BTDT>* &pn, BTDT d);
    avlnode<BTDT> ** rfind(const avlnode<BTDT>* const &pn, BTDT d);
	
    int  rdel(avlnode<BTDT>** pn);
    void rshow(const avlnode<BTDT>* const pn) const;

    
    void rbalance(avlnode<BTDT>* &pn);
    
    void check_avl(avlnode<BTDT>* &pn, bool dir);
    
    void rotate(avlnode<BTDT>* &pn, bool dir);
    
    void dbl_rotate(avlnode<BTDT>* &pn, bool dir);


public:
    sTree()
    {
        entry = NULL;
        next = NULL;
        toggle = false;
        rval = 0;
    }

    sTree(const sTree<BTDT> &src);        
    ~sTree();                             
    const sTree<BTDT> &operator =(const sTree<BTDT> &src);
    
    void release();
    int  add(BTDT d);
    int  find(BTDT d);
    int  del(BTDT d);
    void show();
};


#ifdef WIN32
	#include "sTree.cpp"
#endif


#endif 
