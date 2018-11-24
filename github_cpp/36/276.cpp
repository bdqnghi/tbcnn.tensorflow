#include<iostream>

using namespace std;

struct Node {
    int value;
    // value less than node
    Node *left;

    // value greater than node
    Node *right;

    Node(int value) {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};

class NodeWalker {
public:
    virtual void execute(Node *currentNode) = 0;
};

class PrintWalker : public NodeWalker {
public:
    void execute(Node *currentNode) {
        cout << currentNode->value << " ";
    }
};

class DestroyWalker : public NodeWalker {
public:
    void execute(Node *currentNode) {
        delete currentNode;
    }
};

class CountWalker : public NodeWalker {
private:
    int nodeCount = 0;
public:
    void execute(Node *currentNode) {
        nodeCount += 1;
    }

    int getCount() const {
        return nodeCount;
    }
};


class PredicateWalker : public CountWalker {
private:
    bool (*pred)(int);

public:
    PredicateWalker(bool (*pred)(int)) {
        this->pred = pred;
    }

    void execute(Node *currentNode) {
        if (pred(currentNode->value)) {
            CountWalker::execute(currentNode);
        }
    }
};

class CountEvenWalker : public PredicateWalker {

private:
    static bool isEven(int a) {
        return a % 2 == 0;
    }

public:
    CountEvenWalker() : PredicateWalker(isEven) {

    }
};

class LeavesCounter : public CountWalker {
public:
    void execute(Node *currentNode) {
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            CountWalker::execute(currentNode);
        }
    }
};

class EmptyWalker : public NodeWalker {
public:
    void execute(Node *currentNode) {

    }
};

class MaxLeafWalker : public NodeWalker {
private:
    int maxValue;
public:
    MaxLeafWalker(int initialValue) {
        maxValue = initialValue;
    }

    void execute(Node *currentNode) {
        maxValue = max(maxValue, currentNode->value);
    }

    int getMaxValue() const {
        return maxValue;
    }
};

class BTree {
private:
    Node *root;

    void addInternal(int value) {
        Node *subRoot = root;
        Node *parent = root;

        // true is for left , false is for right
        bool direction;

        while (subRoot != nullptr) {
            parent = subRoot;
            if (value < subRoot->value) {
                subRoot = subRoot->left;
                direction = true;
            } else {
                subRoot = subRoot->right;
                direction = false;
            }
        }

        subRoot = new Node(value);

        if (direction) {
            parent->left = subRoot;
        } else {
            parent->right = subRoot;
        }

    }

    int traverseInternal(Node *node, NodeWalker &walker, int height) {
        if (node == nullptr) return height;
        int maxHeight = 0;
        maxHeight = max(traverseInternal(node->left, walker, height + 1),
                        traverseInternal(node->right, walker, height + 1));
        walker.execute(node);
        return maxHeight;
    }

public:
    BTree() : root(nullptr) {

    }

    ~BTree() {
        DestroyWalker d;
        traverse(d);
    }

    void add(int value) {
        if (root == nullptr) {
            root = new Node(value);
        } else {
            addInternal(value);
        }

    }

    void print() {
        PrintWalker p;
        traverse(p);
    }

    int traverse(NodeWalker &walker) {
        return traverseInternal(root, walker, 0);
    }

    int count() {
        CountWalker c;
        traverse(c);
        return c.getCount();
    }

    int countEvens() {
        CountEvenWalker c;
        traverse(c);
        return c.getCount();
    }

    int searchCount(bool (*pred)(const int)) {
        PredicateWalker p(pred);
        traverse(p);
        return p.getCount();
    }

    int countLeaves() {
        LeavesCounter l;
        traverse(l);
        return l.getCount();
    }

    int height() {
        EmptyWalker e;
        return traverse(e);
    }

    int maxLeaf() {
        // if root is null I don't care :)
        MaxLeafWalker m(root->value);
        traverse(m);
        return m.getMaxValue();
    }


};

bool isOdd(const int a) {
    return a % 2;
}

int main() {

    BTree b = BTree();

    b.add(10);
    b.add(5);
    b.add(20);
    b.add(15);
    b.add(25);


    b.print();
    cout << endl;
    cout << "All node count: " << b.count() << endl;
    cout << "Even valued node count: " << b.countEvens() << endl;

    cout << "Odd valued node count: " << b.searchCount(isOdd) << endl;
    cout << "Leaves count is: " << b.countLeaves() << endl;

    cout << "Tree height is: " << b.height() << endl;

    cout << "The max value of a leaf is: " << b.maxLeaf() << endl;
}