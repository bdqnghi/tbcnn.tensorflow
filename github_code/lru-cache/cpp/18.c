#include "lru_cache.h"
#include <iostream>
#include <cassert>



lru_cache::node::node() : node(std::make_pair(INT_MAX, "Undef")) {}
lru_cache::node::node(value_type x) : key(x.first), mapped(x.second), left(nullptr), right(nullptr), parent(nullptr), prev(nullptr), next(nullptr) {}
lru_cache::node::node(const node& other) : key(other.key), mapped(other.mapped), left(other.left), right(other.right), parent(other.parent), next(other.next), prev(other.prev) {}
lru_cache::node::~node() {}

void swap(lru_cache::node &a, lru_cache::node &b) {
    std::swap(a.key, b.key);
    std::swap(a.mapped, b.mapped);
    std::swap(a.left, b.left);
    std::swap(a.right, b.right);
    std::swap(a.parent, b.parent);
    std::swap(a.next, b.next);
    std::swap(a.prev, b.prev);
}

lru_cache::node* lru_cache::node::next_tree_node() {
    node *tmp = this;
    if (tmp->right) {
        tmp = tmp->right;
        while (tmp->left) {
            tmp = tmp->left;
        }
        return tmp;
    }
    while (tmp->parent && tmp == tmp->parent->right) {
        tmp = tmp->parent;
    }
    return tmp->parent;
}
lru_cache::node* lru_cache::node::prev_tree_node() {
    node *tmp = this;
    if (tmp->left) {
        tmp = tmp->left;
        while (tmp->right) {
            tmp = tmp->right;
        }
        return tmp;
    }
    while (tmp->parent && tmp == tmp->parent->left) {
        tmp = tmp->parent;
    }
    return tmp->parent;
}

void lru_cache::node::erase_tree() {
    if (left) {
        left->erase_tree();
        delete left;
    }
    if (right) {
        right->erase_tree();
        delete right;
    }
}

lru_cache::node * lru_cache::node::find(key_type _key) {
    if (_key < key && left) {
        return left->find(_key);
    } else if (_key> key && right) {
        return right->find(_key);
    } else {
        return this;
    }
}


lru_cache::iterator::iterator() : cur(nullptr) {}
lru_cache::iterator::iterator(const iterator& other) : cur(other.cur) {}
lru_cache::iterator::iterator(node* other) : cur(other) {}
lru_cache::iterator::~iterator() {}


bool lru_cache::iterator::operator==(iterator other) const {
    return cur == other.cur;
}
bool lru_cache::iterator::operator!=(iterator other) const {
    return !(cur == other.cur);
}
lru_cache::value_type lru_cache::iterator::operator*() const {
    return std::make_pair(cur->key, cur->mapped);
}

lru_cache::iterator& lru_cache::iterator::operator++() {
    cur = cur->next_tree_node();
    return *this;
}
lru_cache::iterator lru_cache::iterator::operator++(int) {
    auto it = *this;
    ++*this;
    return it;
}
lru_cache::iterator& lru_cache::iterator::operator--() {
    cur = cur->prev_tree_node();
    return *this;
}
lru_cache::iterator lru_cache::iterator::operator--(int) {
    auto it = *this;
    --*this;
    return it;
}

void lru_cache::iterator::next() {
    if (cur)
        cur = cur->next;
}

lru_cache::lru_cache(size_t capacity) : f_root(new node()), capacity(capacity), size(0)
{
    iterator_begin = iterator_end = iterator(f_root);
}

lru_cache::~lru_cache() {
    f_root->erase_tree();
    delete f_root;
}

lru_cache::iterator lru_cache::find(key_type x) {
    auto q = f_root->find(x);
    return (q->key != x ? iterator_end : q);
}

void lru_cache::node::delete_node() {
    node *cur = nullptr;
    if (left) {
        cur = left;
        while (cur->right) {
            cur = cur->right;
        }
        cur->right = right;
        if (right)
            right->parent = cur;
        left->parent = parent;
        cur = left;
    } else if (right) {
        right->parent = parent;
        cur = right;
    }
    if (parent)
        (parent->left == this ? parent->left : parent->right) = cur;
}

void lru_cache::node::erase() {
    if (next) next->prev = prev;
    if (prev) prev->next = next;
    delete_node();
}

void lru_cache::node::insert(node* x) {
    if (key < x->key) {
        if (right)
            right->insert(x);
        else {
            right = x;
            x->parent = this;
            x->left = x->right = nullptr;
        }
    } else {
        if (left)
            left->insert(x);
        else {
            left = x;
            x->parent = this;
            x->left = x->right = nullptr;
        }
    }
}

std::pair<lru_cache::iterator, bool> lru_cache::insert(value_type x) {
    auto it = find(x.first);
    node *cur_node;
    if (it != end()) {
        return std::make_pair(it, false);
    } else if (size == capacity) {
        cur_node = list_begin.cur;
        list_begin.cur = list_begin.cur->next;
        if (cur_node == iterator_begin.cur) {
            ++iterator_begin;
        }
        cur_node->delete_node();
        cur_node->key = x.first;
        cur_node->mapped = x.second;
        
    } else {
        cur_node = new node(x);
        if (size == 0) {
            iterator_begin.cur = cur_node;
            list_begin.cur = cur_node;
        }
        size++;
    }
    f_root->insert(cur_node);
    if (cur_node->key < iterator_begin.cur->key) {
        --iterator_begin;
    }
    cur_node->prev = iterator_end.cur->prev;
    cur_node->next = iterator_end.cur;
    if (iterator_end.cur->prev)
        iterator_end.cur->prev->next = cur_node;
    iterator_end.cur->prev = cur_node;
    return std::make_pair(iterator(cur_node), true);
}


void lru_cache::erase(lru_cache::iterator it) {
    if (it == end())
        return;
    if (it == begin()) {
        iterator_begin++;
        list_begin.next();
    }
    it.cur->erase();
    delete it.cur;
    size--;
}

lru_cache::iterator lru_cache::begin() const {
    return iterator_begin;
}
lru_cache::iterator lru_cache::end() const {
    return iterator_end;
}


int main() {
    {
        lru_cache a(20);
        for (int i = 0; i < 20; i++)
            a.insert({rand() % 50, "12332"});
        for (auto x : a)
            std::cout << x.first << ' ' << x.second << "\n";
        for (int i = 0; i < 10; i++) {
            auto it = a.begin();
            int x = rand() % (a.size - 1);
            while (x--) it++;
            std::cout << "size="<< a.size << "\n";
            std::cout << it.cur->key << " erased\n";
assert(a.find(it.cur->key) == it);
//            a.erase(it);
//
//        }
//        for (auto x : a)
//            std::cout << x.first << ' ' << x.second << "\n";
//    }
//    {
//
//    }
//
//
//    it = a.begin();
//        std::cout << (*it).first << ' ' << (*it).second << "\n";
//        assert(a.f_root == a.end().cur);
//        std::cout << (*it).first << ' ' << (*it).second << "\n";
//        it++;
//        std::cout << (*it).first << ' ' << (*it).second << "\n";
//        it++;
//        std::cout << (*it).first << ' ' << (*it).second << "\n";
//
//          for (auto x : a) {
//        }
//    a.insert(std::make_pair (3,"a"));
//    /*for (auto it : a)
//     std::cout << (it).first << ' ' << (it).second << '\n';
//     std::pair<lru_cache::iterator, bool> itt =  a.insert(std::make_pair (2,"b"));
//     std::cout<< (itt.second==false) << "\n";
//     std::cout << " " << itt.second<<"\n";
//     for (auto x : a)*/
//    std::cout << x.first << ' ' << x.second << "\n";
//    /*a.insert(std::make_pair (2,"b"));
//     lru_cache::iterator it = a.begin();
//     lru_cache::iterator last = a.end();
//     last--;
//     std::cout<<(*last).first<< " " <<(*last).second;
//     std::cout<<"1234";*/
//
//
//
//}