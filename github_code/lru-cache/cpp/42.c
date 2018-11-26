//
//  lru.cpp
//  LRU-Cache
//
//  Created by Данил Шкарупин on 28.09.16.
//  Copyright © 2016 Данил Шкарупин. All rights reserved.
//

#include "lru.hpp"

lru_cache::lru_cache(size_t cap) : capacity(cap) {
    assert(cap > 0);
    root = new node();
    queBegin = root;
    size = 0;
}

lru_cache::~lru_cache() {
    node * a = root, *b = a;
    while (a -> prev != nullptr) {
        a = a -> prev;
        delete b;
        b = a;
    }
}

lru_cache::iterator lru_cache::find(lru_cache::key_type tofind) {
    node *a = dofind(tofind);
    return iterator(((a -> key == tofind && a != root) ? a : root), this);
}

lru_cache::node* lru_cache::dofind(lru_cache::key_type tofind) {
    if (root -> left == nullptr) return root;
    node* a = root -> left;
    
    while (true) {
        
        if (a -> key == tofind) break;
        
        if (a -> key > tofind) {
            if (a -> left == nullptr) {
                return a;
            } else {
                a = a -> left;
            }
        }
        if (a -> key < tofind) {
            if (a -> right == nullptr) {
                return a;
            } else {
                a = a -> right;
            }
        }
        
    }
    
    a -> next -> prev = a -> prev;
    if (a -> prev != nullptr) a -> prev -> next = a -> next;
    a -> prev = nullptr;
    a -> next = queBegin;
    a -> next -> prev = a;
    
    return a;
}


void lru_cache::removerefers(lru_cache::node* a) {
    bool parent;
    if (a -> parent -> left == a) parent = 0;
    else parent = 1;
    //Если нет детей -- всё хорошо
    if (a -> left == nullptr && a -> right == nullptr) {
        (parent == false ? a -> parent -> left: a -> parent -> right) = nullptr;
    }
    //Если два ребенка -- подвесить левого вместо current правого к самому большому ребенку левого
    else if (a -> left != nullptr && a -> right != nullptr) {
        (parent == false ? a -> parent -> left : a -> parent -> right) = a -> left;
        a -> left -> parent = a -> parent;
        
        node* trying = a -> left;
        while (trying -> right != nullptr) trying = trying -> right;
        
        trying -> right = a -> right;
        a -> right -> parent = trying;
    }
    //Если один ребенок -- подвесить вместо current
    else {
        (parent == false ? a -> parent -> left : a -> parent -> right) = (a -> left != nullptr ? a -> left : a -> right);
        (a -> left != nullptr ? a -> left : a -> right) -> parent = a -> parent;
    }

}

std::pair<lru_cache::iterator, bool> lru_cache::insert(lru_cache::value_type tofind) {
    node *a = dofind(tofind.first);
    if (a -> key == tofind.first && a != root) return std::pair<lru_cache::iterator, bool> (iterator(a, this), false);
    
    //if filled -- use old
    node *ins;
    if (size < capacity) {
        ins = new node();
        ++size;
    } else {
        //should erase and insert
        ins = root -> prev;
        if (ins == a) {
            if (a -> right != nullptr) {
                a = a -> right;
                while (a -> left != nullptr) a = a -> left;
            }
            else if (a -> left != nullptr) {
                a = a -> left;
                while (a -> right != nullptr) a = a -> right;
            }
        }
        removerefers(ins);
        if (ins -> prev != nullptr) ins -> prev -> next = ins -> next;
        if (ins -> next != nullptr) ins -> next -> prev = ins -> prev;
        ins -> prev = nullptr;
        ins -> left = nullptr;
        ins -> right = nullptr;
    }
    ins -> key = tofind.first;
    ins -> mapped = tofind.second;
    
    ins -> parent = a;
    
    ins -> next = queBegin;
    queBegin -> prev = ins;
    queBegin = ins;
    if (a -> key > tofind.first || a == root) {
        a -> left = ins;
    }
    else if (a -> key < tofind.first) {
        a -> right = ins;
    }
    
    return std::pair<lru_cache::iterator, bool> (iterator(ins, this), true);
}

// Удаление элемента.
// Все итераторы на указанный элемент инвалидируются.
void lru_cache::erase(lru_cache::iterator it) {
    if (it.belongs == this) {
        if (it.current -> parent != nullptr) {
            removerefers(it.current);
        
            if (it.current -> prev != nullptr) it.current -> prev -> next = it.current -> next;
            if (it.current -> next != nullptr) it.current -> next -> prev = it. current -> prev;
        
            --size;
            delete it.current;
        }
    }
}

// Возващает итератор на элемент с минимальный ключом.
lru_cache::iterator lru_cache::begin() const {
    node * a = root;
    while (a -> left != nullptr) a = a -> left;
    return iterator(a, this);
}
// Возващает итератор на элемент следующий за элементом с максимальным ключом.
lru_cache::iterator lru_cache::end() const {
    return iterator(root, this);
}

lru_cache::iterator::iterator(lru_cache::node* a, const lru_cache* cache) : current(a), belongs(cache) {}

lru_cache::mapped_type const& lru_cache::iterator::operator*() const {
    return current -> mapped;
}

lru_cache::iterator& lru_cache::iterator::operator++() {
    if (current -> right != nullptr) {
        current = current -> right;
        while (current -> left != nullptr) current = current -> left;
    } else {
        while ((current -> parent != nullptr) && (current -> parent -> right == current)) current = current -> parent;
        if (current -> parent != nullptr) current = current -> parent;
    }
    return *this;
}
lru_cache::iterator lru_cache::iterator::operator++(int) {
    iterator res(*this);
    ++(*this);
    return res;
}

lru_cache::iterator& lru_cache::iterator::operator--() {
    if (current -> left != nullptr) {
        current = current -> left;
        while (current -> right != nullptr) current = current -> right;
    } else {
        while ((current -> parent != nullptr) && (current -> parent -> left == current)) current = current -> parent;
        if (current -> parent != nullptr) current = current -> parent;
    }
    return *this;
}
lru_cache::iterator lru_cache::iterator::operator--(int) {
    iterator res(*this);
    --(*this);
    return res;
}
bool lru_cache::iterator::operator==(const iterator right) const {
    return (belongs == right.belongs ? current == right.current : false);
}
bool lru_cache::iterator::operator!=(const iterator right) const {
    return (belongs == right.belongs ? current != right.current : false);
}

using namespace std;

int main() {
    lru_cache a(500);
    int sch = 0;
    for (int i = 0; i < 10000; i++) {
        for (int j = -1000; j < 1000; j++) {
            a.insert(std::make_pair(j, j));
            sch++;
        }
    }
    cout << sch << endl;
    
    for (int i = 0; i < 1000; i++) {
        a.erase(a.begin());
    }
}
