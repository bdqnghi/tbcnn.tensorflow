/*
 * =====================================================================================
 *
 *       Filename:  AVLTree.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年03月01日 20时03分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "AVLTree.h"
#include "../stack/stack.h"

int DefaultCompareFunc(void* data1,void* data2)
{
    if(data1 == data2)
        return 0;

    if(data1 < data2 )
        return -1;

    return 1;
}


AVLTree::AVLTree()
{
    m_nSize = 0;
	m_pRoot = 0;
	m_CompareFunc = DefaultCompareFunc;

}

AVLTree::AVLTree(AVLTreeDataCompareFunc compareFunc)
{
	m_nSize = 0;
	m_pRoot = 0;
	m_CompareFunc = compareFunc;
}

AVLTree::~AVLTree()
{
    Clear();
}

size_t AVLTree::Size()
{
	return m_nSize;
}

bool AVLTree::Empty()
{
	if(0 == m_nSize)
		return true;

	return false;
}

AVLTreeNode* AVLTree::Root()
{
    return m_pRoot;
}

void AVLTree::RotateLeft(PAVLTreeNode& node )
{
    AVLTreeNode* left = 0;
    AVLTreeNode* grandchild = 0;
    left = node->left;
    if(left->factor == left_heavy)
    {
        // LL旋转
        node->left = left->right;
        left->right = node;
        node->factor = balanced;
        left->factor = balanced;
        node = left;
    }
    else
    {
        // LR旋转
        grandchild = left->right;
        left->right = grandchild->left;
        grandchild->left = left;
        node->left = grandchild->right;
        grandchild->right = node;

        switch(grandchild->factor)
        {
        case left_heavy:
            node->factor = right_heavy;
            left->factor = balanced;
            break;
        case balanced:
            node->factor = balanced;
            left->factor = balanced;
            break;
        case right_heavy:
            node->factor = balanced;
            left->factor = left_heavy;
            break;
        }
        grandchild->factor = balanced;
        node = grandchild;
    }
}

void AVLTree::RotateRight(PAVLTreeNode& node)
{
    AVLTreeNode* right = 0;
    AVLTreeNode* grandchild = 0;

    right = node->right;

    if(right->factor == right_heavy)
    {
        // RR
        node->right = right->left;
        right->left = node;
        node->factor = balanced;
        right->factor = balanced;
        node = right;
    }
    else
    {
        // RL
        grandchild = right->left;
        right->left = grandchild->right;
        grandchild->right = right;
        node->right = grandchild->left;
        grandchild->left = node;

        switch(grandchild->factor)
        {
               case left_heavy:
                   node->factor = balanced;
                   right->factor = right_heavy;
                   break;
               case balanced:
                   node->factor = balanced;
                   right->factor = balanced;
                   break;
               case right_heavy:
                   node->factor = left_heavy;
                   right->factor = balanced;
                   break;
        }
            grandchild->factor = balanced;
            node = grandchild;
   }

}

AVLTreeNode* AVLTree::Insert(void* data)
{
    bool isbalanced = true;
    return InsertRecu(data,m_pRoot,isbalanced);
}

AVLTreeNode* AVLTree::InsertRecu(void *data, PAVLTreeNode &node,bool& isbalanced)
{
    AVLTreeNode* insertNode = 0;

    if(node == 0)
    {
        ++m_nSize;
        insertNode = new AVLTreeNode;
        insertNode->data = data;
        node = insertNode;
        return insertNode;
    }
    else
    {
        int ret = m_CompareFunc(data,node->data);

        if(ret < 0)
        {
            if(node->left == 0)
            {
                ++m_nSize;

                insertNode = new AVLTreeNode;

                insertNode->data = data;

                node->left = insertNode;

                isbalanced = false;
            }
            else
            {
                InsertRecu(data,node->left,isbalanced);
            }

            if(isbalanced == false)
            {
                switch(node->factor)
                {
                case left_heavy:
                    RotateLeft(node);
                    isbalanced = true;
                    break;
                case balanced:
                    node->factor = left_heavy;
                    break;
                case right_heavy:
                    node->factor = balanced;
                    isbalanced = true;
                    break;
                }
            }
        }
        else if(ret > 0)
        {
            if(node->right == 0)
            {
                ++m_nSize;

                insertNode = new AVLTreeNode;

                insertNode->data = data;

                node->right = insertNode;

                isbalanced = false;
            }
            else
            {
                InsertRecu(data,node->right,isbalanced);
            }

            if(isbalanced == false)
            {
                switch(node->factor)
                {
                case left_heavy:
                    node->factor = balanced;
                    isbalanced = true;
                    break;
                case balanced:
                    node->factor = right_heavy;
                    break;
                case right_heavy:
                    RotateRight(node);
                    isbalanced = true;
                    break;
                }
            }
        }
        else // ret == 0
        {
            if(node->hidden == false)
                return 0;

            ++m_nSize;

            node->data = data;
            node->hidden = false;
            isbalanced = true;
            insertNode = node;
        }
    }

    return insertNode;
}

void AVLTree::Remove(void *data)
{
    while (true)
    {
        AVLTreeNode* node = Find(data);

        if(0 == node)
            break;

        --m_nSize;
        node->hidden = true;
    }
}

AVLTreeNode* AVLTree::Find(void *data)
{
    return FindRecu(data,m_pRoot);
}

AVLTreeNode* AVLTree::FindRecu(void *data, AVLTreeNode *node)
{
    if(node == 0)
        return 0;

    int ret = m_CompareFunc(data,node->data);
    if(ret == 0)
    {
        if(node->hidden == true)
            return 0;

        return node;
    }
    else if(ret < 0)
        return FindRecu(data,node->left);
    else// ret > 0
        return FindRecu(data,node->right);

}

void AVLTree::MidOrderTraverseRecu(AVLTreeNode* node,AVLTreeNodeHandle handle,void* userData)
{
    if(node == 0 )
        return;
    MidOrderTraverseRecu(node->left,handle,userData);
    if(node->hidden  == false)
        handle(userData,node);
    MidOrderTraverseRecu(node->right,handle,userData);
}

void AVLTree::PreOrderTraverseRecu(AVLTreeNode* node,AVLTreeNodeHandle handle,void* userData)
{
    if(node == 0)
        return;

    if(node->hidden  == false)
        handle(userData,node);
    PreOrderTraverseRecu(node->left,handle,userData);
    PreOrderTraverseRecu(node->right,handle,userData);
}

void AVLTree::PostOrderTraverseRecu(AVLTreeNode* node,AVLTreeNodeHandle handle,void* userData)
{
    if(node == 0)
        return;
    PostOrderTraverseRecu(node->left,handle,userData);
    PostOrderTraverseRecu(node->right,handle,userData);
    if(node->hidden  == false)
        handle(userData,node);
}


void AVLTree::MidOrderTraverse(AVLTreeNodeHandle handle,void* userData,AVLTreeNode* node )
{
    if(node == 0)
        return MidOrderTraverseRecu(m_pRoot,handle,userData);
    else
        return MidOrderTraverseRecu(node,handle,userData);
}

void AVLTree::PreOrderTraverse(AVLTreeNodeHandle handle,void* userData,AVLTreeNode* node )
{
    if(node == 0)
        return PreOrderTraverseRecu(m_pRoot,handle,userData);
    else
        return PreOrderTraverseRecu(node,handle,userData);
}

void AVLTree::PostOrderTraverse(AVLTreeNodeHandle handle,void* userData,AVLTreeNode* node )
{
    if(node == 0)
        return PostOrderTraverseRecu(m_pRoot,handle,userData);
    else
        return PostOrderTraverseRecu(node,handle,userData);
}

void AVLTree::ClearRecu(AVLTreeNode *node)
{
    if(0 == node)
        return;
    ClearRecu(node->left);
    ClearRecu(node->right);
    delete node;
    node = 0;
}

void AVLTree::Clear()
{

    ClearRecu(m_pRoot);
    m_nSize = 0;
    m_pRoot = 0;
}

size_t AVLTree::DepthRecu(AVLTreeNode *node)
{
    if(node == 0)
        return 0;

    size_t left = DepthRecu(node->left);
    size_t right = DepthRecu(node->right);

    if(left > right)
        return 1 + left;
    else
        return 1 + right;
}

size_t AVLTree::Depth(AVLTreeNode *node)
{
    if(node == 0)
        return DepthRecu(m_pRoot);
    else
        return DepthRecu(node);
}

size_t AVLTree::LeafsRecu(AVLTreeNode *node)
{
    if(0 == node)
        return 0;

    if(node->left == 0 && node->right == 0)
        return 1;
    else
    {
        return LeafsRecu(node->left) + LeafsRecu(node->right);
    }
}

size_t AVLTree::Leafs(AVLTreeNode *node)
{
    if(0 == node)
        return LeafsRecu(m_pRoot);
    else
        return LeafsRecu(node);
}
