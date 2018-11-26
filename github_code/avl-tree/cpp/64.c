#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include <iostream>
#include <list>
#include <vector>
#include <functional>

using namespace std;
/**
 * An AVL Tree is a  self-balancing binary search tree.
 * This container class saves elements called nodes with integer values.
 * In the left part of the tree, the values are smaller than the root and in the right part they are bigger.
 */
class AVLTree {

private:
    /**
     * Nodes are the elements saved in the AVL Tree and
     * the purpose of one node is to save exactly one integer value.
     * Futher, every node knows his two sons called right and left node.
     * If a node is a leaf, the sons are nullpointer.
     */
    struct Node {
        /**
         * The key value this node contains.
         * By this value difines the position of the node in the tree.
         * The value is constant, so it can never be changed.
         */
        const int key;

        /**
         * This is a pointer on the previous node in the tree.
         */
        Node *previous = nullptr;

        /**
         * This is a pointer on the next element in the tree, that has a smaller value,
         * than the current Node.
         */
        Node *left = nullptr;

        /**
         * This is a pointer on the next element in the tree, that has a greater value,
         * than the current Node.
         */
        Node *right = nullptr;

        /**
         * This is a balace factor. Here just the following values are alloed:
         * -1: there is one more node in the left branch than in the right branch of the current node.
         * 0: there are as many nodes in the left branch as in the right branch. This node is perfectly balanced.
         * 1: there is one more node in the right branch than in the left branch of the current node.
         * If there is another value in any of the nodes in the tree, the tree has to be rearranged.
         */
        int balance = 0;

        /**
         * The tree, where the node belongs to.
         */
        AVLTree *tree = nullptr;

        /**
         * Creates a new node with this value in the tree.
         * @param k the key, the node contains.
         * @param t the tree, where the node is placed in.
         */
        Node(const int k, AVLTree *t);

        /**
         * Creates a new node with this value and this predefined position in the tree.
         * @param k the key, the node contains.
         * @param p the pointer on the previous node.
         * @param l the pointer on the next smaller node.
         * @param r the pointer on the next bigger node.
         * @param t the tree, where the node is placed in.
         */
        Node(const int k, Node *p, Node *l, Node *r, AVLTree *t);

        /**
         * Delets the node;
         */
        ~Node();

        /**
         * Ensures that the tree is still an AVL-Tree.
         * If the tree is not an AVL-Tree the necessary rotation will be executed.
         * @param growedLeft true if the left subtree of the noed growed, false if the right subtree of the node growed
         */
        void upin(bool growedLeft);

        /**
         * Ensures that the tree is still an AVL-Tree when a node is removed. If the tree is not an AVL-Tree the
         * necessary rotation will be executed.
         * @param leftShrinked ture if the left subree of the node shrinked
         */
        void upout(bool leftShrinked);

        /**
         * Rotates the (sub)tree to the right so that this node will get the root of the (sub)tree.
         * The rotation includes just nodes in the subtree of which the previous of this node is the root.
         */
        void rightRotation();

        /**
         * Rotates the (sub)tree first to the left and then to the right, so that the right follower of this node gets
         * the root of the (sub)tree. The rotation includes just nodes in the subtree of which the previous of this node
         * is the root.
         */
        void leftRightRotation();

        /**
         * Rotates the (sub)tree first to the right and then to the left, so that the left follower of this node gets
         * the root of the (sub)tree. The rotation includes just nodes in the subtree of which the previous of this node
         * is the root.
         */
        void rightLeftRotation();

        /**
         * Rotates the (sub)tree to the left so that this node will get the root of the (sub)tree.
         * The rotation includes just nodes in the subtree of which the previous of this node is the root.
         */
        void leftRotation();

        /**
         * Returns if the current node is the root of the tree or not.
         * @return true, if the node is the root of the tree.
         */
        bool isRoot();

        /**
         * Returns true if this node is the left follower of its previous element, else false.
         * @return true if this node is the left follower of its previous element, else false.
         */
        bool isLeftFollower();

        /**
         * Returns the hight of a tree, defined by the maximum number of connections between the root and a leaf.
         * @return hight of the tree.
         */
        int height();

        /**
         * The preorder goes from the root to the left branch of the tree (in preorder) to the right branch of the tree (in preorder).
         * @return a preordered vector.
         */
        vector<int> *preorder() const;  // (Hauptreihenfolge)

        /**
        * The inorder goes from the left branch of the tree (in preorder) to the root to the right branch of the tree (in preorder).
        * @return a inordered vector.
        */
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)

        /**
        * The postorder goes from the left branch of the tree (in preorder) to the right branch of the tree (in preorder) to the root.
        * @return a postordered vector.
        */
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    /**
     * This is the starting point of the tree, from where all other elements can be reached.
     */
    Node *root = nullptr;

public:
    /**
     * Delets the tree.
     */
    ~AVLTree();

    /**
     * Returns if tree contains a certain value.
     * @return true, if the tree contains a node with this value.
     */
    bool search(const int) const;

    /**
     * Adds a node with this value to the tree.
     * If the value already exists, nothing happens.
     * Ensures that it is still an AVL-Tree
     */
    void insert(const int);

    /**
     * Removes a node with this value to the tree.
     * If the value does not exists, nothing happens.
     */
    void remove(const int);

    /**
     * The preorder goes from the root to the left branch of the tree (in preorder) to the right branch of the tree (in preorder).
     * @return a preordered vector of integers with the values of the tree.
     */
    vector<int> *preorder() const;  // (Hauptreihenfolge)

    /**
    * The inorder goes from the left branch of the tree (in preorder) to the root to the right branch of the tree (in preorder).
    * @return a inordered vector of integers with the values of the tree.
    */
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)

    /**
    * The postorder goes from the left branch of the tree (in preorder) to the right branch of the tree (in preorder) to the root.
    * @return a postordered vector of integers with the values of the tree.
    */
    vector<int> *postorder() const; // (Nebenreihenfolge)


    friend ostream &operator<<(ostream &, const AVLTree &);
    friend class treeplotter;
    /**
     * Returns the balance factor of the node with this value.
     * @return balance factor of the node with this value, if the value exists od -1000 else.
     */
    int getBalance(const int);

    /**
     * Returns a pointer on the node with this value.
     * If the value does not exist, a nullpointer is returned.
     * @return pointer on the seached node, if the value exists or a nullpointer else.
     */
    Node* find(const int);

};

#endif //TREES_AVLTREE_H
