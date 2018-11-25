#ifndef _RedBlack_H
#define _RedBlack_H

typedef enum ColorType { Red, Black } ColorType;

struct RedBlackNode;
typedef struct RedBlackNode *RedBlackTree;
typedef int ElementType;

RedBlackTree MakeEmpty( RedBlackTree T );
RedBlackTree Find( ElementType X, RedBlackTree T );
RedBlackTree FindMin( RedBlackTree T );
RedBlackTree FindMax( RedBlackTree T );
RedBlackTree Initialize( void );
RedBlackTree Insert( ElementType X, RedBlackTree T );
RedBlackTree Remove( ElementType X, RedBlackTree T );
ElementType Retrieve( RedBlackTree T );
void PrintTree( RedBlackTree T );
void PrintPreTree( RedBlackTree T );

#endif
