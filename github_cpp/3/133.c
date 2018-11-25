#include "avl-tree.h"

struct Node
{
    int value;
    int height;
    Node *leftChild;
    Node *rightChild;
};

struct Tree
{
    Node *root;
};

Node *createNode(int value)
{
    Node *node = new Node;
    node->value = value;
    node->height = 1;
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    return node;
}

Tree *createTree()
{
    Tree *tree = new Tree;
    tree->root = nullptr;
    return tree;
}

int countHeight(Node *node)
{
    return node ? node->height : 0;
}

int balanceFactor(Node *node)
{
    return countHeight(node->rightChild) - countHeight(node->leftChild);
}

void updateHeight(Node *node)
{
    int heightLeft = countHeight(node->leftChild);
    int heightRight = countHeight(node->rightChild);
    node->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
}

Node *rotateRight(Node* node)
{
    Node *pivot = node->leftChild;
    node->leftChild = pivot->rightChild;
    pivot->rightChild = node;
    updateHeight(node);
    updateHeight(pivot);
    return pivot;
}

Node *rotateLeft(Node* node)
{
    Node *pivot = node->rightChild;
    node->rightChild = pivot->leftChild;
    pivot->leftChild = node;
    updateHeight(node);
    updateHeight(pivot);
    return pivot;
}

Node *balance(Node* node)
{
    updateHeight(node);
    if (balanceFactor(node) == 2)
    {
        if (balanceFactor(node->rightChild) < 0)
            node->rightChild = rotateRight(node->rightChild);

        return rotateLeft(node);
    }
    if (balanceFactor(node) == -2)
    {
        if (balanceFactor(node->leftChild) > 0)
            node->leftChild = rotateLeft(node->leftChild);

        return rotateRight(node);
    }
    return node;
}

void addElement(Node* &node, int value)
{
    if (node == nullptr)
        node = createNode(value);
    else
    {
        if (node->value < value)
            addElement(node->rightChild, value);
        if (node->value > value)
            addElement(node->leftChild, value);
        node = balance(node);
    }
}

void addElement(Tree *tree, int value)
{
    addElement(tree->root, value);
}

void printIncreasingOrder(Node *node)
{
    if (node != nullptr)
    {
        printIncreasingOrder(node->leftChild);
        cout << node->value << " ";
        printIncreasingOrder(node->rightChild);
    }
}

void printIncreasingOrder(Tree *tree)
{
    printIncreasingOrder(tree->root);
}

void printDecreasingOrder(Node *node)
{
    if (node != nullptr)
    {
        printDecreasingOrder(node->rightChild);
        cout << node->value << " ";
        printDecreasingOrder(node->leftChild);
    }
}

void printDecreasingOrder(Tree *tree)
{
    printDecreasingOrder(tree->root);
}

void printPreorder(Node *node)
{
    if (node != nullptr)
    {
        cout << "(" << node->value << " ";
        printPreorder(node->leftChild);
        printPreorder(node->rightChild);
        cout << ") ";
    }
    else
        cout << "NULL ";
}

void printPreorder(Tree *tree)
{
    printPreorder(tree->root);
}

bool exists(Node *node, int value)
{
    if (node != nullptr)
    {
        if (node->value < value)
            return exists(node->rightChild, value);
        if (node->value > value)
            return exists(node->leftChild, value);
        return true;
    }
    return false;
}

bool exists(Tree *tree, int value)
{
    return exists(tree->root, value);
}

enum NodeType
{
    noChildren,
    onlyLeftChild,
    onlyRightChild,
    twoChildren
};

NodeType determineType(Node *node)
{
    if (node->leftChild == nullptr && node->rightChild == nullptr)
        return noChildren;
    if (node->leftChild == nullptr)
        return onlyRightChild;
    if (node->rightChild == nullptr)
        return onlyLeftChild;

    return twoChildren;
}

void removeNodeWithNoChildren(Node* &node)
{
    delete node;
    node = nullptr;
}
void removeNodeWithLeftChild(Node* &node)
{
    Node* currentNode = node;
    node = node->leftChild;
    delete currentNode;
    currentNode = nullptr;
}
void removeNodeWithRightChild(Node* &node)
{
    Node *currentNode = node;
    node = node->rightChild;
    delete currentNode;
    currentNode = nullptr;
}

int findMin(Node* node)
{
    while (node->leftChild != nullptr)
        node = node->leftChild;

    int value = node->value;

    return value;
}

void deleteElement(Node* &node, int value);

void removeNodeWithTwoChildren(Node* &node)
{
    int value = findMin(node->rightChild);
    deleteElement(node->rightChild, value);
    node->value = value;
}

void deleteElement(Node* &node, int value)
{
    if (node != nullptr)
    {
        if (node->value == value)
        {
           NodeType currentNode = determineType(node);

           switch (currentNode)
           {
                case noChildren:
                    removeNodeWithNoChildren(node); break;
                case onlyLeftChild:
                    removeNodeWithLeftChild(node); break;
                case onlyRightChild:
                    removeNodeWithRightChild(node); break;
                case twoChildren:
                    removeNodeWithTwoChildren(node); break;
           }
        }
        else
        {
            if (node->value > value)
                deleteElement(node->leftChild, value);
            else
                deleteElement(node->rightChild, value);
            node = balance(node);
        }
    }
}

void deleteElement(Tree *tree, int value)
{
    return deleteElement(tree->root, value);
}

void deleteNode(Node* &node)
{
    if (node != nullptr)
    {
        deleteNode(node->leftChild);
        deleteNode(node->rightChild);
        delete node;
        node = nullptr;
    }
}

void deleteTree(Tree *tree)
{
    deleteNode(tree->root);
}
