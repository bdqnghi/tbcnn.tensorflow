    

    #include <iostream>
    #include <cstdio>
    #include <cstring>
    #include <algorithm>
    #include <cmath>
    #include <vector>
    #include <cstdlib>
    #include <cassert>

    #define INDENT_STEP  4

    using namespace std;

    enum color { RED, BLACK };

    

    typedef struct rbtree_node
    {
        enum color color;
        void *key;
        void *value;
        rbtree_node *left, *right, *parent;
    }*node;
     
    typedef struct rbtree_t
    {
        node root;
    }*rbtree;
     
    

    class RBTree
    {
        public:
            typedef int (*compare_func)(void* left, void* right);
            rbtree rbtree_create();
            void* rbtree_lookup(rbtree t, void* , compare_func compare);
            void rbtree_insert(rbtree t, void* , void* , compare_func compare);
            void rbtree_delete(rbtree t, void* , compare_func compare);
            node grandparent(node n);
            node sibling(node n);
            node uncle(node n);
            void verify_properties(rbtree t);
            void verify_property_1(node root);
            void verify_property_2(node root);
            color node_color(node n);
            void verify_property_4(node root);
            void verify_property_5(node root);
            void verify_property_5_helper(node n, int , int*);
            node new_node(void* key, void* , color , node , node);
            node lookup_node(rbtree t, void* , compare_func compare);
            void rotate_left(rbtree t, node n);
            void rotate_right(rbtree t, node n);
            void replace_node(rbtree t, node oldn, node newn);
            void insert_case1(rbtree t, node n);
            void insert_case2(rbtree t, node n);
            void insert_case3(rbtree t, node n);
            void insert_case4(rbtree t, node n);
            void insert_case5(rbtree t, node n);
            node maximum_node(node root);
            void delete_case1(rbtree t, node n);
            void delete_case2(rbtree t, node n);
            void delete_case3(rbtree t, node n);
            void delete_case4(rbtree t, node n);
            void delete_case5(rbtree t, node n);
            void delete_case6(rbtree t, node n);
    };

    

    node RBTree::grandparent(node n)
    {
        assert (n != NULL);
        assert (n->parent != NULL);
        assert (n->parent->parent != NULL);
        return n->parent->parent;
    }  

    

    node RBTree::sibling(node n)
    {
        assert (n != NULL);
        assert (n->parent != NULL);
        if (n == n->parent->left)
            return n->parent->right;
        else
            return n->parent->left;
    }   

    

    node RBTree::uncle(node n)
    {
        assert (n != NULL);
        assert (n->parent != NULL);
        assert (n->parent->parent != NULL);
        return sibling(n->parent);
    }   

    

    void RBTree::verify_properties(rbtree t)
    {
        verify_property_1 (t->root);
        verify_property_2 (t->root);
        verify_property_4 (t->root);
        verify_property_5 (t->root);
    }

    

    void RBTree::verify_property_1(node n)
    {
        assert (node_color(n) == RED || node_color(n) == BLACK);
        if (n == NULL)
            return;
        verify_property_1(n->left);
        verify_property_1(n->right);
    }

    

    void RBTree::verify_property_2(node root)
    {
        assert (node_color(root) == BLACK);
    }

    

    color RBTree::node_color(node n)
    {
        return n == NULL ? BLACK : n->color;
    }

    

    void RBTree::verify_property_4(node n)
    {
        if (node_color(n) == RED)
        {
            assert (node_color(n->left) == BLACK);
            assert (node_color(n->right) == BLACK);
            assert (node_color(n->parent) == BLACK);
        }
        if (n == NULL)
            return;
        verify_property_4(n->left);
        verify_property_4(n->right);
    }

    

    void RBTree::verify_property_5(node root)
    {
        int black_count_path = -1;
        verify_property_5_helper(root, 0, &black_count_path);
    }     

    void RBTree::verify_property_5_helper(node n, int black_count, int* path_black_count)
    {
        if (node_color(n) == BLACK)
        {
            black_count++;
        }
        if (n == NULL)
        {
           if (*path_black_count == -1)
            {
                *path_black_count = black_count;
            }
            else
            {
                assert (black_count == *path_black_count);
            }
            return;
        }
        verify_property_5_helper(n->left,  black_count, path_black_count);
        verify_property_5_helper(n->right, black_count, path_black_count);
    }     

    

    rbtree RBTree::rbtree_create()
    {
        rbtree t = new rbtree_t;
        t->root = NULL;
        verify_properties(t);
        return t;
    }     

    

    node RBTree::new_node(void* k, void* v, color n_color, node left, node right)
    {
        node result = new rbtree_node;
        result->key = k;
        result->value = v;
        result->color = n_color;
        result->left = left;
        result->right = right;
        if (left  != NULL)
            left->parent = result;
        if (right != NULL)
            right->parent = result;
        result->parent = NULL;
        return result;
    }

    

    node RBTree::lookup_node(rbtree t, void* key, compare_func compare)
    {
        node n = t->root;
        while (n != NULL)
        {
            int comp_result = compare(key, n->key);
            if (comp_result == 0)
            {
                return n;
            }
            else if (comp_result < 0)
            {
                n = n->left;
            }
            else
            {
                assert(comp_result > 0);
                n = n->right;
            }
        }
        return n;
    }

    

    void* RBTree::rbtree_lookup(rbtree t, void* key, compare_func compare)
    {
        node n = lookup_node(t, key, compare);
        return n == NULL ? NULL : n->value;
    }     

    

    void RBTree::rotate_left(rbtree t, node n)
    {
        node r = n->right;
        replace_node(t, n, r);
        n->right = r->left;
        if (r->left != NULL)
        {
            r->left->parent = n;
        }
        r->left = n;
        n->parent = r;
    }

    

    void RBTree::rotate_right(rbtree t, node n)
    {
        node L = n->left;
        replace_node(t, n, L);
        n->left = L->right;
        if (L->right != NULL)
        {
            L->right->parent = n;
        }
        L->right = n;
        n->parent = L;
    }

    

    void RBTree::replace_node(rbtree t, node oldn, node newn)
    {
        if (oldn->parent == NULL)
        {
            t->root = newn;
        }
        else
        {
            if (oldn == oldn->parent->left)
                oldn->parent->left = newn;
            else
                oldn->parent->right = newn;
        }
        if (newn != NULL)
        {
            newn->parent = oldn->parent;
        }
    }

    

    void RBTree::rbtree_insert(rbtree t, void* key, void* value, compare_func compare)
    {
        node inserted_node = new_node(key, value, RED, NULL, NULL);
        if (t->root == NULL)
        {
            t->root = inserted_node;
        }
        else
        {
            node n = t->root;
            while (1)
            {
                int comp_result = compare(key, n->key);
                if (comp_result == 0)
                {
                    n->value = value;
                    return;
                }
                else if (comp_result < 0)
                {
                    if (n->left == NULL)
                    {
                        n->left = inserted_node;
                        break;
                    }
                    else
                    {
                        n = n->left;
                    }
                }
                else
                {
                    assert (comp_result > 0);
                    if (n->right == NULL)
                    {
                        n->right = inserted_node;
                        break;
                    }
                    else
                    {
                        n = n->right;
                    }
                }
            }
            inserted_node->parent = n;
        }
        insert_case1(t, inserted_node);
        verify_properties(t);
    }
     
    

    void RBTree::insert_case1(rbtree t, node n)
    {
        if (n->parent == NULL)
            n->color = BLACK;
        else
            insert_case2(t, n);
    }
     
    
    void RBTree::insert_case2(rbtree t, node n)
    {
        if (node_color(n->parent) == BLACK)
            return;
        else
            insert_case3(t, n);
    }
     
    

    void RBTree::insert_case3(rbtree t, node n)
    {
        if (node_color(uncle(n)) == RED)
        {
            n->parent->color = BLACK;
            uncle(n)->color = BLACK;
            grandparent(n)->color = RED;
            insert_case1(t, grandparent(n));
        }
        else
        {
            insert_case4(t, n);
        }
    }
     
    

    void RBTree::insert_case4(rbtree t, node n)
    {
        if (n == n->parent->right && n->parent == grandparent(n)->left)
        {
            rotate_left(t, n->parent);
            n = n->left;
        }
        else if (n == n->parent->left && n->parent == grandparent(n)->right)
        {
            rotate_right(t, n->parent);
            n = n->right;
        }
        insert_case5(t, n);
    }
     
    

    void RBTree::insert_case5(rbtree t, node n)
    {
        n->parent->color = BLACK;
        grandparent(n)->color = RED;
        if (n == n->parent->left && n->parent == grandparent(n)->left)
        {
            rotate_right(t, grandparent(n));
        }
        else
        {
            assert (n == n->parent->right && n->parent == grandparent(n)->right);
            rotate_left(t, grandparent(n));
        }
    }
     
    

    void RBTree::rbtree_delete(rbtree t, void* key, compare_func compare)
    {
        node child;
        node n = lookup_node(t, key, compare);
        if (n == NULL)
            return;
        if (n->left != NULL && n->right != NULL)
        {
            node pred = maximum_node(n->left);
            n->key   = pred->key;
            n->value = pred->value;
            n = pred;
        }
        assert(n->left == NULL || n->right == NULL);
        child = n->right == NULL ? n->left  : n->right;
        if (node_color(n) == BLACK)
        {
            n->color = node_color(child);
            delete_case1(t, n);
        }
        replace_node(t, n, child);
        free(n);
        verify_properties(t);
    }
     
    

    node RBTree::maximum_node(node n)
    {
        assert (n != NULL);
        while (n->right != NULL)
        {
            n = n->right;
        }
        return n;
    }
     
    

    void RBTree::delete_case1(rbtree t, node n)
    {
        if (n->parent == NULL)
            return;
        else
            delete_case2(t, n);
    }
     
    

    void RBTree::delete_case2(rbtree t, node n)
    {
        if (node_color(sibling(n)) == RED)
        {
            n->parent->color = RED;
            sibling(n)->color = BLACK;
            if (n == n->parent->left)
                rotate_left(t, n->parent);
            else
                rotate_right(t, n->parent);
        }
        delete_case3(t, n);
    }
     
    

    void RBTree::delete_case3(rbtree t, node n)
    {
        if (node_color(n->parent) == BLACK && node_color(sibling(n)) == BLACK &&
            node_color(sibling(n)->left) == BLACK && node_color(sibling(n)->right) == BLACK)
        {
            sibling(n)->color = RED;
            delete_case1(t, n->parent);
        }
        else
            delete_case4(t, n);
    }
     
    

    void RBTree::delete_case4(rbtree t, node n)
    {
        if (node_color(n->parent) == RED && node_color(sibling(n)) == BLACK &&
            node_color(sibling(n)->left) == BLACK && node_color(sibling(n)->right) == BLACK)
        {
            sibling(n)->color = RED;
            n->parent->color = BLACK;
        }
        else
            delete_case5(t, n);
    }
     
    

    void RBTree::delete_case5(rbtree t, node n)
    {
        if (n == n->parent->left && node_color(sibling(n)) == BLACK &&
            node_color(sibling(n)->left) == RED && node_color(sibling(n)->right) == BLACK)
        {
            sibling(n)->color = RED;
            sibling(n)->left->color = BLACK;
            rotate_right(t, sibling(n));
        }
        else if (n == n->parent->right && node_color(sibling(n)) == BLACK &&
                 node_color(sibling(n)->right) == RED && node_color(sibling(n)->left) == BLACK)
        {
            sibling(n)->color = RED;
            sibling(n)->right->color = BLACK;
            rotate_left(t, sibling(n));
        }
        delete_case6(t, n);
    }
     
    

    void RBTree::delete_case6(rbtree t, node n)
    {
        sibling(n)->color = node_color(n->parent);
        n->parent->color = BLACK;
        if (n == n->parent->left)
        {
            assert (node_color(sibling(n)->right) == RED);
            sibling(n)->right->color = BLACK;
            rotate_left(t, n->parent);
        }
        else
        {
            assert (node_color(sibling(n)->left) == RED);
            sibling(n)->left->color = BLACK;
            rotate_right(t, n->parent);
        }
    }
     
    

    int compare_int(void* leftp, void* rightp)
    {
        int left = (int)leftp;
        int right = (int)rightp;
        if (left < right)
            return -1;
        else if (left > right)
            return 1;
        else
        {
            assert (left == right);
            return 0;
        }
    }

    

    void print_tree_helper(node n, int indent)
    {
        int i;
        if (n == NULL)
        {
            fputs("<empty tree>", stdout);
            return;
        }
        if (n->right != NULL)
        {
            print_tree_helper(n->right, indent + INDENT_STEP);
        }
        for(i = 0; i < indent; i++)
            fputs(" ", stdout);
        if (n->color == BLACK)
            cout<<(int)n->key<<endl;
        else
            cout<<"<"<<(int)n->key<<">"<<endl;
        if (n->left != NULL)
        {
            print_tree_helper(n->left, indent + INDENT_STEP);
        }
    }

    void print_tree(rbtree t)
    {
        print_tree_helper(t->root, 0);
        puts("");
    }
     
    

    int main()
    {
        int i;
        RBTree rbt;
        rbtree t = rbt.rbtree_create();
        for (i = 0; i < 12; i++)
        {
            int x = rand() % 10;
            int y = rand() % 10;
            print_tree(t);
            cout<<"Inserting "<<x<<" -> "<<y<<endl<<endl;
            rbt.rbtree_insert(t, (void*)x, (void*)y, compare_int);
            assert(rbt.rbtree_lookup(t, (void*)x, compare_int) == (void*)y);
        }
        for (i = 0; i < 15; i++)
        {
            int x = rand() % 10;
            print_tree(t);
            cout<<"Deleting key "<<x<<endl<<endl;
            rbt.rbtree_delete(t, (void*)x, compare_int);
        }
        return 0;
    }
