#include <algorithm>
#include <utility>

template<class ValueType>
class Set {
 private:
    struct node {
        const ValueType key;
        node* l;
        node* r;
        node* parent;
        node* next;
        node* prev;
        bool flag;
        node(ValueType value = ValueType()) : key(value), l(nullptr), r(nullptr), parent(nullptr),
                                              next(nullptr), prev(nullptr), flag(false) {}
    };

    size_t t_size;
    mutable node* root;
    mutable node* mx_node;
    mutable node* mn_node;
    mutable node* end_node;

 public:
    struct iterator {
        node* me;
        iterator(node* new_node = nullptr) : me(new_node) {}

        const ValueType operator *() const {
            return me->key;
        }

        const ValueType* operator ->() const {
            return &(me->key);
        }

        iterator& operator ++() {
            me = me->next;
            return *this;
        }

        iterator& operator --() {
            me = me->prev;
            return *this;
        }

        iterator operator ++(int) {
            iterator tmp = iterator(me);
            me = me->next;
            return tmp;
        }

        iterator operator --(int) {
            iterator tmp = iterator(me);
            me = me->prev;
            return tmp;
        }

        bool operator ==(const iterator it) const {
            return me == it.me || (me->flag && it.me->flag);
        }

        bool operator !=(const iterator it) const {
            return !(*this == it);
        }
    };

    mutable iterator begin_, end_;

    Set() : t_size(0), root(nullptr), mx_node(nullptr), mn_node(nullptr) {
        end_node = new node();
        end_node->flag = true;
    }

    template<typename It>
    Set(It first, It last) : Set() {
        while (first != last) {
            insert(*first);
            ++first;
        }
    }

    Set(std::initializer_list<ValueType> elements) : Set() {
        for (auto& x : elements) {
            insert(x);
        }
    }

    bool eq(const ValueType& first, const ValueType& second) const {
        return !(first < second) && !(second < first);
    }

    size_t size() const {
        return t_size;
    }

    bool empty() const {
        return t_size == 0;
    }

    void update() const {
        end_node->prev = mx_node;
        if (mx_node != nullptr) {
            mx_node->next = end_node;
        }
        end_ = iterator(end_node);
        begin_ = iterator(mn_node);
    }

    bool l_child(node* vertex) const {
        return vertex == vertex->parent->l;
    }

    node* R_Rotate(node* p) const {
        node* t = p->l;
        node* b = t->r;
        node* d = p->parent;
        if (d != nullptr) {
            if (d->r == p) {
                d->r = t;
            } else {
                d->l = t;
            }
        }
        if (b != nullptr) {
            b->parent = p;
        }
        t->parent = d;
        t->r = p;
        p->parent = t;
        p->l = b;
        return t;
    }

    node* L_Rotate(node* p) const {
        node* t = p->r;
        node* b = t->l;
        node* d = p->parent;
        if (d != nullptr) {
            if (d->r == p) {
                d->r = t;
            } else {
                d->l = t;
            }
        }
        if (b != nullptr) {
            b->parent = p;
        }
        t->parent = d;
        t->l = p;
        p->parent = t;
        p->r = b;
        return t;
    }

    node* zig(node* x, node* p) const {
        if (l_child(x)) {
            return R_Rotate(p);
        } else {
            return L_Rotate(p);
        }
    }

    node* zig_zig(node* x, node* p) const {
        p = zig(p, p->parent);
        return zig(x, p);
    }

    node* zig_zag(node* x, node* p) const {
        x = zig(x, p);
        return zig(x, x->parent);
    }

    node* splay(node* cur) const {
        while (cur != nullptr && cur->parent != nullptr) {
            if (cur->parent->parent == nullptr) {
                cur = zig(cur, cur->parent);
                continue;
            }
            if (l_child(cur) == l_child(cur->parent)) {
                cur = zig_zig(cur, cur->parent);
            } else {
                cur = zig_zag(cur, cur->parent);
            }
        }
        return cur;
    }

    void insert(const ValueType& key) {
        if (root == nullptr) {
            root = new node(key);
            mn_node = root;
            mx_node = root;
            update();
            ++t_size;
            return;
        }
        node* last = nullptr;
        node* lastLeft = nullptr;
        node* lastRight = nullptr;
        while (root != nullptr) {
            last = root;
            if (eq(root->key, key)) {
                root = splay(root);
                return;
            }
            if (key < root->key) {
                lastLeft = root;
                root = root->l;
            } else {
                lastRight = root;
                root = root->r;
            }
        }
        if (key < last->key) {
            last->l = new node(key);
            last->l->parent = last;
            root = last->l;
        } else {
            last->r = new node(key);
            last->r->parent = last;
            root = last->r;
        }
        root->next = lastLeft;
        root->prev = lastRight;
        if (root->next != nullptr) {
            root->next->prev = root;
        }
        if (root->prev != nullptr) {
            root->prev->next = root;
        }
        ++t_size;
        root = splay(root);
        if (root->next == nullptr) {
            mx_node = root;
        }
        if (root->prev == nullptr) {
            mn_node = root;
        }
        update();
    }

    void erase(const ValueType& key) {
        if (root == nullptr) {
            return;
        }
        node* last = nullptr;
        while (root != nullptr) {
            last = root;
            if (eq(root->key, key)) {
                --t_size;
                break;
            }
            if (key < root->key) {
                root = root->l;
            } else {
                root = root->r;
            }
        }
        if (root == nullptr) {
            root = splay(last);
            return;
        }
        root = splay(root);

        if (root->l != nullptr) {
            root->l->parent = nullptr;
        }
        if (root->r != nullptr) {
            root->r->parent = nullptr;
        }

        root->next->prev = root->prev;
        if (root->prev != nullptr) {
            root->prev->next = root->next;
        }
        node* was_root = root;
        if (root->next == end_node) {
            mx_node = root->prev;
        }
        if (root->prev == nullptr) {
            mn_node = root->next;
        }
        root = merge(root->l, root->r);
        delete was_root;
        update();
    }

    node* merge(node* tl, node* tr) const {
        if (tl == nullptr) {
            return tr;
        }
        if (tr == nullptr) {
            return tl;
        }
        while (tl->r != nullptr) {
            tl = tl->r;
        }
        tl = splay(tl);
        tr->parent = tl;
        tl->r = tr;
        return tl;
    }

    iterator begin() const {
        update();
        if (empty()) {
            return end_;
        }
        return begin_;
    }

    iterator end() const {
        update();
        return end_;
    }

    iterator find(const ValueType& key) const {
        node* last = nullptr;
        while (root != nullptr) {
            last = root;
            if (eq(root->key, key)) {
                root = splay(root);
                return iterator(root);
            }
            if (key < root->key) {
                root = root->l;
            } else {
                root = root->r;
            }
        }
        if (last != nullptr) {
            root = splay(last);
        }
        return end();
    }

    iterator lower_bound(const ValueType& key) const {
        node* last = nullptr;
        node* res = nullptr;
        auto found = find(key);
        if (found != end()) {
            return found;
        }
        while (root != nullptr) {
            last = root;
            if (key < root->key) {
                res = root;
                root = root->l;
            } else {
                root = root->r;
            }
        }
        if (res != nullptr) {
            root = splay(res);
            return iterator(root);
        }
        if (last != nullptr) {
            root = splay(last);
        }
        return end();
    }
    ~Set() {
        while (end_node != nullptr) {
            node* next = end_node->prev;
            delete(end_node);
            end_node = nullptr;
            end_node = next;
        }
    }

    void swap(Set& other) throw() {
        std::swap(t_size, other.t_size);
        std::swap(root, other.root);
        std::swap(mn_node, other.mn_node);
        std::swap(mx_node, other.mx_node);
        std::swap(end_node, other.end_node);
        std::swap(end_, other.end_);
        std::swap(begin_, begin_);
    }

    Set& operator =(const Set& other) {
        Set temp(other);
        temp.swap(*this);
        return *this;
    }

    Set(const Set& other) : Set() {
        node* cur = other.end_node;
        cur = cur->prev;
        while (cur != nullptr) {
            insert(cur->key);
            cur = cur->prev;
        }
    }
};
