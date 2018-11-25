



#include "node.h"
#include <mutex>

#ifndef PROJECT_B_TREE_H
#define PROJECT_B_TREE_H

using std::mutex;
using std::lock_guard;

template<class KEY,class DATA>
class b_tree
{
    public:
        b_tree();
        b_tree(const b_tree<KEY,DATA> &obj);
        ~b_tree();
        DATA* sort() const;
        bool find(KEY const &key, DATA &to_return);
        int insert(const KEY& key, const DATA& data);
        int insert(const datum<KEY,DATA>& to_insert);
        std::ostream &display(std::ostream &out);
    private:
        node<KEY,DATA> *root;
        mutex t_lock;
        long total;
};

#include "b_tree.cpp"

#endif 

