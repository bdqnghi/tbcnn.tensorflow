//#include "AVLTree.h"

//#ifndef __AVLTREE_H__
//#define __AVLTREE_H__

//#include <stdlib.h>

//#define MAX(a,b) ((a) > (b) ? (a) : (b))

///**//*
//*********************************************************************
//*                CONFIG
//*********************************************************************
//*/

//#define MAX_ELEMT 500000

///**//*
//*********************************************************************
//*             Structure Of AVLTree Declared
//*********************************************************************
//*/


//template <class T>
//AVLTree<T>::AVLTree()
//{
//    int i;
//    pPool = (BSTNode *)calloc(MAX_ELEMT, sizeof(BSTNode));
//    for(i = 0; i < MAX_ELEMT - 1; i++)
//        pPool[i].pLeft = pPool + i + 1;
//    pPool[MAX_ELEMT - 1].pLeft = 0;
//    pHead = 0;
//    pFree = pPool;
//}

//template <class T>
//AVLTree<T>::~AVLTree()
//{
//    free(pPool);
//    pPool = pFree = pHead = 0;
//}

//template <class T>
//AVLTree<T>::BSTNode* AVLTree<T>::CreateBSTNode()
//{
//    BSTNode *pTemp = pFree;
//    pFree = pFree->pLeft;
//    return pTemp;
//}

//template <class T>
//void AVLTree<T>::DelBSTNode(BSTNode* pNode)
//{
//    pNode->pLeft = pFree;
//    pFree->pLeft = pNode;
//    pNode = 0;
//}

//template <class T>
//char AVLTree<T>::Height(BSTNode *pNode)
//{
//    if(pNode == 0)
//        return 0;
//    return pNode->nHeight;
//}

//template <class T>
//AVLTree<T>::BSTNode* AVLTree<T>::SingleRotateWithLeft(BSTNode *pNode)
//{
//    BSTNode* pTemp;
//    pTemp = pNode->pLeft;
//    pNode->pLeft = pTemp->pRight;
//    pTemp->pRight = pNode;
//    pNode->nHeight = MAX(Height(pNode->pLeft), Height(pNode->pRight)) + 1;
//    pTemp->nHeight = MAX(Height(pNode->pLeft), Height(pNode->pRight)) + 1;
//    return pTemp;
//}

//template <class T>
//AVLTree<T>::BSTNode* AVLTree<T>::SingleRotateWithRight(BSTNode* pNode)
//{
//    BSTNode* pTemp;
//    pTemp = pNode->pRight;
//    pNode->pRight = pTemp->pLeft;
//    pTemp->pLeft = pNode;
//    pNode->nHeight = MAX(Height(pNode->pLeft), Height(pNode->pRight)) + 1;
//    pTemp->nHeight = MAX(Height(pNode->pLeft), Height(pNode->pRight)) + 1;
//    return pTemp;
//}

//template <class T>
//AVLTree<T>::BSTNode* AVLTree<T>::DoubleRotateWithLeft(BSTNode *pNode)
//{
//    pNode->pLeft = SingleRotateWithRight(pNode->pLeft);
//    return SingleRotateWithLeft(pNode);
//}

//template <class T>
//AVLTree<T>::BSTNode* AVLTree<T>::DoubleRotateWithRight(BSTNode *pNode)
//{
//    pNode->pRight = SingleRotateWithLeft(pNode->pRight);
//    return SingleRotateWithRight(pNode);
//}

//template <class T>
//AVLTree<T>::BSTNode* AVLTree<T>::AVLInsert(T nDat, BSTNode *&pNode)
//{
//    if(pNode == 0)
//    {
//        pNode = CreateBSTNode();
//        pNode->dat = nDat;
//        pNode->nHeight = 1;
//        pNode->pLeft = pNode->pRight = 0;
//        return pNode;
//    }
//    if(nDat < pNode->dat)
//    {
//        pNode->pLeft = AVLInsert(nDat, pNode->pLeft);
//        if(Height(pNode->pLeft) - Height(pNode->pRight) == 2)
//        {
//            if(nDat < pNode->pLeft->dat)
//                pNode = SingleRotateWithLeft(pNode);
//            else if(nDat > pNode->pLeft->dat)
//                pNode = DoubleRotateWithLeft(pNode);
//        }
//    }
//    else if(nDat > pNode->dat)
//    {
//        pNode->pRight = AVLInsert(nDat, pNode->pRight);
//        if(Height(pNode->pRight) - Height(pNode->pLeft) == 2)
//        {
//            if(nDat > pNode->pRight->dat)
//                pNode = SingleRotateWithRight(pNode);
//            else if(nDat < pNode->pRight->dat)
//                pNode = DoubleRotateWithRight(pNode);
//        }
//    }
//    pNode->nHeight = MAX(Height(pNode->pLeft), Height(pNode->pRight)) + 1;
//    return pNode;
//}

//template <class T>
//void AVLTree<T>::Process(BSTNode *p, BSTNode *&tmp)
//{
//    if(tmp->pRight == NULL)
//    {
//        p->dat = tmp->dat;
//        p = tmp;
//        tmp = tmp->pLeft;
//        DelBSTNode(p);
//    }
//    else
//    {
//        Process(p, tmp->pRight);
//        if(Height(tmp->pLeft) - Height(tmp->pRight) == 2)
//        {
//            if(Height(tmp->pLeft->pLeft) < Height(tmp->pLeft->pRight))
//                DoubleRotateWithLeft(tmp);
//            else
//                SingleRotateWithLeft(tmp);
//        }
//    }
//    p->nHeight = MAX(Height(p->pLeft), Height(p->pRight)) + 1;
//}

//template <class T>
//int AVLTree<T>::AVLDelete(BSTNode *&p, T x)
//{
//    int res;
//    BSTNode *q;
//    if(p == NULL)
//    {
//        return 0;
//    }
//    else if(x < p->dat)
//    {
//        res = AVLDelete(p->pLeft, x);
//        if(Height(p->pRight) - Height(p->pLeft) == 2)
//        {
//            if(Height(p->pRight->pRight) < Height(p->pRight->pLeft))
//                DoubleRotateWithRight(p);
//            else
//                SingleRotateWithRight(p);
//            p->nHeight = MAX(Height(p->pLeft), Height(p->pRight)) + 1;
//        }
//        return res;
//    }
//    else if(x > p->dat)
//    {
//        res = AVLDelete(p->pRight, x);
//        if(Height(p->pLeft) - Height(p->pRight) == 2)
//        {
//            if(Height(p->pLeft->pLeft) < Height(p->pLeft->pRight))
//                DoubleRotateWithLeft(p);
//            else
//                SingleRotateWithLeft(p);
//            p->nHeight = MAX(Height(p->pLeft), Height(p->pRight)) + 1;
//        }
//        return res;
//    }
//    else
//    {
//        q = p;
//        if(p->pLeft == NULL)
//        {
//            p = p->pRight;
//            DelBSTNode(q);
//        }
//        else if(p->pRight == NULL)
//        {
//            p = p->pLeft;
//            DelBSTNode(q);
//        }
//        else
//        {
//            Process(q, q->pLeft);
//            if(Height(p->pRight) - Height(p->pLeft) == 2)
//            {
//                if(Height(p->pRight->pRight) < Height(p->pRight->pLeft))
//                    p = DoubleRotateWithRight(p);
//                else
//                    p = SingleRotateWithRight(p);
//            }
//            p = q;
//        }
//    }
//    p->nHeight = MAX(Height(p->pLeft), Height(p->pRight)) + 1;
//    return 1;
//}

//template <class T>
//void AVLTree<T>::insert(T nDat)
//{
//    pHead = AVLInsert(nDat, pHead);
//}

//template <class T>
//T* AVLTree<T>::find(T nDat)
//{
//    struct BSTNode *pTemp = pHead;
//    while(pTemp != 0)
//    {
//        if(nDat < pTemp->dat)
//            pTemp = pTemp->pLeft;
//        else if(nDat > pTemp->dat)
//            pTemp = pTemp->pRight;
//        else
//            return &pTemp->dat;
//    }
//    return 0;
//}

//template <class T>
//int AVLTree<T>::remove(T x)
//{
//    return AVLDelete(pHead, x);
//}
