//
// Created by Big Z on 03.10.2015.
//

#include "lru_cache.h"

typedef lru_cache::Node *point;

lru_cache::lru_cache(size_t capacity) {
    __size = 0;
    __cap = capacity;
    root = nullptr;
    __first = nullptr;
    //__empty.resize(capacity);
    //lru_cache::Node tmp[capacity];
    for (size_t i=0;i<__cap;i++){
        key_type t;
        __empty.push_back(&t);
    }
}

lru_cache::lru_cache(const lru_cache &cache) {
    __size = cache.__size;
    __cap = cache.__cap;
    root = *(new point(cache.root));
    __first = *(new point(cache.__first));
    __empty.resize(__cap);

}

lru_cache &lru_cache::operator=(const lru_cache &cache) {
    __size = cache.__size;
    __cap = cache.__cap;
    root = cache.root;
    root = *(new point(cache.root));
    __first = *(new point(cache.__first));
    __empty.resize(__cap);
    return *this;
}

std::pair<bool, mapped_type &> lru_cache::lookup(const key_type &type) {
    std::pair<bool, std::pair<point,point>> t =__lookup(root, type);
    root = t.second.first;
    return std::pair<bool, mapped_type &>(t.first,t.second.second->i);
}

bool lru_cache::erase(const key_type &type) {
    std::pair<bool, point> t =__recerase(root, type);
    root = t.second;
    return t.first;
}

lru_cache::~lru_cache() {

}


void lru_cache::__copy(const lru_cache &cache) {

}

std::pair<bool, point> lru_cache::__recerase(lru_cache::point n, key_type const &x) {
    if (n == nullptr) {
        return std::make_pair(0, n);
    }
    std::pair<bool, point> ret;
    if (x < n->i) {
        std::pair<bool, point> t = __recerase(n->l, x);
        ret.first = t.first;
        n = t.second;
    } else if (x > n->i) {
        std::pair<bool, point> t = __recerase(n->l, x);
        ret.first = t.first;
        n = t.second;
    } else if (n->l != nullptr && n->r != nullptr) {
        point t = __minimum(n->r);
        n->k = t->k;
        n->i = t->i;
        n->n = t->n;
        n->pr = t->pr;
        std::pair<bool, point> tmp = __recerase(n->r, t->k);
        ret.first = tmp.first;
        n->l = tmp.second;
    } else if (n->l != nullptr) {
        __empty.push_back(n);
        point t = *new point(n);
        if (n->pr != nullptr)
            n->pr->n = t->n;
        if (n->n != nullptr)
            n->n->pr = t->pr;
        n = n->l;
        ret.first = 1;
        __size--;
    } else if (n->r != nullptr) {
        __empty.push_back(n);
        point t = *new point(n);
        if (n->pr != nullptr)
            n->pr->n = t->n;
        if (n->n != nullptr)
            n->n->pr = t->pr;
        n = (n->r);
        __size--;
        ret.first = 1;
    } else n = nullptr;
    ret.second = n;
    return ret;
}

point lru_cache::__minimum(point n) {
    return ((n->l == nullptr) ? n : __minimum(n->l));
}

std::pair<bool, std::pair<point,point>> lru_cache::__lookup(point n, key_type const &x) {
    if (n == nullptr) {
        if (__size == __cap)
            __recerase(root, __first->k);
        else{
            __size++;
        }
        Node *t = __empty.back();
        __empty.pop_back();
        return std::make_pair(0,std::make_pair(t,t));
    }
    if (n->k == x){
        return std::make_pair(1,std::make_pair(n,n));
    }
    if (x < n->k){
        std::pair<bool, std::pair<point,point>> t = __lookup(n->l, x);
        return std::make_pair(t.first,std::make_pair(n->l = t.second.first,t.second.second));
    }else{
        std::pair<bool, std::pair<point,point>> t = __lookup(n->r, x);
        return std::make_pair(t.first,std::make_pair(n->r = t.second.first, t.second.first));
    }
}
