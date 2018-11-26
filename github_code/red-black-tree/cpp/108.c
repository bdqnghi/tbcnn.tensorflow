#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

template <class T>
class RedBlackTree;

template <class T>
class RedBlackNode;

template <class T>
class RedBlackTree
{
public:
    RedBlackTree(const T & negInf);
    ~RedBlackTree();

    void insert(const T & x);

    typedef RedBlackNode<T> Node;
private:
    Node *header;
    Node *nullNode;

    Node *current;
    Node *parent;  //fu jie dian
    Node *grand;    //zu fu
    Node *great;    //zeng zu fu
};

template <class T>
class RedBlackNode
{
    T            element;
    RedBlackNode *left, *right;
    int          color;
    enum {RED, BLACK};

    RedBlackNode(const T & theElement = T(), RedBlackNode * lt = NULL, RedBlackNode *rt = NULL, int c = RedBlackNode<T>::BLACK)
                :element(theElement), left(lt), right(rt), color(c){}

    friend class RedBlackTree<T>;
};

template <class T>
RedBlackTree<T>::RedBlackTree(const T &negInf)
{
    nullNode = new Node();
    nullNode->left = nullNode->right = nullNode;
    header = new Node(negInf);
    header->left = header->right = nullNode;
}

template <class T>
RedBlackTree<T>::~RedBlackTree()
{
    delete nullNode;
    delete header;
}

template <class T>
void RedBlackTree<T>::insert(const T & x)
{
    current = parent = grand = header;
    nullNode->element = x;

    while(current->element != x)
    {
        great = grand;
        grand = parent;
        parent = current;
        current = x < current->element ? current->left : current->right;
    }

    if(current != nullNode)
        throw DuplicateItemException();

    current = new Node(x, nullNode, nullNode);

    if(x < parent->element)
        parent->left = current;
    else
        parent->right = current;
}

#endif // REDBLACKTREE_H
