#ifndef SRC_RED_BLACK_TREE_CPP_
#define SRC_RED_BLACK_TREE_CPP_

#include <iostream>
#include <vector>       //for returning set of keys between two given keys

using namespace std;

template<typename K, typename V> class red_black_tree {

        // ===========================================================
        // Inner structures and classes
        // ===========================================================
    private:
        enum Color {
            red, black
        };

    public:
        struct rb_tree_entry {
                K key;
                V val;
                rb_tree_entry(K k, V v)
                        : key(k), val(v) {
                }
        };
        // ===========================================================
    private:
        struct rb_tree_node {
                rb_tree_entry* entry;
                rb_tree_node* left_child;
                rb_tree_node* right_child;
                Color col;
                int height;
                int black_height;
                rb_tree_node(rb_tree_entry* pEntry, Color pColor)
                        : entry(pEntry), left_child(NULL), right_child(NULL), height(0), col(pColor), black_height(pColor == black ? 0 : -1) {
                }
                rb_tree_node()
                        : entry(NULL), left_child(NULL), right_child(NULL), height(0), col(black), black_height(0) {
                }
                inline void update_height() {
                    this->height = 1 + max(left_child ? left_child->height : -1, right_child ? right_child->height : -1);
                    this->black_height = (this->col == black ? 1 : 0) + max(left_child ? left_child->black_height : -1, right_child ? right_child->black_height : -1);
                }
        };
        inline static int black_height(rb_tree_node* node) {
            return ((node) ? node->black_height : -1);
        }
        inline bool is_red(rb_tree_node* node) {
            return node && node->col == red;
        }
        // ===========================================================
    public:
        class rb_tree_iterator {
            private:
                rb_tree_node* node;
                rb_tree_iterator(rb_tree_node* node)
                        : node(node) {
                }
            public:
                rb_tree_entry& operator *() {
                    return *(node->entry);
                }
                bool operator ==(const rb_tree_iterator& p) const {
                    return node == p.node;
                }
                bool operator !=(const rb_tree_iterator& p) const {
                    return node != p.node;
                }
                friend ostream& operator<<(ostream& output, const rb_tree_iterator& it) {
                    output << "(key=" << it.node->entry->key << ", value=" << it.node->entry->val << ")";
                    return output;
                }
                friend class red_black_tree;
        };
        // ===========================================================
        // Fields
        // ===========================================================
    private:
        rb_tree_node* root;
        unsigned mSize;
        rb_tree_node* end_node;
        rb_tree_iterator* end_iterator;
        // ===========================================================
        // Constructor & Destructor
        // ===========================================================
    public:
        red_black_tree() {
            root = NULL;
            mSize = 0;
            end_node = new rb_tree_node();
            end_iterator = new rb_tree_iterator(end_node);
        }

        ~red_black_tree() {
            delete_node(root);
        }
    private:
        void delete_node(rb_tree_node* node) {
            if (!node) return;
            delete_node(node->left_child);
            delete_node(node->right_child);
            delete node;
        }
        // ===========================================================
        // End Iterator
        // ===========================================================
    public:
        rb_tree_iterator end() {
            return *end_iterator;
        }
        // ===========================================================
        // Put/Insert
        // ===========================================================
    public:
        void insert(K k, V v) {
            cout << "Inserting " << k << "\n";
            rb_tree_entry* entry = new rb_tree_entry(k, v);
            root = insert(root, entry);
            root->col = black;
            root->update_height();
            this->print();
        }
        // ===========================================================
        // Miscellaneous Functions
        // ===========================================================
    public:
        int leaves() {
            return leaves(root);
        }
        int height() {
            return root->height;
        }
        vector<int> keys_between(int a, int b) {
            vector<int> keys;
            if (root) add_keys(root, a, b, keys);
            return keys;
        }
        unsigned size() {
            return mSize;
        }
    private:
        int leaves(rb_tree_node* node) {
            if (!node->left_child && !node->right_child) return 2;
            if (!node->left_child && node->right_child) return 1 + leaves(node->right_child);
            if (node->left_child && !node->right_child) return 1 + leaves(node->left_child);
            else return leaves(node->left_child) + leaves(node->right_child);
        }
        void add_keys(rb_tree_node* node, int a, int b, vector<int>& vec) {
            if (node->left_child) add_keys(node->left_child, a, b, vec);
            if (a <= node->entry->key && node->entry->key <= b) vec.push_back(node->entry->key);
            if (node->right_child) add_keys(node->right_child, a, b, vec);
        }
        // ===========================================================
        // Put/Insert Internal Functions
        // ===========================================================
    private:
        rb_tree_node* rotate_right(rb_tree_node* u) {
            cout << "Rotating right at " << u->entry->key << "\n";
            rb_tree_node* v = u->left_child;
            rb_tree_node* t2 = v->right_child;
            u->left_child = t2;
            v->right_child = u;
            u->update_height();
            v->update_height();
            return v;
        }

        rb_tree_node* rotate_left(rb_tree_node* v) {
            cout << "Rotating left at " << v->entry->key << "\n";
            rb_tree_node* u = v->right_child;
            rb_tree_node* t2 = u->left_child;
            v->right_child = t2;
            u->left_child = v;
            v->update_height();
            u->update_height();
            return u;
        }

        rb_tree_node* insert(rb_tree_node* node, rb_tree_entry* entry) {
            if (!node) {
                mSize++;
                return new rb_tree_node(entry, red);
            } else {
                // ===========================================================
                // Insertion
                // ===========================================================
                rb_tree_node* child;
                bool is_left_child = false;
                if (entry->key < node->entry->key) {
                    is_left_child = true;
                    child = insert(node->left_child, entry);
                    node->left_child = child;
                } else if (entry->key > node->entry->key) {
                    /*is_left_child=false*/
                    child = insert(node->right_child, entry);
                    node->right_child = child;
                } else /*entry->key == node->entry->key*/node->entry->val = entry->val;
                node->update_height();
                // this->print();
                if (entry->key == node->entry->key) {
                    cout << "Updated\n";
                    return node;
                }
                // ===========================================================
                // Balancing
                // ===========================================================
                if (is_red(child)) {
                    if (is_red(child->left_child) || is_red(child->right_child)) {
                        if ((is_left_child && !is_red(node->right_child)) || (!is_left_child && !is_red(node->left_child))) {
                            node->col = red;
                            if (is_red(child->left_child)) {
                                if (!is_left_child) {
                                    node->right_child = rotate_right(node->right_child);
                                    node = rotate_left(node);
                                } else node = rotate_right(node);
                            } else {
                                if (is_left_child) {
                                    node->left_child = rotate_left(node->left_child);
                                    node = rotate_right(node);
                                } else node = rotate_left(node);
                            }
                            node->col = black;
                        } else {
                            cout << "Changing Colours\n";
                            node->col = red;
                            node->left_child->col = black;
                            node->left_child->update_height();
                            node->right_child->col = black;
                            node->right_child->update_height();
                        }
                    } else cout << "No Balancing at " << node->entry->key << "\n";
                } else cout << "No Balancing at " << node->entry->key << "\n";
                node->update_height();
                return node;
                // ===========================================================
            }
        }

        // ===========================================================
        // Find
        // ===========================================================
    public:
        rb_tree_iterator search(K k) {
            rb_tree_node* node = root;
            if (!node) return end();
            do {
                if (k < node->entry->key) node = node->left_child;
                else if (k > node->entry->key) node = node->right_child;
                else return rb_tree_iterator(node);
            } while (node);
            return end();
        }
        // ===========================================================
        // Remove
        // ===========================================================
    public:
        void remove(K k) {
            cout << "Deleting " << k << "\n";
            root = remove(root, k);
            mSize--;
            this->print();
        }

    private:
        rb_tree_node* remove(rb_tree_node* node, K k) {
            // ===========================================================
            // Erase
            // ===========================================================
            int black_height_before = -1;
            bool removed_from_left = false;
            if (!node) {
                cout << "No such Node.\n";
                throw;
            } else if (k < node->entry->key) {
                black_height_before = black_height(node->left_child);
                removed_from_left = true;
                node->left_child = remove(node->left_child, k);
            } else if (k > node->entry->key) {
                black_height_before = black_height(node->right_child);
                /*removed_from_left=false;*/
                node->right_child = remove(node->right_child, k);
            } else /* k==node->entry->key */{
                if (!node->left_child && !node->right_child) {
                    rb_tree_node* node2 = node;
                    node = NULL;
                    delete node2;
                } else if (!node->left_child || !node->right_child) {
                    rb_tree_node* node2 = node;
                    rb_tree_node* child = node->left_child ? node->left_child : node->right_child;
                    bool black_before = node;
                    *node = *child;
                    if (black_before) node->col = black;
                    delete child;
                } else {
                    rb_tree_node* min_right = node->right_child;
                    while (min_right->left_child)
                        min_right = min_right->left_child;
                    *(node->entry) = *(min_right->entry);
                    /*removed_from_left=false;*/
                    black_height_before = black_height(node->right_child);
                    node->right_child = remove(node->right_child, min_right->entry->key);
                }
            }
            if (!node) return NULL;
            node->update_height();
            //this->print();
            // ===========================================================
            // Balancing
            // ===========================================================
            int black_height_after = black_height(removed_from_left ? node->left_child : node->right_child);
            if (black_height_after < black_height_before) {
                cout << "Balancing at " << node->entry->key << "\n";
                rb_tree_node* b = removed_from_left ? node->right_child : node->left_child;
                if (node->col == red) {
                    if (b && (is_red(b->left_child) || is_red(b->right_child))) {
                        //Case 1.1
                        cout << "Case 1.1\n";
                        rb_tree_node* c = is_red(b->left_child) ? b->left_child : b->right_child;
                        if (!removed_from_left) {
                            if (c == b->right_child) node->left_child = rotate_left(node->left_child);
                            node = rotate_right(node);
                        } else {
                            if (c == b->left_child) node->right_child = rotate_right(node->right_child);
                            node = rotate_left(node);
                        }
                        node->col = red;
                        node->left_child->col = black;
                        node->right_child->col = black;
                        node->left_child->update_height();
                        node->right_child->update_height();
                    } else {
                        //Case 1.2
                        cout << "Case 1.2\n";
                        node->col = black;
                        if (b) {
                            b->col = red;
                            b->update_height();
                        }
                    }
                } else {
                    if (is_red(b)) {
                        rb_tree_node* c = removed_from_left ? b->left_child : b->right_child;
                        if (is_red(c->left_child) || is_red(c->right_child)) {
                            //Case 2.1.1
                            cout << "Case 2.1.1\n";
                            rb_tree_node* d = (removed_from_left ? (is_red(c->right_child) ? c->right_child : c->left_child) : (is_red(c->left_child) ? c->left_child : c->right_child));
                            if (!removed_from_left) {
                                if (d == c->left_child) node->left_child->right_child = rotate_right(node->left_child->right_child);
                                node->left_child = rotate_left(node->left_child);
                                node->left_child = rotate_left(node->left_child);
                                node = rotate_right(node);
                                node->left_child = rotate_right(node->left_child);
                                node->left_child->right_child->col = black;
                                node->left_child->right_child->update_height();
                                node->left_child->update_height();
                            } else {
                                if (d == c->right_child) node->right_child->left_child = rotate_left(node->right_child->left_child);
                                node->right_child = rotate_right(node->right_child);
                                node->right_child = rotate_right(node->right_child);
                                node = rotate_left(node);
                                node->right_child = rotate_left(node->right_child);
                                node->right_child->left_child->col = black;
                                node->right_child->left_child->update_height();
                                node->right_child->update_height();
                            }
                            node->col = black;
                        } else {
                            //Case 2.1.2
                            cout << "Case 2.1.2\n";
                            b->col = black;
                            c->col = red;
                            if (!removed_from_left) node = rotate_right(node);
                            else node = rotate_left(node);
                            c->update_height();
                            node->left_child->update_height();
                            node->right_child->update_height();
                        }
                    } else {
                        if (is_red(b->left_child) || is_red(b->right_child)) {
                            //Case 2.2.1
                            cout << "Case 2.2.1\n";
                            rb_tree_node* c = removed_from_left ? (is_red(b->right_child) ? b->right_child : b->left_child) : (is_red(b->left_child) ? b->left_child : b->right_child);
                            if (!removed_from_left) {
                                if (c == b->right_child) node->left_child = rotate_left(node->left_child);
                                node = rotate_right(node);
                            } else {
                                if (c == b->left_child) node->right_child = rotate_right(node->right_child);
                                node = rotate_left(node);
                            }
                            node->col = black;
                            node->left_child->col = black;
                            node->right_child->col = black;
                            node->left_child->update_height();
                            node->right_child->update_height();
                        } else {
                            //Case 2.2.2
                            cout << "Case 2.2.2\n";
                            b->col = red;
                            b->update_height();
                        }
                    }
                }
                node->update_height();
            } else cout << "No Balancing at " << node->entry->key << "\n";
            // ===========================================================
            return node;
        }
// ===========================================================
// Printing
// ===========================================================
    private:
        void print(string prefix, rb_tree_node* node, bool left, bool root) {
            if (node->right_child) print(prefix + (!left || root ? "    " : "│   "), node->right_child, false, false);
            cout << prefix << (root ? "X─── " : (left ? "└── " : "┌── ")) << "[" << node->entry->key << (node->col == red ? "(R)" : "(B),") << node->height << "," << node->black_height << "]\n";
            if (node->left_child) print(prefix + (left ? "    " : "│   "), node->left_child, true, false);
        }
    public:
        void print() {
            cout << string(100, '=') << "\n";
            if (root) print("", root, true, true);
            else cout << "Empty Tree\n";
            cout << string(100, '=') << "\n";
        }
}
;

#endif /*SRC_RED_BLACK_TREE_CPP_*/
