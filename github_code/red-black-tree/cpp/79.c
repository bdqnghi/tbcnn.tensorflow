#include "BinarySearchTree.h"
#include <assert.h>
#include <iomanip>

using namespace std;

template<class T>
class RedBlackTree : public BinarySearchTree<T>
{
public:
  RedBlackTree();

  BNode<T> * grandParent(BNode<T> * node);
  BNode<T> * uncle(BNode<T> * node);
  BNode<T> * sibling(BNode<T> * node);
  BNode<T> * maximum_node(BNode<T> * node);

  string color(BNode<T> * node);

  void rotateLeft(RedBlackTree * tree, BNode<T> * node);
  void rotateRight(RedBlackTree * tree, BNode<T> * node);

  void insertRedBlack(T value);
  void insertCase1(RedBlackTree * tree, BNode<T> * node);
  void insertCase2(RedBlackTree * tree, BNode<T> * node);
  void insertCase3(RedBlackTree * tree, BNode<T> * node);
  void insertCase4(RedBlackTree * tree, BNode<T> * node);
  void insertCase5(RedBlackTree * tree, BNode<T> * node);

  void deleteRedBlack(T value);
  void deleteCase1(RedBlackTree * tree, BNode<T> * node);
  void deleteCase2(RedBlackTree * tree, BNode<T> * node);
  void deleteCase3(RedBlackTree * tree, BNode<T> * node);
  void deleteCase4(RedBlackTree * tree, BNode<T> * node);
  void deleteCase5(RedBlackTree * tree, BNode<T> * node);
  void deleteCase6(RedBlackTree * tree, BNode<T> * node);

  void isRedBlack(RedBlackTree * tree);
  void property1(BNode<T> * node);
  void property2(BNode<T> * node);
  void property4(BNode<T> * node);

};

template<class T>
RedBlackTree<T>::RedBlackTree() : BinarySearchTree<T>() {}

template<class T>
BNode<T> * RedBlackTree<T>::grandParent(BNode<T> * node)
{
    if(node != nullptr && node->getParent() != nullptr)
        return node->getParent()->getParent();
    else
        return nullptr;
}

template<class T>
BNode<T> * RedBlackTree<T>::uncle(BNode<T> * node)
{
    BNode<T> * grandparent = grandParent(node);

    if(grandparent == nullptr)
        return nullptr;
    else if(node->getParent() == grandparent->getLeft())
        return grandparent->getRight();
    else
        return grandparent->getLeft();
}

template<class T>
BNode<T> * RedBlackTree<T>::sibling(BNode<T> * node)
{
    if(node != nullptr && node->getParent() != nullptr)
    {
        if(node == node->getParent()->getLeft())
            return node->getParent()->getRight();
        else
            return node->getParent()->getLeft();
    }
    else
        return nullptr;
}

template<class T>
BNode<T> * RedBlackTree<T>::maximum_node(BNode<T> * node)
{
    while (node->getRight() != nullptr)
    {
        node = node->getRight();
    }
    return node;
}

template<class T>
string RedBlackTree<T>::color(BNode<T> * node)
{
    if(node == nullptr)
        return "black";
    else
        return node->getColor();
}

template<class T>
void RedBlackTree<T>::rotateLeft(RedBlackTree * tree, BNode<T> * item)
{
    BNode<T> *right = item->getRight();

    item->setRight(right->getLeft());

    if (item->getRight() != nullptr)
        item->getRight()->setParent(item);

    right->setParent(item->getParent());

    if (item->getParent() == nullptr)
        this->setRoot(right);

    else if (item == item->getParent()->getLeft())
        item->getParent()->setLeft(right);

    else
        item->getParent()->setRight(right);

    right->setLeft(item);
    item->setParent(right);
}

template<class T>
void RedBlackTree<T>::rotateRight(RedBlackTree * tree, BNode<T> * item)
{
    BNode<T> *left = item->getLeft();

    item->setLeft(left->getRight());

    if (item->getLeft() != nullptr)
        item->getLeft()->setParent(item);

    left->setParent(item->getParent());

    if (item->getParent() == nullptr)
        this->setRoot(left);

    else if (item == item->getParent()->getLeft())
        item->getParent()->setLeft(left);

    else
        item->getParent()->setRight(left);

    left->setRight(item);
    item->setParent(left);
}

template<class T>
void RedBlackTree<T>::insertRedBlack(T value)
{
    BNode<T> * node = this->insert(value);
    node->setColor("red");
    insertCase1(this, node);
}

template<class T>
void RedBlackTree<T>::insertCase1(RedBlackTree * tree, BNode<T> * node)
{
    if(node->getParent() == nullptr)
        node->setColor("black");
    else
        insertCase2(this, node);
}

template<class T>
void RedBlackTree<T>::insertCase2(RedBlackTree * tree, BNode<T> * node)
{
    if(node->getParent()->getColor() == "black")
        return;
    else
        insertCase3(this, node);
}

template<class T>
void RedBlackTree<T>::insertCase3(RedBlackTree * tree, BNode<T> * node)
{
    if(color(uncle(node)) == "red")
    {
        node->getParent()->setColor("black");
        uncle(node)->setColor("black");
        grandParent(node)->setColor("red");
        insertCase1(tree, grandParent(node));
    }
    else
    {
        insertCase4(tree, node);
    }
}

template<class T>
void RedBlackTree<T>::insertCase4(RedBlackTree * tree, BNode<T> * node)
{
    if(node == node->getParent()->getRight() && node->getParent() == grandParent(node)->getLeft())
    {
        rotateLeft(tree, node->getParent());
        node = node->getLeft();
    }
    else if(node == node->getParent()->getLeft() && node->getParent() == grandParent(node)->getRight())
    {
        rotateRight(tree, node->getParent());
        node = node->getRight();
    }
    insertCase5(tree, node);
}

template<class T>
void RedBlackTree<T>::insertCase5(RedBlackTree * tree, BNode<T> * node)
{
    node->getParent()->setColor("black");
    grandParent(node)->setColor("red");
    if (node == node->getParent()->getLeft() && node->getParent() == grandParent(node)->getLeft())
    {
        rotateRight(tree, grandParent(node));
    }
    else
    {
        rotateLeft(tree, grandParent(node));
    }
}

template <class T>
void RedBlackTree<T>::deleteRedBlack(T value)
{
    BNode<T> * des;
    BNode<T> * node;
    node = this->getNode(value);

    if (node == nullptr)
        return;

    if (node->getLeft() != nullptr && node->getRight() != nullptr)
    {
        BNode<T> * pred = maximum_node(node->getLeft());
        node->setInfo(pred->getInfo());
        node = pred;
    }

    des = node->getRight() == nullptr ? node->getLeft()  : node->getRight();
    if (color(node) == "black")
    {
        node->getColor() = color(des);
        deleteCase1(this, node);
    }

    if (node->getParent() == nullptr)
    {
        this->setRoot(des);
    }
    else
    {
        if (node == node->getParent()->getLeft())
            node->getParent()->setLeft(des);
        else
            node->getParent()->setRight(des);
    }

    if (des != nullptr)
    {
        des->setParent(node->getParent());
    }

    delete node;
    isRedBlack(this);
}

template <class T>
void RedBlackTree<T>::deleteCase1(RedBlackTree * tree, BNode<T> * node)
{

    if(node->getParent() == nullptr)
        return;
    else
        deleteCase2(this, node);
}

template <class T>
void RedBlackTree<T>::deleteCase2(RedBlackTree * tree, BNode<T> * node)
{
    BNode<T> * s = sibling(node);

    if (s->getColor() == "red")
    {
        node->getParent()->setColor("red");
        s->setColor("black");
        if (node == node->getParent()->getLeft())
            rotateLeft(this, node->getParent());
        else
            rotateRight(this, node->getParent());
    }

    deleteCase3(this, node);
}

template <class T>
void RedBlackTree<T>::deleteCase3(RedBlackTree * tree, BNode<T> * node)
{
    BNode<T> * s = sibling(node);
    if (color(node->getParent()) == "black" && color(s) == "black" && color(s->getLeft()) == "black" && color(s->getRight()) == "black")
    {
        s->setColor("red");
        deleteCase1(this, node->getParent());
    }
    else
    {
        deleteCase4(this, node);
    }
}

template <class T>
void RedBlackTree<T>::deleteCase4(RedBlackTree * tree, BNode<T> * node)
{
    BNode<T> * s = sibling(node);
    if (color(node->getParent()) == "red" && color(s) == "black" &&  color(s->getLeft()) == "black" && color(s->getRight()) == "black")
    {
        s->setColor("red");
        node->getParent()->setColor("black");
    }
    else
    {
        deleteCase5(this, node);
    }
}

template<class T>
void RedBlackTree<T>::deleteCase5(RedBlackTree * tree, BNode<T> * node)
{
    BNode<T> * s = sibling(node);
    if (node == node->getParent()->getLeft() && color(s) == "black" && color(s->getLeft()) == "red" && color(s->getRight()) == "black")
    {
        s->setColor("red");
        s->getLeft()->setColor("black");
        rotateRight(this, s);
    }
    else if (node == node->getParent()->getRight() && color(s) == "black" && color(s->getRight()) == "red" && color(s->getLeft()) == "black")
    {
        s->setColor("red");
        s->getRight()->setColor("black");
        rotateLeft(this, s);
    }

    deleteCase6(this, node);
}

template<class T>
void RedBlackTree<T>::deleteCase6(RedBlackTree * tree, BNode<T> * node)
{
    BNode<T> * s = sibling(node);
    s->setColor(color(node->getParent()));
    node->getParent()->setColor("black");
    if (node == node->getParent()->getLeft())
    {
        s->getRight()->setColor("black");
        rotateLeft(this, node->getParent());
    }
    else
    {
        s->getLeft()->setColor("black");
        rotateRight(this, node->getParent());
    }
}

template<class T>
void RedBlackTree<T>::isRedBlack(RedBlackTree * tree)
{
    property1(tree->getRoot());
    property2(tree->getRoot());
    property4(tree->getRoot());
    // Missing verification of property 5.
}

template<class T>
void RedBlackTree<T>::property1(BNode<T> * node)
{
    if(node == nullptr)
        return;
    if(node->getColor() == "black" || node->getColor() == "red")
    {
        // PROPERTY 1 VALID.
    } else {
        cout << "PROPERTY 1 INVALID: Node is not red or black." << endl;
    }
    property1(node->getLeft());
    property1(node->getRight());
}

template<class T>
void RedBlackTree<T>::property2(BNode<T> * node)
{
    if(node->getColor() != "black")
    {
        cout << "PROPERTY 2 INVALID: Root is not black." << endl;
    }
}

template<class T>
void RedBlackTree<T>::property4(BNode<T> * node)
{
    if (node == nullptr)
        return;

    if (color(node) == "red")
    {
        if(color(node->getLeft()) != "black")
        {
            cout << "PROPERTY 4 INVALID: Left son of a red node is not black." << endl;
        }
        if(color(node->getRight()) != "black")
        {
            cout << "PROPERTY 4 INVALID: Right son of a red node is not black." << endl;
        }
        if(color(node->getParent()) != "black")
        {
            cout << "PROPERTY 4 INVALID: Parent of red node is not black." << endl;
        }
    }
    property4(node->getLeft());
    property4(node->getRight());
}
