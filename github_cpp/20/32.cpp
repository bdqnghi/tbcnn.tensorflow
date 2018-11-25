#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <vector>
#define MAXINT 32767
using namespace std;


class rbtree{
private:
    rbnode*nil;
    rbnode*root;

    void left_rotate(rbnode *x) {
        rbnode *y;
        y = x->right;
        x->right = y->left;
        if (y->left != this->nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == this->nil) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
        
        y->size = x->size;
        x->size = x->right->size + x->left->size + 1;
        return;
    }

    void right_rotate(rbnode *x) {
        rbnode *y;
        y = x->left;
        x->left = y->right;
        if (y->right != this->nil) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == this->nil) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
        
        y->size = x->size;
        x->size = x->right->size + x->left->size + 1;
        return;
    }

    void rbtree_transplant(rbnode *x, rbnode *y) {
        
        if (x->parent == this->nil) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->parent = x->parent;
    }

    void rbtree_delete_fixup(rbnode *x) {
        rbnode *w;
        while (x != this->root && x->color == black) {
            if (x == x->parent->left) {
                w = x->parent->right;
                if (w->color == red) {
                    
                    w->color = black;
                    x->parent->color = red;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == black && w->right->color == black) {
                    
                    w->color = red;
                    x = x->parent;
                } else {
                    if (w->right->color == black) {
                        
                        w->left->color = black;
                        w->color = red;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    left_rotate(x->parent);
                    x = this->root;
                }
            } else {
                w = x->parent->left;
                if (w->color == red) {
                    
                    w->color = black;
                    x->parent->color = red;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == black && w->left->color == black) {
                    
                    w->color = red;
                    x = x->parent;
                } else {
                    if (w->left->color == black) {
                        
                        w->right->color = black;
                        w->color = red;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    right_rotate(x->parent);
                    x = this->root;
                }
            }
        }
        x->color = black;
        return;
    }

    void rbtree_insert_fixup(rbnode *z) {
        rbnode *y;
        while (z->parent->color == red) {
            if (z->parent == z->parent->parent->left) {
                y = z->parent->parent->right;
                if (y->color == red) {
                    
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                } else {
                    
                    if (z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);
                    }
                    
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    right_rotate(z->parent->parent);
                }
            } else {
                y = z->parent->parent->left;
                if (y->color == red) {
                    
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        
                        z = z->parent;
                        right_rotate(z);
                    }
                    
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    left_rotate(z->parent->parent);
                }
            }
        }
        this->root->color = black;
        return;
    }

public:
    class rbnode {
    public:
        int value;
        enum color color;
        int size;
        rbnode *parent, *left, *right;

        rbnode() {
            
            this->value = -1;
            this->size = 0;
            this->color = black;
            this->left = this->right = NULL;
        }

        rbnode(int key, enum color color) {
            
            this->color = color;
            this->value = key;
            this->size = 1;
            this->left = this->right = this->parent = NULL;
        }
    };

    enum color {
        red, black
    };

    rbtree() {
        nil = new rbnode();
        root = nil;
    }

    rbnode *newnode(int key, enum color color) {
        
        rbnode *temp = new rbnode(key, color);
        temp->left = temp->right = this->nil;
        return temp;
    }

    rbnode *tree_minimum(rbnode *x) {
        
        while (x->left != nil)
            x = x->left;
        return x;
    }

    rbnode *tree_successor(rbnode *x) {
        rbnode *y;
        
        if (x->right != nil) {
            return tree_minimum(x->right);
        } else {
            
            y = x->parent;
            while (y != nil && y->right == x) {
                x = y;
                y = y->parent;
            }
            return y;
        }
    }
    void rbtree_delete(rbnode*z){
        rbnode*x,*y,*tobechangesize;
        
        y=z;
        enum color y_original_color=y->color;
        if(z->left == this->nil){
            tobechangesize=z->parent;
            x=z->right;
            rbtree_transplant(z,z->right);
        }else if(z->right==this->nil){
            tobechangesize=z->parent;
            x=z->left;
            rbtree_transplant(z,z->left);
        }else{
            y=tree_minimum(z->right);
            y_original_color=y->color;
            x=y->right;
            if(y->parent==z){
                x->parent=y;
                tobechangesize=y;
            }
            else{
                tobechangesize=y->parent;
                rbtree_transplant(y,y->right);
                y->right=z->right;
                y->right->parent=y;
            }
            rbtree_transplant(z,y);
            y->left=z->left;
            y->left->parent=y;
            y->color=z->color;
        }
        
        while(tobechangesize!=nil){
            tobechangesize->size=tobechangesize->left->size+tobechangesize->right->size+1;
            tobechangesize=tobechangesize->parent;
        }

        if(y_original_color==black){
            rbtree_delete_fixup(x);
        }
        return ;
    }
    rbnode* os_select(rbnode*x,int i){
        
        int k=x->left->size+1;
        if(i==k)return x;
        else if(i<k) return os_select(x->left,i);
        else return os_select(x->right,i-k);
    }

    void rbtree_insert(rbnode*z){
        rbnode *x,*y;
        y=this->nil;
        x=this->root;
        while(x!=this->nil){
            y=x;
            if(z->value<x->value)
                x=x->left;
            else
                x=x->right;
        }
        z->parent=y;
        if(y==this->nil){
            this->root=z;
        }else if(z->value<y->value){
            y->left=z;
        }else{
            y->right=z;
        }
        z->left=this->nil;
        z->right=this->nil;
        z->color=red;

        
        y=z;
        for(y=z;y!=this->root;y=y->parent){
            y->parent->size=y->parent->right->size+y->parent->left->size+1;
        }
        rbtree_insert_fixup(z);
        return ;
    }
};

int main(){
    int values[20000];
    

    int i;

    
    ifstream data_in;
    data_in.open("../input/data.txt");
    for(i=0;i<TESTSIZE;i++)
        data_in>>values[i];
    data_in.close();


    ofstream data_out;

    
    data_out.open("../output/size40/time1.txt");

    rbtree T;
    clock_t BeginTime,EndTime;
    BeginTime=clock();
    for(i=0;i<TESTSIZE;i++){
        if(i%10==0){
            EndTime=clock();
            data_out<<EndTime-BeginTime<<endl;
        }
        T.rbtree_insert(T.newnode(values[i],red));
    }
    EndTime=clock();
    data_out<<EndTime-BeginTime<<endl;

    data_out.close();



    
    BeginTime=clock();
    rbnode*tobedelete=T.os_select(T.root,TESTSIZE/3);
    cout<<"通过红黑树查找的结果：1/3:"<<tobedelete->value<<endl;
    T.rbtree_delete(tobedelete);
    delete tobedelete;

    tobedelete=T.os_select(T.root,TESTSIZE/3*2);
    cout<<"通过红黑树查找的结果：2/3:"<<tobedelete->value<<endl;
    T.rbtree_delete(tobedelete);
    delete tobedelete;
    EndTime=clock();
    cout<<"总共耗时："<<EndTime-BeginTime<<"ms"<<endl;
    data_out.open("../output/size40/time2.txt");
    data_out<<EndTime-BeginTime<<"ms"<<endl;
    data_out.close();

    
    FILE*dumper_fp=fopen("get_a_pic.dot","w");
    DumpDOT *dumper=new DumpDOT(dumper_fp);
    T.dumpdot(T.root,dumper);
    delete dumper;
    fclose(dumper_fp);

    return 0;
}