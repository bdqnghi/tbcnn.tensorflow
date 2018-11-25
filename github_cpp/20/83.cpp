#ifndef CPP_RED_BLACK_TREE_H
#define CPP_RED_BLACK_TREE_H

#include "binary_search_tree.hpp"

template<typename K, typename V>
class red_black_tree : public binary_search_tree<K, V>
{
private:
    typedef binary_search_tree<K, V> bst;

    typedef struct binary_tree<K, V>::binary_node binary_node_K_V;

protected:
    enum color
    {
        RED, BLACK
    };

    struct red_black_node : binary_node_K_V
    {
        bool is_nil;

        color node_color;

        red_black_node *_parent()
        {
            return (red_black_node *) this->parent;
        }

        red_black_node *_grandparent()
        {
            return (red_black_node *) (this->parent == nullptr ? nullptr : this->parent->parent);
        }

        red_black_node *_sibling()
        {
            binary_node_K_V *p = this->parent;
            return (red_black_node *) ((p != nullptr) ? ((this == p->left) ? p->right : p->left) : nullptr);
        }

        red_black_node *_left()
        {
            return (red_black_node *) this->left;
        }

        red_black_node *_right()
        {
            return (red_black_node *) this->right;
        }

        red_black_node *_extend_left()
        {
            if (!this->left) {
                this->left = new red_black_node(this->key, this->value, BLACK, true, this);
            }
            return _left();
        }

        red_black_node *_extend_right()
        {
            if (!this->right) {
                this->right = new red_black_node(this->key, this->value, BLACK, true, this);
            }
            return _right();
        }

        red_black_node(const K &k, const V &v, color c, bool nil = false, binary_node_K_V *p = nullptr,
                       binary_node_K_V *lt = nullptr, binary_node_K_V *rt = nullptr)
                : binary_node_K_V{k, v, p, lt, rt}, node_color{c}, is_nil{nil} { }

        red_black_node(K &&k, V &&v, color c, bool nil = false, binary_node_K_V *p = nullptr,
                       binary_node_K_V *lt = nullptr, binary_node_K_V *rt = nullptr)
                : binary_node_K_V{std::move(k), std::move(v), p, lt, rt}, node_color{c}, is_nil{nil} { }
    };

public:
    red_black_tree()
    {
        this->root = nullptr;
    }

    red_black_tree(const red_black_tree &rhs)
    {
        this->root = clone(rhs.root, nullptr);
    }

    red_black_tree(red_black_tree &&rhs)
    {
        this->root = rhs.root;
        rhs.root = nullptr;
    }

    ~red_black_tree()
    {
        bst::dispose();
    }

    red_black_tree &operator=(const red_black_tree &rhs)
    {
        red_black_tree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    red_black_tree &operator=(red_black_tree &&rhs)
    {
        std::swap(this->root, rhs.root);
        return *this;
    }

    virtual bool insert(const K &k, const V &v) override
    {
        return insert_node(new red_black_node{k, v, RED});
    }

    virtual bool insert(K &&k, V &&v) override
    {
        return insert_node(new red_black_node{std::move(k), std::move(v), RED});
    }

    bool is_valid()
    {
        return black_height((red_black_node *) this->root) > 0;
    }

protected:
    virtual binary_node_K_V *clone(binary_node_K_V *t, binary_node_K_V *p) const override
    {
        if (t == nullptr)
            return nullptr;
        else {
            red_black_node *n = new red_black_node{t->key, t->value, ((red_black_node *) t)->node_color,
                                                   ((red_black_node *) t)->is_nil, p};
            n->left = clone(t->left, n);
            n->right = clone(t->right, n);
            return n;
        }
    }

    virtual bool insert_node(binary_node_K_V *n) override
    {
        bool result = bst::insert_node(n);
        if (result) {
            insert_fixup((red_black_node *) n);
        }
        return result;
    }

    virtual bool remove_node(binary_node_K_V *n) override
    {
        red_black_node *z = (red_black_node *) n;
        if (z == nullptr) {
            return false;
        }
        if (this->root == z && z->left == nullptr && z->right == nullptr) {
            delete z;
            this->root = nullptr;
            return true;
        }
        red_black_node *x;
        color lost_color = z->node_color;
        if (z->left == nullptr) {
            x = z->_extend_right();
            bst::transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->_extend_left();
            bst::transplant(z, z->left);
        } else {
            red_black_node *y = (red_black_node *) bst::find_min_node(z->right);
            lost_color = y->node_color;
            x = y->_extend_right();
            if (y->parent != z) {
                bst::transplant(y, y->right);
                bst::set_right_child(y, z->right);
            }
            bst::transplant(z, y);
            bst::set_left_child(y, z->left);
            y->node_color = z->node_color;
        }
        if (lost_color == BLACK) {
            delete_fixup(x);
        }
        if (x->is_nil) {
            bst::transplant(x, nullptr);
            delete x;
        }
        delete z;
        return true;
    }

private:
    bool is_red_node(red_black_node *n)
    {
        return n != nullptr && !n->is_nil && n->node_color == RED;
    }

    bool is_black_node(red_black_node *n)
    {
        return !is_red_node(n);
    }

    void insert_fixup(red_black_node *z)
    {
        if (z == nullptr) {
            return;
        }
        if (z->parent == nullptr) {
            z->node_color = BLACK;
            return;
        }
        while (is_red_node(z->_parent())) {
            red_black_node *p = z->_parent();
            red_black_node *g = z->_grandparent();
            red_black_node *u = p->_sibling();
            if (is_red_node(u)) {
                p->node_color = BLACK;
                u->node_color = BLACK;
                g->node_color = RED;
                z = g;
            } else {
                if (bst::is_left_child(p)) {
                    if (bst::is_right_child(z)) {
                        z = z->_parent();
                        bst::rotate_with_right_child(z);
                    }
                    z->_parent()->node_color = BLACK;
                    z->_grandparent()->node_color = RED;
                    bst::rotate_with_left_child(z->_grandparent());
                } else {
                    if (bst::is_left_child(z)) {
                        z = z->_parent();
                        bst::rotate_with_left_child(p);
                    }
                    z->_parent()->node_color = BLACK;
                    z->_grandparent()->node_color = RED;
                    bst::rotate_with_right_child(z->_grandparent());
                }
            }
        }
        ((red_black_node *) this->root)->node_color = BLACK;
    }

    void delete_fixup(red_black_node *x)
    {
        if (x == nullptr) {
            return;
        }
        while (x != this->root && is_black_node(x)) {
            red_black_node *p = x->_parent();
            red_black_node *w = x->_sibling();
            if (bst::is_left_child(x)) {
                if (is_red_node(w)) {
                    w->node_color = BLACK;
                    p->node_color = RED;
                    bst::rotate_with_right_child(p);
                    w = p->_right();
                }
                if (is_black_node(w->_left()) && is_black_node(w->_right())) {
                    w->node_color = RED;
                    x = x->_parent();
                } else {
                    if (is_black_node(w->_right())) {
                        w->_left()->node_color = BLACK;
                        w->node_color = RED;
                        bst::rotate_with_left_child(w);
                        w = p->_right();
                    }
                    w->node_color = p->node_color;
                    p->node_color = BLACK;
                    w->_right()->node_color = BLACK;
                    bst::rotate_with_right_child(p);
                    x = (red_black_node *) this->root;
                }
            } else {
                if (is_red_node(w)) {
                    w->node_color = BLACK;
                    p->node_color = RED;
                    bst::rotate_with_left_child(p);
                    w = p->_left();
                }
                if (is_black_node(w->_right()) && is_black_node(w->_left())) {
                    w->node_color = RED;
                    x = x->_parent();
                } else {
                    if (is_black_node(w->_left())) {
                        w->_right()->node_color = BLACK;
                        w->node_color = RED;
                        bst::rotate_with_right_child(w);
                        w = p->_left();
                    }
                    w->node_color = p->node_color;
                    p->node_color = BLACK;
                    w->_left()->node_color = BLACK;
                    bst::rotate_with_left_child(p);
                    x = (red_black_node *) this->root;
                }
            }
        }
        x->node_color = BLACK;
    }

    int black_height(red_black_node *x)
    {
        if (x == nullptr || x->is_nil) {
            return 1;
        }
        if (is_red_node(x) && is_red_node(x->_parent())) {
            return -2;
        }
        int left_bh = black_height(x->_left());
        if (left_bh <= 0) {
            return left_bh;
        }
        int right_bh = black_height(x->_right());
        if (right_bh <= 0) {
            return right_bh;
        }
        if (left_bh != right_bh) {
            return -1;
        }
        return is_black_node(x) ? 1 + left_bh : left_bh;
    }
};

#endif 
