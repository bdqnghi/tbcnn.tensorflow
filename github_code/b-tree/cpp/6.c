/*
* Author: Edimar Jacob Bauer
* Email: edimarjb@gmail.com
* Date: February 17, 2018
*/

#include <bits/stdc++.h>

using namespace std;
#define N (1 << 24)
#define BLACK 0
#define RED 1

int last, total;

struct Tree{
    bool color;
    int key;
    struct Tree *left, *right, *parent;
};

Tree* newNode(Tree *parent, int x);
Tree *mySibling(Tree *tree);
Tree* myAvo(Tree *tree);
Tree* myUncle(Tree *avo, Tree *tree);
Tree* updateRoot(Tree *tree);
Tree* search(Tree *tree, int x);

void rotate_left(Tree *tree);
void rotate_right(Tree *tree);
void treat_inclusion(Tree *tree);
Tree* insert(Tree *tree, int x);

void delete_node(Tree *tree);
int replace(Tree *head, Tree *tree);
void treat_exclusion(Tree *tree);
Tree* remove(Tree *tree, int x);

void print(Tree *tree, int i);
void check_is_correct(Tree *tree);
int check(Tree *tree, int color);


int main(){

    Tree *tree = NULL;
    int x;

    for (int j = 0; j < 2; j++){
        printf("Inserting...\n");
        for (int i = 0; i < N; i++){
            x = rand() % N;
            tree = insert(tree, x);
            //check_is_correct(tree);
        }

        printf("Deleting...\n");
        for (int i = 0; i < N; i++){
            x = rand() % N;
            tree = remove(tree, x);
            //check_is_correct(tree);
        }
    }
}


//#######################################################################################################################
//#######################################################################################################################


Tree* newNode(Tree *parent, int x){

    Tree* tree = (Tree*)malloc(sizeof(Tree));
    if (tree == NULL) {
        puts("Err of allocation");
        exit(0);
    }
    total++;
    tree->color = RED;
    tree->key = x;
    tree->parent = parent;
    tree->left = tree->right = NULL;
    return tree;
}

Tree *mySibling(Tree *tree){
    assert(tree); assert(tree->parent);
    if (tree->parent->left == tree) return tree->parent->right;
    return tree->parent->left;
}

Tree* myAvo(Tree *tree){
    if(tree != NULL and tree->parent != NULL) return tree->parent->parent;
    return NULL;
}

Tree* myUncle(Tree *avo, Tree *tree){
    assert(tree); assert(avo);
    if (avo->left == tree->parent) return avo->right;
    return avo->left;
}

Tree* updateRoot(Tree *tree){
    if (tree == NULL) return NULL;
    while(tree->parent != NULL) tree = tree->parent;
    return tree;
}

Tree* search(Tree *tree, int x){

    while(tree != NULL){
        if (x == tree->key) return tree;
        if (x < tree->key) tree = tree->left;
        else tree = tree->right;
    }

    return NULL;
}





void rotate_left(Tree *tree){

    //puts("Rotate left");
    assert(tree);
    if (tree->parent != NULL)
        if (tree == tree->parent->left)
            tree->parent->left = tree->right;
        else
            tree->parent->right = tree->right;

    tree->right->parent = tree->parent;
    tree->parent = tree->right;
    tree->right = tree->right->left;
    tree->parent->left = tree;
    if (tree->right) tree->right->parent = tree;
}

void rotate_right(Tree *tree){

    //puts("Rotate right");
    assert(tree);
    if (tree->parent != NULL)
        if (tree == tree->parent->left)
            tree->parent->left = tree->left;
        else
            tree->parent->right = tree->left;

    tree->left->parent = tree->parent;
    tree->parent = tree->left;
    tree->left = tree->left->right;
    tree->parent->right = tree;
    if (tree->left) tree->left->parent = tree;
}

void treat_inclusion(Tree *tree){

    assert(tree);
    if (tree->parent == NULL){
        tree->color = BLACK;
        return;
    }
    if (tree->parent->color == BLACK) return;

    Tree *avo = myAvo(tree);
    Tree *uncle = myUncle(avo, tree);
    if (uncle != NULL and uncle->color == RED){
        uncle->color = tree->parent->color = BLACK;
        avo->color = RED;
        treat_inclusion(avo);
        return;
    }

    if (tree == tree->parent->right && tree->parent == avo->left){
        rotate_left(tree->parent);
        tree = tree->left;
    }else if (tree == tree->parent->left && tree->parent == avo->right){
        rotate_right(tree->parent);
        tree = tree->right;
    }

    tree->parent->color = BLACK;
    avo->color = RED;
    if (tree == tree->parent->left) rotate_right(avo);
    else rotate_left(avo);
}

Tree* insert(Tree *tree, int x){

    if (tree == NULL) {
        tree = newNode(NULL, x);
        tree->color = BLACK;
        return tree;
    }

    Tree *head = tree;
    while(tree->key != x){
        if (x < tree->key){
            if (tree->left != NULL) tree = tree->left;
            else {
                tree->left = newNode(tree, x);
                break;
            }
        }else{
            if (tree->right != NULL) tree = tree->right;
            else {
                tree->right = newNode(tree, x);
                break;
            }
        }
    }

    if (tree->key == x) return head;    //means that the element already inserted and nothing was do

    if (tree->left != NULL && tree->left->key == x) treat_inclusion(tree->left);
    else treat_inclusion(tree->right);

    return updateRoot(head);
}





void delete_node(Tree *tree){

    assert(tree);
    Tree *child = (tree->left) ? tree->left : tree->right;
    if (tree->parent != NULL){
        if (tree->parent->left == tree) tree->parent->left = child;
        else tree->parent->right = child;
    }
    if (child) child->parent = tree->parent;

    free(tree);
    total--;
}

void treat_exclusion(Tree *tree){

    assert(tree);
    //printf("Treating %d\n", tree->key);
    //case 1, node is the root, nothing to do
    if (tree->parent){
        Tree *sibling = mySibling(tree);
        //case 2, only sibling is red. Ajusts for case 4 or 6
        if (sibling->color == RED){
            swap(sibling->color, tree->parent->color);
            if (tree == tree->parent->right) rotate_right(tree->parent);
            else rotate_left(tree->parent);
            sibling = mySibling(tree);
        //case 3, father and sibling are black, nephews do not exists or they are black. Recursion on father required
        }else if (tree->parent->color == BLACK and (sibling->left == NULL || sibling->left->color == BLACK) and
                  (sibling->right == NULL || sibling->right->color == BLACK)){
            sibling->color = RED;
            treat_exclusion(tree->parent);
            return;
        }
        //case 4, only father is red
        if (tree->parent->color && (!sibling->right || !sibling->right->color) && (!sibling->left || !sibling->left->color)){
            sibling->color = RED;
            tree->parent->color = BLACK;
        }else {
            //case 5, nephew nearest is red. Adjusts for case 6
            if (tree == tree->parent->left && sibling->left && sibling->left->color == RED){
                swap(sibling->color, sibling->left->color);
                rotate_right(sibling);
                sibling = sibling->parent;
            }else if (tree == tree->parent->right && sibling->right && sibling->right->color == RED){
                swap(sibling->color, sibling->right->color);
                rotate_left(sibling);
                sibling = sibling->parent;
            }
            //case 6, nephew farthest is red
            swap(tree->parent->color, sibling->color);
            if (tree == tree->parent->left){
                sibling->right->color = BLACK;
                rotate_left(tree->parent);
            }else{
                sibling->left->color = BLACK;
                rotate_right(tree->parent);
            }
        }
    }
}

int replace(Tree *tree){

    assert(tree);
    while(tree->left != NULL)
        tree = tree->left;

    int x = tree->key;

    if (tree->color == BLACK){
        if (tree->right && tree->right->color == RED) tree->right->color = BLACK;
        else treat_exclusion(tree);
    }

    delete_node(tree);
    return x;
}

Tree* remove(Tree *tree, int x){

    Tree *head = tree;
    tree = search(tree, x);
    if (!tree){
        //puts("Element do not exists");
        return head;
    }

    if (!tree->left && !tree->right){
        //cout << "NULL childs of " << tree->key << endl;
        if (tree->parent == NULL)head = NULL;   //if is the root
        else if (tree->color == BLACK) treat_exclusion(tree);
    }else if (tree->left && tree->right) {
        //printf("Two childs of %d\n", tree->key);
        tree->key = replace(tree->right);
        return updateRoot(head);
    }else{
        //printf("One child of %d\n", tree->key);
        if (tree->color == BLACK){
            Tree *child = (tree->left) ? tree->left : tree->right;
            if (tree == head) head = child; //case the element that will be removed is the root
            if (child->color == RED) child->color = BLACK;
            else treat_exclusion(tree);
        }
    }

    delete_node(tree);
    return updateRoot(head);
}





void print(Tree *tree, int height){

    if (tree == NULL) return;

    print(tree->left, height+1);
    cout << tree->key << " color: " << tree->color << " height:" << height << endl;
    print(tree->right, height+1);
}

void check_is_correct(Tree *tree){

    last = -1;
    int tot = total;
    check(tree, RED);
    if (total != 0) printf("Diference of %d elements\n", total);
    total = tot;
}

int check(Tree *tree, int color){

    if (tree == NULL) return 0;

    total--;
    if (color && tree->color){
        printf("Consecutive red in %d and %d\n", tree->color, tree->parent->color);
        exit(0);
        return -1;
    }

    int l, r;
    l = check(tree->left, tree->color);
    if (last >= tree->key){
        printf("Err in %d and %d\n", last, tree->key);
        exit(0);
    }
    last = tree->key;
    r = check(tree->right, tree->color);

    if (l != r){
        if (l != -1 && r != -1)
            printf("Err in quantity of black childs, starting the parent %d\n", tree->key);
        exit(0);
        return -1;
    }

    if (tree->color == BLACK) l++;
    return l;
}

