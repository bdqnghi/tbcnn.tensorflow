#include <iostream>

using namespace std;

int const RED = 1;
int const BLACK = 2;

template <typename KEY, typename VALUE>
class RedBlackTree {
public:
    struct Node{
        KEY key;
        VALUE value;
        Node *left, *right, *parent;
        int color;
        
        Node (KEY k, VALUE v){
            key = k;
            value = v;
            left = right = parent = NULL;
            color = RED;
        }
        
        Node (){
            left = right = parent = NULL;
            color = BLACK;
        }
        
    } *root, *x, *y, *now;
    
    Node *NIL;
    
    RedBlackTree (){
        NIL = new Node();
        root = NIL;
    }
    
    ~RedBlackTree(){
        clear();
        delete (NIL);
    }
    
    void insert (KEY key, VALUE value){
        now = new Node (key, value);
        now->left = now->right = now->parent = NIL;
        
        x = root;
        y = NIL;
        
        while (x!=NIL){
            y = x;
            if (now->key < x->key){
                x = x->left;
            }
            else if (now->key > x->key) {
                x = x->right;
            }
            else{
                x->value += value;
                return ;
            }
        }
        
        if (y==NIL){
            root = now;
        }
        else if (now->key <  y->key){
            y->left = now;
        }
        else{
            y->right = now;
        }
        
        now->parent = y;
        
        insert_fix(now);
    }
    
    void print (){
        print (root);
        cout<<endl;
    }
    
    void print (Node *n){
        if (n == NIL)return;
        print (n->left);
        cout<<n->key<<" "<<n->value<<" "<<n->color<<endl;
        print (n->right);
    }
    
    void clear(){
        clear(root);
        root = NIL;
    }
    
    void clear (Node *n){
        if (n == NIL)return;
        clear (n->left);
        clear (n->right);
        delete (n);
    }
    
    Node* search (KEY key){
        x = root;
        
        while (x!=NIL){
            if (key < x->key){
                x = x->left;
            }
            else if (key > x->key){
                x = x->right;
            }
            else break;
        }
        
        return x;
    }
    
    void left_rotate(Node *x){
        //make y
        y = x->right;
        
        //connect x->right to b
        x->right = y->left;
        if (x->right!=NIL){
            x->right->parent = x;
        }
        
        //connect y to parent's x
        y->parent = x->parent;
        if (x->parent == NIL){
            root = y;
        }
        else if (x->parent->left == x){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
        
        //connect y to x
        y->left = x;
        x->parent = y;
    }
    
    // copy from left_rotate but change x to y, left to right and vice versa
    void right_rotate(Node *y){
        x = y->left;
        
        y->left = x->right;
        if (y->left!=NIL){
            y->left->parent = y;
        }
        
        x->parent = y->parent;
        if (y->parent == NIL){
            root = x;
        }
        else if (y->parent->left == y){
            y->parent->left = x;
        }
        else{
            y->parent->right = x;
        }
        
        x->right = y;
        y->parent = x;
    }
    
    void insert_fix(Node *x){
        while (x->parent->color == RED){
            if (x->parent->parent->left == x->parent){
                y = x->parent->parent->right;
                if (y->color == RED){
                    y->color = BLACK;
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }else{
                    if (x->parent->right == x){
                        x = x->parent;
                        left_rotate(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    right_rotate(x->parent->parent);
                }
            }
            else{
                y = x->parent->parent->left;
                if (y->color == RED){
                    y->color = BLACK;
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }else{
                    if (x->parent->left == x){
                        x = x->parent;
                        right_rotate(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    left_rotate(x->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

};

int main (){
    RedBlackTree <string,int > rbt;
    rbt.insert("pawan",2);
    rbt.insert("salil",4);
    rbt.insert("pawan",1);
   /* rbt.insert(2,3);
    rbt.insert(2,5);
    rbt.insert(2,3);
    rbt.insert(2,9);
    rbt.insert(3,6);
    rbt.insert(4,7);
    rbt.insert(5,5);
    rbt.insert(6,2);
    rbt.insert(7,8);
    */
    rbt.print();
	return 0;
}












