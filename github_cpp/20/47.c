#include "RedBlackTree.h"









bool RedBlackTree::IsRed(RedBlackTreeNode* inNode)
{
    if (inNode && (inNode->color == RED))
        return true;
    return false;
}

RedBlackTreeNode* RedBlackTree::rightRotate(RedBlackTreeNode*& inNode)
{
    printf("RedBlackTree::rightRotate\n");
    RedBlackTreeNode* tmp = inNode->left;
    inNode->left = tmp->right;

    RedBlackTreeNode* tmp2 = inNode;

    tmp->right = inNode;
    tmp->color = inNode->color;
    inNode->color = RED;

    inNode = tmp;
    return tmp;
}
RedBlackTreeNode* RedBlackTree::leftRotate(RedBlackTreeNode*& inNode)
{
    printf("RedBlackTree::leftRotate\n");
    RedBlackTreeNode* tmp = inNode->right;
    inNode->right = tmp->left;
    tmp->left = inNode;
    tmp->color = inNode->color;
    inNode->color = RED;

    inNode = tmp;
    return tmp;
}
void RedBlackTree::flipColors(RedBlackTreeNode* inNode)
{
    printf("RedBlackTree::flipColors\n");
    if (IsRed(inNode->left) && IsRed(inNode->right))
    {
        inNode->color = RED;
        inNode->left->color = BLACK;
        inNode->right->color = BLACK;
    }
}

void RedBlackTree::insert(RedBlackTreeNode*& root, RedBlackTreeNode* node)
{
    if (!root){
        root = node;
        return;
    }

    if (root->getkey() == node->getkey())
        root->setVal(node->getVal());

    if (root->getkey() > node->getkey())
    {
        if (root->left)
            return insert(root->left, node);
        else
            root->left = node;
    }
    else {
        if (root->right)
            return insert(root->right, node);
        else
            root->right = node;
    }

    if (IsRed(root->right) && !IsRed(root->left))
        root = leftRotate(root);
    if (IsRed(root->left) && IsRed(root->left->left))
        root = rightRotate(root);
    if (IsRed(root->right) && IsRed(root->left))
        flipColors(root);
}

RedBlackTreeNode* RedBlackTree::find(RedBlackTreeNode* root, int key)
{
    if (root == NULL)
        return NULL;
    if (root->getkey() == key)
        return root;
    if (root->getkey() > key)
        return find(root->left, key);
    else
        return find(root->right, key);
}

int RedBlackTree::maxDepth(RedBlackTreeNode* node){
    if (node == NULL)
        return 0;
    else
    {
        
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);
        
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}
void RedBlackTree::printGivenLevel(RedBlackTreeNode* root, int level){
    if (root == NULL)
        return;
    if (level == 1)
        printf("(%d:%d)", root->getkey(), root->getVal());
    else if (level > 1)
    {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}
void RedBlackTree::printLevelOrder(RedBlackTreeNode* root){
    int h = maxDepth(root);
    int i;
    for (i = 1; i <= h; i++)
    {
        printf("Level %d", i);
        printGivenLevel(root, i);
        printf("\n");
    }
}


void RedBlackTreeTest()
{
    RedBlackTree rbt;
    RedBlackTreeNode* root = rbt.getTreeRoot();
    for (int i = 0; i < 100; i++)
    {
        int iKey = rand() % 100;
        int iVal = rand() % 100;
        RedBlackTreeNode* node = new RedBlackTreeNode(iKey, iVal);

        printf("inserting (%d:%d) \n", iKey, iVal);
        rbt.insert(root, node);
    }
    rbt.printLevelOrder(root);
}
