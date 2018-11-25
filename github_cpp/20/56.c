#ifndef REDBLACKTREEHELPERS_H
#define REDBLACKTREEHELPERS_H

#include "_redBlackTree.h"
#include <stdbool.h>

void RedBlackTree_RemoveRepair( RedBlackTree*, RedBlackTreeNode*, RedBlackTreeNode* );
void RedBlackTree_InsertRepair( RedBlackTree* redBlackTree, RedBlackTreeNode* redBlackTreeNode );
bool RedBlackTree_NodeRecolor( RedBlackTreeNode* redBlackTreeNode );
bool RedBlackTree_NodeShiftLeft ( RedBlackTree* redBlackTree, RedBlackTreeNode* grandParentNode );
bool RedBlackTree_NodeShiftRight( RedBlackTree* redBlackTree, RedBlackTreeNode* grandParentNode );

#endif