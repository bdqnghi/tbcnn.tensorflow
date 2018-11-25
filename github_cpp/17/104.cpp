

#ifndef __LS_UTILS_BTREE__
#define __LS_UTILS_BTREE__

#include <utility> 

#include "lightsky/utils/Bits.h"

namespace ls {
namespace utils {




enum bnode_dir_t : unsigned {
    BNODE_LEFT = 0,
    BNODE_RIGHT = 1,
    BNODE_MAX
};




template <typename data_t>
class BTreeNode {
  private:
    template <typename, typename>
    friend
    class BTree;

    
    data_t* data = nullptr;

    
    BTreeNode* subNodes = nullptr;

  public:
    
    constexpr
    BTreeNode();

    
    BTreeNode(const BTreeNode& btn);

    
    BTreeNode(BTreeNode&& btn);

    
    ~BTreeNode();

    
    BTreeNode& operator=(const BTreeNode& btn);

    
    BTreeNode& operator=(BTreeNode&& btn);
};


template <typename data_t>
constexpr
BTreeNode<data_t>::BTreeNode() {
}


template <typename data_t>
BTreeNode<data_t>::BTreeNode(const BTreeNode& btn)
    :
    data{
    btn.data != nullptr
    ?
    new data_t(*btn.data)
    :
    nullptr
},
subNodes{nullptr}
{
    if (btn.subNodes != nullptr) {
        subNodes = new BTreeNode[BNODE_MAX];
        subNodes[BNODE_LEFT] = btn.subNodes[BNODE_LEFT];
        subNodes[BNODE_RIGHT] = btn.subNodes[BNODE_RIGHT];
    }
}


template <typename data_t>
BTreeNode<data_t>::BTreeNode(BTreeNode&& btn)
    :
    data{btn.data},
subNodes{btn.subNodes}
{
    btn.data = nullptr;
    btn.subNodes = nullptr;
}


template <typename data_t>
BTreeNode<data_t>::~BTreeNode() {
    delete data;
    data = nullptr;

    delete [] subNodes;
    subNodes = nullptr;
}


template <typename data_t>
BTreeNode<data_t>& BTreeNode<data_t>::operator=(const BTreeNode& btn) {
    delete data;
    if (btn.data) {
        data = new data_t;
        *data = *btn.data;
    }
    else {
        data = nullptr;
    }

    delete subNodes;
    if (btn.subNodes) {
        subNodes = new BTreeNode[BNODE_MAX];
        subNodes[BNODE_LEFT] = btn.subNodes[BNODE_LEFT];
        subNodes[BNODE_RIGHT] = btn.subNodes[BNODE_RIGHT];
    }
    else {
        subNodes = nullptr;
    }
    return *this;
}


template <typename data_t>
BTreeNode<data_t>& BTreeNode<data_t>::operator=(BTreeNode&& btn) {
    data = btn.data;
    btn.data = nullptr;

    subNodes = btn.subNodes;
    btn.subNodes = nullptr;
}






template <typename key_t, typename data_t>
class BTree {
  private:
    
    BTreeNode<data_t> head = BTreeNode<data_t>{};

    
    unsigned numNodes = 0;

    
    const BTreeNode<data_t>* iterate(const key_t* k) const;

    
    BTreeNode<data_t>* iterate(const key_t* k, bool createNodes);

  public:
    
    constexpr
    BTree();

    
    BTree(const BTree& tree);

    
    BTree(BTree&& tree);

    
    ~BTree() {
    }

    
    BTree& operator=(const BTree& tree);

    
    BTree& operator=(BTree&& tree);

    
    const data_t& operator[](const key_t& k) const;

    
    data_t& operator[](const key_t& k);

    
    void emplace(const key_t& k, data_t&& d);

    
    void push(const key_t& k, const data_t& d);

    
    void pop(const key_t& k);

    
    bool contains(const key_t& k) const;

    
    const data_t& at(const key_t& k) const;

    
    data_t& at(const key_t& k);

    
    inline
    unsigned size() const;

    
    void clear();
};



template <typename key_t, typename data_t>
constexpr BTree<key_t, data_t>::BTree()
    :
    head{},
numNodes{0}
{
}


template <typename key_t, typename data_t>
BTree<key_t, data_t>::BTree(const BTree& bt)
    :
    head{bt.head},
numNodes{bt.numNodes}
{
}


template <typename key_t, typename data_t>
BTree<key_t, data_t>::BTree(BTree&& bt) {
    head.subNodes = bt.head.subNodes;
    bt.head.subNodes = nullptr;

    numNodes = bt.numNodes;
    bt.numNodes = 0;
}


template <typename key_t, typename data_t>
BTree<key_t, data_t>& BTree<key_t, data_t>::operator=(const BTree& bt) {
    head = bt.head;
    numNodes = bt.numNodes;
    return *this;
}


template <typename key_t, typename data_t>
BTree<key_t, data_t>& BTree<key_t, data_t>::operator=(BTree&& bt) {
    head.subNodes = bt.head.subNodes;
    bt.head.subNodes = nullptr;

    numNodes = bt.numNodes;
    bt.numNodes = 0;

    return *this;
}


template <typename key_t, typename data_t>
const BTreeNode<data_t>* BTree<key_t, data_t>::iterate(const key_t* k) const {
    unsigned bytePos = 0;
    const BTreeNode<data_t>* bNodeIter = &head;
    const utils::BitMask* byteIter = nullptr;

    while ((byteIter = ls::utils::get_byte<key_t>(k, bytePos++))) {
        for (unsigned currBit = LS_BITS_PER_BYTE; currBit--;) {
            
            if (!bNodeIter->subNodes) {
                return nullptr;
            }

            
            const int dir = byteIter->get(currBit);
            bNodeIter = &(bNodeIter->subNodes[dir]);
        }
    }

    return bNodeIter;
}


template <typename key_t, typename data_t>
BTreeNode<data_t>* BTree<key_t, data_t>::iterate(const key_t* k, bool createNodes) {
    unsigned bytePos = 0;
    BTreeNode<data_t>* bNodeIter = &head;
    const utils::BitMask* byteIter = nullptr;

    while ((byteIter = ls::utils::get_byte<key_t>(k, bytePos++))) {
        for (unsigned currBit = LS_BITS_PER_BYTE; currBit--;) {
            
            if (!bNodeIter->subNodes) {
                if (createNodes) {
                    
                    bNodeIter->subNodes = new BTreeNode<data_t>[BNODE_MAX];
                }
                else {
                    return nullptr;
                }
            }

            
            const int dir = byteIter->get(currBit);
            bNodeIter = &(bNodeIter->subNodes[dir]);
        }
    }

    return bNodeIter;
}


template <typename key_t, typename data_t>
void BTree<key_t, data_t>::clear() {
    delete head.data;
    delete [] head.subNodes;

    head.data = nullptr;
    head.subNodes = nullptr;
    numNodes = 0;
}


template <typename key_t, typename data_t>
const data_t& BTree<key_t, data_t>::operator[](const key_t& k) const {
    const BTreeNode<data_t> * const iter = iterate(&k);

    if (!iter || !iter->data) {
        throw ls::utils::error_t::LS_ERROR;
    }

    return *iter->data;
}


template <typename key_t, typename data_t>
data_t& BTree<key_t, data_t>::operator[](const key_t& k) {
    BTreeNode<data_t> * const iter = iterate(&k, true);

    if (!iter->data) {
        iter->data = new data_t{};
        ++numNodes;
    }

    return *iter->data;
}


template <typename key_t, typename data_t>
void BTree<key_t, data_t>::emplace(const key_t& k, data_t&& d) {
    BTreeNode<data_t> * const iter = iterate(&k, true);

    if (!iter->data) {
        iter->data = new data_t{std::move(d)};
        ++numNodes;
    }
    else {
        *iter->data = std::move(d);
    }
}


template <typename key_t, typename data_t>
void BTree<key_t, data_t>::push(const key_t& k, const data_t& d) {
    BTreeNode<data_t> * const iter = iterate(&k, true);

    if (!iter->data) {
        iter->data = new data_t{d};
        ++numNodes;
    }
    else {
        *iter->data = d;
    }
}


template <typename key_t, typename data_t>
void BTree<key_t, data_t>::pop(const key_t& k) {
    BTreeNode<data_t> * const iter = iterate(&k, false);

    if (!iter || !iter->data) {
        return;
    }

    delete iter->data;

    iter->data = nullptr;

    --numNodes;
}


template <typename key_t, typename data_t>
bool BTree<key_t, data_t>::contains(const key_t& k) const {
    const BTreeNode<data_t> * const iter = iterate(&k);
    return iter && iter->data;
}


template <typename key_t, typename data_t>
const data_t& BTree<key_t, data_t>::at(const key_t& k) const {
    const BTreeNode<data_t> * const iter = iterate(&k);

    if (!iter || !iter->data) {
        throw ls::utils::error_t::LS_ERROR;
    }

    return *iter->data;
}


template <typename key_t, typename data_t>
inline
unsigned BTree<key_t, data_t>::size() const {
    return numNodes;
}


template <typename key_t, typename data_t>
data_t& BTree<key_t, data_t>::at(const key_t& k) {
    BTreeNode<data_t> * const iter = iterate(&k, false);

    if (!iter || !iter->data) {
        throw ls::utils::error_t::LS_ERROR;
    }

    return *iter->data;
}

} 
} 

#endif  
