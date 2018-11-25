#ifndef CPP_B_TREE_H
#define CPP_B_TREE_H

#include <list>
#include <iostream>
#include <stdexcept>

#define B_TREE_ORDER 3

template<typename K, typename V>
class b_tree
{
public:
    b_tree()
    {
        root = new b_tree_node{nullptr};
    }

    b_tree(b_tree &&rhs) : root{rhs.root}
    {
        rhs.root = nullptr;
    }

    ~b_tree()
    {
        dispose();
    }

    b_tree &operator=(b_tree &&rhs)
    {
        std::swap(root, rhs.root);
        return *this;
    }

    bool is_empty() const
    {
        return root->size == 0;
    }

    const K &find_min_key() const
    {
        if (is_empty())
            throw std::underflow_error("empty tree!");
        return find_min_cell(root)->key;
    }

    const K &find_max_key() const
    {
        if (is_empty())
            throw std::underflow_error("empty tree!");
        return find_max_cell(root)->key;
    }

    const V *find_min_value() const
    {
        if (is_empty())
            return nullptr;
        return &(find_min_cell(root)->value);
    }

    const V *find_max_value() const
    {
        if (is_empty())
            return nullptr;
        return &(find_max_cell(root)->value);
    }

    bool has(const K &key)
    {
        return search_cell(root, key) != nullptr;
    }

    const V *get(const K &key)
    {
        b_tree_cell *r = search_cell(root, key);
        if (r == nullptr)
            return nullptr;
        return &(r->value);
    }

    void insert(const K &key, const V &value)
    {
        insert_cell(new b_tree_cell{key, value});
    }

    void insert(K &&key, V &&value)
    {
        insert_cell(new b_tree_cell{std::move(key), std::move(value)});
    }

    bool is_valid()
    {
        return check_node(root);
    }

    void remove(const K &key)
    {
        if (!is_empty()) {
            remove(root, key);
        }
    }

    void dispose()
    {
        dispose_node(root);
    }

private:
    struct b_tree_cell;

    struct b_tree_node
    {
        b_tree_node *pnode;
        b_tree_cell *pcell;

        b_tree_cell *header;
        b_tree_cell *tail;
        int size;

        b_tree_node(b_tree_node *pn = nullptr, b_tree_cell *pc = nullptr)
                : pnode{pn}, pcell{pc}, header{nullptr}, tail{nullptr}, size{0} { }

        void insert_after(b_tree_cell *pos, b_tree_cell *n)
        {
            if (n == nullptr) {
                return;
            }
            if (pos == nullptr) {
                header = tail = n;
                n->previous = n->next = nullptr;
            } else {
                n->set_next(pos->next);
                pos->set_next(n);
                if (pos == tail) {
                    tail = n;
                }
            }
            size++;
        }

        void insert_before(b_tree_cell *pos, b_tree_cell *n)
        {
            if (n == nullptr) {
                return;
            }
            if (pos == nullptr) {
                header = tail = n;
                n->previous = n->next = nullptr;
            } else {
                n->set_previous(pos->previous);
                pos->set_previous(n);
                if (pos == header) {
                    header = n;
                }
            }
            size++;
        }

        void push_back(b_tree_cell *n)
        {
            insert_after(tail, n);
        }

        void push_front(b_tree_cell *n)
        {
            insert_before(header, n);
        }

        void erase(b_tree_cell *n)
        {
            if (n == nullptr) {
                return;
            }
            if (n->previous != nullptr) {
                n->previous->next = n->next;
            }
            if (n->next != nullptr) {
                n->next->previous = n->previous;
            }
            if (header == n) {
                header = n->next;
            }
            if (tail == n) {
                tail = n->previous;
            }
            if (n->child != nullptr) {
                delete n->child;
            }
            delete n;
            size--;
        }

        b_tree_cell *pop_back()
        {
            if (tail == nullptr) {
                return nullptr;
            }
            b_tree_cell *old_tail = tail;
            if (header == tail) {
                header = tail = nullptr;
            } else {
                tail->previous->next = nullptr;
                tail = tail->previous;
            }
            size--;
            old_tail->previous = nullptr;
            return old_tail;
        }
    };

    struct b_tree_cell
    {
        K key;
        V value;
        b_tree_node *child;
        b_tree_cell *next;
        b_tree_cell *previous;

        b_tree_cell(const K &k)
                : key{k}, child{nullptr}, next{nullptr}, previous{nullptr} { }

        b_tree_cell(K &&k)
                : key{std::move(k)}, child{nullptr}, next{nullptr}, previous{nullptr} { }

        b_tree_cell(const K &k, const V &v)
                : key{k}, value{v}, child{nullptr}, next{nullptr}, previous{nullptr} { }

        b_tree_cell(K &&k, V &&v)
                : key{std::move(k)}, value{std::move(v)}, child{nullptr}, next{nullptr}, previous{nullptr} { }

        void set_next(b_tree_cell *n)
        {
            next = n;
            if (next != nullptr) {
                next->previous = this;
            }
        }

        void set_previous(b_tree_cell *n)
        {
            previous = n;
            if (previous != nullptr) {
                previous->next = this;
            }
        }
    };

    b_tree_node *root;

    void merge_node(b_tree_node *n1, b_tree_node *n2)
    {
        if (n1 && n2) {
            n1->tail->set_next(n2->header);
            n1->tail = n2->tail;
            n1->size += n2->size;
            b_tree_cell *itr = n2->header;
            while (itr) {
                if (itr->child != nullptr) {
                    itr->child->pnode = n1;
                }
                itr = itr->next;
            }
            remove_cell_from_node(n2->pnode, n2->pcell);
        }
    }

    void split_node(b_tree_node *n)
    {
        if (n != nullptr && n->size > B_TREE_ORDER) {
            if (n->pnode == nullptr) {
                n->pnode = new b_tree_node;
                n->pcell = new b_tree_cell{n->header->key};
                n->pcell->child = n;
                insert_cell_to_node(n->pnode, n->pcell);
                root = n->pnode;
            }
            b_tree_node *m = new b_tree_node(n->pnode);
            while (n->size > (B_TREE_ORDER + 1) / 2) {
                b_tree_cell *cell = n->pop_back();
                if (cell->child) {
                    cell->child->pnode = m;
                }
                m->push_front(cell);
            }
            m->pcell = new b_tree_cell{m->header->key};
            m->pcell->child = m;
            insert_cell_to_node(m->pnode, m->pcell);
        }
    }

    void dispose_node(b_tree_node *n)
    {
        if (n != nullptr) {
            b_tree_cell *p = n->header;
            b_tree_cell *q;
            while (p != nullptr) {
                q = p;
                if (p->child) {
                    dispose_node(p->child);
                }
                p = p->next;
                delete q;
            }
            delete n;
        }
    }

    void refresh_index_upwards(b_tree_node *p)
    {
        while (p && p->pcell && p->header) {
            p->pcell->key = p->header->key;
            p = p->pnode;
        }
    }

    void insert_cell(b_tree_cell *cell)
    {
        b_tree_node *p = root;
        while (p && p->header && p->header->child) {
            b_tree_cell *itr = p->header;
            while (itr->next && cell->key >= itr->next->key) {
                itr = itr->next;
            }
            p = itr->child;
        }
        insert_cell_to_node(p, cell);
    }

    void insert_cell_to_node(b_tree_node *n, b_tree_cell *cell)
    {
        if (n != nullptr && cell != nullptr) {
            if (n->header == nullptr || cell->key < n->header->key) {
                n->push_front(cell);
                refresh_index_upwards(n);
            } else {
                b_tree_cell *itr = n->header;
                while (itr->next && cell->key >= itr->next->key) {
                    itr = itr->next;
                }
                if (cell->key == itr->key) {
                    std::swap(itr->value, cell->value);
                    delete cell;
                } else {
                    n->insert_after(itr, cell);
                }
            }
            split_node(n);
        }
    }

    b_tree_cell *search_cell(b_tree_node *n, const K &key)
    {
        b_tree_cell *itr;
        while (n && n->header && n->header->child) {
            itr = n->header;
            while (itr->next && key >= itr->next->key) {
                itr = itr->next;
            }
            n = itr->child;
        }
        if (n && n->header) {
            itr = n->header;
            while (itr->next && key >= itr->next->key) {
                itr = itr->next;
            }
            if (key == itr->key) {
                return itr;
            }
        }
        return nullptr;
    }

    b_tree_cell *find_min_cell(b_tree_node *n) const
    {
        if (n == nullptr) {
            return nullptr;
        }
        while (n->header && n->header->child) {
            n = n->header->child;
        }
        return n->header;
    }

    b_tree_cell *find_max_cell(b_tree_node *n) const
    {
        if (n == nullptr) {
            return nullptr;
        }
        while (n->tail && n->tail->child) {
            n = n->tail->child;
        }
        return n->tail;
    }

    void remove(b_tree_node *n, const K &key)
    {
        b_tree_cell *itr;
        while (n && n->header && n->header->child) {
            itr = n->header;
            while (itr->next && key >= itr->next->key) {
                itr = itr->next;
            }
            n = itr->child;
        }
        if (n && n->header) {
            itr = n->header;
            while (itr->next && key >= itr->next->key) {
                itr = itr->next;
            }
            if (key == itr->key) {
                remove_cell_from_node(n, itr);
            }
        }
    }

    void remove_cell_from_node(b_tree_node *n, b_tree_cell *cell)
    {
        if (n != nullptr && cell != nullptr) {
            b_tree_cell *old_header = n->header;
            n->erase(cell);
            if (old_header != n->header) {
                refresh_index_upwards(n);
            }
            if (n->size < (B_TREE_ORDER + 1) / 2 && n->pcell) {
                b_tree_node *target;
                if (n->pcell->next != nullptr) {
                    target = n;
                    merge_node(target, n->pcell->next->child);
                    split_node(target);
                } else if (n->pcell->previous != nullptr) {
                    target = n->pcell->previous->child;
                    merge_node(target, n);
                    split_node(target);
                }
            }
            while (root->size == 1 && root->header->child) {
                b_tree_node *t = root;
                root = root->header->child;
                root->pcell = nullptr;
                root->pnode = nullptr;
                delete t->header;
                delete t;
            }
        }
    }

    bool check_node(b_tree_node *n)
    {
        b_tree_cell *it = n->header;
        int count = 0;
        while (it != nullptr) {
            if (it->next && it->key > it->next->key) {
                return false;
            }
            if (it->child && it->child->pnode != n) {
                return false;
            }
            if (!check_cell(it)) {
                return false;
            }
            count++;
            it = it->next;
        }
        return n->size == count && n->size <= B_TREE_ORDER && (root == n || n->size >= (B_TREE_ORDER + 1) / 2);
    }

    bool check_cell(b_tree_cell *cell)
    {
        if (cell == nullptr) {
            return false;
        }
        if (cell->child == nullptr) {
            return true;
        }
        if (cell->child->pcell != cell) {
            return false;
        }
        if (cell->child->header == nullptr || cell->child->header->key != cell->key) {
            return false;
        }
        return check_node(cell->child);
    }

private:
    b_tree(const b_tree &rhs) : root{nullptr}
    {
    }

    b_tree &operator=(const b_tree &rhs)
    {
        b_tree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
};

#endif 
