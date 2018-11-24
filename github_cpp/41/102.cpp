#include <iostream>
#include <algotrithm>

template<typename Value, class Compare = std::less<Value>>
class RB_tree {
public:
    RB_tree();
    RB_tree(const RB_tree& tree);
    RB_tree(RB_tree&& tree);
    ~RB_tree();
    insert(const Value& val);
    insert(Value&& val);
    bool del(const Value& val);
    const Value& find_min() const;
    const Value& find_max() const;
    bool has(const Value& val) const;
    bool empty() const;

    void insert(const Value& x );
    void insert(Value&& x );
    bool remove(const Value& x);
    RB_tree & operator=( const RB_tree& rhs );
    RB_tree & operator=( RB_tree&& rhs );

    friend void swap(RB_tree& tree1, RB_tree& tree2);

private:
    enum Color {
        RED,
        BLACK
    };

    struct Node {
        Color color;
        Value val;
        Node* left;
        Node* right;
        Node* parent;
    } *root;

    Compare comp;

    Node* B_tree_insert(Value&& val);
    void right_rotate(Node* left, Node* right, Node* &last_ptr);
    void left_rotate(Node* left, Node* right, Node* &last_ptr);
};

using namespace std;

template<typename V, class C = std::less<Value>>
RB_tree<V, C>& RB_tree<V, C>::operator=( RB_tree<V, C>&& rhs ) {
    swap(*this, rhs);
}

template<typename Value, class Compare = std::less<Value>>
RB_tree<Value, Compare>& RB_tree<Value, Compare>::operator=(const RB_tree& rhs ) {
    swap(*this, RB_tree{rhs});
}

template<typename Value, class Compare = std::less<Value>>
RB_tree<Value, Compare>::RB_tree(RB_tree&& tree) {
    swap(*this, tree);
}

template<typename Value, class Compare = std::less<Value>>
RB_tree<Value, Compare>::RB_tree(const RB_tree& tree) {
    swap(*this, RB_tree{tree});
}

template<typename Value, class Compare = std::less<Value>>
RB_tree<Value, Compare>::RB_tree() : root{nullptr} {

}

template<typename Value, class Compare = std::less<Value>>
Node* RB_tree<Value, Compare>::B_tree_insert(Value&& val) {
    Node* cur = root;
    Node* last;
    if (root == nullptr) {
        root = new Node{.color=BLACK, .left=nullptr, .right=nullptr, .parent=nullptr};
        swap(root->val, val);
        return root;
    }

    while (!cur) {
        last = cur;
        if (comp(val, cur->val))
            cur = cur -> left;
        else
            cur = cur -> right;
    }

    if (comp(val, last->val)) {
        last->left = new Node {.color=RED, .left=nullptr, .right=nullptr, .parent=last};
        swap(last->left->val, val);
    }
    else {
        last->right = new Node {.color=RED, .left=nullptr, .right=nullptr, .parent=last};
        swap(last->left->val, val);
    }

    return last;
}

template<typename Value, class Compare = std::less<Value>>
friend void swap(RB_tree<Value, Compare>& tree1, RB_tree<Value, Compare>& tree2) {
    swap(tree1.root, tree2.root);
}

template<typename Value, class Compare = std::less<Value>>
void RB_tree<Value, Compare>::left_rotate(Node* left, Node* right, Node* &last_ptr) {
    last_ptr = right;
    left -> right = right -> left;
    right -> left = left;
}

template<typename Value, class Compare = std::less<Value>>
void RB_tree<Value, Compare>::right_rotate(Node* left, Node* right, Node* &last_ptr) {
    last_ptr = left;
    right -> left = left -> right;
    left -> right = right;
}

/* insert val into RB-tree */
template<typename Value, class Compare = std::less<Value>>
void RB_tree<Value, Compare>::insert(Value&& val) {
    /* insert new node with color red */
    Node* ptr = B_tree_insert(val);
    if (ptr->parent == null) // only one node
        return;

    /* pecolate up the color, if vialate the rull do rotate */
    while (ptr->parent->parent && ptr -> parent -> color == RED) {
        Node* parent = ptr->parent;
        Node* grand = parent->parent;

        /* X'parent is the left side node */
        if (ptr->parent == ptr->parent->parent->left) {
            Node* uncle = grand->right;

            /* case1: uncle's color is red, recolor parent,uncle and grandpa */
            if (uncle != nullptr && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand->color = RED;

                ptr = grand;
                if (ptr->parent == nullptr) // ptr at root;
                    break;

            /* case2: ptr is right child, rotate to left, convert to case3 */
            } else if (ptr == parent->right) {
                left_rotate(parent, ptr, grand->left);
                ptr = ptr -> left;

            /* case3: zig-zig, righ-rotate parent and grandpa*/
            } else {
                if (grand == root) {
                    right_rotate(parent, grand, root);
                    grand -> color = RED;
                    parent -> color = BLACK;
                    break;

                } else {
                    grand == grand->parent->left ?
                    right_rotate(parent, grand, grand->parent->left):
                    right_rotate(parent, grand, grand->parent->right);
                    grand -> color = RED;
                    parent -> color = BLACK;
                    ptr = grand;
                }

            }

        /* X'parent is the right side node, do opposite */
        } else {
            Node* uncle = grand->left;

            /* case1: uncle's color is red, recolor parent,uncle and grandpa */
            if (uncle != nullptr && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand->color = RED;

                ptr = grand;
                if (ptr->parent == nullptr) // ptr at root;
                    break;

            /* case2: ptr is left child, rotate to right, convert to case3 */
            } else if (ptr == parent->left) {
                right_rotate(ptr, parent, grand->right);
                ptr = ptr -> right;

            /* case3: zig-zig, left-rotate parent and grandpa*/
            } else {
                if (grand == root) {
                    left_rotate(grand, parent, root);
                    grand -> color = RED;
                    parent -> color = BLACK;
                    break;

                } else {
                    grand == grand->parent->left ?
                    left_rotate(grand, parent, grand->parent->left):
                    left_rotate(grand, parent, grand->parent->right);
                    grand -> color = RED;
                    parent -> color = BLACK;
                    ptr = grand;
                }
            }
        }
    }

    root -> color = BLACK;
}

template<typename Value, class Compare = std::less<Value>>
RB_tree<Value, Compare>::insert(Value& val) {
    insert(Value{val});
}

/* delete val from RB-tree */
template<typename Value, class Compare = std::less<Value>>
void RB_tree<Value, Compare>::del(const Value& val) {
    auto cur = root;
    while (cur) {
        if (comp(val, cur->val)) {
            cur = cur -> left;

        } else if (comp(cur->val, val)) {
            cur = cur -> right;

        } else {
            break;
        }
    }
    if (cur == nullptr)
        return;

    auto s_ptr = find_left_most(cur->right);

    if (s_ptr == nullptr) {

    /* smallest node is cur's right node */
    } else if (cur->right == s_prt) {

    /* normal case */
    } else {

    }
}

template<typename Value, class Compare = std::less<Value>>
Node* RB_tree<Value, Compare>::find_left_most(const Node* node) {
    auto cur = node;
    while (cur && cur -> left) {
        cur = cur -> left;
    }
    return cur;
}
