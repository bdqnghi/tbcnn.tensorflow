#include <iostream>
using namespace std;

template <class T>
class AVLTreeNode{
    public:
        T key;                
        int height;         
        AVLTreeNode *left;    
        AVLTreeNode *right;    

        AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode *r):
            key(value), height(0),left(l),right(r) {}
};

template <class T>
class AVLTree {
    private:
        AVLTreeNode<T> *mRoot;    

    public:
        AVLTree():mRoot(NULL){};
        ~AVLTree();

        
        int height();
        
        T max(T a, T b);

        
        T minimum();
        
        T maximum();

        AVLTreeNode<T>* search(T key);


        
        void insert(T key);

        
        void remove(T key);

        
        void destroy();

        void Preorder();
    private:
        
        int height(AVLTreeNode<T>* tree) ;

        
        AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
        
        AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

        
        AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* k2);

        
        AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* k1);

        
        AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* k3);

        
        AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* k1);

        AVLTreeNode<T>* search(AVLTreeNode<T>* &tree, T key);

        
        AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);

        
        AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);

        
        void destroy(AVLTreeNode<T>* &tree);

        void preorder(AVLTreeNode<T>* &tree);
        
        void print(AVLTreeNode<T>* tree, T key, int direction);
};

template <class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree){
    if(tree != NULL){
        return tree->height;
    }

    return 0;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree){
    if(tree == NULL)
        return tree;
    while(tree->left != NULL){
        tree = tree->left;
    }
    return tree;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree){
    if(tree == NULL)
        return tree;
    while(tree->right != NULL){
        tree = tree->right;
    }
    return tree;
}

template <class T>
T AVLTree<T>::max(T a, T b){
    return a>b?a:b;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* k2){
    AVLTreeNode<T>* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;

    return k1;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1){
    AVLTreeNode<T> * k2 = k1->left;
    k1->left = k2->right;
    k2->right = k1;

    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->left), height(k2->right)) + 1;

    return k2;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* k3){
    AVLTreeNode<T> *k1 = k3->left;

    k3->left = leftLeftRotation(k1);

    return rightRightRotation(k3);
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1){
    k1->right = rightRightRotation(k1->right);

    return leftLeftRotation(k1);
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* &tree, T key){
    if(tree == NULL || tree->key == key){

        return tree;
    } else if(key > tree->key){
        return search(tree->right, key);
    } else return search(tree->left, key);
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key){
    if(tree == NULL){
        tree = new AVLTreeNode<T>(key, NULL, NULL);
        if(tree == NULL){
            cout<<"ERROR: create AVLTreeNode failed!"<<endl;
            return tree;
        }
    } else if(key < tree->key){
        tree->left = insert(tree->left, key);
        if(height(tree->left) - height(tree->right) == 2){
            if(key < tree->left->key) {
                tree = rightRightRotation(tree);
            } else{
                tree = leftRightRotation(tree);
            }
        }
    } else if(key > tree->key) {
        tree->right = insert(tree->right, key);
        if(height(tree->right) - height(tree->left) == 2){
            if(key > tree->right->key) {
                tree = leftLeftRotation(tree);
            } else {
                tree = rightLeftRotation(tree);
            }
        }
    } else {
        cout<<"WARN: can not insert the exist node"<<endl;
        return tree;
    }

    tree->height = max(height(tree->left), height(tree->right)) + 1;
    return tree;
}


template <class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z){
    if(tree == NULL || z == NULL){
        return NULL;
    }

    if(z->key < tree->key){
        tree->left = remove(tree->left, z);

        if(height(tree->right) - height(tree->left) == 2){
            if(height(tree->right->left) > height(tree->right->right)){
                tree = rightLeftRotation(tree);
            }
            else {
                tree = leftLeftRotation(tree);
            }
        }
    } else if(z->key > tree->key){
        tree->right = remove(tree->right, z);

        if(height(tree->left) - height(tree->right) == 2){
            if(height(tree->left->right) > height(tree->left->left)){
                tree = leftRightRotation(tree);
            }
            else {
                tree = rightRightRotation(tree);
            }
        }
    } else {
        if(tree->left && tree->right){
            if(height(tree->left) > height(tree->right)){
                AVLTreeNode<T> *left_max = maximum(tree->left);
                tree->key = left_max->key;
                tree->left = remove(tree->left, left_max);
            }
            else {
                AVLTreeNode<T> *right_min = minimum(tree->right);
                tree->key = right_min->key;
                tree->right = remove(tree->right, right_min);
            }
        }
        else {
           AVLTreeNode<T>* tmp = tree;
           tree = tree->left ? tree->left:tree->right;
           delete tmp;
        }
    }
    return tree;
}

template <class T>
void AVLTree<T>::preorder(AVLTreeNode<T>* &tree){
    if(tree == NULL){
        return;
    } else {
        cout<<tree->key<<" ";
        preorder(tree->left);
        preorder(tree->right);
    }
}


template <class T>
void AVLTree<T>::destroy(AVLTreeNode<T>* &tree){

}


template <class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction){

}

template <class T>
int AVLTree<T>::height(){
    return height(mRoot);
}


template <class T>
T AVLTree<T>::minimum(){
AVLTreeNode<T>* p = minimum(mRoot);

    if(p != NULL){
        return p->key;
    }

    return (T)NULL;
}


template <class T>
T AVLTree<T>::maximum(){
    AVLTreeNode<T>* p = maximum(mRoot);

    if(p != NULL){
        return p->key;
    }

    return (T)NULL;
}

template <class T>
AVLTreeNode<T>* AVLTree<T>::search(T key){
    return search(mRoot, key);
}


template <class T>
void AVLTree<T>::insert(T key){
    insert(mRoot, key);
}


template <class T>
void AVLTree<T>::remove(T key){
    AVLTreeNode<T>* a_node = search(key);
    if(a_node != NULL){
        mRoot = remove(mRoot, a_node);
    }
}

template <class T>
void AVLTree<T>::Preorder(){
    preorder(mRoot);
}



static int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};

#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
    int i,ilen;
    AVLTree<int>* tree=new AVLTree<int>();

    cout << "== 依次添加: ";
    ilen = TBL_SIZE(arr);
    for(i=0; i<ilen; i++)
    {
        cout << arr[i] <<" ";
        tree->insert(arr[i]);
    }

    cout << "\n== 前序遍历: ";
    tree->Preorder();


    cout << "== 高度: " << tree->height() << endl;
    cout << "== 最小值: " << tree->minimum() << endl;
    cout << "== 最大值: " << tree->maximum() << endl;


    for(i = 1; i <= 16; i++){
        cout << "\n== 删除根节点: " << i;
        tree->remove(i);
        cout << "\n== 高度: " << tree->height() ;
        cout << "\n== 中序遍历: " ;
        tree->Preorder();
    }


    return 0;
}
