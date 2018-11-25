#include <cstddef>
#include "../../utils/exception.h"
#include "rb_tree.h"

Node::Node(int _key, unsigned _color, Node* _parent, Node* sentinel)
    : key(_key)
    , color(_color)
    , parent(_parent)
    , leftChild(sentinel)
    , rightChild(sentinel) {
}

void Node::deleteAllDescendents() {
    if (!leftChild->isSentinel()) {
        leftChild->deleteAllDescendents();
        delete leftChild;
    }
    if (!rightChild->isSentinel()) {
        rightChild->deleteAllDescendents();
        delete rightChild;
    }
}

Node::~Node() {}

bool Node::isSentinel() {
    return false;
}

static const int ANY_KEY = 0;

Sentinel::Sentinel() : Node(ANY_KEY, BLACK, nullptr, nullptr) {}

bool Sentinel::isSentinel() {
    return true;
}

RedBlackTree::RedBlackTree()
    : sentinel(new Sentinel()) {
    root = dynamic_cast<Node*>(sentinel);
}

RedBlackTree::~RedBlackTree() {
    if (!empty()) {
        root->deleteAllDescendents();
        delete root;
    }

    delete sentinel;
}

void RedBlackTree::insert(int newKey) {
    Node**  placeForNewNode;
    Node*   parentForNewNode;

    if (empty()) {
        placeForNewNode     = &root;
        parentForNewNode    = dynamic_cast<Node*>(sentinel);
    }
    else {
        parentForNewNode = findParentForKey(newKey);
        if (newKey < parentForNewNode->key) {
            placeForNewNode = &(parentForNewNode->leftChild);
        }
        else {
            placeForNewNode = &(parentForNewNode->rightChild);
        }
    }

    *placeForNewNode = new Node(newKey, RED, parentForNewNode,
                                dynamic_cast<Node*>(sentinel));
}

Node* RedBlackTree::findParentForKey(int newKey) const {
    Node* previousLevelNode = dynamic_cast<Node*>(sentinel);
    Node* thisLevelNode     = root;

    while (isNotEndOfTree(thisLevelNode)) {
        previousLevelNode = thisLevelNode;

        if (newKey < thisLevelNode->key) {
            thisLevelNode = thisLevelNode->leftChild;
        }
        else {
            thisLevelNode = thisLevelNode->rightChild;
        }
    }

    return previousLevelNode;
}

void RedBlackTree::traverse(key_handler* handler) const {
    std::stack<Node*> traverseStack;

    fillStackWithLeftBranchOf(root, traverseStack);

    while (!traverseStack.empty()) {
        Node* node = traverseStack.top();
        traverseStack.pop();
        handler(node);

        if (hasRightChild(node)) {
            traverseStack.push(node->rightChild);

            node = node->rightChild->leftChild;
            fillStackWithLeftBranchOf(node, traverseStack);
        }
    }
}

void RedBlackTree::fillStackWithLeftBranchOf(   Node* node,
                                                std::stack<Node*>& stack) const {
    while (isNotEndOfTree(node)) {
        stack.push(node);
        node = node->leftChild;
    }
}

bool RedBlackTree::hasRightChild(Node* node) const {
    return !node->rightChild->isSentinel();
}

bool RedBlackTree::hasLeftChild(Node* node) const {
    return !node->leftChild->isSentinel();
}

bool RedBlackTree::isNotEndOfTree(Node* node) const {
    return !node->isSentinel();
}

bool RedBlackTree::empty() const {
    return root->isSentinel();
}
