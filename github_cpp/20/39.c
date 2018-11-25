#ifndef _RedBlack_H
#define _RedBlack_H
 
typedef int ElementType;
#define NegInfinity ~0U
 
typedef enum ColorType {
    Red, Black
} ColorType;
 
typedef struct RedBlackNode *RedBlackTree;
 
struct RedBlackNode {
    ElementType Element;
    RedBlackTree Left;
    RedBlackTree Right;
    ColorType Color;
};


RedBlackTree MakeEmpty(RedBlackTree T);


RedBlackTree Initialize(void);


RedBlackTree Insert(ElementType X, RedBlackTree T);


int Contains(ElementType X, RedBlackTree T);
 

void Central_RBT_Header(RedBlackTree T, void (*visitor)(RedBlackTree));


int isNullNode(RedBlackTree T);
 
#endif
